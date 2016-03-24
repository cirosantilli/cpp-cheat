/*
Very simple example of textures and FPS collision detection.

Controls:

- `S`: left
- `D`: right
- `E`: fast
- `X`: slow

Demo video: http://youtu.be/wAQxIla7F68
*/

#include <iostream>
#include <cstdio>
#include <cmath>

#include <GL/glut.h>
#include <opencv2/opencv.hpp>

using namespace std;

class Vector3D {

    public:

        GLfloat x;
        GLfloat y;
        GLfloat z;

        Vector3D() {
            this->x = 0.0;
            this->y = 0.0;
            this->z = 0.0;
        }

        Vector3D(GLfloat x, GLfloat y, GLfloat z) {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        //vector sum
        Vector3D operator+(Vector3D otherv) {
            return Vector3D(this->x + otherv.x, this->y + otherv.y, this->z + otherv.z);
        }

        //vector subtraction
        Vector3D operator-(Vector3D otherv) {
            return Vector3D(this->x - otherv.x, this->y - otherv.y, this->z - otherv.z);
        }

        //multiplication by constant
        Vector3D operator*(GLfloat a) {
            return Vector3D(this->x * a, this->y * a, this->z * a);
        }

        //division by constant
        Vector3D operator/(GLfloat a) {
            return Vector3D(this->x / a, this->y / a, this->z / a);
        }

        //dot product
        GLfloat dot(Vector3D otherv) {
            return this->x * otherv.x + this->y * otherv.y + this->z * otherv.z;
        }

        //returns the euclidean norm of this vector
        GLfloat norm() {
            return sqrt(this->dot(*this));
        }

        //returns the taxi norm of this vector (largest absolute value of a corrdinate)
        GLfloat taxi_norm() {
            //return max(abs(x), abs(y), abs(z));
            return 0.0;
        }

        //returns a unit vector in the same direction as this vector
        Vector3D unit() {
            return (*this) / this->norm();
        }

        /* rotates this vector around Y axis by given angle
         *
         * operates inline
         * */
        void rotY(GLfloat angle) {
            GLfloat oldx = x;
            GLfloat oldz = z;
            GLfloat sina = sin(angle);
            GLfloat cosa = cos(angle);
            x = oldx*cosa + oldz*sina;
            z = - oldx*sina + oldz*cosa;
        }

        //euclidean distance
        GLfloat eucl(Vector3D other) {
            return (*this - other).norm();
        }

        /* To a string, with given precision p */
        string str(int precision) {
            char out[64];
            char format[64];
            sprintf(format, "%%4.%df\n%%4.%df\n%%4.%df\n", precision, precision, precision);
            sprintf(out, format, x, y, z);
            return std::string(out);
        }

};

GLuint loadTextureJpg(string filename, int wrap) {
    GLuint texture;
    cv::Mat I;
    int nRows, nCols, channels;
    uchar* p;
    uchar r, g, b;

    I = cv::imread(filename, 1);
    if (!I.data) {
        cerr << "no data\n" << filename << endl;
        return 2;
    }

    cout << filename << endl;
    cout << I.rows << endl;
    cout << I.cols << endl;
    cout << (int)I.data[0] << endl;
    cout << (int)I.data[1] << endl;
    cout << (int)I.data[2] << endl;
    cout << (int)I.data[3] << endl;
    cout << (int)I.data[4] << endl;
    cout << (int)I.data[5] << endl;

    //put as R, G, B: given is B, G, R
    channels = I.channels();
    nRows = I.rows;
    nCols = I.cols * channels;
    if (I.isContinuous()) {
        nCols *= nRows;
        nRows = 1;
    }
    for (int i = 0; i < nRows; ++i) {
        p = I.ptr<uchar>(i);
        for (int j = 0; j < nCols; j=j+channels) {
            b = p[j]  ;
            g = p[j+1];
            r = p[j+2];
            p[j] = r;
            p[j+1] = g;
            p[j+2] = b;
        }
    }

    // allocate a texture name
    glGenTextures(1, &texture);

    // select our current texture
    glBindTexture(GL_TEXTURE_2D, texture);

    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    //modulate: mix texture with color for shading. only makes sense with lights present.
    //decal: texture color directly

    // when texture area is small, bilinear filter the closest mipmap
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
            GL_LINEAR_MIPMAP_NEAREST);
    // when texture area is large, bilinear filter the first mipmap
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // if wrap is true, the texture wraps over at the edges (repeat)
    //       ... false, the texture ends at the edges (clamp)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
            wrap ? GL_REPEAT : GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
            wrap ? GL_REPEAT : GL_CLAMP);

    // build our texture mipmaps because we set mipmap option
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, I.rows, I.cols,
            GL_RGB, GL_UNSIGNED_BYTE, I.data);

    return texture;
}

GLfloat PERSON_H = 1.7; //person height
GLfloat PERSON_R = 0.3; //the person is a cylinder of 30cm radius
GLfloat PERSON_SPEEDS[] = {0.5,2.0,5.0}; //the 3 speeds in m/s
GLfloat PERSON_LOOK_DOWN = -.2; //how much the person looks down
GLfloat WALL_H = 2.0; //wall height
GLfloat WALL_L = 20.0; //wall length
GLfloat WALL_HL = WALL_L/2.; //wall half-length
GLfloat SKY_H = 100.0;
GLfloat SKY_HL = 1000000.0;
GLfloat SKY_TEX_COORD = SKY_HL/100.0; //how many times the sky pattern is put on the sky
GLfloat ROT_SPEED_MAX = M_PI/4.0; //maximum rotation speed

GLint WINDOW_W = 700;
GLint WINDOW_H = 700;
GLint WINDOW_POSX = 10;
GLint WINDOW_POSY = 10;

Vector3D center = Vector3D(0.0,PERSON_H,0.0); //head position.
Vector3D eye = Vector3D(1.0,0.0,0.0); //eye direction of the person.
Vector3D lookat = center + eye;

GLfloat speed = PERSON_SPEEDS[1]; //speed forward
GLfloat rot_speed = 0.;//rotation speed in rad/s

GLfloat upx=0.0;
GLfloat upy=1.0;
GLfloat upz=0.0;

GLfloat frustrum_min = PERSON_R/2.;
GLfloat frustrum_max = 10000.0;
GLfloat frustrum_l = PERSON_R/6.;

GLfloat WHITE[] = {1.0, 1.0, 1.0};
GLfloat GRAY[] = {.5, .5, .5};
GLfloat DARK_GRAY[] = {.15, .15, .15};
GLfloat BLACK[] = {0.0, 0.0, 0.0};
GLfloat RED[] = {1.0, 0.0, 0.0};
GLfloat GREEN[] = {0.0, 1.0, 0.0};
GLfloat BLUE[] = {0.0, 0.0, 1.0};

enum NTEXTURES {NTEXTURES = 3};
string texture_files[] = {"grass.jpg", "wood.jpg", "sky.jpg"};
GLuint textures[NTEXTURES];

GLfloat clear_color_r = 0.0;
GLfloat clear_color_g = 0.0;
GLfloat clear_color_b = 0.0;

GLfloat fast_forward = 1.0;

// Room corners.
static GLfloat vs[][3] = {
    {-WALL_HL, 0,-WALL_HL},
    {-WALL_HL, 0, WALL_HL},
    {-WALL_HL, WALL_H,-WALL_HL},
    {-WALL_HL, WALL_H, WALL_HL},
    { WALL_HL, 0,-WALL_HL},
    { WALL_HL, 0, WALL_HL},
    { WALL_HL, WALL_H,-WALL_HL},
    { WALL_HL, WALL_H, WALL_HL},
};

int old_t = 0;

void init(int argc, char** argv) {
    int i;
    glutInit(&argc, argv);
    glShadeModel(GL_FLAT);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_W, WINDOW_H);
    glutInitWindowPosition(WINDOW_POSX, WINDOW_POSY);
    glutCreateWindow(argv[0]);
    glClearColor(clear_color_r,clear_color_g,clear_color_b,1.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glEnable(GL_POLYGON_OFFSET_LINE);
    glEnable(GL_DEPTH_TEST);
    glPolygonOffset(1.0, 1.0);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    for (i = 0; i < NTEXTURES; i++) {
        textures[i] = loadTextureJpg(texture_files[i], 1);
    }
}

void calc_new_scene(void) {

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

    eye.rotY(rot_speed*dt);
    new_center = center + eye*speed*dt;

    if (fabs(new_center.x) > WALL_HL-PERSON_R) {
        //dont move
    } else if (fabs(new_center.z) > WALL_HL-PERSON_R) {
        //dont move
    } else{//move and normal update
        center = new_center;
    }

    glutPostRedisplay();
}

void draw_cube() {

    GLfloat TEX_COORD = 10.;

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);

    //bottom
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0,       0.0     ); glVertex3fv(vs[0]);
    //1.0 means put 1 time the texture in that dimension
    //2.0 means put 2 times the texture in that dimension: it becomes smaller thus.
    glTexCoord2f(0.0,       TEX_COORD); glVertex3fv(vs[1]);
    glTexCoord2f(TEX_COORD, TEX_COORD); glVertex3fv(vs[5]);
    glTexCoord2f(TEX_COORD, 0.0     ); glVertex3fv(vs[4]);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textures[1]);

    glBegin(GL_QUADS);
    //back
    glTexCoord2f(0.0,       0.0); glVertex3fv(vs[0]);
    glTexCoord2f(TEX_COORD, 0.0); glVertex3fv(vs[1]);
    glTexCoord2f(TEX_COORD, 1.0); glVertex3fv(vs[3]);
    glTexCoord2f(0.0,       1.0); glVertex3fv(vs[2]);

    //front
    glTexCoord2f(0.0,       0.0); glVertex3fv(vs[4]);
    glTexCoord2f(TEX_COORD, 0.0); glVertex3fv(vs[5]);
    glTexCoord2f(TEX_COORD, 1.0); glVertex3fv(vs[7]);
    glTexCoord2f(0.0,       1.0); glVertex3fv(vs[6]);

    //right
    glTexCoord2f(0.0,       0.0); glVertex3fv(vs[0]);
    glTexCoord2f(0.0,       1.0); glVertex3fv(vs[2]);
    glTexCoord2f(TEX_COORD, 1.0); glVertex3fv(vs[6]);
    glTexCoord2f(TEX_COORD, 0.0); glVertex3fv(vs[4]);

    //left
    glTexCoord2f(0.0,       0.0); glVertex3fv(vs[1]);
    glTexCoord2f(0.0,       1.0); glVertex3fv(vs[3]);
    glTexCoord2f(TEX_COORD, 1.0); glVertex3fv(vs[7]);
    glTexCoord2f(TEX_COORD, 0.0); glVertex3fv(vs[5]);
    glEnd();

    //sky
    glBindTexture(GL_TEXTURE_2D, textures[2]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0,       0.0     ); glVertex3f(-SKY_HL,SKY_H,-SKY_HL);
    glTexCoord2f(0.0,       SKY_TEX_COORD); glVertex3f(-SKY_HL,SKY_H,SKY_HL);
    glTexCoord2f(SKY_TEX_COORD, SKY_TEX_COORD); glVertex3f(SKY_HL,SKY_H,SKY_HL);
    glTexCoord2f(SKY_TEX_COORD, 0.0     ); glVertex3f(SKY_HL,SKY_H,-SKY_HL);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void draw_scene(void) {
    glLoadIdentity();
    lookat = center+eye;
    gluLookAt(center.x, center.y, center.z, lookat.x, lookat.y + PERSON_LOOK_DOWN, lookat.z, upx, upy, upz);
    draw_cube();
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
    glFrustum(-frustrum_l, frustrum_l, -frustrum_l, frustrum_l, frustrum_min, frustrum_max);
    glMatrixMode(GL_MODELVIEW);
}

void keyDown(unsigned char key, int x, int y) {
    switch(key) {
        case 's':
            rot_speed = ROT_SPEED_MAX;
            break;
        case 'd':
            rot_speed = -ROT_SPEED_MAX;
            break;
        case 'e':
            speed = PERSON_SPEEDS[2];
            break;
        case 'x':
            speed = PERSON_SPEEDS[0];
            break;
        case 27:
            exit(0);
            break;
    }
}

void keyUp(unsigned char key, int x, int y) {
    switch(key) {
        case 's':
            rot_speed = 0.;
            break;
        case 'd':
            rot_speed = 0.;
            break;
        case 'e':
            speed = PERSON_SPEEDS[1];
            break;
        case 'x':
            speed = PERSON_SPEEDS[1];
            break;
    }
}

int main(int argc, char** argv) {
    init(argc,argv);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(calc_new_scene);
    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);
    glutMainLoop();
    return 0;
}
