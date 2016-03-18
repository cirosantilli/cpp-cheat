/*
# GL_SMOOTH

The most important use case of GL_SMOOTH is lightning:
when an object is lit, each vertex gets a different color
depending on the position of the light.

OpenGL then interpolates the vertices just like in this example,
giving the illusion of realistic illumination.
*/

#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

static void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();
    glFlush();
}

static void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    if (argc > 1) {
        /* The color of the last point wins. */
        glShadeModel(GL_FLAT);
    } else {
        glShadeModel(GL_SMOOTH);
    }
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return EXIT_SUCCESS;
}
