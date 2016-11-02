/*
- fragmentUv varies on the fragment shader between uvs[]
- sampler2D: TODO
*/

#include "common.h"

static const GLuint WIDTH = 500;
static const GLuint HEIGHT = 500;
static const GLchar *vertex_shader_source =
    "#version 330 core\n"
    "layout(location = 0) in vec2 coord2d;\n"
    "layout(location = 1) in vec2 vertexUv;\n"
    "out vec2 fragmentUv;\n"
    "void main(){\n"
    "    gl_Position =  vec4(coord2d, 0, 1);\n"
    "    fragmentUv = vertexUv;\n"
    "}\n";
static const GLchar *fragment_shader_source =
    "#version 330 core\n"
    "in vec2 fragmentUv;\n"
    "out vec3 color;\n"
    "uniform sampler2D myTextureSampler;\n"
    "void main(){\n"
    "    color = texture(myTextureSampler, fragmentUv).rgb;\n"
    "}\n";
static const GLfloat vertices[] = {
     0.0,  0.8,
    -0.8, -0.8,
     0.8, -0.8,
};
static const GLfloat uvs[] = {
    0.0, 0.0,
    4.0, 0.0,
    0.0, 2.0,
};

int main(void) {
    GLFWwindow *window;
    GLuint
        attribute_coord2d,
        attribute_myTextureSampler,
        attribute_vertexUv,
        program,
        texture,
        uvbo,
        vbo
    ;
    unsigned int
        texture_height = 20,
        texture_width = 20
    ;
    unsigned char *texture_image;

    /* Window system. */
    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow(WIDTH, HEIGHT, __FILE__, NULL, NULL);
    glfwMakeContextCurrent(window);
    glewInit();

    /* Shader setup. */
    program = common_get_shader_program(vertex_shader_source, fragment_shader_source);
    attribute_coord2d = glGetAttribLocation(program, "coord2d");
    attribute_vertexUv = glGetAttribLocation(program, "vertexUv");
	attribute_myTextureSampler = glGetUniformLocation(program, "myTextureSampler");

    /* Global settings.. */
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glUseProgram(program);
    glViewport(0, 0, WIDTH, HEIGHT);

    /* Vertex buffer. */
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* UV buffer. */
	glGenBuffers(1, &uvbo);
	glBindBuffer(GL_ARRAY_BUFFER, uvbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* Texture buffer. */
    {
        texture_image = common_texture_get_image(texture_width, texture_height);
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture_width, texture_width,
                     0, GL_BGR, GL_UNSIGNED_BYTE, texture_image);

        /* Cheap. filtering. */
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        /* Expensive trilinear filtering. */
        /*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);*/
        /*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);*/
        /*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);*/
        /*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); */
        /*glGenerateMipmap(GL_TEXTURE_2D);*/

        glBindTexture(GL_TEXTURE_2D, texture);
        free(texture_image);
    }

    glClear(GL_COLOR_BUFFER_BIT);

    glEnableVertexAttribArray(attribute_coord2d);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(
        attribute_coord2d,
        2,
        GL_FLOAT,
        GL_FALSE,
        0,
        0
    );
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glEnableVertexAttribArray(attribute_vertexUv);
    glBindBuffer(GL_ARRAY_BUFFER, uvbo);
    glVertexAttribPointer(
        attribute_vertexUv,
        2,
        GL_FLOAT,
        GL_FALSE,
        0,
        0
    );
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(attribute_myTextureSampler, 0);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(attribute_coord2d);
    glDisableVertexAttribArray(attribute_vertexUv);
    glfwSwapBuffers(window);

    /* Main loop. */
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    /* Cleanup. */
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &uvbo);
	glDeleteTextures(1, &attribute_myTextureSampler);
    glDeleteProgram(program);
    glfwTerminate();
    return EXIT_SUCCESS;
}
