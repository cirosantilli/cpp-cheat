/*
TODO: add a perspective matrix transform.
*/

#include "common.h"

static const GLuint WIDTH = 512;
static const GLuint HEIGHT = 512;
static const GLchar* vertex_shader_source =
    "#version 120\n"
    "attribute vec3 coord3d;\n"
    "void main(void) {\n"
    "    gl_Position = vec4(coord3d, 1.0);\n"
    "}\n";
static const GLchar* fragment_shader_source =
    "#version 120\n"
    "void main(void) {\n"
    "    gl_FragColor[0] = 0.0;\n"
    "    gl_FragColor[1] = 0.0;\n"
    "    gl_FragColor[2] = 1.0;\n"
    "}\n";
static const GLfloat vertices[] = {
     0.0,  0.8,   2.0,
    -0.8, -0.8,   0.0,
     0.8, -0.8,   0.0,
};

int main(void) {
    GLFWwindow *window;
    GLint attribute_coord3d, program;
    GLuint vbo;
    const char *attribute_name = "coord3d";

    glfwInit();
    window = glfwCreateWindow(WIDTH, HEIGHT, __FILE__, NULL, NULL);
    glfwMakeContextCurrent(window);
    glewInit();

    program = common_get_shader_program(vertex_shader_source, fragment_shader_source);
    attribute_coord3d = glGetAttribLocation(program, attribute_name);
    if (attribute_coord3d == -1) {
        fprintf(stderr, "error: attribute_coord3d: %s\n", attribute_name);
        return EXIT_FAILURE;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glUseProgram(program);
    glViewport(0, 0, WIDTH, HEIGHT);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glEnableVertexAttribArray(attribute_coord3d);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(
            attribute_coord3d,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            0
        );
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(attribute_coord3d);
        glfwSwapBuffers(window);
    }

    glDeleteBuffers(1, &vbo);
    glDeleteProgram(program);
    glfwTerminate();
    return EXIT_SUCCESS;
}
