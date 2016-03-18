/*
The triangle only becomes gray because ambient light is halved:
http://forum.unity3d.com/threads/why-is-ambient-light-at-half-strength.33955/
*/

#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

static void init(void) {
    GLfloat light0_ambient[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light0_position[] = {0.0, -1.0, 0.0, 0.0};
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    glColorMaterial(GL_FRONT, GL_AMBIENT);
    glEnable(GL_COLOR_MATERIAL);
}

static void draw_triangle() {
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
}

static void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glBegin(GL_TRIANGLES);
    draw_triangle();
    glEnd();
    glFlush();
}

static void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -1.0, 1.0);
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
