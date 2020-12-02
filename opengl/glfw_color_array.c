/* One color per vertex, taken from the same array as the vertices.
 *
 * Color interpolation on the fragment shader is automatic.
 *
 * Adapted from: https://github.com/JoeyDeVries/LearnOpenGL/blob/d5c3be70ab2b884cf2b2c94cbf73a31f632fbf47/src/1.getting_started/3.shaders/shaders-using-object.cpp
 *
 * - https://stackoverflow.com/questions/17789575/what-are-shaders-in-opengl-and-what-do-we-need-them-for/36211337#36211337
 * - https://stackoverflow.com/questions/6733934/what-does-immediate-mode-mean-in-opengl/36166310#36166310
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

int main(int argc, char **argv) {
    int immediate = (argc > 1) && argv[1][0] == '1';
    GLFWwindow *window;

    /* Only needed for shader version. */
    GLuint program, vbo, vao;

    /* Window system. */
    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow(WIDTH, HEIGHT, __FILE__, NULL, NULL);
    glfwMakeContextCurrent(window);
    glewInit();

    if (immediate) {
        puts("immediate");
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glBegin(GL_TRIANGLES);
        glColor3f(  1.0f,  0.0f, 0.0f);
        glVertex3f(-0.5f, -0.5f, 0.0f);
        glColor3f(  0.0f,  1.0f, 0.0f);
        glVertex3f( 0.5f, -0.5f, 0.0f);
        glColor3f(  0.0f,  0.0f, 1.0f);
        glVertex3f( 0.0f,  0.5f, 0.0f);
        glEnd();
    } else {
        GLint attribute_vertColor, attribute_position;

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
    }
    glfwSwapBuffers(window);

    /* Main loop. */
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    /* Cleanup. */
    if (!immediate) {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteProgram(program);
    }
    glfwTerminate();
    return EXIT_SUCCESS;
}
