/*
Compute shader hello world.

Does a simple computation, and writes it directly to the
texture seen by the frament shader.

This could be done easily on a fragment shader,
so this is is just an useless sanity check example.

The main advantage of compute shaders (which we are not doing here),
is that they can keep state data on the GPU between draw calls.

This is basically the upper limit speed of compute to texture operations,
since we are only doing a very simple operaiton on the shader.

TODO understand:

GL_MAX_COMPUTE_WORK_GROUP_COUNT
GL_MAX_COMPUTE_WORK_GROUP_SIZE
GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS
glDispatchCompute
glMemoryBarrier
local_size_x
binding
*/

#include "common.h"

static const GLuint WIDTH = 512;
static const GLuint HEIGHT = 512;
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
static const char *compute_shader_source =
    "#version 430\n"
    "layout (local_size_x = 1, local_size_y = 1) in;\n"
    "layout (rgba32f, binding = 0) uniform image2D img_output;\n"
    "void main () {\n"
    "    ivec2 gid = ivec2(gl_GlobalInvocationID.xy);\n"
    "    ivec2 dims = imageSize(img_output);\n"
    "    vec4 pixel = vec4(gid.x / float(dims.x), gid.y / float(dims.y), 1.0, 1.0);\n"
    "    imageStore(img_output, gid, pixel);\n"
    "}\n";

int main(void) {
    GLFWwindow *window;
    GLint
        coord2d_location,
        textureSampler_location,
        vertexUv_location
    ;
    GLuint
        ebo,
        program,
        compute_program,
        texture,
        vbo,
        vao
    ;
    unsigned int
        width = WIDTH,
        height = HEIGHT
    ;

    /* Window. */
    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow(width, height, __FILE__, NULL, NULL);
    glfwMakeContextCurrent(window);
    glewInit();

    /* Shader. */
    program = common_get_shader_program(vertex_shader_source, fragment_shader_source);
    coord2d_location = glGetAttribLocation(program, "coord2d");
    vertexUv_location = glGetAttribLocation(program, "vertexUv");
	textureSampler_location = glGetUniformLocation(program, "textureSampler");

    /* Compute shader. */
    compute_program = common_get_compute_program(compute_shader_source);

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

    /* Texture. */
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    /* Same internal format as compute shader input.
     * data=NULL to just allocate the memory but not set it to anything. */
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
    /* Bind to image unit, to allow writting to it from the compute shader. */
    glBindImageTexture(0, texture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);

    /* Compute. */
    glUseProgram(compute_program);
    /* Dimensions given here appear in gl_GlobalInvocationID.xy in the shader. */
    glDispatchCompute((GLuint)width, (GLuint)height, 1);
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

    /* Global state. */
    glViewport(0, 0, width, height);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    /* Main loop. */
    common_fps_init();
    while (!glfwWindowShouldClose(window)) {
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
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
	glDeleteTextures(1, &texture);
    glDeleteProgram(program);
    glDeleteProgram(compute_program);
    glfwTerminate();
    return EXIT_SUCCESS;
}
