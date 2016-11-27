/*
Minimal sane OpenGL 3 example.

Will be extensively commented.

Expected outcome: a red triangle on black background.
*/

#include "common.h"

static const GLuint WIDTH = 512;
static const GLuint HEIGHT = 512;
static const GLchar* vertex_shader_source =
    "#version 120\n"
    "attribute vec2 coord2d;\n"
    "void main() {\n"
    "    gl_Position = vec4(coord2d, 0.0, 1.0);\n"
    "}\n";
static const GLchar* fragment_shader_source =
    "#version 120\n"
    "void main() {\n"
    "    gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
    "}\n";
static GLfloat vertices[] = {
     0.0,  0.8,
    -0.8, -0.8,
     0.8, -0.8,
};

int main(void) {
    GLFWwindow *window;
    GLint attribute_coord2d;
    GLuint program, vbo;

    /* Window system. */
    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow(WIDTH, HEIGHT, __FILE__, NULL, NULL);
    glfwMakeContextCurrent(window);
    glewInit();

    /* Shader setup. */
    program = common_get_shader_program(vertex_shader_source, fragment_shader_source);
    attribute_coord2d = glGetAttribLocation(program, "coord2d");

    /* Buffer setup. */
    {
        /* Create a buffer object. */
        glGenBuffers(1, &vbo);

        /* Bind the buffer object to the GL_ARRAY_BUFFER. */
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        /* Set data of the buffer object currently bound GL_ARRAY_BUFFER. */
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        /*
        CPU input data has already been copied: changing the array now has no effect.
        It is likely not yet on GPU as the driver will likely wait to send a bunch of memory
        in one go later on, so it has just been copied by the driver to a buffer it owns.
        */
        /* vertices[0] = 1.0; */

        /*
        Set currently bound GL_ARRAY_BUFFER as the vertex shader input.

        -   argument 2: size. Can only be 1, 2, 3, or 4. Each one of those maps to a
            vec1, 2, 3 or 4 argument in the shader.
        */
        glVertexAttribPointer(attribute_coord2d, 2, GL_FLOAT, GL_FALSE, 0, 0);

        /* Unbind GL_ARRAY_BUFFER. */
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    /* Draw. */
    glUseProgram(program);
    glViewport(0, 0, WIDTH, HEIGHT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    /* TODO why is this needed? Isn't glVertexAttribPointer enough? */
    glEnableVertexAttribArray(attribute_coord2d);
    glDrawArrays(GL_TRIANGLES, 0, 3);
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
