/*
# Depth

Draw one triangle on top of the other with and without depth.

Without depth, what gets drawn last wins.

With depth, more real-world-like rendering happens.

https://www.youtube.com/watch?v=TbVImw3HJtE
Still works if triangles overlap, but then generates triangle fragments.
*/

#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

int depth = 0;

static void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    if (depth)
        glEnable(GL_DEPTH_TEST);
}

static void display(void) {
    if (depth)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    else
        glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f( 0.0f,  1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f( 1.0f, -1.0f, 1.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f,  1.0f, 0.0f);
    glVertex3f( 0.0f, -1.0f, 0.0f);
    glVertex3f( 1.0f,  1.0f, 0.0f);
    glEnd();
    glFlush();
}

static void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -2.0, 1.5);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    if (argc > 1)
        depth = 1;
    if (depth)
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    else
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
