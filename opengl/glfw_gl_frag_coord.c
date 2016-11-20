/*
Magic variable that contais the coordinates in the fragment shader, in pixels.

All is calculated in screen pixel position, not local pixel position.

Depreacted in 1.3 in favor of TODO.
*/

#include "common.h"

static const GLuint WIDTH = 1000;
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
    GLint attribute_coord2d;
    GLuint program, vbo;
    const char *attribute_name = "coord2d";

    /* Window system. */
    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow(WIDTH, HEIGHT, __FILE__, NULL, NULL);
    glfwMakeContextCurrent(window);
    glewInit();

    /* Shader setup. */
    program = common_get_shader_program(vertex_shader_source, fragment_shader_source);
    attribute_coord2d = glGetAttribLocation(program, attribute_name);

    /* vbo */
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /* Draw. */
    glViewport(0, 0, WIDTH, HEIGHT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(program);
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

    /* Main loop. */
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    /* Cleanup. */
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(program);
    glfwTerminate();
    return EXIT_SUCCESS;
}
