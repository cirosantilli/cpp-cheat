/*
Demo: https://www.youtube.com/watch?v=MRhAljmHq-o

Capture webcam video, show it on screen, and next to it show
a version modified by a fragment shader.

Computer vision on the GPU.

Usage:

    ./prog [width [height [cpu]]

-   width and height: size of captured image.
    Only certain sizes can be returned by the camera.

    If what you put is not one of them, the largest possible one is taken,
    and a warning is printed saying what was actually used, and a segfault may happen.

    You can then just use the actual numbers reported and it should work. TODO don't segfault.

    `v4l2-ctl --all` shows the largest supported size. TODO how to get all supported sub-sizes.

-   cpu: if `1`, use a CPU of the image transform, to see if are actually gaining anything with the GPU.

    Using -O3 can make a HUGE difference, so always use it.

    TODO: does O3 use SIMD operations? If not, we should use some
    portable library for it to be faire and use the full CPU power.

Examples:

    ./prog
    ./prog 960 540 1

Fragment shaders can access any byte of a texture, and so do operations over multiple pixels.

Several web examples:
https://www.chromeexperiments.com/webgl,webcam-input?page=0

Questions:

-   http://stackoverflow.com/questions/13693946/image-processing-with-glsl-shaders

Demos:

-   https://www.youtube.com/watch?v=fJtOdJ9MHsA GLSL Linux camera real time edge detection shown on screen.
    Getting started: <https://github.com/premsasidharan/gpu_img_proc/issues/1#issuecomment-257504913>
-   WebRTC chess with camera: https://www.youtube.com/watch?v=aK1DC2zp6ZE

Android:

-   http://stackoverflow.com/questions/7847912/is-it-possible-to-give-effect-like-vertex-shader-and-fragment-shader-to-the-andr
-   http://stackoverflow.com/questions/30723055/how-to-obtain-the-rgb-colors-of-the-camera-texture-in-opengl-es-2-0-for-android
-   http://stackoverflow.com/questions/18449162/simultaneous-camera-preview-and-processing
-   http://stackoverflow.com/questions/12519235/modifying-camera-output-using-surfacetexture-and-opengl

Post processing is equivalent to image processing (unless there is some
magic Krhonos way to bypass the CPU camera image copy to texture):

-   https://en.wikibooks.org/wiki/OpenGL_Programming/Post-Processing
-   r3dux tori demo https://www.youtube.com/watch?v=9nDxIbj3mPU

## Benchmark results

Lenovo Thinkpad T430, NVIDIA NVS 5400, Linux:

- linear blur: max width without frame drop:

    - CPU: 5
    - GPU: 23

    Consider that this parameter has a squared effect, and feel the wrath of the GPU here.

    AKA box blur: https://en.wikipedia.org/wiki/Box_blur

    Good GPU bogger since n^2.

*/

#include "common.h"
#include "../v4l2/common_v4l2.h"

static const GLuint WIDTH = 640;
static const GLuint HEIGHT = 480;
static const GLfloat vertices[] = {
/*  xy            uv */
    -1.0,  1.0,   0.0, 1.0,
     0.0,  1.0,   0.0, 0.0,
     0.0, -1.0,   1.0, 0.0,
    -1.0, -1.0,   1.0, 1.0,
};
static const GLuint indices[] = {
    0, 1, 2,
    0, 2, 3,
};

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
    "    color = texture(textureSampler, fragmentUv.yx).rgb;\n"
    "}\n";

static const GLchar *vertex_shader_source2 =
    "#version 330 core\n"
    "in vec2 coord2d;\n"
    "in vec2 vertexUv;\n"
    "out vec2 fragmentUv;\n"
    "void main() {\n"
    "    gl_Position = vec4(coord2d + vec2(1.0, 0.0), 0, 1);\n"
    "    fragmentUv = vertexUv;\n"
    "}\n";
static const GLchar *fragment_shader_source2 =
    "#version 330 core\n"
    "in vec2 fragmentUv;\n"
    "out vec3 color;\n"
    "uniform sampler2D textureSampler;\n"
    "/* pixel Delta. How large a pixel is in 0.0 to 1.0 that textures use. */\n"
    "uniform vec2 pixD;\n"
    "void main() {\n"

    /*"// Identity\n"*/
    /*"    color = texture(textureSampler, fragmentUv.yx ).rgb;\n"*/

    /*"// Inverter\n"*/
    /*"    color = 1.0 - texture(textureSampler, fragmentUv.yx ).rgb;\n"*/

    /*"// Swapper\n"*/
    /*"    color = texture(textureSampler, fragmentUv.yx ).gbr;\n"*/

    /*"// Double vision ortho.\n"*/
    /*"    color = ("*/
    /*"        texture(textureSampler, fragmentUv.yx ).rgb +\n"*/
    /*"        texture(textureSampler, fragmentUv.xy ).rgb\n"*/
    /*"    ) / 2.0;\n"*/

    /*"// Multi-me.\n"*/
    /*"    color = texture(textureSampler, 4.0 * fragmentUv.yx ).rgb;\n"*/

    /*"// Horizontal linear blur.\n"*/
    /*"    int blur_width = 21;\n"*/
    /*"    int blur_width_half = blur_width / 2;\n"*/
    /*"    color = vec3(0.0, 0.0, 0.0);\n"*/
    /*"    for (int i = -blur_width_half; i <= blur_width_half; ++i) {\n"*/
    /*"       color += texture(textureSampler, vec2(fragmentUv.y + i * pixD.x, fragmentUv.x)).rgb;\n"*/
    /*"    }\n"*/
    /*"    color /= blur_width;\n"*/

    /*"// Square linear blur.\n"*/
    "    int blur_width = 23;\n"
    "    int blur_width_half = blur_width / 2;\n"
    "    color = vec3(0.0, 0.0, 0.0);\n"
    "    for (int i = -blur_width_half; i <= blur_width_half; ++i) {\n"
    "       for (int j = -blur_width_half; j <= blur_width_half; ++j) {\n"
    "           color += texture(\n"
    "               textureSampler, fragmentUv.yx + ivec2(i, j) * pixD\n"
    "           ).rgb;\n"
    "       }\n"
    "    }\n"
    "    color /= (blur_width * blur_width);\n"

    "}\n";

int main(int argc, char **argv) {
    CommonV4l2 common_v4l2;
    GLFWwindow *window;
    GLint
        coord2d_location,
        textureSampler_location,
        vertexUv_location,
        coord2d_location2,
        pixD_location2,
        textureSampler_location2,
        vertexUv_location2
    ;
    GLuint
        ebo,
        program,
        program2,
        texture,
        vbo,
        vao,
        vao2
    ;
    unsigned int
        cpu,
        width,
        height
    ;
    uint8_t *image;
    float *image2 = NULL;

    /* CLI arguments. */
    if (argc > 1) {
        width = strtol(argv[1], NULL, 10);
    } else {
        width = WIDTH;
    }
    if (argc > 2) {
        height = strtol(argv[2], NULL, 10);
    } else {
        height = HEIGHT;
    }
    if (argc > 3) {
        cpu = (argv[3][0] == '1');
    } else {
        cpu = 0;
    }

    /* Window system. */
    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow(2 * width, height, __FILE__, NULL, NULL);
    glfwMakeContextCurrent(window);
    glewInit();
    CommonV4l2_init(&common_v4l2, COMMON_V4L2_DEVICE, width, height);

    /* Shader setup. */
    program = common_get_shader_program(vertex_shader_source, fragment_shader_source);
    coord2d_location = glGetAttribLocation(program, "coord2d");
    vertexUv_location = glGetAttribLocation(program, "vertexUv");
	textureSampler_location = glGetUniformLocation(program, "textureSampler");

    /* Shader setup 2. */
    const GLchar *fs;
    if (cpu) {
        fs = fragment_shader_source;
    } else {
        fs = fragment_shader_source2;
    }
    program2 = common_get_shader_program(vertex_shader_source2, fs);
    coord2d_location2 = glGetAttribLocation(program2, "coord2d");
    vertexUv_location2 = glGetAttribLocation(program2, "vertexUv");
	textureSampler_location2 = glGetUniformLocation(program2, "textureSampler");
	pixD_location2 = glGetUniformLocation(program2, "pixD");

    /* Create vbo. */
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* Create ebo. */
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    /* vao. */
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(coord2d_location, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(vertices[0]), (GLvoid*)0);
    glEnableVertexAttribArray(coord2d_location);
    glVertexAttribPointer(vertexUv_location, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(vertices[0])));
    glEnableVertexAttribArray(vertexUv_location);
    glBindVertexArray(0);

    /* vao2. */
    glGenVertexArrays(1, &vao2);
    glBindVertexArray(vao2);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(coord2d_location2, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(vertices[0]), (GLvoid*)0);
    glEnableVertexAttribArray(coord2d_location2);
    glVertexAttribPointer(vertexUv_location2, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(vertices[0])));
    glEnableVertexAttribArray(vertexUv_location2);
    glBindVertexArray(0);

    /* Texture buffer. */
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    /* Constant state. */
    glViewport(0, 0, 2 * width, height);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glActiveTexture(GL_TEXTURE0);

    /* Main loop. */
    common_fps_init();
    do {
        /* Blocks until an image is available, thus capping FPS to that.
         * 30FPS is common in cheap webcams. */
        CommonV4l2_updateImage(&common_v4l2);
        image = CommonV4l2_getImage(&common_v4l2);
        glClear(GL_COLOR_BUFFER_BIT);

        /* Original. */
        glTexImage2D(
            GL_TEXTURE_2D, 0, GL_RGB, width, height,
            0, GL_RGB, GL_UNSIGNED_BYTE, image
        );
        glUseProgram(program);
        glUniform1i(textureSampler_location, 0);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        if (cpu) {
            image2 = realloc(image2, 3 * width * height * sizeof(image2[0]));
            for (unsigned int i = 0; i < height; ++i) {
                for (unsigned int j = 0; j < width; ++j) {
                    size_t index = 3 * (i * width + j);

                    /* Inverter. */
                    /*image2[index + 0] = 1.0 - (image[index + 0] / 255.0);*/
                    /*image2[index + 1] = 1.0 - (image[index + 1] / 255.0);*/
                    /*image2[index + 2] = 1.0 - (image[index + 2] / 255.0);*/

                    /* Swapper. */
                    /*image2[index + 0] = image[index + 1] / 255.0;*/
                    /*image2[index + 1] = image[index + 2] / 255.0;*/
                    /*image2[index + 2] = image[index + 0] / 255.0;*/

                    /* Square linear blur. */
                    int blur_width = 5;
                    int blur_width_half = blur_width / 2;
                    int blur_width2 = (blur_width * blur_width);
                    image2[index + 0] = 0.0;
                    image2[index + 1] = 0.0;
                    image2[index + 2] = 0.0;
                    for (int k = -blur_width_half; k <= blur_width_half; ++k) {
                        for (int l = -blur_width_half; l <= blur_width_half; ++l) {
                            int i2 = i + k;
                            int j2 = j + l;
                            // Out of bounds is black. TODO: do module to match shader exactly. 
                            if (i2 > 0 && i2 < (int)height && j2 > 0 && j2 < (int)width) {
                                unsigned int srcIndex = index + 3 * (k * width + l);
                                image2[index + 0] += image[srcIndex + 0];
                                image2[index + 1] += image[srcIndex + 1];
                                image2[index + 2] += image[srcIndex + 2];
                            }
                        }
                    }
                    image2[index + 0] /= (blur_width2 * 255.0);
                    image2[index + 1] /= (blur_width2 * 255.0);
                    image2[index + 2] /= (blur_width2 * 255.0);
                }
            }
            glTexImage2D(
                GL_TEXTURE_2D, 0, GL_RGB, width, height,
                0, GL_RGB, GL_FLOAT, image2
            );
        }

        /* Modified. */
        glUseProgram(program2);
        glUniform1i(textureSampler_location2, 0);
        glUniform2f(pixD_location2, 1.0 / width, 1.0 / height);
        glBindVertexArray(vao2);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
        common_fps_print();
    } while (!glfwWindowShouldClose(window));

    /* Cleanup. */
    if (cpu) {
        free(image2);
    }
    CommonV4l2_deinit(&common_v4l2);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
	glDeleteTextures(1, &texture);
    glDeleteProgram(program);
    glfwTerminate();
    return EXIT_SUCCESS;
}
