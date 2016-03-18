/*
http://stackoverflow.com/questions/726379/multiple-viewports-in-opengl/36048277#36048277
*/

#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

static int width;
static int height;

static void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);

    glViewport(0, 0, width/2, height/2);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, -3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glutWireTeapot(1);

    glViewport(width/2, 0, width/2, height/2);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glutWireTeapot(1);

    glViewport(0, height/2, width/2, height/2);
    glLoadIdentity();
    gluLookAt(0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    glutWireTeapot(1);

    glViewport(width/2, height/2, width/2, height/2);
    glLoadIdentity();
    gluLookAt(0.0, -3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    glutWireTeapot(1);

    glFlush();
}

static void reshape(int w, int h) {
    width = w;
    height = h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
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
