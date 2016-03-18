/*
https://www.opengl.org/wiki/Face_Culling
http://stackoverflow.com/questions/3595087/opengl-newbie-question-what-is-back-face-culling

TODO not working. Shouldn't one of the triangles disappear?
How to observe culling at all? It is an optional operation?
*/

#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

static void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_CULL_FACE);
    /* The defaults. */
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
}

static void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(1.0f, 0.0f, 0.0f);

    /* Counter clock wise. */
    glBegin(GL_TRIANGLES);
    glVertex3f( 0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glVertex3f( 1.0f, -1.0f, 0.0f);
    glEnd();

    /* Clock wise. */
    glBegin(GL_TRIANGLES);
    glVertex3f(2.0f, 1.0f, 0.0f);
    glVertex3f(3.0f, -1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();

    glFlush();
}

static void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 3.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 250);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return EXIT_SUCCESS;
}
