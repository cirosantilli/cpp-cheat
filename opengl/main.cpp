#include <cstdio>
#include <iostream>
#include <stdlib.h>

// TODO this is just a cheap workaround for an Ubuntu 13.10 bug: https://bugs.launchpad.net/ubuntu/+source/nvidia-graphics-drivers-319/+bug/1248642?comments=all
// Get rid of this in the future.
#include <pthread.h>

// Required to open extension prototypes on the glext.h.
#define GL_GLEXT_PROTOTYPES 1

#include <GL/glut.h>  // Also includes gl.h and glu.h.
#include <GL/glext.h>

#include "vec3.h"
#include "glInfo.h"

using namespace std;

//#fps

    // Depending on your driver, onscreen rendering may be limited to screen refresh rate (often 60FPS) when
    // rendering is done to the screen, and unlimited if done to buffers.

    // It is also interesting to see how FPS may be affected by giving another window
    // focus and hiding the OpenGL window. Certain drivers are smart enough to
    // let FPS increase since the image no longer needs to be rendered.

    // If false: outputs to screen and an image representation to stdout.

    // If true : outputs to stdout only.

        bool offscreen = false;

int maxNFrames = -1; //number of frames to calculate on offscreen rendering.
                     //After that number, stop.
                     //If negative, never stop (until program receives a signal).

// Some color constants:
    const GLfloat white[] = {1.0, 1.0, 1.0};
    const GLfloat gray [] = {0.1, 0.1, 0.1};
    const GLfloat black[] = {0.0, 0.0, 0.0};
    const GLfloat red  [] = {1.0, 0.0, 0.0};
    const GLfloat green[] = {0.0, 1.0, 0.0};
    const GLfloat blue [] = {0.0, 0.0, 1.0};

GLubyte stipplePattern[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x03, 0x80, 0x01, 0xC0, 0x06, 0xC0, 0x03, 0x60,
    0x04, 0x60, 0x06, 0x20, 0x04, 0x30, 0x0C, 0x20,
    0x04, 0x18, 0x18, 0x20, 0x04, 0x0C, 0x30, 0x20,
    0x04, 0x06, 0x60, 0x20, 0x44, 0x03, 0xC0, 0x22,
    0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,
    0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,
    0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,
    0x66, 0x01, 0x80, 0x66, 0x33, 0x01, 0x80, 0xCC,
    0x19, 0x81, 0x81, 0x98, 0x0C, 0xC1, 0x83, 0x30,
    0x07, 0xe1, 0x87, 0xe0, 0x03, 0x3f, 0xfc, 0xc0,
    0x03, 0x31, 0x8c, 0xc0, 0x03, 0x33, 0xcc, 0xc0,
    0x06, 0x64, 0x26, 0x60, 0x0c, 0xcc, 0x33, 0x30,
    0x18, 0xcc, 0x33, 0x18, 0x10, 0xc4, 0x23, 0x08,
    0x10, 0x63, 0xC6, 0x08, 0x10, 0x30, 0x0c, 0x08,
    0x10, 0x18, 0x18, 0x08, 0x10, 0x00, 0x00, 0x08
};

//param values not to see cross wall
    //GLfloat frustrumNear = 0.95*personR; //so that won't see across wall
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

        Sphere(
            Vec3<> pos,
            T rad = 1.0,
            int slices = 50,
            int stacks = 50,
            const GLfloat* color = white,
            Vec3<> speed = Vec3<>()
        ) :
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

//view parameter
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

        Camera(
            Vec3<T> pos, //position of the camera
            Vec3<T> dir, //direction of viewing
            Vec3<T> up = Vec3<T>(0.0, 1.0, 0.0f),
            T frustrumNear = 1.0,
            T frustrumFar = 100.0,
            T frustrumL = 1.0,
            GLint resX = 700,
            GLint resY = 700,
            GLint format = GL_RGB
        ) :
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
        int getNComponents() {
            switch (format) {
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
    GLint windowW = 50;
    GLint windowH = 50;

    GLint windowPosX = 10;
    GLint windowPosY = 10;

    int oldT;  //used to keep real time consistent
    int nFrames = 0; //total number of frame

//event
    bool mouseLeftDown;
    bool mouseRightDown;
    float mouseX, mouseY;

//camera
    //create a camera
    Camera<> camera;
    GLubyte* pixels; //stores the pixels from the rendering
    GLuint fboId;
    GLuint texId;
    GLuint rboColor;
    GLuint rboDepth;

//light
    GLfloat lightPos[] = { 2.0, 0.0, 0.0, 0.0 };

//scenario
    GLfloat mat_shininess[] = { 100.0 };

enum nDrawables { nDrawables=2, nSpheres=2 };
    Drawable* drawables[nDrawables];
    Sphere<> spheres[nSpheres];

//physical viewer param
    float fast_forward = 1.f;
    GLfloat personR = 1.f; //radius for collision detection

    //wait for input mode
    GLfloat dirStep = 2.f;     //speed forward
    GLfloat dirRotStep = 2.f;     //speed forward

    //don't wait for input
    GLfloat speedMax = 2.f;      //trsnalation speed
    GLfloat rotSpeedMax = 0.0f;  //rotation speed in rad/
    Vec3<> speed;  //translation speed in rad/
    Vec3<> rotSpeed;  //rotation speed in rad/s. right hand rule

//stuff set only once at beginning
void init(int argc, char** argv) {
    int doubleBuffer;

    glutInit(&argc, argv);

    if (offscreen) {
        glutInitWindowSize(1, 1);
        doubleBuffer = GLUT_SINGLE;
    } else {
        glutInitWindowSize( windowW, windowH );
        glutInitWindowPosition( windowPosX, windowPosY );
        doubleBuffer = GLUT_DOUBLE;
    }

    glutInitDisplayMode( doubleBuffer | GLUT_RGB | GLUT_DEPTH );
        //GLUT_SINGLE
            //use single framebuffer GL_FRONT.
            //drawing makes change immediatelly visible even before complete
            //not appropriate for animation
        //GLUT_DOUBLE
            //use 2 framebuffers, draw to GL_BACK
            //call glutSwapBuffers to put back on GL_FRONT once drawing is complete
            //user only sees completed drawing
            //appropriate for animation
        //GLUT_RGB vs indexed color: instead of using 8bit per channel, choose 256 colors that represent well an image, and use 1byte for each pixel.
        //  http://en.wikipedia.org/wiki/Indexed_color
        //GLUT_DEPTH depth buffering: calculate pixels for each plane and their distances,
            //keep only closest one, cheapest way to hide parts of objects that go behind others.

    //window
        //must always create a window
        //for offscreen rendering, create 1x1 window and hide it

        glutInitWindowSize(windowW, windowH);
        glutInitWindowPosition(windowPosX, windowPosY);
        glutCreateWindow(argv[0]);
        //glutShowWindow();
        //glutHideWindow();
        //glutIconifyWindow();


    if (offscreen) {
        //setup framebuffer
        //generate namespace for the frame buffer, colorbuffer and depthbuffer

        //fbo is made to render and read pixels back to CPU
        //render to texture is made to render and reutilize in GUP
        //backbuffer is to print to screen, therefore slower than fbo
        //pixel buffer objects to make read pixels asynchronou

        //color renderbuffer
            glGenRenderbuffers(1, &rboColor);
                //create a new renderbuffer unique name
            glBindRenderbuffer(GL_RENDERBUFFER, rboColor);
                //set it as the current
            glRenderbufferStorage(
                GL_RENDERBUFFER,
                GL_RGBA8,
                windowW,
                windowH
            );
                //sets storage type for currently bound renderbuffer

        //depth renderbuffer
            glGenRenderbuffers(1, &rboDepth);
            glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
            glRenderbufferStorage(
                GL_RENDERBUFFER,
                GL_DEPTH_COMPONENT24,
                windowW,
                windowH
            );

        //framebuffer
            glGenFramebuffers(1, &fboId);
                //create a framebuffer and a renderbuffer object
                //you need to delete them when program exits.

            glBindFramebuffer(GL_FRAMEBUFFER, fboId);
                //from now on, operate on the given framebuffer
                    //GL_FRAMEBUFFER        read write
                    //GL_READ_FRAMEBUFFER   read
                    //GL_FRAMEBUFFER   write

            glFramebufferRenderbuffer(
                GL_FRAMEBUFFER,
                GL_COLOR_ATTACHMENT0,
                GL_RENDERBUFFER,
                rboColor
            );
            //adds a color renderbuffer to currently bound framebuffer

            glFramebufferRenderbuffer(
                GL_FRAMEBUFFER,
                GL_DEPTH_ATTACHMENT,
                GL_RENDERBUFFER,
                rboDepth
            );

            //glBindFramebuffer(GL_FRAMEBUFFER, 0);
                //unbinds current framebuffer
                //goes back to default (GL_BACK or GL_FRONT)

        glReadBuffer(GL_COLOR_ATTACHMENT0);
        //glReadBuffer(GL_BACK);
            //sets read target for:
                //glReadPixel
                //glCopyTexImage1D
                //glCopyTexImage2D
                //glCopyTexSubImage1D
                //glCopyTexSubImage2D
                //glCopyTexSubImage3D

        GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (status != GL_FRAMEBUFFER_COMPLETE) {
            cout << "framebuffer error:" << endl;
            switch (status) {
                case GL_FRAMEBUFFER_UNDEFINED:
                    cout << "GL_FRAMEBUFFER_UNDEFINED" << endl;
                break;

                case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
                    cout << "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT" << endl;
                break;

                case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
                    cout << "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT" << endl;
                break;

                case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
                    cout << "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER" << endl;
                break;

                case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
                    cout << "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER" << endl;
                break;

                case GL_FRAMEBUFFER_UNSUPPORTED:
                    cout << "GL_FRAMEBUFFER_UNSUPPORTED" << endl;
                break;

                case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
                    cout << "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE" << endl;
                break;

                case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
                    cout << "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS" << endl;
                break;

                case 0:
                    cout << "0" << endl;
                break;
            }
            exit(EXIT_FAILURE);
        }
        glutHideWindow();  //TEST COMMENT
    }

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
        //glPolygonMode(GL_FRONT, GL_FILL); //will fill the solid

    //light
        //learn the color algorithm *now*
        //http://www.glprogramming.com/red/chapter05.html

        glEnable(GL_LIGHTING);

        //glLightModelfv
            glLightModelfv(GL_LIGHT_MODEL_AMBIENT, white);
                //global ambient light. is not distance attenuated.
                //if white, are no shadows, ever!
                //also, if this is the only light, no shadow
            //glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE); //TODO ?
            //glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE); //light both side

        //glShadeModel(GL_FLAT);
        glShadeModel(GL_SMOOTH);

        //light0
            //glEnable(GL_LIGHT0);

            glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
            //4 vector. if [3]==0, x,y,z is the position.
            //otherwise, light is at infinity and x,y,z is the incoming direction

            //all of the following are distance attenuated
                glLightfv(GL_LIGHT0, GL_AMBIENT,  gray ); //if this is white and close, you see no shadow
                glLightfv(GL_LIGHT0, GL_DIFFUSE,  white);
                glLightfv(GL_LIGHT0, GL_SPECULAR, white);

            //attenuation
                //\frac{1}{k+ld+qd^2}
                //glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 2.0);
                //glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1.0);
                //glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.5);

        //glEnable(GL_LIGHT1);
            //... up to 8 light

    //two ways to define material

        //gl_color_material and glmaterialfv

        //GL_COLOR_MATERIAL + glcolor
            //glEnable(GL_COLOR_MATERIAL);
            ////glColor has no effect if lightning is on and you dont enable thi
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

        pixels = new GLubyte[camera.getNComponents() * windowW];
        //to store output pixel

    //create drawable objects to model initial scene
        spheres[0] = Sphere<>(Vec3<>(0.0, 0.0, 0.0), 1.0, 50, 50, red);
        spheres[1] = Sphere<>(Vec3<>(0.0, 0.0, 0.0), 1.0, 50, 50, blue);
        int total = 0;
        for (int i = total; i < nSpheres; i++) {
            drawables[i] = &spheres[i];
        }

    oldT = glutGet(GLUT_ELAPSED_TIME); //init old time in ms.
}

//calculates the parameters of the new scene and calls display again
void idle(void) {
    //cout << "idle" << endl;

    Vec3<> dx, newpos;
    float dt;
    int t;

    //keep animation real time consistent
        t = glutGet(GLUT_ELAPSED_TIME);
        dt = fast_forward*(t - oldT)/1000.0;
        oldT = t;

    //cout << "===============================================" << endl;
    //cout << "pos" << endl << camera.pos.str();
    //cout << "dir" << endl << camera.dir.str();
    //cout << "dir" << endl << camera.getLookat().str();
    //cout << "speed\n" << speed;
    //cout << "rotSpeed\n" << rotSpeed;
    cout << "FPS average: " << 1000 * (((float)nFrames) / t);
    cout << endl;

    //speed nonstop movement method
        //camera.dir.rotY(rotSpeed*dt);
        //newpos = camera.pos + speed*dt;
        //camera.pos -= Vec3<>(0.005, 0.0, 0.0);
        spheres[0].pos += Vec3<>(0.005, 0.0, 0.0);

    nFrames++;
    if (offscreen && nFrames == maxNFrames) {
        exit(EXIT_SUCCESS);
    }
    glutPostRedisplay();
}

void display()
{

    //cout << "display" << endl;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //clears given buffers to clear value
        //GL_COLOR_BUFFER_BIT
        //GL_DEPTH_BUFFER_BIT
        //GL_ACCUM_BUFFER_BIT
        //GL_STENCIL_BUFFER_BIT

    glLoadIdentity(); // reset everything before starting

    Vec3<> lookat = camera.getLookat();

    gluLookAt(
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

    //we can check/modify state of attributes like so
        //void glEnable(GLenum cap);
        //void glDisable(GLenum cap);
        //GLboolean glIsEnabled(GLenum capability)
        //void glGet*v(GLenum pname, GL* *params);
        //void glGetPointerv(GLenum pname, GLvoid **params);

        //void glPushAttrib(GLbitfield mask);
        //void glPopAttrib(void);
            //this can be done more efficiently in a stacked manner for groups of attribute
            //GLbitfield represents a group of several attribute

    glPushMatrix();
    //before transforming save the old matrix
    //potentially faster than loading identity at the end

    //geometric transformation
        //glMultMatrixf(N);
        //glScalef(1.0, 1.0, 1.0);
        //glRotatef(45., 1.0, 1.0, 0.0);
        //glTranslatef(1., 0.0, 0.0);

    //can format primitives with
        //void glPointSize(GLfloat size);
        //void glLineWidth(GLfloat width);
        //void glLineStipple(GLint factor, GLushort pattern);
            ////pattern=0x3F07 (translates to 0011111100000111 in binary),
            ////a line would be drawn with 3 pixels on, then 5 off, 6 on, and 2 off
        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default mode
            //GL_FRONT, GL_BACK
            //GL_FILL, GL_LINE, GL_POINT
        //void glFrontFace(GLenum mode) TODO

        //PolygonStipple
            //puts a 32x32 pattern on polygon
            //glEnable (GL_POLYGON_STIPPLE);
            //glPolygonStipple (stipplePattern);
            //glDisable (GL_POLYGON_STIPPLE)

    //planar polygons are primitives, and thus dealt by opengl
        //glBegin(GL_POLYGON);
            //glVertex3f (-0.5, -0.5, 0.0);
            //glVertex3f ( 0.5, -0.5, 0.0);
            //glVertex3f ( 0.5,  0.5, 0.0);
            //glVertex3f (-0.5,  0.5, 0.0);
        //glEnd();

        //other types of basic shapes:
            //GL_POINT
            //GL_LINE
            //GL_LINE_STRIP
            //GL_LINE_LOOP
            //GL_TRIANGLE
            //GL_TRIANGLE_STRIP
            //GL_TRIANGLE_FAN
            //GL_QUAD
            //GL_QUAD_STRIP
            //GL_POLYGON
                //convex polygon
            //glVertex*()

        //the following are also allowed betwen glBegin and glEnd
            //glColor3f(1.0, 0.0, 0.0);
            //glIndex*
            //glNormal*
                //normal affects lightning
                //
                //normal is set per vertex, not surface
                //since all calculations are per vertex,
                //and then later interpolated

                //glBegin (GL_POLYGON);
                    //glNormal3fv(n0);
                    //glVertex3fv(v0);
                    //glNormal3fv(n1);
                    //glVertex3fv(v1);
                    //glNormal3fv(n2);
                    //glVertex3fv(v2);
                    //glNormal3fv(n3);
                    //glVertex3fv(v3);
                //glEnd();

            //glTexCoord*
            //glEdgeFlag*
            //glMaterial*
            //glArrayElement
            //glEvalCoord*, glEvalPoint*
            //glCallList, glCallList


        //vertex array
            //reduce amounts of GL_VERTEX call
            //to a single call on array

            //static GLint vertices[] =
            //{
                //25, 25,
                //100, 325,
                //175, 25,
                //175, 325,
                //250, 25,
                //325, 325
            //};

            //static GLfloat colors[] =
            //{
                //1.0, 0.2, 0.2,
                //0.2, 0.2, 1.0,
                //0.8, 1.0, 0.2,
                //0.75, 0.75, 0.75,
                //0.35, 0.35, 0.35,
                //0.5, 0.5, 0.5
            //};

            ///color and position on the same array
            //static GLfloat intertwined[] =
            //{
                //1.0, 0.2, 1.0, 100.0, 100.0, 0.0,
                //1.0, 0.2, 0.2, 0.0, 200.0, 0.0,
                //1.0, 1.0, 0.2, 100.0, 300.0, 0.0,
                //0.2, 1.0, 0.2, 200.0, 300.0, 0.0,
                //0.2, 1.0, 1.0, 300.0, 200.0, 0.0,
                //0.2, 0.2, 1.0, 200.0, 100.0, 0.0
            //};

            //glEnableClientState( GL_COLOR_ARRAY  );
            //glEnableClientState( GL_VERTEX_ARRAY );
            //glEnableClientState( GL_NORMAL_ARRAY );

            //glColorPointer (3, GL_FLOAT, 0, colors);
            //glVertexPointer(2, GL_INT, 0, vertices);
            //glInterleavedArrays (GL_C3F_V3F, 0, intertwined);

            //glDisableClientState( GL_COLOR_ARRAY  );
            //glDisableClientState( GL_VERTEX_ARRAY );
            //glDisableClientState( GL_NORMAL_ARRAY );

        //glRectf(0.0, 0.0, 1.0, 1.0;)
            //rectangle, x1, y1, x2, y2, z=0
            //may be optimized with respect to GL_POLYGON
            //can be transformed to leave z=0

        //non convex line polygon
            //build up from smaller triangle
            //+ EdgeFlag

            //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            //glBegin(GL_POLYGON);
                //glEdgeFlag ( GL_TRUE  );
                //glVertex3fv( V0       );
                //glEdgeFlag ( GL_FALSE );
                //glVertex3fv( V1       );
                //glEdgeFlag ( GL_TRUE  );
                //glVertex3fv(V2);
            //glEnd();

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

    for (int i = 0; i < nDrawables; i++) {
        drawables[i]->draw();
    }

    //ensures draw is up to date

        //glFlush();
        //- send all commands even if output is not read. (parallel processing, network)
        //- pauses application until drawing is complete and back framebuffer updated
        //- does not put back framebuffer on front, so you see nothing

        glutSwapBuffers();
        //- puts backbuffer into frontbuffer making drawn scene visible
        //- *waits* for the screen to refresh, limiting application speed to screen refresh rate
        //- also flushe
        //- backbuffer becomes undefined
        //- if not GL_DOUBLE, simply flushe

    //read pixels from render
        //find where glReadPixels is reading from
            //int buff;
            //glGetIntegerv(GL_READ_BUFFER,&buff);
            //cout << "glReadPixels reads from:" << endl;
            //switch (buff)
            //{
                //case GL_BACK:
                    //cout << "GL_BACK" << endl;
                    //break;

                //case GL_FRONT:
                    //cout << "GL_FRONT" << endl;
                    //break;

                //case GL_COLOR_ATTACHMENT0:
                    //cout << "GL_COLOR_ATTACHMENT0" << endl;
            //}

        //#glReadPixels

            // Reads a rectangle of pixels from last render

                glReadPixels(
                    0,                  // top X rectangle
                    windowH/2,          // top Y rectangle
                    camera.resX,        // rectangle width
                    1,                  // rectangle height
                    camera.format,      // GL_RGB, output format
                    GL_UNSIGNED_BYTE,   // output data type
                    pixels              // where output will be saved
                );

        for (int i = 0; i < camera.resX * camera.getNComponents(); i = i + 3) {
            //cout << i/3 << " ";
            printf(
                "%3d %3d %3d | ",
                (int)pixels[i],
                (int)pixels[i+1],
                (int)pixels[i+2]
            );
        }
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
        //try w/2: will only draw on left half of the screen

    glMatrixMode(GL_PROJECTION);
        //from now on, modify projection transform matrix stack

    glLoadIdentity();
        //clear all transform

    //glOrtho(-1.0, 1.0, -1.0, 1.0, -0.0, 2.0);
        //use 2D like projection transform

    glFrustum
    (
        -camera.frustrumL,
        camera.frustrumL,
        -camera.frustrumL,
        camera.frustrumL,
        camera.frustrumNear,
        camera.frustrumFar
    );
        //use 3D like real life projection transform

    glMatrixMode(GL_MODELVIEW);
    //from now on, modify model (scene objects) transform matrix stack
}

//move model
    //fixed displacement (fixed steps)
    //fixed speed (displacement is proportional to elapsed time)
    //fixed acceleration (displacement acceleration is proportional to elapsed time)
        //can have max speed or not

//fixed displacement
    void keyDown(unsigned char key, int x, int y)
    {
        switch (key)
        {
            case 's':
                camera.dir.z -= dirStep;
            break;
            case 'w':
                camera.dir.z += dirStep;
            break;
            case 27: //esc
                //quit
                exit(EXIT_SUCCESS);
            break;
        }
    }

//fixed speed
    //position will be calculated as function of elapsed time in idle()
    void keyDownSpeed(unsigned char key, int x, int y) {
        switch (key) {
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
                //forward
                //speed = dirSpeedMax;
            break;
            case 27: //esc
                //quit
                exit(EXIT_SUCCESS);
            break;
        }
    }

    void keyUpSpeed(unsigned char key, int x, int y) {
        switch (key) {
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

    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            mouseLeftDown = true;
        } else if (state == GLUT_UP) {
            mouseLeftDown = false;
        }
    }

    else if (button == GLUT_RIGHT_BUTTON) {
        if (state == GLUT_DOWN) {
            mouseRightDown = true;
        } else if (state == GLUT_UP) {
            mouseRightDown = false;
        }
    }
}

void mouseMotion(int x, int y) {
    if (mouseLeftDown) {
        mouseX = x;
        mouseY = y;
    }
    if (mouseRightDown) {
        mouseY = y;
    }
}

void exitCB() {
    //cout << "exiting" << endl;
}

int main(int argc, char** argv) {

    // TODO this is just a cheap workaround for an Ubuntu 13.10 bug: https://bugs.launchpad.net/ubuntu/+source/nvidia-graphics-drivers-319/+bug/1248642?comments=all
    // Get rid of this in the future.
    int i=pthread_getconcurrency();

    if (argc > 1) {
        cout << argv[1] << endl;
        if ( string(argv[1]) == "0" )
            offscreen = false;
    }

    init(argc,argv);

    //#DisplayFunc

        // Sets callback function used to draw the scene,
        // therefore the most important call back.

        // This callback should be set on any OpenGL program.

        // The display function is set to be called on next loop when `glutPostRedisplay` is called.

        // Scene calculation should be left for the `glutIdleFunc` set callback,
        // this callback should only draw to screen.

            glutDisplayFunc(display);

    //#DisplayFunc

        // What to do when the window changes size.

        // This is required as it is called when the window is first shown TODO confirm.

            glutReshapeFunc(reshape);

    //#IdleFunc

        // Called when nothing else is happening: rendering, event handling.

        // Often used to recalculate positions for the next frame, with a `glutPostRedisplay`
        // added to the end of the idle function, so that refresh will happen

        // Not required, but used by almost all programs.

        // TODO why not put calculations directly inside the display func?

            glutIdleFunc(idle);

    //#event handlers

            glutKeyboardFunc(keyDown);
            //glutKeyboardUpFunc(keyUp);
            //glutMouseFunc(mouse);
            //glutMotionFunc(mouseMotion); //mouse motion
            atexit(exitCB);

    //Get and print OpenGL info. This class was define by us, not OpenGL standard.
    glInfo glInfo;
    glInfo.getInfo();
    //glInfo.printSelf();

    //#MainLoop

        // Start the main loop which calls all the callbacks at the right time.

        // TODO how to leave the main loop from a program? <http://www.opengl.org/discussion_boards/showthread.php/142428-How-to-exit-MainLoop-WITHOUT-killing-the-app>
        // The most common way is a simple exit.

            glutMainLoop();

    // This point is only reached when the program window is closed by the user.

    return 0;
}
