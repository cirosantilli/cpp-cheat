/*
One sphere bouncing inside a cube with gravity
and energy dissipation on impact.
*/

#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <math.h>

#include "common.hpp"

static GLfloat eyex = 2.75;
static GLfloat eyey = 0.75;
static GLfloat eyez = 0.0;

static GLfloat centerx = 0.0;
static GLfloat centery = 0.0;
static GLfloat centerz = 0.0;

static GLfloat upx = 0.0;
static GLfloat upy = 1.0;
static GLfloat upz = 0.0;

static GLfloat clear_color_r = 0.0;
static GLfloat clear_color_g = 0.0;
static GLfloat clear_color_b = 0.0;

static int old_t = 0;

// How much faster than reality the video is. 2.0 means
// the video will appear 2x as fast as reality.
static GLfloat fast_forward = 2.0;
static GLfloat REST_COEF = 0.95;
// Working unit is 10m.
static Vector3D GRAVITY = Vector3D(0.0, -0.98, 0.0);

static int total_spheres = 1;
static Sphere spheres[1] = {
    Sphere(
        Vector3D(0.0, 0.75, 0.0),
        Vector3D(rand_range(-1, 1), rand_range(-1, 1), rand_range(-1, 1)),
        GREEN
    ),
};

static GLfloat vs[][3] = {
    {-1,-1,-1},
    {-1,-1,1},
    {-1,1,-1},
    {-1,1,1},
    {1,-1,-1},
    {1,-1,1},
    {1,1,-1},
    {1,1,1},
};

void calc_new_scene(void) {
    // Keep animation's real time consistent.
    int t = glutGet(GLUT_ELAPSED_TIME);
    float dt = fast_forward*(t - old_t)/1000.0f;
    old_t = t;

    // Calculate new scene based on dt (ms).
    for (int i = 0; i < total_spheres; ++i){

        //cout << "\n---------------------------\n";
        //cout << "center\n" << spheres[i].center.str() << "\n";
        //cout << "speed\n" << spheres[i].speed.str() << "\n";
        //cout << "dt " << dt << "\n";

        Vector3D new_center = spheres[i].center + spheres[i].speed*dt;

        if( fabs(new_center.x) > 1.0f-SPHERE_RADIUS){
            spheres[i].speed.x = -REST_COEF*spheres[i].speed.x;
        } else if( fabs(new_center.y) > 1.0f-SPHERE_RADIUS){
            spheres[i].speed.y = -REST_COEF*spheres[i].speed.y;
        } else if( fabs(new_center.z) > 1.0f-SPHERE_RADIUS){
            spheres[i].speed.z = -REST_COEF*spheres[i].speed.z;
        } else{//move and normal update
            spheres[i].center = new_center;
            spheres[i].speed = spheres[i].speed + GRAVITY*dt;
        }
    }
    glutPostRedisplay();
}

void draw_cube(){
    glColor3fv(DARK_GRAY);

    // back
    glBegin(GL_POLYGON);
    glVertex3fv(vs[0]);
    glVertex3fv(vs[1]);
    glVertex3fv(vs[3]);
    glVertex3fv(vs[2]);
    glEnd();

    // right
    glBegin(GL_POLYGON);
    glVertex3fv(vs[0]);
    glVertex3fv(vs[2]);
    glVertex3fv(vs[6]);
    glVertex3fv(vs[4]);
    glEnd();

    // bottom
    glBegin(GL_POLYGON);
    glVertex3fv(vs[0]);
    glVertex3fv(vs[1]);
    glVertex3fv(vs[5]);
    glVertex3fv(vs[4]);
    glEnd();

    // left
    glBegin(GL_POLYGON);
    glVertex3fv(vs[1]);
    glVertex3fv(vs[3]);
    glVertex3fv(vs[7]);
    glVertex3fv(vs[5]);
    glEnd();

    // 3d shapes are not primitives, so you must call them from glut (or glu)
    glColor3fv(WHITE);
    glLineWidth(2.0);
    glutWireCube(2.0);
}

void draw_spheres() {
    for (int i=0; i<total_spheres; i++){
        spheres[i].draw();
    }
}

void draw_scene(void) {
    glLoadIdentity();
    gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);
    draw_cube();
    draw_spheres();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw_scene();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0,(GLsizei) w,(GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyDown(unsigned char key, int x, int y) {
    switch(key){
        case 27:
            exit(0);
            break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    glClearColor(clear_color_r, clear_color_g, clear_color_b, 1.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glEnable(GL_POLYGON_OFFSET_LINE);
    glEnable(GL_DEPTH_TEST);
    glPolygonOffset(1.0, 1.0);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(calc_new_scene);
    glutKeyboardFunc(keyDown);
    glutMainLoop();
    return EXIT_SUCCESS;
}
