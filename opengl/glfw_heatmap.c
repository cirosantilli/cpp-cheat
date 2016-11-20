/*
Usage:

    ./prog [width]
*/

#include "common.h"

static const GLuint WIDTH = 512;
static const GLchar* vertex_shader_source =
    "#version 120\n"
    "attribute vec2 coord2d;\n"
    "void main(void) {\n"
    "    gl_Position = vec4(coord2d, 0.0, 1.0);\n"
    "}\n";
static const GLchar* fragment_shader_source =
    "#version 120\n"
    "uniform float pi2;\n"
    "uniform float time;\n"
    "uniform vec2 win_dim;\n"
    "uniform vec2 periods;\n"
    "void main(void) {\n"
    "    vec2 center = win_dim / 2.0;"
    "    vec2 xy = (gl_FragCoord.xy - center) * periods / win_dim;"
    "    gl_FragColor[0] = 0.5 * (1.0 + (sin((pi2 * (length(xy) + time)))));\n"
    "    gl_FragColor[1] = 0.0;\n"
    "    gl_FragColor[2] = 0.0;\n"
    "}\n";
static const GLfloat vertices[] = {
    -1.0,  1.0,
     1.0,  1.0,
     1.0, -1.0,
    -1.0, -1.0,
};
static const GLuint indexes[] = {
    0, 2, 1,
    0, 3, 2,
};

int main(int argc, char **argv) {
    GLFWwindow *window;
    GLint
        attribute_coord2d,
        ibo_size,
        periods_location,
        pi2_location,
        time_location,
        win_dim_location
    ;
    GLuint height, ibo, program, width, vbo;
    const char *attribute_name = "coord2d";
    const float
        periods_x = 5.0,
        periods_y = 10.0,
        pi2 = 2.0 * acos(-1.0)
    ;

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
    glewInit();

    /* Shader setup. */
    program = common_get_shader_program(vertex_shader_source, fragment_shader_source);
    attribute_coord2d = glGetAttribLocation(program, attribute_name);
    periods_location = glGetUniformLocation(program, "periods");
    pi2_location = glGetUniformLocation(program, "pi2");
    time_location = glGetUniformLocation(program, "time");
    win_dim_location = glGetUniformLocation(program, "win_dim");

    /* Global settings. */
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glUseProgram(program);
    glViewport(0, 0, width, height);

    /* vbo */
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(
        attribute_coord2d,
        2,
        GL_FLOAT,
        GL_FALSE,
        0,
        0
    );
    glEnableVertexAttribArray(attribute_coord2d);

    /* ibo */
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);
    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &ibo_size);

    /* Uniforms. */
    glUniform1f(pi2_location, pi2);
    glUniform2f(win_dim_location, width, height);
    glUniform2f(periods_location, periods_x, periods_y);

    /* Main loop. */
    common_fps_init();
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glUniform1f(time_location, glfwGetTime());
        glDrawElements(GL_TRIANGLES, ibo_size / sizeof(indexes[0]), GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        common_fps_print();
    }

    /* Cleanup. */
    glDisableVertexAttribArray(attribute_coord2d);
    glDeleteBuffers(1, &ibo);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(program);
    glfwTerminate();
    return EXIT_SUCCESS;
}
