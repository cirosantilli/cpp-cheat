/*
Transformation matrices.

It is just an explicit uniform passed to the vertex shader,
and explicitly multiplies vectors.
*/

#include "common.h"

static const GLuint WIDTH = 800;
static const GLuint HEIGHT = 600;
/* ourColor is passed on to the fragment shader. */
static const GLchar* vertex_shader_source =
    "#version 330 core\n"
    "in vec3 position;\n"
    "in vec3 vColor;\n"
    "out vec3 fColor;\n"
    "uniform mat4 transform;\n"
    "void main() {\n"
    "    gl_Position = transform * vec4(position, 1.0f);\n"
    "    fColor = vColor;\n"
    "}\n";
static const GLchar* fragment_shader_source =
    "#version 330 core\n"
    "in vec3 fColor;\n"
    "out vec4 color;\n"
    "void main() {\n"
    "    color = vec4(fColor, 1.0f);\n"
    "}\n";
static GLfloat vertices[] = {
/*   Positions          Colors */
     0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
     0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
};

int main(void) {
    GLFWwindow* window;
    GLfloat transform[] = {
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
    };
    GLint
        vColor_location,
        position_location,
        transform_location
    ;
    GLuint program, vao, vbo;
    double time;

    /* Window system. */
    glfwInit();
    window = glfwCreateWindow(WIDTH, HEIGHT, __FILE__, NULL, NULL);
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    glewInit();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glViewport(0, 0, WIDTH, HEIGHT);

    /* Shaders. */
    program = common_get_shader_program(vertex_shader_source, fragment_shader_source);
    vColor_location = glGetAttribLocation(program, "vColor");
    position_location = glGetAttribLocation(program, "position");
    transform_location = glGetUniformLocation(program, "transform");
    glUseProgram(program);

    /* Buffers. */
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    /* Position attribute */
    glVertexAttribPointer(position_location, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    /* Color attribute */
    glVertexAttribPointer(vColor_location, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glBindVertexArray(0);

    /* Main loop. */
    common_fps_init();
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);

        /* To do serious things, we'd need a math library like glm here. */
        time = glfwGetTime();
        transform[0] = 2.0f * sin(time);
        transform[5] = 2.0f * cos(time);
        glUniformMatrix4fv(transform_location, 1, GL_FALSE, transform);

        glBindVertexArray(vao);
        glEnableVertexAttribArray(position_location);
        glEnableVertexAttribArray(vColor_location);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(position_location);
        glDisableVertexAttribArray(vColor_location);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        common_fps_print();
    }

    /* Cleanup. */
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glfwTerminate();
    return EXIT_SUCCESS;
}
