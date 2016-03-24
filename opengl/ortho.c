/*
Compare glOrtho and glFrustrum + gluLookAt with a wire cube.

Usage:

    ./executable [<anything>]

If an argument is given, us glOrtho, otherwise, use glFrustrum.

http://stackoverflow.com/questions/2571402/explain-the-usage-of-glortho/36046924#36046924
*/

#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

static int ortho = 0;

static void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    if (ortho) {
    } else {
        gluLookAt(0.0, 0.0, -3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    }
    glColor3f(1.0f, 1.0f, 1.0f);
#if 1
    glutWireCube(2);
#else
    /* To test for depth. */
    glBegin(GL_TRIANGLES);
    glVertex3f( 0.0f,  0.5f, -1.1f);
    glVertex3f(-0.5f, -0.5f, -1.1f);
    glVertex3f( 0.5f, -0.5f, -1.1f);
    glEnd();
#endif
    glFlush();
}

static void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (ortho) {
        /* The default viewport is the cube of length 2, double that. */
        glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
    } else {
        glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
    }
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    if (argc > 1) {
        ortho = 1;
    }
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return EXIT_SUCCESS;
}
