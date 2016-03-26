#include <GL/glut.h>
#include <vector>
#include <iostream>

using namespace std;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10, 10, -10, 10, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glScalef(5,5,5);
    glBegin(GL_QUADS);
    glColor3ub(255,0,0);
    glVertex2f(-1,-1);
    glColor3ub(0,255,0);
    glVertex2f(1,-1);
    glColor3ub(0,0,255);
    glVertex2f(1,1);
    glColor3ub(255,255,255);
    glVertex2f(-1,1);
    glEnd();

    glutSwapBuffers();
}

void mouse( int x, int y )
{
    // 4 bytes per pixel (RGBA), 1x1 bitmap
    vector< unsigned char > pixels( 1 * 1 * 4 );
    glReadPixels
        ( 
        x, glutGet( GLUT_WINDOW_HEIGHT ) - y, 
        1, 1, 
        GL_RGBA, GL_UNSIGNED_BYTE, &pixels[0] 
        );

    cout << "r: " << (int)pixels[0] << endl;
    cout << "g: " << (int)pixels[1] << endl;
    cout << "b: " << (int)pixels[2] << endl;
    cout << "a: " << (int)pixels[3] << endl;
    cout << endl;
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

    glutInitWindowSize(800,600);
    glutCreateWindow("glReadPixels()");

    glutDisplayFunc(display);
    glutPassiveMotionFunc(mouse);
    glutMainLoop();
    return 0;
}
