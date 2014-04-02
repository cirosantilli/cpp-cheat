#include <GL/glut.h> // includes both opengl (gl.h, rendering) and glu (glu.h, opengl utilities), besides glut.h (windowing, input/output)
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;

GLfloat SPHERE_RADIUS = 0.1;
GLint SPHERE_SLICES = 5;
GLint SPHERE_STACKS = 5;

GLfloat WHITE[] = {1.0, 1.0, 1.0};
GLfloat GRAY[] = {.5, .5, .5};
GLfloat DARK_GRAY[] = {.15, .15, .15};
GLfloat BLACK[] = {0.0, 0.0, 0.0};
GLfloat RED[] = {1.0, 0.0, 0.0};
GLfloat GREEN[] = {0.0, 1.0, 0.0};
GLfloat BLUE[] = {0.0, 0.0, 1.0};

GLfloat eyex=2.75;
//GLfloat eyex=5.0;
GLfloat eyey=.75;
GLfloat eyez=0.0;

GLfloat centerx=0.0;
GLfloat centery=0.0;
GLfloat centerz=0.0;

GLfloat upx=0.0;
GLfloat upy=1.0;
GLfloat upz=0.0;

GLfloat clear_color_r = 0.0;
GLfloat clear_color_g = 0.0;
GLfloat clear_color_b = 0.0;


//multiple sphere simulation
float rand_range(float a, float b)
{
  return ((b-a)*((float)rand()/RAND_MAX))+a;
}

class Vector3D{

  public:

    GLfloat x;
    GLfloat y;
    GLfloat z;

    Vector3D(){
      this->x = 0.0;
      this->y = 0.0;
      this->z = 0.0;
    }

    Vector3D(GLfloat x, GLfloat y, GLfloat z){
      this->x = x;
      this->y = y;
      this->z = z;
    }

    //vector sum
    Vector3D operator+(Vector3D otherv){
      return Vector3D( this->x + otherv.x, this->y + otherv.y, this->z + otherv.z);
    }

    //vector subtraction
    Vector3D operator-(Vector3D otherv){
      return Vector3D( this->x - otherv.x, this->y - otherv.y, this->z - otherv.z);
    }

    //multiplication by constant
    Vector3D operator*(GLfloat a){
      return Vector3D( this->x * a, this->y * a, this->z * a);
    }

    //division by constant
    Vector3D operator/(GLfloat a){
      return Vector3D( this->x / a, this->y / a, this->z / a);
    }

    //dot product
    GLfloat dot(Vector3D otherv){
      return this->x * otherv.x + this->y * otherv.y + this->z * otherv.z;
    }

    //returns the euclidean norm of this vector
    GLfloat norm(){
      return sqrt( this->dot(*this) );
    }

    //returns the taxi norm of this vector (largest absolute value of a corrdinate)
    GLfloat taxi_norm(){
      //return max(abs(x), abs(y), abs(z));
      return 0.0;
    }

    //returns a unit vector in the same direction as this vector
    Vector3D unit(){
      return (*this) / this->norm();
    }

    //euclidean distance
    GLfloat eucl(Vector3D other){
      return (*this - other).norm();
    }

    /* To a string */
    string str(){
      char out[64];
      sprintf(out, "%4.2f\n%4.2f\n%4.2f\n", x, y, z);
      return std::string(out);
    }

};

class Sphere{

  public:

    Vector3D center;
    Vector3D speed;
    GLfloat* color;

    /*default constructor*/
    Sphere(){
      this->center = Vector3D();
      this->speed = Vector3D();
      this->color = new GLfloat[3];
      this->color[0] = 0.0;
      this->color[1] = 0.0;
      this->color[2] = 0.0;
    }

    Sphere(Vector3D center, Vector3D speed, GLfloat color[]){
      this->center = center;
      this->speed = speed;
      this->color = new GLfloat[3];
      this->color[0] = color[0];
      this->color[1] = color[1];
      this->color[2] = color[2];
    }

    /*draws the sphere*/
    void draw(){

      glPushMatrix();

        glTranslatef( center.x, center.y, center.z );

        glLineWidth(1.0);
        glColor3fv(BLACK);
        glutWireSphere(SPHERE_RADIUS, SPHERE_SLICES, SPHERE_STACKS);

        glColor3fv(color);
        glutSolidSphere(SPHERE_RADIUS, SPHERE_SLICES, SPHERE_STACKS);

      glPopMatrix();

    }

};

GLfloat fast_forward = 2.0; //how much faster than reality the video is. 2.0 means the video will appear 2x as fast as reality
GLfloat REST_COEF = 0.95;
Vector3D GRAVITY = Vector3D(0.0, -0.98, 0.0); //working unit is 10m

//single sphere simulation
int total_spheres = 1;
Sphere spheres[1] = {
    Sphere( Vector3D(0.,0.75,0.), Vector3D(rand_range(-1,1),rand_range(-1,1),rand_range(-1,1)), GREEN ),
};

//multiple
//int spheres_side = 3;
//int total_spheres = spheres_side * spheres_side * spheres_side;
//Sphere* spheres;
//bool* collided_other; //which spheres have collided in this round.spheres that collide stop moving in this round in this round, and get speeds that will separate them.

/*Stuff that is only set once for all.*/
void init(int argc, char** argv)
{


  //multiple spheres
  //srand ( time(NULL) );
  //spheres = new Sphere[total_spheres];
  //collided_other = new bool[total_spheres];
  //int sphere_count = 0;
  //for(int i=0; i<spheres_side; i++){
    //for(int j=0; j<spheres_side; j++){
      //for(int k=0; k<spheres_side; k++){
        //float dx = i*(1.0f/spheres_side);
        //float dy = j*(1.0f/spheres_side);
        //float dz = k*(1.0f/spheres_side);
        //float* c = new float[3];
        //c[0] = dx;
        //c[1] = dy;
        //c[2] = dz;
        //spheres[sphere_count] = Sphere(
            //Vector3D(-0.5+dx,-0.5+dy,-0.5+dz),
            //Vector3D(rand_range(-1,1),rand_range(-1,1),rand_range(-1,1)),
            //c
          //);
        //sphere_count++;
      //}
    //}
  //}

  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);

  glutCreateWindow(argv[0]);
  //clear the screen after each image
  glClearColor(clear_color_r,clear_color_g,clear_color_b,1.0);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default mode

  glEnable(GL_POLYGON_OFFSET_FILL);
  glEnable(GL_POLYGON_OFFSET_LINE);
  glEnable(GL_DEPTH_TEST);
  glPolygonOffset(1.0, 1.0);
}

int old_t = 0; //old time in ms. used to keep real time consistent

/*calculates new scene and call display again after it is done*/
void calc_new_scene(void){

  //keep animation's real time consistent
  int t = glutGet(GLUT_ELAPSED_TIME);
  float dt = fast_forward*(t - old_t)/1000.0f;
  old_t = t;

  //calculate new scene based on dt (ms)

  for( int i=0; i<total_spheres; i++){

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


/* cube corners */
GLfloat vs[][3] = {
  {-1,-1,-1},
  {-1,-1,1},
  {-1,1,-1},
  {-1,1,1},
  {1,-1,-1},
  {1,-1,1},
  {1,1,-1},
  {1,1,1},
};

void draw_cube(){

  glPushMatrix();

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

  glPopMatrix();

}

void draw_spheres(){

  for( int i=0; i<total_spheres; i++){
    spheres[i].draw();
  }

}

void draw_scene(void){

  glLoadIdentity();
  gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);

  draw_cube();
  draw_spheres();

}

void display(void)
{

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer

  draw_scene();

  glutSwapBuffers(); //also flushes first

}

void reshape(int w, int h)
{
   glViewport(0, 0,(GLsizei) w,(GLsizei) h);

   glMatrixMode(GL_PROJECTION);

   glLoadIdentity();

   glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);

   glMatrixMode(GL_MODELVIEW);
}

void keyDown(unsigned char key, int x, int y)
{
   switch(key){
      case 27:
         exit(0);
         break;
   }
}

int main(int argc, char** argv)
{

  init(argc,argv);

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);

  glutIdleFunc(calc_new_scene); //called after render is done, typically to recalculate positions for the next frame

  glutKeyboardFunc(keyDown);
  glutMainLoop();

  return 0;
}
