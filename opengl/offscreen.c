/*
- http://stackoverflow.com/questions/3191978/how-to-use-glut-opengl-to-render-to-a-file/14324292#14324292
- http://stackoverflow.com/questions/5844858/how-to-take-screenshot-in-opengl/36236839#36236839
- http://stackoverflow.com/questions/12157646/how-to-render-offscreen-on-opengl
- http://stackoverflow.com/questions/8841422/glreadpixels-data-argument-usage
- http://stackoverflow.com/questions/16509531/render-opengl-es-2-0-to-image
- http://www.songho.ca/opengl/gl_fbo.html
- http://www.mesa3d.org/brianp/sig97/offscrn.htm
- http://stackoverflow.com/questions/17711673/render-off-screen-with-fbo-and-renderbuffer-and-pixel-transfer-of-color-depth
- http://gamedev.stackexchange.com/questions/59204/opengl-fbo-render-off-screen-and-texture

FBO larger than window

- http://stackoverflow.com/questions/29598007/opengl-how-to-create-and-render-to-a-framebuffer-thats-larger-than-the-window
- http://stackoverflow.com/questions/28393664/fbo-lwjgl-bigger-than-screen-size-what-im-doing-wrong
- http://stackoverflow.com/questions/16826750/renderbuffers-larger-than-window-size-opengl
- http://stackoverflow.com/questions/682517/problem-saving-opengl-fbo-larger-than-window

Apparently OpenGL is not made for that,
and it is provided by the interface between OpenGL and the windowing system, e.g. GLX.

glPixelStorei might be needed https://www.opengl.org/sdk/docs/man/html/glPixelStore.xhtml
glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
*/

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define GL_GLEXT_PROTOTYPES 1
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glext.h>

static GLubyte *pixels = NULL;
static GLuint fbo;
static GLuint rbo_color;
static GLuint rbo_depth;
static const GLenum FORMAT = GL_RGBA;
static const GLuint FORMAT_NBYTES = 4;
static const unsigned int HEIGHT = 100;
static const unsigned int WIDTH = 100;
static int offscreen = 1;
static unsigned int time0;
static unsigned int max_nframes = 100;
static unsigned int nframes = 0;

/* Model. */
static double angle = 0;
static double delta_angle = 1;

static void init(void)  {
    int glget;

    if (offscreen) {
        /*  Framebuffer */
        glGenFramebuffers(1, &fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);

        /* Color renderbuffer. */
        glGenRenderbuffers(1, &rbo_color);
        glBindRenderbuffer(GL_RENDERBUFFER, rbo_color);
        /* Storage must be one of: */
        /* GL_RGBA4, GL_RGB565, GL_RGB5_A1, GL_DEPTH_COMPONENT16, GL_STENCIL_INDEX8. */
        glRenderbufferStorage(GL_RENDERBUFFER, GL_RGB565, WIDTH, HEIGHT);
        glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, rbo_color);

        /* Depth renderbuffer. */
        glGenRenderbuffers(1, &rbo_depth);
        glBindRenderbuffer(GL_RENDERBUFFER, rbo_depth);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, WIDTH, HEIGHT);
        glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo_depth);

        glReadBuffer(GL_COLOR_ATTACHMENT0);

        /* Sanity check. */
        assert(glCheckFramebufferStatus(GL_FRAMEBUFFER));
        glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &glget);
        assert(WIDTH * HEIGHT < (unsigned int)glget);
    } else {
        glReadBuffer(GL_BACK);
    }

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glViewport(0, 0, WIDTH, HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);

    pixels = malloc(FORMAT_NBYTES * WIDTH * HEIGHT);
    time0 = glutGet(GLUT_ELAPSED_TIME);
}

static void deinit(void)  {
    printf("FPS = %f\n", 1000.0 * nframes / (double)(glutGet(GLUT_ELAPSED_TIME) - time0));
    free(pixels);
    if (offscreen) {
        glDeleteFramebuffers(1, &fbo);
        glDeleteRenderbuffers(1, &rbo_color);
        glDeleteRenderbuffers(1, &rbo_depth);
    }
}

static void create_ppm(char *prefix, int frame_id, unsigned int width, unsigned int height,
        unsigned int color_max, unsigned int pixel_nbytes, GLubyte *pixels) {
    size_t i, j, k, cur;
    enum Constants { max_filename = 256 };
    char filename[max_filename];
    snprintf(filename, max_filename, "%s%d.ppm", prefix, frame_id);
    FILE *f = fopen(filename, "w");
    fprintf(f, "P3\n%d %d\n%d\n", width, HEIGHT, 255);
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            cur = pixel_nbytes * ((height - i - 1) * width + j);
            fprintf(f, "%3d %3d %3d ", pixels[cur], pixels[cur + 1], pixels[cur + 2]);
        }
        fprintf(f, "\n");
    }
    fclose(f);
}

static void draw_scene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(angle, 0.0f, 0.0f, -1.0f);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f( 0.0f,  0.5f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f( 0.5f, -0.5f, 0.0f);
    glEnd();
}

static void display(void) {
    draw_scene();
    if (offscreen) {
        glFlush();
    } else {
        glutSwapBuffers();
    }
    glReadPixels(0, 0, WIDTH, HEIGHT, FORMAT, GL_UNSIGNED_BYTE, pixels);
    nframes++;
    create_ppm("tmp", nframes, WIDTH, HEIGHT, 255, FORMAT_NBYTES, pixels);
    if (nframes > max_nframes)
        exit(EXIT_SUCCESS);
}

static int update_model() {
    angle += delta_angle;
    return 0;
}

static void idle(void) {
    while (update_model());
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    GLint glut_display;
    glutInit(&argc, argv);
    if (argc > 1)
        offscreen = 0;
    if (offscreen) {
        /* TODO: if we use anything smaller than the window, it only renders a smaller version of things. */
        glutInitWindowSize(50, 50);
        glutInitWindowSize(WIDTH, HEIGHT);
        glut_display = GLUT_SINGLE;
    } else {
        glutInitWindowSize(WIDTH, HEIGHT);
        glutInitWindowPosition(100, 100);
        glut_display = GLUT_DOUBLE;
    }
    glutInitDisplayMode(glut_display | GLUT_RGBA | GLUT_DEPTH);
    glutCreateWindow(argv[0]);
    if (offscreen) {
        /* TODO: if we hide the window the program blocks. */
        /*glutHideWindow();*/
    }
    init();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    atexit(deinit);
    glutMainLoop();
    return EXIT_SUCCESS;
}
