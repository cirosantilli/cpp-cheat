/*
Minimal triangle example with VAO.

Uses methods:

- glGenVertexArrays
- glBindVertexArray

Expected outcome: a red triangle is drawn.

TODO: what is the advantage of using VAO compared to just VBO?

- http://stackoverflow.com/questions/11821336/what-are-vertex-array-objects
- http://gamedev.stackexchange.com/questions/99236/what-state-is-stored-in-an-opengl-vertex-array-object-vao-and-how-do-i-use-the/99238

Looks like a way to bind a bunch of things at once:

> stores all of the state needed to supply vertex data (with one minor exception noted below).
It stores the format of the vertex data as well as the Buffer Objects

VAO is a container object: it contains other objects.
https://www.opengl.org/wiki/Vertex_Specification#Vertex_Array_Object

Adapted from
https://github.com/JoeyDeVries/LearnOpenGL/blob/d5c3be70ab2b884cf2b2c94cbf73a31f632fbf47/src/1.getting_started/2.hello_triangle/hellotriangle2.cpp
*/

#include "common.h"

static const GLuint WIDTH = 500;
static const GLuint HEIGHT = 500;
static const GLchar *vertex_shader_source =
    "#version 330 core\n"
    "in vec3 position;\n"
    "void main() {\n"
    "   gl_Position = vec4(position, 1.0);\n"
    "}\n";
static const GLchar *fragment_shader_source =
    "#version 330 core\n"
    "out vec4 color;\n"
    "void main() {\n"
    "   color = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
    "}\n";
/* Passed as input to the vertex shader. */
static const GLfloat vertices[] = {
     0.0f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
};

int main(void) {
    GLFWwindow *window;
    GLint attribute_position;
    GLuint program, vbo, vao;

    /* Window system. */
    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow(WIDTH, HEIGHT, __FILE__, NULL, NULL);
    glfwMakeContextCurrent(window);
    glewInit();

    program = common_get_shader_program(vertex_shader_source, fragment_shader_source);
    attribute_position = glGetAttribLocation(program, "position");

    /* Buffer setup. */
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(attribute_position, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    /* Draw. */
    glUseProgram(program);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glViewport(0, 0, WIDTH, HEIGHT);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    glfwSwapBuffers(window);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    /* Cleanup. */
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(program);
    glfwTerminate();
    return EXIT_SUCCESS;
}
