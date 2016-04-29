/*
# Texture

Use a hand crafted texture on a triangle:

    Black / Green
    Red / Blue

TODO: there is one line of texture wrong at the left and bottom sides.

- http://gamedev.stackexchange.com/questions/46963/how-to-avoid-texture-bleeding-in-a-texture-atlas
- http://stackoverflow.com/questions/6023400/opengl-es-texture-coordinates-slightly-off
*/

#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

static GLuint texture;

static void init_texture(void) {
    const unsigned int height = 20;
    const unsigned int width = 20;
    unsigned char *cur;
    unsigned char *image;
    unsigned int i, j;
    image = malloc(3 * width * height);
    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            cur = &image[3 * (i * width + j)];
            cur[0] = 0;
            cur[1] = 0;
            cur[2] = 0;
            if (i < width / 2) {
                if (j < height / 2) {
                } else {
                    cur[0] = 255;
                }
            } else {
                if (j < height / 2) {
                    cur[1] = 255;
                } else {
                    cur[2] = 255;
                }
            }
        }
    }
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    /* TODO also play with: */
    /*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);*/
    /*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);*/
    /*glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);*/
    /*gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, image);*/
    free(image);
}

static void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    init_texture();
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
