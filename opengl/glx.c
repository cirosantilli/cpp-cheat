/*
# GLX

    http://stackoverflow.com/questions/879035/initializing-opengl-without-glut/36038230#36038230

    Example without GLUT, but rather GLX which is what GLUT uses in Linux as backend:
    https://www.opengl.org/discussion_boards/showthread.php/177999-GCC-OpenGL-without-glut?p=1239444&viewfull=1#post1239444

    GLX is the X11 API that interfaces with OpenGL.

    Requires -lGL -lGLU -lX11.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h>
#define GL_GLEXT_PROTOTYPES
#define GLX_GLXEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>

struct MyWin {
    Display  *display;
    Window win;
    int displayed;
    int width;
    int height;
};

const int WIN_XPOS = 256;
const int WIN_YPOS = 64;
const int WIN_XRES = 320;
const int WIN_YRES = 320;
const int NUM_SAMPLES = 4;

struct MyWin Win;

double elapsedMsec(const struct timeval *start, const struct timeval *stop) {
    return ((stop->tv_sec  - start->tv_sec ) * 1000.0 +
            (stop->tv_usec - start->tv_usec) / 1000.0);
}

void displayCB() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f( 0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glVertex3f( 1.0f, -1.0f, 0.0f);
    glEnd();
    glFlush();
    glXSwapBuffers(Win.display, Win.win);
}

void keyboardCB(KeySym sym, unsigned char key, int x, int y,
        int *setting_change) {
    switch (tolower(key)) {
        case 27:
            exit(EXIT_SUCCESS);
            break;
        case 'k':
            printf("You hit the 'k' key\n");
            break;
        case 0:
            switch (sym) {
                case XK_Left  :
                    printf("You hit the Left Arrow key\n");
                    break;
                case XK_Right :
                    printf("You hit the Right Arrow key\n");
                    break;
            }
            break;
    }
}

void reshapeCB(int width, int height) {
    Win.width = width;
    Win.height = height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

/* Try to find a framebuffer config that matches
 * the specified pixel requirements.
 */
GLXFBConfig chooseFBConfig(Display *display, int screen) {
    static const int Visual_attribs[] = {
        GLX_X_RENDERABLE  , True,
        GLX_DRAWABLE_TYPE , GLX_WINDOW_BIT,
        GLX_RENDER_TYPE   , GLX_RGBA_BIT,
        GLX_X_VISUAL_TYPE , GLX_TRUE_COLOR,
        GLX_RED_SIZE      , 8,
        GLX_GREEN_SIZE    , 8,
        GLX_BLUE_SIZE     , 8,
        GLX_ALPHA_SIZE    , 8,
        GLX_DEPTH_SIZE    , 24,
        GLX_STENCIL_SIZE  , 8,
        GLX_DOUBLEBUFFER  , True,
        GLX_SAMPLE_BUFFERS, 1,
        GLX_SAMPLES       , 4,
        None
    };
    int attribs [ 100 ] ;
    memcpy(attribs, Visual_attribs, sizeof(Visual_attribs));
    GLXFBConfig ret = 0;
    int fbcount;
    GLXFBConfig *fbc = glXChooseFBConfig(display, screen, attribs, &fbcount);
    if (fbc) {
        if (fbcount >= 1)
            ret = fbc[0];
        XFree(fbc);
    }
    return ret;
}

GLXContext createContext(Display *display, int screen,
        GLXFBConfig fbconfig, XVisualInfo *visinfo, Window window) {
#define GLX_CONTEXT_MAJOR_VERSION_ARB       0x2091
#define GLX_CONTEXT_MINOR_VERSION_ARB       0x2092
    typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*,
            GLXFBConfig, GLXContext, int, const int*);
    /* Verify GL driver supports glXCreateContextAttribsARB() */
    /*   Create an old-style GLX context first, to get the correct function ptr. */
    glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 0;
    GLXContext ctx_old = glXCreateContext(display, visinfo, 0, True);
    if (!ctx_old) {
        printf("Could not even allocate an old-style GL context!\n");
        exit(EXIT_FAILURE);
    }
    glXMakeCurrent (display, window, ctx_old) ;
    /* Verify that GLX implementation supports the new context create call */
    if (strstr(glXQueryExtensionsString(display, screen),
                "GLX_ARB_create_context") != 0)
        glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)
            glXGetProcAddress((const GLubyte *) "glXCreateContextAttribsARB");
    if (!glXCreateContextAttribsARB) {
        printf("Can't create new-style GL context\n");
        exit(EXIT_FAILURE);
    }
    /* Got the pointer.  Nuke old context. */
    glXMakeCurrent(display, None, 0);
    glXDestroyContext(display, ctx_old);

    /* Try to allocate a GL 4.2 COMPATIBILITY context */
    static int Context_attribs[] = {
        GLX_CONTEXT_MAJOR_VERSION_ARB, 4,
        GLX_CONTEXT_MINOR_VERSION_ARB, 2,
        GLX_CONTEXT_PROFILE_MASK_ARB , GLX_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
        /*GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB, */
        /*GLX_CONTEXT_FLAGS_ARB       , GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB, */
        /*GLX_CONTEXT_FLAGS_ARB       , GLX_CONTEXT_DEBUG_BIT_ARB, */
        None
    };
    GLXContext context = glXCreateContextAttribsARB(display, fbconfig, 0,
            True, Context_attribs);
    /* Forcably wait on any resulting X errors */
    XSync(display, False);
    if (!context) {
        printf("Failed to allocate a GL 4.2 context\n");
        exit(EXIT_FAILURE);
    }
    printf("Created GL 4.2 context\n");
    return context;
}

void createWindow() {
    /* Init X and GLX */
    Win.displayed = 0;
    Display *display = Win.display = XOpenDisplay(":0.0");
    if (!display)
        printf("Cannot open X display\n");
    int    screen   = DefaultScreen(display);
    Window root_win = RootWindow(display, screen);
    if (!glXQueryExtension(display, 0, 0))
        printf("X Server doesn't support GLX extension\n");
    /* Pick an FBconfig and visual */
    GLXFBConfig fbconfig = chooseFBConfig(display, screen);
    if (!fbconfig) {
        printf("Failed to get GLXFBConfig\n");
        exit(EXIT_FAILURE);
    }
    XVisualInfo *visinfo = glXGetVisualFromFBConfig(display, fbconfig);
    if (!visinfo) {
        printf("Failed to get XVisualInfo\n");
        exit(EXIT_FAILURE);
    }
    printf("X Visual ID = 0x%.2x\n", (int)visinfo->visualid);
    /* Create the X window */
    XSetWindowAttributes winAttr ;
    winAttr.event_mask = StructureNotifyMask | KeyPressMask ;
    winAttr.background_pixmap = None ;
    winAttr.background_pixel  = 0    ;
    winAttr.border_pixel      = 0    ;
    winAttr.colormap = XCreateColormap(display, root_win,
            visinfo->visual, AllocNone);
    unsigned int mask = CWBackPixmap | CWBorderPixel | CWColormap | CWEventMask;
    Window win = Win.win = XCreateWindow (display, root_win,
            WIN_XPOS, WIN_YPOS,
            WIN_XRES, WIN_YRES, 0,
            visinfo->depth, InputOutput,
            visinfo->visual, mask, &winAttr) ;
    XStoreName(Win.display, win, "My GLX Window");
    /* Create an OpenGL context and attach it to our X window */
    GLXContext context = createContext(display, screen, fbconfig, visinfo, win);
    if (! glXMakeCurrent(display, win, context))
        printf("glXMakeCurrent failed.\n");
    if (! glXIsDirect (display, glXGetCurrentContext()))
        printf("Indirect GLX rendering context obtained\n");
    /* Display the window */
    XMapWindow(display, win);
    if (! glXMakeCurrent(display, win, context))
        printf("glXMakeCurrent failed.\n");
    printf("Window Size    = %d x %d\n", WIN_XRES, WIN_YRES);
    printf("Window Samples = %d\n", NUM_SAMPLES);
}

void processXEvents(Atom wm_protocols, Atom wm_delete_window) {
    int setting_change = 0;
    while (XEventsQueued(Win.display, QueuedAfterFlush)) {
        XEvent event;
        XNextEvent(Win.display, &event);
        if(event.xany.window != Win.win)
            continue;
        switch (event.type) {
            case MapNotify:
                {
                    Win.displayed = 1;
                    break;
                }
            case ConfigureNotify:
                {
                    XConfigureEvent cevent = event.xconfigure;
                    reshapeCB(cevent.width, cevent.height);
                    break;
                }
            case KeyPress:
                {
                    char chr;
                    KeySym symbol;
                    XComposeStatus status;
                    XLookupString(&event.xkey, &chr, 1, &symbol, &status);
                    keyboardCB(symbol, chr, event.xkey.x, event.xkey.y,
                            &setting_change);
                    break;
                }
            case ClientMessage:
                {
                    if (event.xclient.message_type == wm_protocols &&
                            (Atom)event.xclient.data.l[0] == wm_delete_window) {
                        exit(EXIT_SUCCESS);
                    }
                    break;
                }
        }
    }
}

void mainLoop() {
    /* Register to receive window close events (the "X" window manager button) */
    Atom wm_protocols     = XInternAtom(Win.display, "WM_PROTOCOLS"    , False);
    Atom wm_delete_window = XInternAtom(Win.display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(Win.display, Win.win, &wm_delete_window, True);

    while (1) {
        /* Redraw window (after it's mapped) */
        if (Win.displayed)
            displayCB();

        /* Update frame rate */
        struct timeval last_xcheck = {0, 0};
        struct timeval now;
        gettimeofday(&now, 0);

        /* Check X events every 1/10 second */
        if (elapsedMsec(&last_xcheck, &now) > 100) {
            processXEvents(wm_protocols, wm_delete_window);
            last_xcheck = now;
        }
    }
}

int main(int argc, char *argv[]) {
    Win.width = WIN_XRES;
    Win.height = WIN_YRES;
    createWindow();

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);

    printf("Valid keys: Left, Right, k, ESC\n");
    printf("Press ESC to quit\n");
    mainLoop();
    return EXIT_SUCCESS;
}
