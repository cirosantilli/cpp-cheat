/*
Reuse vertices on multiple triangles via vertex indices.
*/

#include "common.h"

static const GLuint WIDTH = 512;
static const GLuint HEIGHT = 512;
/* ourColor is passed on to the fragment shader. */
static const GLchar *vertex_shader_source =
    "#version 330 core\n"
    "in vec3 position;\n"
    "in vec3 color;\n"
    "out vec3 ourColor;\n"
    "void main() {\n"
    "    gl_Position = vec4(position, 1.0f);\n"
    "    ourColor = color;\n"
    "}\n";
static const GLchar *fragment_shader_source =
    "#version 330 core\n"
    "in vec3 ourColor;\n"
    "out vec4 color;\n"
    "void main() {\n"
    "    color = vec4(ourColor, 1.0f);\n"
    "}\n";
static const GLfloat vertices[] = {
/*   Positions            Colors */
     0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,
     0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,
};
static const GLuint indices[] = {
    /* First triangle. */
    0, 1, 3,
    /* Second triangle. */
    1, 2, 3,
};

int main(void) {
    GLint attribute_position, attribute_color;
    GLuint ebo, program, vbo, vao;

    /* Window system. */
    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, __FILE__, NULL, NULL);
    glfwMakeContextCurrent(window);
    glewInit();

    /* Shader program. */
    program = common_get_shader_program(vertex_shader_source, fragment_shader_source);
    attribute_position = glGetAttribLocation(program, "position");
    attribute_color = glGetAttribLocation(program, "color");

    /* vbo */
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* ebo */
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    /* Buffer setup. */
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(attribute_position, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(attribute_position);
    /* Color attribute */
    glVertexAttribPointer(attribute_color, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(attribute_color);
    glBindVertexArray(0);

    /* Draw. */
    glViewport(0, 0, WIDTH, HEIGHT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(program);
    glBindVertexArray(vao);
    /* glDrawElements must be used instead of glDrawArrays. TODO where is that documented? */
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glfwSwapBuffers(window);

    /* Main loop. */
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    /* Cleanup. */
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(program);
    glfwTerminate();
    return EXIT_SUCCESS;
}
