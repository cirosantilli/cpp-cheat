#include <glut.h> // includes both opengl (gl.h, rendering) and glu (glu.h, opengl utilities), besides glut.h (windowing, input/output)

#include <stdlib.h>
#include <iostream>
#include <stdio.h>

#include <math.h>

#include "vec3.h"

using namespace std;

//some colors constants
    const GLfloat white[] = {1.0, 1.0, 1.0};
    const GLfloat gray[] = {.5, .5, .5};
    const GLfloat black[] = {0.0, 0.0, 0.0};
    const GLfloat red[] = {1.0, 0.0, 0.0};
    const GLfloat green[] = {0.0, 1.0, 0.0};
    const GLfloat blue[] = {0.0, 0.0, 1.0};


//TODO understand
  //swap_the_buffers() TODO understand
  //glutSwapBuffers();
  //glutIdleFunc(spinDisplay); //called after render is done, typically to recalculate positions for the next frame

//not to see cross walls
    //GLfloat frustrumNear = 0.95*personR; //so that won't see across walls
    //GLfloat frustrumFar = 100.0;
    //GLfloat frustrumL = 2*personR*0.9;

class Drawable
{
    public:

        virtual void draw() = 0;
};

template <class T=float>
class Sphere : public Drawable {

    public:

        Vec3<T> pos;         
        Vec3<T> speed;       
        GLfloat color[3];

        T rad;
        int slices;
        int stacks;

        Sphere()
        :
            pos(Vec3<>()),
            rad(1.0),
            slices(20),
            stacks(20),
            speed(Vec3<>())
        {
            color[0] = 1.0;
            color[1] = 1.0;
            color[2] = 1.0;
        }

        Sphere
        (
            Vec3<> pos,
            T rad = 1.0,
            int slices = 20,
            int stacks = 20,
            const GLfloat* color = white,
            Vec3<> speed = Vec3<>()
        )
        :
            pos(pos),
            rad(rad),
            slices(slices),
            stacks(stacks),
            speed(speed)
        {
            this->color[0] = color[0];
            this->color[1] = color[1];
            this->color[2] = color[2];
        }

        void draw(){
        
            glPushMatrix();

                glTranslatef( pos.x, pos.y, pos.z );

                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color);
                
                //glLineWidth(1.0); 
                //glutWireSphere(rad, slices, stacks);
 
                glutSolidSphere(rad, slices, stacks);

            glPopMatrix();

        }

};

//view parameters
template <class T=float>
class Camera
{
    public:

        Camera()
        :
            pos(Vec3<T>(0.0, 0.0, 0.0)),
            dir(Vec3<T>(1.0, 0.0, 0.0)),
            up(Vec3<T>(0.0, 1.0, 0.0f)),
            frustrumNear(1.0),
            frustrumFar(100.0),
            frustrumL(1.0),
            resX(700),
            resY(700)
        {
        }

        Camera
        (
            Vec3<T> pos, //position of the camera
            Vec3<T> dir, //direction of viewing
            Vec3<T> up = Vec3<T>(0.0, 1.0, 0.0f),
            T frustrumNear = 1.0,
            T frustrumFar = 100.0,
            T frustrumL = 1.0,
            int resX = 700,
            int resY = 700
        )
        :
            pos(pos),
            dir(dir),
            up(up),
            frustrumNear(frustrumNear),
            frustrumFar(frustrumFar),
            frustrumL(frustrumL),
            resX(resX),
            resY(resY)
        {
        }

        Vec3<T> getLookat(){ return pos+dir; }

        Vec3<T> pos;
        Vec3<T> dir;
        Vec3<T> up;

        GLfloat frustrumNear;
        GLfloat frustrumFar;
        GLfloat frustrumL;

        int resX;
        int resY;
};

//window
    GLint windowW = 700;
    GLint windowH = 700; 
    GLint windowPosX = 10;
    GLint windowPosY = 10; 

    GLdouble clearColorR = 0.0;
    GLdouble clearColorG = 0.0;
    GLdouble clearColorB = 0.0;

    int oldT;  //used to keep real time consistent

//light
    GLfloat lightPos[] = { 2.0, 2.0, 2.0 };

//scenario
    const GLfloat* mat_ambient = red;
    const GLfloat* mat_diffuse = white;
    const GLfloat* mat_specular = white;
    const GLfloat* mat_emission = white;
    const GLfloat mat_shininess[] = { 50.0 };

    const int nDrawables = 1;
    Drawable* drawables[nDrawables];
    const int nSpheres = 1;
    Sphere<> spheres[nSpheres];

//camera
    //create a camera
    Camera<> camera = Camera<>
    (
        Vec3<>(0.0,0.0,-2.0),
        Vec3<>(0.0,0.0,1.0)
    );

//physical viewer params
    float fast_forward = 1.f;
    GLfloat personR = 1.f; //radius for collision detection

    //wait for input mode
    GLfloat dirStep = 2.f;     //speed forward
    GLfloat dirRotStep = 2.f;     //speed forward

    //don't wait for input
    GLfloat speedMax = 2.f;      //trsnalation speed
    GLfloat rotSpeedMax = 0.0f;  //rotation speed in rad/s
    Vec3<> speed;  //translation speed in rad/s
    Vec3<> rotSpeed;  //rotation speed in rad/s. right hand rule

//stuff set only once at beginning
void init(int argc, char** argv) 
{

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    //GLUT_DOUBLE vs GLUT_SINGLE wait to change frames when the second is read, necessary for heavy animations.
    //GLUT_RGB vs indexed color: instead of using 8bit per channel, choose 256 colors that represent well an image, and use 1byte for each pixel.
    //  http://en.wikipedia.org/wiki/Indexed_color
    //GLUT_DEPTH depth buffering: calculate pixels for each plane and their distances,
        //keep only closest one, cheapest way to hide parts of objects that go behind others.

    //window
        glutInitWindowSize(windowW, windowH); 
        glutInitWindowPosition(windowPosX, windowPosY);
        glutCreateWindow(argv[0]);

    //clear the screen after each image
        glClearColor(clearColorR,clearColorG,clearColorB,1.0);

    glEnable(GL_DEPTH_TEST); //TODO ?

    glEnable(GL_POLYGON_OFFSET_FILL); //TODO ?
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
        glEnable(GL_LIGHTING);

        //glLightModelfv
            //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, white); //ambient light
            //glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE); //TODO ?
            //glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE); //light both sides

        //glShadeModel(GL_FLAT);
        glShadeModel(GL_SMOOTH);

        //light0
            glEnable(GL_LIGHT0);
            glLightfv(GL_LIGHT0, GL_POSITION, lightPos); 
            glLightfv(GL_LIGHT0, GL_AMBIENT, white);
            glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
            glLightfv(GL_LIGHT0, GL_SPECULAR, white);

            //attenuation
                //\frac{1}{k+ld+qd^2}
                //glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 2.0);
                //glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1.0);
                //glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.5);
 
        //glEnable(GL_LIGHT1);
            //... up to 8 lights

    //two ways to define materials
 
        //gl_color_material and glmaterialfv


        //GL_COLOR_MATERIAL
            //glEnable(GL_COLOR_MATERIAL);
            //glColorMaterial(GL_FRONT, GL_DIFFUSE);
            //// now glColor* changes diffuse reflection 
            //glColor3f(0.2, 0.5, 0.8);
            //// draw some objects here
            //glColorMaterial(GL_FRONT, GL_SPECULAR);
            //// glColor* no longer changes diffuse reflection
            //// now glColor* changes specular reflection
            //glColor3f(0.9, 0.0, 0.2);
            //// draw other objects here */
            //glDisable(GL_COLOR_MATERIAL); 

        //glMaterialfv
            //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
            //glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
            //glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
            //glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission);
            //glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

    //create drawable objects to model initial scene
        spheres[0] = Sphere<>( Vec3<>(0.0,0.0,0.0), 1.0, 20, 20, red );
        //spheres[1] = Sphere( Vec3<>(-0.5,0.75,0.0), Vec3<>( 0.1, 0.0, 0.0), green );
        int total=0;
        for (int i=total; i<nSpheres; i++)
        {
            drawables[i] = &spheres[i];
        }

    oldT = glutGet(GLUT_ELAPSED_TIME); //init old time in ms.

}

/*calculates the parameters of the new scene and calls display again*/
void calcNewScene(void)
{
    Vec3<> dx, newpos;
    float dt;
    int t;

    //cout << "===========================\n";
    //cout << "pos" << endl << camera.pos.str();
    //cout << "dir" << endl << camera.dir.str();
    //cout << endl;
    //cout << "speed\n" << speed;
    //cout << "rotSpeed\n" << rotSpeed;

    //keep animation real time consistent
        t = glutGet(GLUT_ELAPSED_TIME);
        dt = fast_forward*(t - oldT)/1000.0f;
        oldT = t;

    //speed nonstop movement method
        //camera.dir.rotY( rotSpeed*dt );
        newpos = camera.pos + speed*dt;

    glutPostRedisplay();
}

void drawScene(void)
{

    glLoadIdentity(); // reset everything before starting

    Vec3<> lookat = camera.getLookat();

    gluLookAt
    (
        camera.pos.x,
        camera.pos.y,
        camera.pos.z,
        lookat.x,
        lookat.y,
        lookat.z,
        camera.up.x,
        camera.up.y,
        camera.up.z
    );

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
        //glTranslatef(.5, .5, 0.5);

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
            //glColor*;
            //glIndex*
            //glNormal*
            //glTexCoord*
            //glEdgeFlag*
            //glMaterial*
            //glArrayElement
            //glEvalCoord*, glEvalPoint*
            //glCallList, glCallLists

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

    for(int i=0; i<nDrawables; i++)
    {
        drawables[i]->draw();
    }

}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
    // TODO ? DEPTH_BUFFER

    drawScene();

    //glFlush(); //send all commands even if output is not read. (parallel processing, network)
    glutSwapBuffers(); //also flushes first

}

void reshape(int w, int h)
{

    glViewport(0, 0,(GLsizei) w,(GLsizei) h); 

    glMatrixMode(GL_PROJECTION); //normal 3d vision
    //glMatrixMode(GL_ORTHO); //2d like projection vision

    glLoadIdentity();
    glFrustum
    (
        -camera.frustrumL,
        camera.frustrumL,
        -camera.frustrumL,
        camera.frustrumL,
        camera.frustrumNear,
        camera.frustrumFar
    ); //this is what can be seen from the camera

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
                camera.dir.z -= dirStep;
                break;
            case 'w':
                camera.dir.z += dirStep;
                break;
            case 27: //esc
                //quit
                exit(0);
                break;
        }
    }

//fixed speed
    //position will be calculated as function of elapsed time in calcNewScene()
    void keyDownSpeed(unsigned char key, int x, int y)
    {
        switch(key)
        {
            case 'a':
                //rotate left
                //rotSpeed = -rotSpeedMax;
                break;
            case 'd':
                //rotate right
                //rotSpeed = rotSpeedMax;
                break;
            case 'e':
                //run faster
                //speed *= 2.f;
                break;
            case 's':
                //backwards 
                //speed = -dirSpeedMax;
                break;
            case 'w':
                //forwards
                //speed = dirSpeedMax;
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
                //rotSpeed = 0.f;
                break;
            case 'd':
                //rotSpeed = 0.f;
                break;
            case 'e':
                //speed /= 2.f;
                break;
            case 's':
                //speed = 0.f;
                break;
            case 'w':
                //speed = 0.f;
                break;
        }
    }

void mouse(int button, int state, int x, int y)
{
   switch (button)
   {
      case GLUT_LEFT_BUTTON:
         if (state == GLUT_DOWN) {

         }
         break;
      case GLUT_MIDDLE_BUTTON:
         if (state == GLUT_DOWN) {

         }
         break;
      case GLUT_RIGHT_BUTTON:
         if (state == GLUT_DOWN) {

         }
         break;
      default:
         break;
   }
}

int main(int argc, char** argv)
{
    init(argc,argv);
    glutDisplayFunc(display); 
    glutReshapeFunc(reshape);
    glutIdleFunc(calcNewScene); //called after render is done, typically to recalculate positions for the next frame
    glutKeyboardFunc(keyDown);
    //glutKeyboardUpFunc(keyUp);
    //glutMouseFunc(mouse);
    glutMainLoop();
    //THIS IS NEVER REACHED
    
    return 0;
}
