/*
Many spheres bouncing inside a cube with gravity,
energy dissipation on impact, and impact between the spheres.

TODO: DRY

- up with bouncing_balls_one.cpp
- balls flicker a lot. Why?
*/

#include <cstdio>
#include <cstdlib>
#include <math.h>

#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>
#include <GL/glext.h>

#include "common.hpp"

static GLfloat eyex = 2.75;
static GLfloat eyey = 0.75;
static GLfloat eyez = 0.0;

static GLdouble eye_speed = 0.1;

static GLfloat centerx = 0.0;
static GLfloat centery = 0.0;
static GLfloat centerz = 0.0;

static GLfloat upx = 0.0;
static GLfloat upy = 1.0;
static GLfloat upz = 0.0;

static GLfloat clear_color_r = 0.0;
static GLfloat clear_color_g = 0.0;
static GLfloat clear_color_b = 0.0;

static GLfloat fast_forward = 1;
static GLfloat REST_COEF = 0.95;
static Vector3D GRAVITY = Vector3D(0.0, -0.98, 0.0);

int spheres_side = 2;
int total_spheres = spheres_side * spheres_side * spheres_side;
Sphere *spheres;
// Which spheres have collided in this round.spheres that collide stop moving
// in this round in this round, and get speeds that will separate them.
bool *collided;

static int old_t = 0; //old time in ms. used to keep real time consistent

static GLfloat vs[][3] = {
    {-1,-1,-1},
    {-1,-1,1},
    {-1,1,-1},
    {-1,1,1},
    {1,-1,-1},
    {1,-1,1},
    {1,1,-1},
    {1,1,1}
};


void init(int argc, char** argv) {
    srand ( time(NULL) );
    spheres = new Sphere[total_spheres];
    collided = new bool[total_spheres];
    int sphere_count = 0;
    for(int i=0; i<spheres_side; i++){
        for(int j=0; j<spheres_side; j++){
            for(int k=0; k<spheres_side; k++){
                float dx = i*(1.0f/spheres_side);
                float dy = j*(1.0f/spheres_side);
                float dz = k*(1.0f/spheres_side);
                float* c = new float[3];
                c[0] = dx;
                c[1] = dy;
                c[2] = dz;
                spheres[sphere_count] = Sphere(
                    Vector3D(-0.5+dx,-0.5+dy,-0.5+dz),
                    Vector3D(rand_range(-1,1),rand_range(-1,1),rand_range(-1,1)),
                    c
                );
                sphere_count++;
            }
        }
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    glClearColor(clear_color_r,clear_color_g,clear_color_b,1.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glEnable(GL_POLYGON_OFFSET_LINE);
    glEnable(GL_DEPTH_TEST);
    glPolygonOffset(1.0, 1.0);
}

void calc_new_scene(void){
    int t = glutGet(GLUT_ELAPSED_TIME);
    float dt = fast_forward*(t - old_t)/1000.0f;
    old_t = t;
    for(int i=0; i<total_spheres; i++) {
        collided[i] = false;
    }
    for(int i=0; i<total_spheres; i++) {
        Vector3D new_center = spheres[i].center + spheres[i].speed*dt;
        if( ! collided[i] ){
            if( fabs(new_center.x) > 1.0f-SPHERE_RADIUS){
                spheres[i].speed.x = -REST_COEF*spheres[i].speed.x;
                collided[i] = true;
            } else if( fabs(new_center.y) > 1.0f-SPHERE_RADIUS){
                spheres[i].speed.y = -REST_COEF*spheres[i].speed.y;
                collided[i] = true;
            } else if( fabs(new_center.z) > 1.0f-SPHERE_RADIUS){
                spheres[i].speed.z = -REST_COEF*spheres[i].speed.z;
                collided[i] = true;
            } else {
                for (int j=i+1; j<total_spheres; j++) {
                    Vector3D other_new_center = spheres[j].center + spheres[j].speed*dt;
                    if( new_center.eucl(other_new_center) < 2*SPHERE_RADIUS ){

                        float x1 = spheres[i].center.x;
                        float y1 = spheres[i].center.y;
                        float z1 = spheres[i].center.z;
                        float x2 = spheres[j].center.x;
                        float y2 = spheres[j].center.y;
                        float z2 = spheres[j].center.z;

                        float vx1 = spheres[i].speed.x;
                        float vy1 = spheres[i].speed.y;
                        float vz1 = spheres[i].speed.z;
                        float vx2 = spheres[j].speed.x;
                        float vy2 = spheres[j].speed.y;
                        float vz2 = spheres[j].speed.z;

                        int error;

                        collision3D(REST_COEF, 1., 1., SPHERE_RADIUS, SPHERE_RADIUS,
                                x1, y1,z1,
                                x2, y2, z2,
                                vx1, vy1, vz1,
                                vx2, vy2, vz2,
                                error
                                );

                        if(error == 0){

                            spheres[i].center = Vector3D(x1, y1, z1);
                            spheres[j].center = Vector3D(x2, y2, z2);
                            spheres[i].speed = Vector3D(vx1, vy1, vz1);
                            spheres[j].speed = Vector3D(vx2, vy2, vz2);

                            collided[j] = true;
                            collided[j] = true;

                        }

                    }
                }
            }
        }


        if( ! collided[i] ){
            spheres[i].center = new_center;
            spheres[i].speed = spheres[i].speed + GRAVITY*dt;
        }
    }

    glutPostRedisplay();
}

void draw_cube(){
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3fv(DARK_GRAY);

    //back
    glBegin(GL_POLYGON);
    glVertex3fv(vs[0]);
    glVertex3fv(vs[1]);
    glVertex3fv(vs[3]);
    glVertex3fv(vs[2]);
    glEnd();

    //right
    glBegin(GL_POLYGON);
    glVertex3fv(vs[0]);
    glVertex3fv(vs[2]);
    glVertex3fv(vs[6]);
    glVertex3fv(vs[4]);
    glEnd();

    //bottom
    glBegin(GL_POLYGON);
    glVertex3fv(vs[0]);
    glVertex3fv(vs[1]);
    glVertex3fv(vs[5]);
    glVertex3fv(vs[4]);
    glEnd();

    //left
    glBegin(GL_POLYGON);
    glVertex3fv(vs[1]);
    glVertex3fv(vs[3]);
    glVertex3fv(vs[7]);
    glVertex3fv(vs[5]);
    glEnd();

    //3d shapes are not primitives, so you must call them from glut (or glu)
    glColor3fv(WHITE);
    glLineWidth(2.0);
    glutWireCube(2.0);

}

void draw_spheres() {
    for( int i=0; i<total_spheres; i++){
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
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
        case 'r':
            eyex += eye_speed;
            break;
        case 'f':
            eyex -= eye_speed;
            break;
        case 'e':
            eyey += eye_speed;
            break;
        case 'd':
            eyey -= eye_speed;
            break;
        case 'w':
            eyez += eye_speed;
            break;
        case 's':
            eyez -= eye_speed;
            break;
    }
}

int main(int argc, char** argv) {
    init(argc,argv);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(calc_new_scene);
    glutKeyboardFunc(keyDown);
    glutMainLoop();
    return EXIT_SUCCESS;
}
