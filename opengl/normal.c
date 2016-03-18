/*
# glNormal

http://stackoverflow.com/questions/5906993/what-is-a-normal-in-opengl/36087311#36087311
http://gamedev.stackexchange.com/questions/50653/opengl-why-do-i-have-to-set-a-normal-with-glnormal/118476#118476
*/

#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

/* Triangle on the x-y plane. */
static void draw_triangle() {
    glBegin(GL_TRIANGLES);
    glVertex3f( 0.0f,  1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glVertex3f( 1.0f, -1.0f, 0.0f);
    glEnd();
}

/* A triangle tilted 45 degrees manually. */
static void draw_triangle_45() {
    glBegin(GL_TRIANGLES);
    glVertex3f( 0.0f,  1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f,  0.0f);
    glVertex3f( 1.0f, -1.0f,  0.0f);
    glEnd();
}

static void display(void) {
    glColor3f(1.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    /*
    Triangle perpendicular to the light.
    0,0,1 also happens to be the default normal if we hadn't specified one.
    */
    glNormal3f(0.0f, 0.0f, 1.0f);
    draw_triangle();

    /*
    This triangle is as bright as the previous one.
    This is not photorealistic, where it should be less bright.
    */
    glTranslatef(2.0f, 0.0f, 0.0f);
    draw_triangle_45();

    /*
    Same as previous triangle, but with the normal set
    to the photorealistic value of 45, making it less bright.
    */
    glTranslatef(2.0f, 0.0f, 0.0f);
    glNormal3f(0.0f, 1.0f, 1.0f);
    draw_triangle_45();

    /*
    This triangle is rotated 45 degrees with a glRotate.
    It should be as bright as the previous one,
    even though we set the normal to 0,0,1.
    So glRotate also affects the normal!
    */
    glTranslatef(2.0f, 0.0f, 0.0f);
    glNormal3f(0.0, 0.0, 1.0);
    glRotatef(45.0, -1.0, 0.0, 0.0);
    draw_triangle();

    glPopMatrix();
    glFlush();
}

static void init(void) {
    GLfloat light0_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    /* Plane wave coming from +z infinity. */
    GLfloat light0_position[] = {0.0, 0.0, 1.0, 0.0};
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

static void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 7.0, -1.0, 1.0, -1.5, 1.5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 200);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return EXIT_SUCCESS;
}
