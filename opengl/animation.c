/*
Animation.

C11 and C++11 have a nanosecond clock, and previous versions only go down to seconds: 
http://stackoverflow.com/questions/361363/how-to-measure-time-in-milliseconds-using-ansi-c/36095407#36095407

So GLUT, `glutGet(GLUT_ELAPSED_TIME);` looks like the best option for C portability.

To make things smoother, we also need:

    glutIdleFunction();
    glutSwapBuffers();
    glutInitDisplayMode(GLUT_DOUBLE);

We always draw to the back buffer, and `glutSwapBuffers` likely only swaps once per vsync. 
Also have a look at `glfwSwapInterval(1);`.

TODO: why use glutIdleFunction() ? Why not do it directly on the `display`?
This setup seems to always lead to one idle per display.

See also:
http://gamedev.stackexchange.com/questions/8623/a-good-way-to-build-a-game-loop-in-opengl?lq=1

## FPS

- http://gamedev.stackexchange.com/questions/83159/simple-framerate-counter
- http://stackoverflow.com/questions/28530798/how-to-make-a-basic-fps-counter
- http://stackoverflow.com/questions/5627803/how-to-calculate-fps-in-opengl
- http://stackoverflow.com/questions/8779936/what-is-the-correct-way-to-calculate-the-fps-given-that-gpus-have-a-task-queue-a

Here we just count display calls, but not exaclty how many frames were rendered.
*/

#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

/* Degrees per second. */
static const GLfloat speed = 45.0f;
static GLfloat angle = 0.0f;
static int old_t;
static int debug;
static int last_func = 1;

static int fps_last_time;
static void fps() {
    int t;
    int dt;
    static int nframes = 0;
    nframes++;
    t = glutGet(GLUT_ELAPSED_TIME);
    dt = t - fps_last_time;
    if (dt > 250) {
        printf("FPS = %f\n", (nframes / (dt / 1000.0)));
        fps_last_time = t;
        nframes = 0;
    }
}

static void display(void) {
    if (debug) {
        puts("display");
        assert(last_func == 1);
        last_func = 0;
    }
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glPushMatrix();
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.0, -1.0/sqrt(3.0), 0.0);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, sqrt(3.0), 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, 0.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glEnd();
    glPopMatrix();
    glutSwapBuffers();
    fps();
}

static void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

void idle(void) {
    int t;
    if (debug) {
        puts("idle");
        assert(last_func == 0);
        last_func = 1;
    }
    t = glutGet(GLUT_ELAPSED_TIME);
    angle += speed * (t - old_t) / 1000.0;
    angle = fmod(angle, 360.0);
    old_t = t;
    glutPostRedisplay();
}

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    old_t = glutGet(GLUT_ELAPSED_TIME);
    fps_last_time = old_t;
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    if (argc > 1)
        debug = 1;
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutMainLoop();
    return EXIT_SUCCESS;
}
