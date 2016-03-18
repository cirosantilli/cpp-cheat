/*
# glutBitmapCharacter

http://stackoverflow.com/questions/8847899/opengl-how-to-draw-text-using-only-opengl-methods
*/

#include <stdlib.h>
#include <string.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

static void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

static void drawString (void *font, char *s, GLfloat x, GLfloat y, GLfloat z){
    unsigned int i;
    /* Must come before glRasterPos. */
    glColor3f(0.0f, 0.0f, 1.0f);
    glRasterPos3f(x, y, z);
    for (i = 0; i < strlen(s); i++)
        glutBitmapCharacter(font, s[i]);
}

static void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f( 0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glVertex3f( 1.0f, -1.0f, 0.0f);
    glEnd();

    /* This is drawn as close as possible to the camera. */
    drawString(GLUT_BITMAP_HELVETICA_18, "bottom", -1.0, -1.0, 3.5);

    /* Depth is considered. Things that come behind are hidden. */
    drawString(GLUT_BITMAP_HELVETICA_18, "behind", 0.0, 0.0, -1.0);
    drawString(GLUT_BITMAP_HELVETICA_18, "front", 0.0, 0.5, 1.0);

    /* The font size is fixed no matter how far back we are.*/
    drawString(GLUT_BITMAP_HELVETICA_18, "far", 200.0, 200.0, -990.0);

    glFlush();
}

static void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return EXIT_SUCCESS;
}
