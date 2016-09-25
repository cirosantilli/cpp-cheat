/*
# Texture

Use a hand crafted texture on a triangle:

    Black / Green
    Red / Blue

TODO: there is one line of texture wrong at the left and bottom sides.

- http://gamedev.stackexchange.com/questions/46963/how-to-avoid-texture-bleeding-in-a-texture-atlas
- http://stackoverflow.com/questions/6023400/opengl-es-texture-coordinates-slightly-off
*/

#include "common_glut.h"

static GLuint texture;

static GLuint init_texture(void) {
    const unsigned int width = 20, height = 20;
    unsigned char *image;
    GLuint texture;
    image = common_texture_get_image(width, height);
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
            0, GL_RGB, GL_UNSIGNED_BYTE, image);
    /* TODO also play with: */
    /*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);*/
    /*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);*/
    /*glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);*/
    /*gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, image);*/
    free(image);
    return texture;
}

static void init(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glShadeModel(GL_FLAT);
    texture = init_texture();
}

static void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_TRIANGLES);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, 0.0f);
    glTexCoord2f(4.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, 0.0f);
    glTexCoord2f(0.0f, 2.0f);
    glVertex3f(0.0f, 0.5f, 0.0f);
    glEnd();
    glFlush();
}

static void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return EXIT_SUCCESS;
}
