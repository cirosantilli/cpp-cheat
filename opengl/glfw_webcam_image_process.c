/*
Capture webcam video, show it on screen, and next to it show
a version modified by a fragment shader.

Computer vision on the GPU.

Fragment shaders can access any byte of a texture, and so do operations over multiple pixels.

Several web examples:
https://www.chromeexperiments.com/webgl,webcam-input?page=0

Questions:

-   http://stackoverflow.com/questions/13693946/image-processing-with-glsl-shaders

Demos:

-   https://www.youtube.com/watch?v=fJtOdJ9MHsA> GLSL Linux camera real time edge detection shown on screen.
    Getting started: <https://github.com/premsasidharan/gpu_img_proc/issues/1#issuecomment-257504913>
-   WebRTC chess with camera: https://www.youtube.com/watch?v=aK1DC2zp6ZE

Android:

-   http://stackoverflow.com/questions/7847912/is-it-possible-to-give-effect-like-vertex-shader-and-fragment-shader-to-the-andr
-   http://stackoverflow.com/questions/30723055/how-to-obtain-the-rgb-colors-of-the-camera-texture-in-opengl-es-2-0-for-android
-   http://stackoverflow.com/questions/18449162/simultaneous-camera-preview-and-processing
-   http://stackoverflow.com/questions/12519235/modifying-camera-output-using-surfacetexture-and-opengl

Post processing is equivalent to image processing (unless there is some
magic Krhonos way to bypass the CPU camera image copy to texture):

-   <https://en.wikibooks.org/wiki/OpenGL_Programming/Post-Processing>
-   r3dux tori demo <https://www.youtube.com/watch?v=9nDxIbj3mPU>
*/

#include "common.h"
#include "../v4l2/common_v4l2.h"

static const GLuint WIDTH = 640;
static const GLuint HEIGHT = 480;
static const GLfloat vertices[] = {
    -1.0,  1.0,
     0.0,  1.0,
     0.0, -1.0,
    -1.0, -1.0,
};
static const GLfloat uvs[] = {
    0.0, 1.0,
    0.0, 0.0,
    1.0, 0.0,
};
static const GLuint indices[] = {
    0, 1, 2,
    0, 2, 3,
};

static const GLchar *vertex_shader_source =
    "#version 330 core\n"
    "in vec2 coord2d;\n"
    "in vec2 vertexUv;\n"
    "out vec2 fragmentUv;\n"
    "void main() {\n"
    "    gl_Position = vec4(coord2d, 0, 1);\n"
    "    fragmentUv = vertexUv;\n"
    "}\n";
static const GLchar *fragment_shader_source =
    "#version 330 core\n"
    "in vec2 fragmentUv;\n"
    "out vec3 color;\n"
    "uniform sampler2D myTextureSampler;\n"
    "void main() {\n"
    "    color = ("
    "         texture(myTextureSampler, fragmentUv.yx ).rgb\n"
    "    ) / 1\n"
    ";\n"
    "}\n";

static const GLchar *vertex_shader_source2 =
    "#version 330 core\n"
    "in vec2 coord2d;\n"
    "in vec2 vertexUv;\n"
    "out vec2 fragmentUv;\n"
    "void main() {\n"
    "    gl_Position = vec4(coord2d + vec2(1.0, 0.0), 0, 1);\n"
    "    fragmentUv = vertexUv;\n"
    "}\n";
static const GLchar *fragment_shader_source2 =
    "#version 330 core\n"
    "in vec2 fragmentUv;\n"
    "out vec3 color;\n"
    "uniform sampler2D myTextureSampler;\n"
    "void main() {\n"
    "    color = ("
    /*"         texture(myTextureSampler, fragmentUv.yx ).brg\n"*/
    "         1.0 - texture(myTextureSampler, fragmentUv.yx ).rgb\n"
    "    ) / 1\n"
    ";\n"
    "}\n";

int main(void) {
    GLFWwindow *window;
    GLint
        coord2d_location,
        myTextureSampler_location,
        vertexUv_location,
        coord2d_location2,
        myTextureSampler_location2,
        vertexUv_location2
    ;
    GLuint
        ebo,
        program,
        program2,
        texture,
        uvbo,
        vbo
    ;
    unsigned char *texture_image;
    CommonV4l2 common_v4l2;

    /* Window system. */
    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow(2 * WIDTH, HEIGHT, __FILE__, NULL, NULL);
    glfwMakeContextCurrent(window);
    glewInit();
    CommonV4l2_init(&common_v4l2, COMMON_V4L2_DEVICE, WIDTH, HEIGHT);

    /* Shader setup. */
    program = common_get_shader_program(vertex_shader_source, fragment_shader_source);
    coord2d_location = glGetAttribLocation(program, "coord2d");
    vertexUv_location = glGetAttribLocation(program, "vertexUv");
	myTextureSampler_location = glGetUniformLocation(program, "myTextureSampler");

    /* Shader setup 2. */
    program2 = common_get_shader_program(vertex_shader_source2, fragment_shader_source2);
    coord2d_location2 = glGetAttribLocation(program2, "coord2d");
    vertexUv_location2 = glGetAttribLocation(program2, "vertexUv");
	myTextureSampler_location2 = glGetUniformLocation(program2, "myTextureSampler");

    /* vbo */
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* uvbo */
	glGenBuffers(1, &uvbo);
	glBindBuffer(GL_ARRAY_BUFFER, uvbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* ebo */
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    /* Texture buffer. */
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    /* vbo */
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(coord2d_location, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(coord2d_location2, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* uvbo */
    glBindBuffer(GL_ARRAY_BUFFER, uvbo);
    glVertexAttribPointer(vertexUv_location, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(vertexUv_location2, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* Constant state. */
    glViewport(0, 0, 2 * WIDTH, HEIGHT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glActiveTexture(GL_TEXTURE0);
    /* A texture must have been activated by glActiveTexture. */
    glBindTexture(GL_TEXTURE_2D, texture);
    /* Sampler will sample from GL_TEXTURE0. */
    glUniform1i(myTextureSampler_location, 0);
    glUniform1i(myTextureSampler_location2, 0);

    /* Main loop. */
    common_fps_init();
    do {
        /* Blocks until an image is available, thus capping FPS to that.
         * 30FPS is common in cheap webcams. */
        CommonV4l2_update_image(&common_v4l2);

        glTexImage2D(
            GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT,
            0, GL_RGB, GL_UNSIGNED_BYTE, CommonV4l2_get_image(&common_v4l2)
        );
        glClear(GL_COLOR_BUFFER_BIT);

        /* Original image. */
        glUseProgram(program);
        glEnableVertexAttribArray(coord2d_location);
        glEnableVertexAttribArray(vertexUv_location);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(coord2d_location);
        glDisableVertexAttribArray(vertexUv_location);

        /* Modified image. */
        glUseProgram(program2);
        glEnableVertexAttribArray(coord2d_location2);
        glEnableVertexAttribArray(vertexUv_location2);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(coord2d_location2);
        glDisableVertexAttribArray(vertexUv_location2);

        glfwSwapBuffers(window);
        glfwPollEvents();
        common_fps_print();
    } while (!glfwWindowShouldClose(window));

    /* Cleanup. */
    CommonV4l2_deinit(&common_v4l2);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &uvbo);
	glDeleteTextures(1, &texture);
    glDeleteProgram(program);
    glfwTerminate();
    return EXIT_SUCCESS;
}
