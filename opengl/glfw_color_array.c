/*
One color per vertex, taken from the same array as the vertices.

Color interpolation on the fragment shader is automatic.

http://stackoverflow.com/questions/6733934/what-does-immediate-mode-mean-in-opengl
*/

#include "common.h"

static const GLuint WIDTH = 512;
static const GLuint HEIGHT = 512;
/* fragColor is passed on to the fragment shader. */
static const GLchar *vertex_shader_source =
    "#version 330 core\n"
    "in vec3 position;\n"
    "in vec3 vertColor;\n"
    "out vec3 fragColor;\n"
    "void main() {\n"
    "    gl_Position = vec4(position, 1.0f);\n"
    "    fragColor = vertColor;\n"
    "}\n";
static const GLchar *fragment_shader_source =
    "#version 330 core\n"
    "in vec3 fragColor;\n"
    "out vec4 color;\n"
    "void main() {\n"
    "    color = vec4(fragColor, 1.0f);\n"
    "}\n";
static GLfloat vertices[] = {
/*   Positions          Colors */
     0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
     0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
};

int main(void) {
    GLFWwindow *window;
    GLint attribute_vertColor, attribute_position;
    GLuint program, vbo, vao;

    /* Window system. */
    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow(WIDTH, HEIGHT, __FILE__, NULL, NULL);
    glfwMakeContextCurrent(window);
    glewInit();

    /* Shader setup. */
    program = common_get_shader_program(vertex_shader_source, fragment_shader_source);
    attribute_position = glGetAttribLocation(program, "position");
    attribute_vertColor = glGetAttribLocation(program, "vertColor");

    /* vbo */
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* Buffer setup. */
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(
        attribute_position,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(GLfloat),
        (GLvoid*)0
    );
    glEnableVertexAttribArray(attribute_position);
    glVertexAttribPointer(
        attribute_vertColor,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(GLfloat),
        (GLvoid*)(3 * sizeof(GLfloat))
    );
    glEnableVertexAttribArray(attribute_vertColor);
    glBindVertexArray(0);

    /* Draw. */
    glViewport(0, 0, WIDTH, HEIGHT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(program);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    glfwSwapBuffers(window);

    /* Main loop. */
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    /* Cleanup. */
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(program);
    glfwTerminate();
    return EXIT_SUCCESS;
}
