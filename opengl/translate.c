/*
# glTranslate
*/

#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

static void draw_triangle(GLfloat x) {
    glPushMatrix();
    glTranslatef(x, 0, 0);
    glBegin(GL_TRIANGLES);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();
    glPopMatrix();
}

static void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);
    glLoadIdentity();
    glColor3f(1.0f, 0.0f, 0.0f);
    draw_triangle(0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    draw_triangle(2.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    draw_triangle(4.0f);
    glFlush();
}

static void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 5.0, -1.0, 1.0, -1.5, 1.5);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 200);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return EXIT_SUCCESS;
}
