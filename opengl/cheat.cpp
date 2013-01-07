#include <GL/glut.h> // includes both opengl (gl.h, rendering) and glu (glu.h, opengl utilities), besides glut.h (windowing, input/output)

#include <stdlib.h>
#include <iostream>
#include <stdio.h>

#include <math.h>

//TODO understand
  //swap_the_buffers() TODO understand
  //glutSwapBuffers();
  //glutIdleFunc(spinDisplay); //called after render is done, typically to recalculate positions for the next frame

GLint WINDOW_W = 700;
GLint WINDOW_H = 700; 
GLint WINDOW_POSX = 10;
GLint WINDOW_POSY = 10; 
 
GLfloat WHITE[] = {1.0, 1.0, 1.0};
GLfloat GRAY[] = {.5, .5, .5};
GLfloat BLACK[] = {0.0, 0.0, 0.0};
GLfloat RED[] = {1.0, 0.0, 0.0};
GLfloat GREEN[] = {0.0, 1.0, 0.0};
GLfloat BLUE[] = {0.0, 0.0, 1.0};

GLdouble eyex=2.0;
GLdouble eyey=2.0;
GLdouble eyez=2.0;
GLdouble eye_speed=0.1;
GLdouble centerx=0.0;
GLdouble centery=0.0;
GLdouble centerz=0.0;
GLdouble upx=0.0;
GLdouble upy=1.0;
GLdouble upz=0.0;

GLdouble clear_color_r = 0.0;
GLdouble clear_color_g = 0.0;
GLdouble clear_color_b = 0.0;

GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = { 50.0 };
GLfloat light_position[] = { 2.0, 2.0, 2.0, 0.0 };

GLfloat PERSON_R = 1.f; //radius for collision detection
GLfloat frustrum_min = 0.95*PERSON_R; //so that won't see across walls
GLfloat frustrum_max = 100.0;
GLfloat frustrum_l = 2*PERSON_R*0.9;

class Drawable{

  public:

    virtual void draw(void){};

};

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

    GLfloat* toArray(){
      GLfloat out[] = {x, y, z};
      return out;
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
    std::string str(){
      char out[64];
      sprintf(out, "%4.2f\n%4.2f\n%4.2f\n", x, y, z);
      return std::string(out);
    }

};

class Sphere : public Drawable {

  static const GLfloat SPHERE_RADIUS = 0.2;
  static const GLint SPHERE_SLICES = 10;
  static const GLint SPHERE_STACKS = 10;

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

enum ndrawables{ndrawables=1};
Drawable* drawables;

/*Stuff that is only set once for all.*/
void init(int argc, char** argv) 
{

  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  //GLUT_DOUBLE vs GLUT_SINGLE wait to change frames when the second is read, necessary for heavy animations.
  //GLUT_RGB vs indexed color: instead of using 8bit per channel, choose 256 colors that represent well an image, and use 1byte for each pixel.
  //  http://en.wikipedia.org/wiki/Indexed_color
  //GLUT_DEPTH depth buffering: calculate pixels for each plane and their distances,
    //keep only closest one, cheapest way to hide parts of objects that go behind others.

  //window
    glutInitWindowSize(WINDOW_W, WINDOW_H); 
    glutInitWindowPosition(WINDOW_POSX, WINDOW_POSY);
    glutCreateWindow(argv[0]);

  //clear the screen after each image
    glClearColor(clear_color_r,clear_color_g,clear_color_b,1.0);

  glEnable(GL_DEPTH_TEST);
  //glEnable(GL_POLYGON_OFFSET_FILL);
  //glEnable(GL_POLYGON_OFFSET_LINE);
  glPolygonOffset(1.0, 1.0); 

  //which side of objcts to take into account
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //glPolygonMode(GL_FRONT, GL_FILL);
    //glPolygonMode(GL_BACK, GL_FILL);

  //fill solids or not
    //glPolygonMode(GL_FRONT, GL_LINE); //only lines will be drawn
    //glPolygonMode(GL_FRONT, GL_FILL); //will fill the solids

  //lights
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position); 
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHT1);
        //... up to 8 lights
    //glLight*() //set light color. default is white

    //glShadeModel(GL_FLAT);
    glShadeModel(GL_SMOOTH);
 
  //create drawable objects to model initial scene
    drawables = new Drawable[ndrawables];
    drawables[0] = Sphere( Vector3D(-0.5,0.75,0.0), Vector3D( 0.1, 0.0, 0.0), GREEN );
    //drawables[1] = Sphere( Vector3D(-0.5,0.75,0.0), Vector3D( 0.1, 0.0, 0.0), GREEN );
}

int old_t = 0; //old time in ms. used to keep real time consistent

/*calculates the parameters of the new scene and calls display again*/
void calc_new_scene(void){

  Vector3D dx, new_center;
  float dt;
  int t;

  //cout << "===========================\n";
  //cout << "center\n" << center.str(2) << endl;
  //cout << "eye\n" << eye.str(2) << endl;
  //cout << "speed\n" << speed << endl;
  //cout << "rot_speed\n" << rot_speed << "\n\n";

  //keep animation's real time consistent
    t = glutGet(GLUT_ELAPSED_TIME);
    dt = fast_forward*(t - old_t)/1000.0f;
    old_t = t;

  //calculate new scene based on dt (s)

  //speed movement method
    eye.rotY( rot_speed*dt );
    new_center = center + eye*speed*dt;

  glutPostRedisplay();
}

void draw_scene(void){

  glLoadIdentity(); // reset everything before starting

  gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);

  //glColor3f(0.0, 0.0, 1.0);

  //you can format those primitives with:
    //void glPointSize(GLfloat size);
    //void glLineWidth(GLfloat width); 
    //void glLineStipple(GLint factor, GLushort pattern); 
      //pattern=0x3F07 (translates to 0011111100000111 in binary), a line would be drawn with 3 pixels on, then 5 off, 6 on, and 2 off
      //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default mode
      //GL_FRONT, GL_BACK
      //GL_FILL, GL_LINE, GL_POINT
      //void glFrontFace(GLenum mode)

  glPushMatrix(); // before transforming save the old matrix

    //geometric transformations
        //glMultMatrixf(N);
        //glScalef(1.0, 1.0, 1.0);
        //glRotatef(90., 1., 0., 0.);
        glTranslatef(.5, .5, 0.5);

    //polygons are primitives, and thus dealt by opengl
        //glBegin(GL_POLYGON);
            //glVertex3f (0.25, 0.25, 0.0);
            //glVertex3f (0.75, 0.25, 0.0);
            //glVertex3f (0.75, 0.75, 0.0);
            //glVertex3f (0.25, 0.75, 0.0);
        //glEnd(); 
        
        //other types of basic shapes:
        //GL_POINTS
        //GL_LINES
        //GL_LINE_STRIP
        //GL_LINE_LOOP
        //GL_TRIANGLES
        //GL_TRIANGLE_STRIP
        //GL_TRIANGLE_FAN
        //GL_QUADS
        //GL_QUAD_STRIP
        //POLYGON
        //glVertex*()
      
    //the following are also allowed betwen glBegin and glEnd
      //glColor*()
      //glIndex*()
      //glNormal*()
      //glTexCoord*()
      //glEdgeFlag*()
      //glMaterial*()
      //glArrayElement()
      //glEvalCoord*(), glEvalPoint*()
      //glCallList(), glCallLists()

    //3d shapes are not primitives, so you must call them from glut (or glu)
        //glutWireCube(1.0);
        //glutSolidCube(1.0);
        //glutWireSphere(1.0, 20, 20); 
        //glutSolidSphere(1.0, 20, 20); 
        //glutSolidTeapot(1.0);
        //glutWireTeapot(1.0);

        //glut can also draw (wire/solid):
            //cone
            //icosahedron
            //octahedron
            //tetrahedron
            //dodecahedron
            //torus 
            //teapot

  glPopMatrix(); //after drawing, reload the old transform

  for(int i=0; i<ndrawables; i++){
    drawables[i].draw();
  }

}

void display(void)
{

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
  // TODO understand DEPTH_BUFFEr

  draw_scene();

  //glFlush(); //send all commands even if output is not read. (parallel processing, network)
  glutSwapBuffers(); //also flushes first

}

void reshape(int w, int h)
{
   glViewport(0, 0,(GLsizei) w,(GLsizei) h); 
   glMatrixMode(GL_PROJECTION);
   //glMatrixMode(GL_ORTHO);
   glLoadIdentity();
   glFrustum(-frustrum_l, frustrum_l, -frustrum_l, frustrum_l, frustrum_min, frustrum_max); //this is what can be seen
   glMatrixMode(GL_MODELVIEW); //needed for transformations TODO
}

//move models
    //fixed displacement (fixed steps)
    //fixed speed (displacement is proportional to elapsed time)
    //fixed acceleration (displacement acceleration is proportional to elapsed time)
        //can have max speed or not

//fixed displacement
    void keyDown(unsigned char key, int x, int y)
    {
        switch(key)
        {
            case 's':
                eyez -= eye_speed;
                break;
            case 'w':
                eyez += eye_speed;
                break;
            case 27: //esc
                //quit
                exit(0);
                break;
        }
    }

//fixed speed
    //position will be calculated as function of elapsed time in calc_new_scene()
    void keyDownSpeed(unsigned char key, int x, int y)
    {
        switch(key)
        {
            case 'a':
                //rotate left
                rot_speed = -ROT_SPEED_MAX;
                break;
            case 'd':
                //rotate right
                rot_speed = ROT_SPEED_MAX;
                break;
            case 'e':
                //run faster
                speed *= 2.f;
                break;
            case 's':
                //backwards 
                speed = -SPEED_MAX;
                break;
            case 'w':
                //forwards
                speed = SPEED_MAX;
                break;
            case 27: //esc
                //quit
                exit(EXIT_SUCCESS);
                break;
        }
    }

    void keyUpSpeed(unsigned char key, int x, int y)
    {
        switch(key)
        {
            case 'a':
                rot_speed = 0.f;
                break;
            case 'd':
                rot_speed = 0.f;
                break;
            case 'e':
                speed /= 2.f;
                break;
            case 's':
                speed = 0.f;
                break;
            case 'w':
                speed = 0.f;
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
  glutKeyboardUpFunc(keyUp);
  glutMainLoop();
  //THIS IS NEVER REACHED
 
  return 0;
}
