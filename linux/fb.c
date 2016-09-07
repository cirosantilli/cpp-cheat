/*
Framebuffer device /dev/fb0

Adapted from:
http://stackoverflow.com/questions/4996777/paint-pixels-to-screen-via-linux-framebuffer

More examples:

- https://github.com/prpplague/fb-test-app
- https://gist.github.com/robmint/4753401
- http://stackoverflow.com/a/14809058/895245

https://en.wikipedia.org/wiki/Linux_framebuffer

To run this, you must:

- be on a TTY, e.g. Ctrl + Alt + F2 on Ubuntu
- add yourself to the `video` group (the group of /dev/fb0 on Ubuntu 16.04) with `sudo usermod -aG video "$USER"`,
    logout and login again , or use sudo
- have kernel support, I think with `CONFIG_FB=y` and related options.
    http://unix.stackexchange.com/questions/33596/no-framebuffer-device-how-to-enable-it

Expected outcome: pink square is printed on screen.
If any terminal text scrolls over it, those square get overwritten.
Get rid of terminal for good:
- http://stackoverflow.com/questions/32620019/c-linux-how-to-takeover-the-framebuffer
- http://stackoverflow.com/questions/14805294/using-linux-framebuffer-for-graphics-but-disabling-console-text

Other things to try:

    printf 'a\nb' sudo tee /dev/fb0 /dev/null

Prints text to current cursor position, thus same as stdout. So we see that fb0 can also do text oriented drawing.
This is different from this program, since here the mmap syscall is used.

TODO: why a single /dev/fb0 on my laptop? Because a single display?

Video and images:

- http://askubuntu.com/questions/46871/how-can-i-play-videos-in-a-framebuffer
- http://unix.stackexchange.com/questions/226995/how-to-watch-films-images-without-x

General apps: not possible if they pass through X11: http://unix.stackexchange.com/questions/22757/how-to-run-an-app-in-a-framebuffer

But SDL 1 notably can render to fbdev. And you could make a GUI in it with AntTweakBar,
which is a platform agnostic pixel manipulation library.
But it looks like SDL2 cannot anymore: http://forums.libsdl.org/viewtopic.php?t=9661&sid=47b3f4fde203ea5710a798bb6093b8dd

Related:

- http://raspberrypi.stackexchange.com/questions/42628/has-anyone-managed-to-get-sdl-2-3-working-without-x-in-raspbian
- http://stackoverflow.com/questions/14615732/how-to-get-sdl-to-use-fbcon-not-caca
- http://stackoverflow.com/questions/26110581/is-there-a-way-to-config-xorg-to-use-a-framebuffer-device-as-the-primary-monitor

There is the NetSurf browser which is implemented like that: TODO failing in Ubuntu 16.04 with:
http://askubuntu.com/questions/817937/how-to-run-netsurf-fb-fails-with-unable-to-set-video-could-not-set-console-s
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

int main(void) {
    char *fbp = 0;
    int fbfd = 0;
    int x = 0, y = 0;
    long int location = 0;
    long int screensize = 0;
    struct fb_fix_screeninfo finfo;
    struct fb_var_screeninfo vinfo;

    /* Open the file for reading and writing */
    fbfd = open("/dev/fb0", O_RDWR);
    if (fbfd == -1) {
        perror("Error: cannot open framebuffer device");
        exit(1);
    }
    printf("The framebuffer device was opened successfully.\n");

    /* Get fixed screen information */
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
        perror("Error reading fixed information");
        exit(2);
    }

    /* Get variable screen information */
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        perror("Error reading variable information");
        exit(3);
    }

    printf(
        "vinfo.xres = %d\n"
        "vinfo.yres = %d\n"
        "vinfo.bits_per_pixel = %d\n"
        "vinfo.xoffset = %d\n"
        "vinfo.yoffset = %d\n"
        "finfo.line_length = %d\n",
        vinfo.xres,
        vinfo.yres,
        vinfo.bits_per_pixel,
        vinfo.xoffset,
        vinfo.yoffset,
        finfo.line_length
    );

    /* Figure out the size of the screen in bytes */
    screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

    /* Map the device to memory */
    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if (fbp == (void *)-1) {
        perror("Error: failed to map framebuffer device to memory");
        exit(4);
    }

    /* Where we are going to put the pixel */
    x = 100; y = 100;

    /* Figure out where in memory to put the pixel */
    for (y = 100; y < 300; y++) {
        for (x = 100; x < 300; x++) {
            location = (x + vinfo.xoffset) * (vinfo.bits_per_pixel / 8) +
                       (y + vinfo.yoffset) * finfo.line_length;
            if (vinfo.bits_per_pixel == 32) {
                /* Blue. */
                *(fbp + location) = 100;
                /* Green. */
                *(fbp + location + 1) = 15 + (x - 100) / 2;
                /* Red. */
                *(fbp + location + 2) = 200 - (y - 100) / 5;
                /* No transparency. */
                *(fbp + location + 3) = 0;
                //location += 4;
            } else {
                /* assume 16bpp */
                int b = 10;
                int g = (x - 100) / 6;
                int r = 31 - (y - 100) / 16;
                unsigned short int t = r << 11 | g << 5 | b;
                *((unsigned short int*)(fbp + location)) = t;
            }

        }
    }
    munmap(fbp, screensize);
    close(fbfd);
    return 0;
}
