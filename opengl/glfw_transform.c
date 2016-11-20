/*
Transformation matrices.

It is just an explicit uniform passed to the vertex shader,
and explicitly multiplies vectors.

Usage:

    ./prog [width]
*/

#include "common.h"

static const GLuint WIDTH = 512;
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

int main(int argc, char **argv) {
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
    GLuint height, program, width, vao, vbo;
    double time;

    /* CLI arguments. */
    if (argc > 1) {
        width = strtol(argv[1], NULL, 10);
    } else {
        width = WIDTH;
    }
    height = width;

    /* Window system. */
    glfwInit();
    window = glfwCreateWindow(width, height, __FILE__, NULL, NULL);
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    glewInit();

    /* Shader program. */
    program = common_get_shader_program(vertex_shader_source, fragment_shader_source);
    vColor_location = glGetAttribLocation(program, "vColor");
    position_location = glGetAttribLocation(program, "position");
    transform_location = glGetUniformLocation(program, "transform");
    glUseProgram(program);

    /* vbo */
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* Buffers. */
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(position_location, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(position_location);
    glVertexAttribPointer(vColor_location, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(vColor_location);
    glBindVertexArray(0);

    /* Global draw calls. */
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glViewport(0, 0, width, height);

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
        glDrawArrays(GL_TRIANGLES, 0, 3);
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
