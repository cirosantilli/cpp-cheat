/*
OpenGL cannot calculate diffuse shadows unless you do a lot of work:

http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-16-shadow-mapping/
http://http.developer.nvidia.com/GPUGems/gpugems_ch12.html

This example only illustrates that the top triangle,
which should act as an umbrella and cover all light coming from +y infinity
from the bottom one, does nothing, and so both have the same color.
*/

#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

static void init(void) {
    GLfloat light0_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light0_position[] = {0.0, 1.0, 0.0, 0.0};
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
}

static void draw_rectangle(void) {
    glBegin(GL_TRIANGLES);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();
}

static void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    /* Bottom triangle. */
    glPushMatrix();
    glRotatef(45.0, -1.0, 0.0, 0.0);
    draw_rectangle();
    glPopMatrix();

    /* Top triangle triangle, 2x as large to cover the light. */
    glPushMatrix();
    glTranslatef(0.0, 2.5, 0.0);
    glScalef(2.0, 2.0, 2.0);
    glRotatef(45.0, -1.0, 0.0, 0.0);
    draw_rectangle();
    glPopMatrix();

    glFlush();
}

static void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-4.0, 4.0, -2.0, 4.0, -4.0, 4.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
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
