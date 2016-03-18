/*
Create a window. Don't draw anything to it.
*/

#include <stdlib.h>

#include <GL/glut.h>

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(200, 100);
    glutCreateWindow(argv[0]);
    glutMainLoop();
    return EXIT_SUCCESS;
}
