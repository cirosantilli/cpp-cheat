/*
Formula:

    color = ambient + attenuation * (diffuse + specular);
    attenuation = / (CONSTANT  + LINEAR * dist + QUADRATIC * dist^2

Docs say: its intensity is attenuated by the reciprocal of the sum of the constant factor,
the linear factor times the distance between the light and the vertex being lighted

Default is 1,0,0, which means no attenuation.

The light is closer to the top vertex, which become brighter.
*/

#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

static void display(void) {
    glColor3f(1.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();
    glFlush();
}

static void init(void) {
    GLfloat light0_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light0_position[] = {0.0, 1.0, 1.0, 1.0};
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.0);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 1.0);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glNormal3f(0.0f, 0.0f, 1.0f);
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
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return EXIT_SUCCESS;
}
