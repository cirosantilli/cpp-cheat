#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "common_glut.h"

static const GLfloat speed = 45.0f;
static GLfloat angle = 0.0f;
static int old_t;

unsigned int triangles_per_line = 200;
unsigned int nlayers = 10;

static void display(void) {
    unsigned int i, j;
    unsigned int repeats;
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    for (repeats = 0; repeats < nlayers; repeats++) {
        for (i = 0; i < triangles_per_line; i++) {
            for (j = 0; j < triangles_per_line; j++) {
                glPushMatrix();
                glTranslatef(2*i, 2*j, 0);
                glRotatef(angle, 0.0f, 0.0f, 1.0f);
                glBegin(GL_TRIANGLES);
                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex3f( 0.0f, 1.0f, 0.0f);
                glColor3f(0.0f, 1.0f, 0.0f);
                glVertex3f(-1.0f, -1.0f, 0.0f);
                glColor3f(0.0f, 0.0f, 1.0f);
                glVertex3f( 1.0f, -1.0f, 0.0f);
                glEnd();
                glPopMatrix();
            }
        }
    }
    glutSwapBuffers();
    common_glut_fps_print();
}

static void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, triangles_per_line + 1, -1.0, triangles_per_line + 1, -1.5, 1.5);
    glMatrixMode(GL_MODELVIEW);
}

void idle(void) {
    int t;
    t = glutGet(GLUT_ELAPSED_TIME);
    angle += speed * (t - old_t) / 1000.0;
    angle = fmod(angle, 360.0);
    old_t = t;
    glutPostRedisplay();
}

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    common_glut_fps_init();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    if (argc > 1) {
        triangles_per_line = strtol(argv[1], NULL, 10);
        if (argc > 2) {
            nlayers = strtol(argv[2], NULL, 10);
        }
    }
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutMainLoop();
    return EXIT_SUCCESS;
}
