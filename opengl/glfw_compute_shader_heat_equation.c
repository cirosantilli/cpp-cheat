/*
Heat equation. TODO CPU only for now.

Usage:

    ./prog [width [window_width [work_group_width [cpu [conduction_coeff [select_boundary]]]]]

Example:

    ./prog 512 512 16 1 0.5 2

- width: window width
- work_group_width. Must divide width.
- cpu: if '1', use CPU, else GPU. If set, work_group_width is ignored.

It is hard to view function values with colors like this, because the range is too limited.

A solution would be to us a 3D plot, but that might require moving the camera around to see certain spots...
*/

#include "common.h"

static const GLuint WIDTH = 512;
static const GLuint WORK_GROUP_WIDTH = 16;
static const GLfloat vertices_xy_uv[] = {
    -1.0,  1.0, 0.0, 1.0,
     1.0,  1.0, 0.0, 0.0,
     1.0, -1.0, 1.0, 0.0,
    -1.0, -1.0, 1.0, 1.0,
};
static const GLuint indices[] = {
    0, 1, 2,
    0, 2, 3,
};
static const float conduction_coeff = 0.5;

static const GLchar *vertex_shader_source =
    "#version 330 core\n"
    "in vec2 coord2d;\n"
    "in vec2 vertexUv;\n"
    "out vec2 fragmentUv;\n"
    "void main() {\n"
    "    gl_Position = vec4(coord2d, 0, 1);\n"
    "    fragmentUv = vertexUv;\n"
    "}\n";
static const GLchar *fragment_shader_source =
    "#version 330 core\n"
    "in vec2 fragmentUv;\n"
    "out vec3 color;\n"
    "uniform sampler2D textureSampler;\n"
    "void main() {\n"
    "    float r = texture(textureSampler, fragmentUv.yx).r;\n"
    "    color = vec3(r, r, r);\n"
    "}\n";
static const char compute_shader_source_template[] =
    "#version 430\n"
    "layout (local_size_x = %d, local_size_y = %d) in;\n"
    "layout (r32f, binding = 0) uniform image2D img_output;\n"
    "layout (std430, binding=0) buffer temperatures {\n"
    "    float temperature[];\n"
    "};\n"
    "uniform uint width;\n"
    "void main() {\n"
    "    ivec2 gid = ivec2(gl_GlobalInvocationID.xy);\n"
    "    ivec2 dims = imageSize(img_output);\n"
    /* TODO: there must be a better way to do this with some GLSL magic? */
    "    uint i = gid.y * width + gid.x;\n"
    "    float t = temperature[i];\n"
    "    vec4 pixel = vec4(t, 0.0, 0.0, 1.0);\n"
    "    imageStore(img_output, gid, pixel);\n"
    /* TODO: does the above pass just a single float, or can we reduce memory bandwidth with something like: */
    /*"    imageStore(img_output, pixel_coords, t);\n"*/
    "    temperature[i] = mod(t + 0.01, 1.0);\n"
    "}\n";

void error_callback(int error, const char* description) {
    puts(description);
}

void init_boundary(GLfloat *temperatures, size_t width, size_t height, int which) {
    const float PI2 = 2.0 * acos(-1.0);
    const unsigned int sin_periods = 2;
    switch (which) {
        case 1:
            /* Linear decrease.
            *
            *     1.0 | 0.5
            *     ---------
            *     0.5 | 0.0
            * */
            for (size_t i = 0; i < height; ++i) {
                temperatures[i * width + 0        ] = 0.5 + (0.5 * (i / (float)height));
                temperatures[i * width + width - 1] = 0.5 * (i / (float)height);
            }
            for (size_t j = 1; j < width - 1; ++j) {
                temperatures[                       j] = 0.5 * (1.0 - (j / (float)width));
                temperatures[(height - 1) * width + j] = 0.99 - (0.5 * (j / (float)width));
            }
        break;

        case 2:
            /* sin:
             *
             *     0.5 | 0.5
             *     ---------
             *     0.5 | 0.5
             *
             * Does N periods in the middle.
             * */
            for (size_t i = 0; i < height; ++i) {
                float f = 0.5 * (0.99 + sin(sin_periods * PI2 * (i / (float)height)));
                temperatures[i * width + 0        ] = f;
                temperatures[i * width + width - 1] = f;
            }
            for (size_t j = 1; j < width - 1; ++j) {
                float f = 0.5 * (0.99 + sin(sin_periods * PI2 * (j / (float)width)));
                temperatures[                       j] = f;
                temperatures[(height - 1) * width + j] = f;
            }
        break;

        case 0:
        default:
            /* Const at 1.0.
            *
            *     1.0 | 0.5
            *     ---------
            *     1.0 | 0.5
            *
            * */
            for (size_t i = 0; i < height; ++i) {
                temperatures[i * width + 0        ] = 0.99;
                temperatures[i * width + width - 1] = 0.99;
            }
            for (size_t j = 1; j < width - 1; ++j) {
                temperatures[                       j] = 0.99;
                temperatures[(height - 1) * width + j] = 0.99;
            }
        break;
    }
}

int main(int argc, char **argv) {
    GLFWwindow *window;
    GLfloat
        *temperatures = NULL,
        *temperatures2 = NULL,
        *temperature_buf = NULL
    ;
    GLint
        coord2d_location,
        textureSampler_location,
        vertexUv_location,
        width_location
    ;
    GLuint
        compute_program,
        ebo,
        height,
        window_height,
        program,
        ssbo,
        texture,
        width,
        window_width,
        work_group_width,
        vao,
        vbo
    ;
    int cpu, which_boundary;
    float conduction_coeff;
    size_t n_temperatures;
    char *compute_shader_source, *work_group_width_str;

    /* CLI arguments. */
    if (argc > 1) {
        width = strtol(argv[1], NULL, 10);
    } else {
        width = WIDTH;
    }
    height = width;
    if (argc > 2) {
        window_width = strtol(argv[2], NULL, 10);
    } else {
        window_width = WIDTH;
    }
    window_height = window_width;
    if (argc > 3) {
        work_group_width = strtol(argv[3], NULL, 10);
    } else {
        work_group_width = WORK_GROUP_WIDTH;
    }
    if (argc > 4) {
        cpu = (argv[4][0] == '1');
    } else {
        cpu = 0;
    }
    /* Must be between 0.0 and 1.0.
     *
     * Physics allows it to be in 0 / infinity.
     *
     * Anything greater than 1.0 leads to numeric instabilities
     * for our simplistic method, as equilibrium is reached in less
     * time than one time step, and goes over.
     *
     * Negative values make temperatures unbounded and breaks energy conservation.
     *
     * But you obviously will try out "bad" values in the simulation to see what happens.
     * The behaviour of this value around 1.99, 2.0, 2.01, 3.0 is specially interesting.
     * */
    if (argc > 5) {
        conduction_coeff = strtod(argv[5], NULL);
    } else {
        conduction_coeff = conduction_coeff;
    }
    if (argc > 6) {
        which_boundary = strtol(argv[6], NULL, 10);
    } else {
        which_boundary = 0;
    }

    /* Window. */
    glfwInit();
    glfwSetErrorCallback(error_callback);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow(window_width, window_height, __FILE__, NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glewInit();

    /* Shader. */
    program = common_get_shader_program(vertex_shader_source, fragment_shader_source);
    coord2d_location = glGetAttribLocation(program, "coord2d");
    vertexUv_location = glGetAttribLocation(program, "vertexUv");
	textureSampler_location = glGetUniformLocation(program, "textureSampler");

    if (!cpu) {
        /* Compute shader. */
        int work_group_width_len = snprintf(NULL, 0, "%d", work_group_width);
        size_t compute_shader_source_len = sizeof(compute_shader_source_template) + 2 * work_group_width_len;
        compute_shader_source = malloc(compute_shader_source_len);
        snprintf(
            compute_shader_source,
            compute_shader_source_len,
            compute_shader_source_template,
            work_group_width,
            work_group_width
        );
        compute_program = common_get_compute_program(compute_shader_source);
        free(compute_shader_source);
        width_location = glGetUniformLocation(compute_program, "width");
    }

    /* vbo */
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_xy_uv), vertices_xy_uv, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* ebo */
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    /* vao */
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(coord2d_location, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(vertices_xy_uv[0]), (GLvoid*)0);
    glEnableVertexAttribArray(coord2d_location);
    glVertexAttribPointer(vertexUv_location, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(vertices_xy_uv[0]), (GLvoid*)(2 * sizeof(vertices_xy_uv[0])));
    glEnableVertexAttribArray(vertexUv_location);
    glBindVertexArray(0);

    /* ssbo */
    srand(time(NULL));
    n_temperatures = width * height;
    temperatures = malloc(n_temperatures * sizeof(temperatures[0]));
    /* Initial condition. TODO: make continuous with boundary conditions. */
    for (size_t i = 1; i < height - 1; ++i) {
        for (size_t j = 1; j < width - 1; ++j) {
            temperatures[i * width + j] = 0.0;
        }
    }
    init_boundary(temperatures, width, height, which_boundary);
    if (cpu) {
        temperatures2 = malloc(n_temperatures * sizeof(temperatures[0]));
        /* Boundary must also be initialized for this buffer,
         * since the boundary is never touched after the beginning. */
        init_boundary(temperatures2, width, height, which_boundary);
    } else {
        glGenBuffers(1, &ssbo);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
        glBufferData(GL_SHADER_STORAGE_BUFFER, n_temperatures * sizeof(temperatures[0]), temperatures, GL_DYNAMIC_COPY);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
        free(temperatures);
    }

    /* Texture. */
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    if (!cpu) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, width, height, 0, GL_RED, GL_FLOAT, NULL);
        /* Bind to image unit so can write to specific pixels from the compute shader. */
        glBindImageTexture(0, texture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_R32F);
    }

    /* Constant state. */
    glViewport(0, 0, window_width, window_height);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    /* Main loop. */
    common_fps_init();
    while (!glfwWindowShouldClose(window)) {
        if (cpu) {
            for (unsigned int i = 1; i < height - 1; ++i) {
                for (unsigned int j = 1; j < width - 1; ++j) {
                    /* TODO: find the name of this naive integration.
                     *
                     * TODO how imprecise it it?
                     *
                     * One limitation of this method is that temperature changes can
                     * only move one square at a time.
                     *
                     * In the real word, a temperature change on one side of the room
                     * immediately affects the other side (very little).
                     *
                     * And a denser grid implies slower propagation which makes no sense.
                     *
                     * The decent method will likely require matrix multiplications?
                     * */
                    size_t idx = i * width + j;
                    temperatures2[idx] =
                        (1.0 - conduction_coeff) * temperatures2[idx] +
                        conduction_coeff * (
                            temperatures[idx - 1] +
                            temperatures[idx + 1] +
                            temperatures[idx - width] +
                            temperatures[idx + width]
                        ) / 4.0;
                }
            }
            glTexImage2D(
                GL_TEXTURE_2D, 0, GL_RED, width, height,
                0, GL_RED, GL_FLOAT, temperatures2
            );
            /* Swap old and new. */
            temperature_buf = temperatures;
            temperatures = temperatures2;
            temperatures2 = temperature_buf;
        } else {
            /* Compute. */
            glUseProgram(compute_program);
            glUniform1ui(width_location, width);
            glDispatchCompute((GLuint)width / work_group_width, (GLuint)height / work_group_width, 1);
            glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
        }

        /* Draw. */
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(program);
        glUniform1i(textureSampler_location, 0);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glfwSwapBuffers(window);

        glfwPollEvents();
        common_fps_print();
    }

    /* Cleanup. */
    glDeleteBuffers(1, &ebo);
    if (cpu) {
        free(temperatures);
    } else {
        glDeleteBuffers(1, &ssbo);
    }
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
	glDeleteTextures(1, &texture);
    glDeleteProgram(program);
    glDeleteProgram(compute_program);
    glfwTerminate();
    return EXIT_SUCCESS;
}
