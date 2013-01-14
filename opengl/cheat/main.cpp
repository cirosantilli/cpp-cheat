#define GL_GLEXT_PROTOTYPES
#include <iostream>
#include <stdlib.h>

#include <glut.h>  // both opengl (gl.h, rendering) and glu (glu.h, opengl utilities), besides glut.h (windowing, input/output)
#include <glext.h> // extensions

#include "vec3.h"
#include "glInfo.h"

using namespace std;

//some colors constants
    GLfloat white[] = {1.0, 1.0, 1.0};
    const GLfloat gray[] = {0.1, 0.1, 0.1};
    const GLfloat black[] = {0.0, 0.0, 0.0};
    const GLfloat red[] = {1.0, 0.0, 0.0, 1.0};
    const GLfloat green[] = {0.0, 1.0, 0.0};
    const GLfloat blue[] = {0.0, 0.0, 1.0};

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
            slices(50),
            stacks(50),
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
            int slices = 50,
            int stacks = 50,
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
            resY(700),
            format(GL_RGB)
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
            GLint resX = 700,
            GLint resY = 700,
            GLint format = GL_RGB
        )
        :
            pos(pos),
            dir(dir),
            up(up),
            frustrumNear(frustrumNear),
            frustrumFar(frustrumFar),
            frustrumL(frustrumL),
            resX(resX),
            resY(resY),
            format(format)
        {
        }

        Vec3<T> getLookat(){ return pos+dir; }

        //gets number of components for the already given format
        int getNComponents()
        {
            switch(format)
            {
                case GL_BGR:
                case GL_RGB:
                    return 3;
                    break;
                case GL_BGRA:
                case GL_RGBA:
                    return 4;
                    break;
                case GL_ALPHA:
                case GL_LUMINANCE:
                    return 1;
                    break;
            }
        }

        Vec3<T> pos;
        Vec3<T> dir;
        Vec3<T> up;

        GLfloat frustrumNear;
        GLfloat frustrumFar;
        GLfloat frustrumL;
        GLint format; //formt of output image

        int resX;
        int resY;
};

//profiling

//window
    GLint windowW = 700;
    GLint windowH = 700;

    GLint windowPosX = 10;
    GLint windowPosY = 10; 

    int oldT;  //used to keep real time consistent
    int nFrames=0; //total number of frames

//events
    bool mouseLeftDown;
    bool mouseRightDown;
    float mouseX, mouseY;

//camera
    //create a camera
    Camera<> camera;
    GLubyte* pixels; //stores the pixels from the rendering
    GLuint fboId;
    GLuint texId;
    GLuint rboId;

//light
    GLfloat lightPos[] = { 2.0, 0.0, 0.0, 0.0 };

//scenario
    GLfloat mat_shininess[] = { 100.0 };

enum nDrawables { nDrawables=1, nSpheres=1 };
    Drawable* drawables[nDrawables];
    Sphere<> spheres[nSpheres];

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

    //color to clear screen after each image
        glClearColor(0.0, 0.0, 0.0, 0.0);

    glEnable(GL_DEPTH_TEST); //TODO ?
    //glEnable(GL_BLEND);  //use those alphas TODO ?

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
        //learn the color algorithm *now*
        //http://www.glprogramming.com/red/chapter05.html
 
        glEnable(GL_LIGHTING);

        //glLightModelfv
            glLightModelfv(GL_LIGHT_MODEL_AMBIENT, white);
                //global ambient light. is not distance attenuated.
                //if white, are no shadows, ever!
                //also, if this is the only light, no shadows
            //glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE); //TODO ?
            //glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE); //light both sides

        //glShadeModel(GL_FLAT);
        glShadeModel(GL_SMOOTH);

        //light0
            glEnable(GL_LIGHT0);

            glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
            //4 vector. if [3]==0, x,y,z is the position.
            //otherwise, light is at infinity and x,y,z is the incoming direction
  
            //all of the following are distance attenuated
                glLightfv(GL_LIGHT0, GL_AMBIENT, gray); //if this is white and close, you see no shadows
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

        //GL_COLOR_MATERIAL + glcolor
            //glEnable(GL_COLOR_MATERIAL);
            ////glColor has no effect if lightning is on and you dont enable this
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
            //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, white);
            //glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white);
            //glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
            //glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, white); //if this is white and close to the scene, no shadows!
            glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess); //specular exponent

    //camera
        camera = Camera<>(
            Vec3<>(0.0, 0.0, -2.0),
            Vec3<>(0.0, 0.0,  1.0),
            Vec3<>(0.0, 1.0,  0.0),
            1.0,
            100.0,
            1.0,
            windowW,
            windowH,
            GL_RGB
        );

        pixels = new GLubyte[ camera.getNComponents() * windowW ];
        //to store output pixels

    //setup framebuffer
        // generate namespace for the frame buffer, colorbuffer and depthbuffer

        //glGenFramebuffers  (1, &fboId);
        glGenRenderbuffers (1, &rboId);
        //glBindFramebuffer  (GL_FRAMEBUFFER, fboId);
        //glBindRenderbuffer (GL_RENDERBUFFER, rboId);
        //glRenderbufferStorage
        //(
            //GL_RENDERBUFFER,
            //GL_DEPTH_COMPONENT24,
            //512,
            //512
        //);
        //glFramebufferRenderbuffer
        //(
            //GL_FRAMEBUFFER,
            //GL_DEPTH_ATTACHMENT,
            //GL_RENDERBUFFER,
            //rboId
        //);

    //create drawable objects to model initial scene
        spheres[0] = Sphere<>( Vec3<>(0.0,0.0,0.0), 1.0, 50, 50, red );
        //spheres[1] = Sphere( Vec3<>(-0.5,0.75,0.0), Vec3<>( 0.1, 0.0, 0.0), green );
        int total=0;
        for (int i=total; i<nSpheres; i++)
        {
            drawables[i] = &spheres[i];
        }

    oldT = glutGet(GLUT_ELAPSED_TIME); //init old time in ms.
}

//calculates the parameters of the new scene and calls display again
void idle(void)
{
    //cout << "idle" << endl;

    Vec3<> dx, newpos;
    float dt;
    int t;

    //keep animation real time consistent
        t = glutGet(GLUT_ELAPSED_TIME);
        dt = fast_forward*(t - oldT)/1000.0;
        oldT = t;

    //cout << "===========================" << endl;
    //cout << "pos" << endl << camera.pos.str();
    //cout << "dir" << endl << camera.dir.str();
    //cout << "dir" << endl << camera.getLookat().str();
    //cout << "speed\n" << speed;
    //cout << "rotSpeed\n" << rotSpeed;
    cout << "FPS average: " << 1000*nFrames/t << endl;
    nFrames++;
    cout << endl;

    //speed nonstop movement method
        //camera.dir.rotY( rotSpeed*dt );
        //newpos = camera.pos + speed*dt;
        camera.pos += Vec3<>(0.005, 0.0, 0.0);

    //read pixels from render
        //glReadPixels
        //( //reads a rectangle of pixels from last render
            //0, //top x rectangle
            //windowH/2, //top y rectangle
            //camera.resX, //rectangle width
            //1, //rectangle height
            //camera.format, //GL_RGB, output format
            //GL_UNSIGNED_BYTE, //output data type
            //pixels //where output will be saved
        //);

        //for(int i=0; i<camera.resX*camera.getNComponents(); i=i+3)
        //{
            ////cout << i/3 << " ";
            //cout << (int)pixels[i] << " ";
            //cout << (int)pixels[i+1] << " ";
            //cout << (int)pixels[i+2] << " ";
            //cout << endl;
        //}

    glutPostRedisplay();
}

void display()
{
    //cout << "display" << endl;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
    //GL_COLOR_BUFFER_BIT
    //GL_DEPTH_BUFFER_BIT
	//GL_ACCUM_BUFFER_BIT
    //GL_STENCIL_BUFFER_BIT
	
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
        //glRotatef(45., 1.0, 1.0, 0.0);
        //glTranslatef(1., 0.0, 0.0);

    //the following are also allowed betwen glBegin and glEnd
        //glColor3f(1.0, 0.0, 0.0);
        //glIndex*
        //glNormal*
        //glTexCoord*
        //glEdgeFlag*
        //glMaterial*
        //glArrayElement
        //glEvalCoord*, glEvalPoint*
        //glCallList, glCallLists


    //polygons are primitives, and thus dealt by opengl
        //glBegin(GL_POLYGON);
            //glVertex3f (-0.5, -0.5, 0.0);
            //glVertex3f ( 0.5, -0.5, 0.0);
            //glVertex3f ( 0.5,  0.5, 0.0);
            //glVertex3f (-0.5,  0.5, 0.0);
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

    for ( int i = 0; i < nDrawables; i++ )
    {
        drawables[i]->draw();
    }

    //glFlush();
    //- send all commands even if output is not read. (parallel processing, network)
    //- pauses application until drawing is complete and back framebuffer updated
    //- does not put back framebuffer on front, so you see nothing

    glutSwapBuffers();
    //
    ////*waits* for the screen to refresh and makes sure that each frame goes to output window,
    ////therefore limiting application speed to screen refresh rate
    //
    ////also flushes
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h); 

    glMatrixMode(GL_PROJECTION); //TODO ?
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

    //glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); //view cube

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
    //position will be calculated as function of elapsed time in idle()
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
    mouseX = x;
    mouseY = y;

    if(button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            mouseLeftDown = true;
        }
        else if(state == GLUT_UP)
            mouseLeftDown = false;
    }

    else if(button == GLUT_RIGHT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            mouseRightDown = true;
        }
        else if(state == GLUT_UP)
            mouseRightDown = false;
    }
}

void mouseMotion(int x, int y)
{
    if(mouseLeftDown)
    {
        mouseX = x;
        mouseY = y;
    }
    if(mouseRightDown)
    {
        mouseY = y;
    }
}

int main(int argc, char** argv)
{
    init(argc,argv);
    glutDisplayFunc(display); 
    glutReshapeFunc(reshape);
    glutIdleFunc(idle); //called after render is done, typically to recalculate positions for the next frame
    glutKeyboardFunc(keyDown);
    //glutKeyboardUpFunc(keyUp);
    //glutMouseFunc(mouse);
    //glutMotionFunc(mouseMotion); //mouse motion
 
    //get and print opengl info
        glInfo glInfo;
        glInfo.getInfo();
        //glInfo.printSelf();

    glutMainLoop();
    //THIS IS NEVER REACHED
    
    return 0;
}
