/*
# glDrawPixels

TODO not working. Problem is the glRasterPos2i I think.
A few blue points appear on screen, but not a continuous line.
Is it using world coordinates instead of window x / y points?

Heard people talking about glWindowPos
https://www.opengl.org/sdk/docs/man2/xhtml/glWindowPos.xml
but that function is not defined for me...

- http://stackoverflow.com/questions/20056174/gldrawpixel-rgb-value-from-a-array
- https://www.quora.com/OpenGL-How-can-I-use-glDrawPixels-correctly
- http://stackoverflow.com/questions/12072799/an-alternative-to-gldrawpixels-in-opengl-3-0
*/

#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define WIDTH 500

static void display(void) {
    unsigned i;
    GLfloat blue_pixel[] = {0.0f, 0.0f, 1.0f};
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f( 0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glVertex3f( 1.0f, -1.0f, 0.0f);
    glEnd();
    for (i = 0; i < WIDTH; ++i) {
        glRasterPos2f(i, i);
        glDrawPixels(1, 1, GL_RGB, GL_FLOAT, blue_pixel);
    }
    glFlush();
}

static void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -1.5, 1.5);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, WIDTH);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return EXIT_SUCCESS;
}
