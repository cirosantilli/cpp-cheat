/*
SDL version of the GLFW shader at ../opengl/glfw_heatmap.c
to compare FPS with heatmap.c.
*/

#include "common.h"

#define GLEW_STATIC
#include <GL/glew.h>

static const GLuint WIDTH = 500;
static const GLuint HEIGHT = 500;
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
    "uniform float width;\n"
    "uniform float height;\n"
    "uniform float periods_x;\n"
    "uniform float periods_y;\n"
    "void main(void) {\n"
    "    float center_x = width / 2.0;"
    "    float center_y = height / 2.0;"
    "    float x = (gl_FragCoord.x - center_x) * periods_x / width;"
    "    float y = (gl_FragCoord.y - center_y) * periods_y / height;"
    "    gl_FragColor[0] = 0.5 * (1.0 + (sin((pi2 * (sqrt(x*x + y*y) - time)))));\n"
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

/* Copy paste. Upstream on OpenGL. */
GLint common_get_shader_program(
        const char *vertex_shader_source,
        const char *fragment_shader_source) {
    GLchar *log = NULL;
    GLint fragment_shader, log_length, program, success, vertex_shader;

    /* Vertex shader */
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &log_length);
    log = malloc(log_length);
    if (log_length > 0) {
        glGetShaderInfoLog(vertex_shader, log_length, NULL, log);
        printf("vertex shader log:\n\n%s\n", log);
    }
    if (!success) {
        printf("vertex shader compile error\n");
        exit(EXIT_FAILURE);
    }

    /* Fragment shader */
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &log_length);
    if (log_length > 0) {
        log = realloc(log, log_length);
        glGetShaderInfoLog(fragment_shader, log_length, NULL, log);
        printf("fragment shader log:\n\n%s\n", log);
    }
    if (!success) {
        printf("fragment shader compile error\n");
        exit(EXIT_FAILURE);
    }

    /* Link shaders */
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);
    if (log_length > 0) {
        log = realloc(log, log_length);
        glGetProgramInfoLog(program, log_length, NULL, log);
        printf("shader link log:\n\n%s\n", log);
    }
    if (!success) {
        printf("shader link error");
        exit(EXIT_FAILURE);
    }

    free(log);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return program;
}

int main(void) {
    /* SDL variables. */
    SDL_Event event;
    SDL_Window *window;
    SDL_GLContext gl_context;
    const unsigned int WINDOW_WIDTH = 500, WINDOW_HEIGHT = WINDOW_WIDTH;
    double dt, initial_time;

    /* OpenGL variables. */
    GLint
        attribute_coord2d,
        ibo_size,
        width_location,
        height_location,
        time_location,
        periods_x_location,
        periods_y_location,
        pi2_location,
        program
    ;
    GLuint ibo, vbo;
    const char *attribute_name = "coord2d";
    const float
        periods_x = 10.0,
        periods_y = 10.0,
        pi2 = 2.0 * acos(-1.0)
    ;

    /* SDL init. */
    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    window = SDL_CreateWindow(__FILE__, 0, 0,
            WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    gl_context = SDL_GL_CreateContext(window);
    glewInit();

    /* OpenGL init. */
    {
        program = common_get_shader_program(vertex_shader_source, fragment_shader_source);
        attribute_coord2d = glGetAttribLocation(program, attribute_name);
        if (attribute_coord2d == -1) {
            fprintf(stderr, "error: attribute_coord2d: %s\n", attribute_name);
            return EXIT_FAILURE;
        }
        height_location = glGetUniformLocation(program, "height");
        periods_x_location = glGetUniformLocation(program, "periods_x");
        periods_y_location = glGetUniformLocation(program, "periods_y");
        pi2_location = glGetUniformLocation(program, "pi2");
        time_location = glGetUniformLocation(program, "time");
        width_location = glGetUniformLocation(program, "width");

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

        glUniform1f(pi2_location, pi2);
        glUniform1f(width_location, WIDTH);
        glUniform1f(height_location, HEIGHT);
        glUniform1f(periods_x_location, periods_x);
        glUniform1f(periods_y_location, periods_y);
    }

    initial_time = common_get_secs();
    common_fps_init();
    while (1) {
        dt = common_get_secs() - initial_time;

        /* OpenGL draw. */
        glClear(GL_COLOR_BUFFER_BIT);
        glEnableVertexAttribArray(attribute_coord2d);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(attribute_coord2d, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glUniform1f(time_location, dt);
        glDrawElements(GL_TRIANGLES, ibo_size / sizeof(indexes[0]), GL_UNSIGNED_INT, 0);
        glDisableVertexAttribArray(attribute_coord2d);

        common_fps_update_and_print();
        SDL_GL_SwapWindow(window);
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
    }

    /* OpenGL cleanup. */
    glDeleteBuffers(1, &ibo);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(program);

    /* SDL cleanup. */
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
