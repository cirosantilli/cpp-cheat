/*
# Transparency

# Alpha channel

# GL_BLEND

# glBlendFunc

How the final color is calculated:
https://www.opengl.org/sdk/docs/man/html/glBlendFunc.xhtml
*/

#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

static void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
}

static void draw_triangle(void) {
    glBegin(GL_TRIANGLES);
    glVertex3f( 0.0f,  0.5f, 0.0f);
    glVertex3f(-0.5f, -0.5f, 0.0f);
    glVertex3f( 0.5f, -0.5f, 0.0f);
    glEnd();
}

static void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
    glPushMatrix();
    glTranslatef(-0.25f, 0.0f, -0.5f);
    draw_triangle();
    glPopMatrix();

    glColor4f(0.0f, 1.0f, 0.0f, 0.5f);
    glPushMatrix();
    glTranslatef(0.25f, 0.0f, 0.5f);
    draw_triangle();
    glPopMatrix();

    glColor4f(0.0f, 0.0f, 1.0f, 0.5f);
    glPushMatrix();
    glTranslatef(0.0f, 0.25f, 0.0f);
    draw_triangle();
    glPopMatrix();

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
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return EXIT_SUCCESS;
}
