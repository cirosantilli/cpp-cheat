/*
x11 c interface hello world

Expected outcome: shows a window with white background
and a black X drawn on it.

Exit when either:

- the X close button of the window is clicked
- a mouse on the window is released
*/

#include <stdlib.h>

#include "X11/Xlib.h"

int main(void) {
    Display *dsp = XOpenDisplay(NULL);
    if (!dsp){ return EXIT_FAILURE; }
    int screenNumber = DefaultScreen(dsp);
    unsigned long white = WhitePixel(dsp, screenNumber);
    unsigned long black = BlackPixel(dsp, screenNumber);
    Window win = XCreateSimpleWindow(
            dsp,
            DefaultRootWindow(dsp),
            50, 50,
            200, 200,
            0, black,
            white);
    XMapWindow(dsp, win);
    long eventMask = StructureNotifyMask;
    XSelectInput(dsp, win, eventMask);
    XEvent evt;
    do {
        XNextEvent(dsp, &evt);
    } while (evt.type != MapNotify);
    GC gc = XCreateGC(dsp, win, 0, NULL);
    XSetForeground(dsp, gc, black);
    XDrawLine(dsp, win, gc, 10,  10, 190, 190);
    XDrawLine(dsp, win, gc, 10, 190, 190,  10);
    eventMask = ButtonPressMask | ButtonReleaseMask;
    XSelectInput(dsp, win, eventMask);
    do {
        XNextEvent(dsp, &evt);
    } while (evt.type != ButtonRelease);
    XDestroyWindow(dsp, win);
    XCloseDisplay(dsp);
    return EXIT_SUCCESS;
}
