/*
Index buffer object.

Give indexes to vertex coordinates, so that we refer to the coordinates
by index instead of full location, and save some memory.

Uses glDrawElements instead of glDrawArrays.

Expected outcome: a blue square on black background.
*/

#include "common.h"

static const GLuint WIDTH = 512;
static const GLuint HEIGHT = 512;
static const GLchar* vertex_shader_source =
    "#version 120\n"
    "attribute vec2 coord2d;\n"
    "void main(void) {\n"
    "    gl_Position = vec4(coord2d, 0.0, 1.0);\n"
    "}\n";
static const GLchar* fragment_shader_source =
    "#version 120\n"
    "void main(void) {\n"
    "    gl_FragColor[0] = 0.0;\n"
    "    gl_FragColor[1] = 0.0;\n"
    "    gl_FragColor[2] = 1.0;\n"
    "}\n";
static const GLfloat vertices[] = {
    -0.8,  0.8,
     0.8,  0.8,
     0.8, -0.8,
    -0.8, -0.8,
};
static const GLuint indexes[] = {
    0, 2, 1,
    0, 3, 2,
};

int main(void) {
    GLFWwindow *window;
    GLint attribute_coord2d, ibo_size, program;
    GLuint ibo, vbo;
    const char *attribute_name = "coord2d";

    glfwInit();
    window = glfwCreateWindow(WIDTH, HEIGHT, __FILE__, NULL, NULL);
    glfwMakeContextCurrent(window);
    glewInit();

    program = common_get_shader_program(vertex_shader_source, fragment_shader_source);
    attribute_coord2d = glGetAttribLocation(program, attribute_name);
    if (attribute_coord2d == -1) {
        fprintf(stderr, "error: attribute_coord2d: %s\n", attribute_name);
        return EXIT_FAILURE;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glUseProgram(program);
    glViewport(0, 0, WIDTH, HEIGHT);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);
    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &ibo_size);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glEnableVertexAttribArray(attribute_coord2d);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(
            attribute_coord2d,
            2,
            GL_FLOAT,
            GL_FALSE,
            0,
            0
        );
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glDrawElements(GL_TRIANGLES, ibo_size / sizeof(indexes[0]), GL_UNSIGNED_INT, 0);
        glDisableVertexAttribArray(attribute_coord2d);
        glfwSwapBuffers(window);
    }

    glDeleteBuffers(1, &ibo);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(program);
    glfwTerminate();
    return EXIT_SUCCESS;
}
