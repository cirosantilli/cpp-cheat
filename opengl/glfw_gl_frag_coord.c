/*
Magic variable that contais the coordinates in the fragment shader, in pixels.

All is calculated in screen pixel position, not local pixel position.
*/

#include "common.h"

static const GLuint WIDTH = 1000;
static const GLuint HEIGHT = 500;
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
    "    gl_FragColor[1] = mod(gl_FragCoord.x, 100.0) / 100.0;\n"
    "    gl_FragColor[2] = mod(gl_FragCoord.y, 100.0) / 100.0;\n"
    "}\n";
static const GLfloat vertices[] = {
    -0.5,  1.0,
    -1.0, -1.0,
     0.0, -1.0,
     0.5,  1.0,
     0.0, -0.8,
     1.0, -0.8,
};

int main(void) {
    GLFWwindow *window;
    GLint attribute_coord2d, program;
    GLuint vbo;
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

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glEnableVertexAttribArray(attribute_coord2d);
        glVertexAttribPointer(
            attribute_coord2d,
            2,
            GL_FLOAT,
            GL_FALSE,
            0,
            0
        );
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glDisableVertexAttribArray(attribute_coord2d);
        glfwSwapBuffers(window);
        glfwSwapBuffers(window);
    }

    glDeleteBuffers(1, &vbo);
    glDeleteProgram(program);
    glfwTerminate();
    return EXIT_SUCCESS;
}
