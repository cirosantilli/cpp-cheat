/*
For fun.
*/

#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define HOW_MANY 500

static void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

static void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(1.0f, 0.0f, 0.0f);

    for (int i = 0; i < HOW_MANY; i++) {
        for (int j = 0; j < HOW_MANY; j++) {
            glPushMatrix();
            glTranslatef(2*i, 2*j, 0);

            /* Counter clock wise. */
            glBegin(GL_TRIANGLES);
            glVertex3f( 0.0f, 1.0f, 0.0f);
            glVertex3f(-1.0f, -1.0f, 0.0f);
            glVertex3f( 1.0f, -1.0f, 0.0f);
            glEnd();

            glPopMatrix();
            glEnd();
        }
    }

    glFlush();
}

static void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, HOW_MANY + 1, -1.0, HOW_MANY + 1, -1.5, 1.5);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(0, 0);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return EXIT_SUCCESS;
}
