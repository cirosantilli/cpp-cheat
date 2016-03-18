/*
Diffuse light coming from +y infinity down falling upon identical rotated triangles.

Note that the triangles more perpendicular to the light are whiter.

Since the light comes from infinity, there is no distance attenuation,
and therefore there is a single color for each face.
*/

#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

static void draw_triangle(GLfloat angle, GLfloat x) {
    glPushMatrix();
    glRotatef(angle, -1, 0, 0);
    glTranslatef(x, 0, 0);
    glBegin(GL_TRIANGLES);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();
    glPopMatrix();
}

static void display(void) {
    glColor3f(1.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    /* Front face facing away from light, is black. */
    draw_triangle(-30.0f, -2.0f);
    /* Parallel to light, is black. */
    draw_triangle(  0.0f,  0.0f);
    /* Front face facing more and more towards the light, thus clearer. */
    draw_triangle( 30.0f,  2.0f);
    draw_triangle( 60.0f,  4.0f);
    draw_triangle( 80.0f,  6.0f);
    /* Back face forward. TODO why not black? */
    draw_triangle(120.0f,  8.0f);
    glFlush();
}

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
    glNormal3f(0.0f, 0.0f, 1.0f);
}

static void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-3.0, 9.0, -1.0, 1.0, -2.0, 2.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(900, 160);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return EXIT_SUCCESS;
}
