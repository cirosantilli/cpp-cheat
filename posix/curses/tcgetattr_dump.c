/* Commented out prints are not implemented in Linux,
 * they are documented in man tcgetattr */

/* GNU extensions needed for several of the values. */
#define _GNU_SOURCE
#include <curses.h>
#include <stdio.h>
#include <inttypes.h>
#include <termios.h>
#include <unistd.h>

#define PRINT(field, flag) printf(#field "." #flag " %zu\n", (uintmax_t)termio.field & flag);

int main(void) {
    struct termios termio;
    tcgetattr(fileno(stdin), &termio);
    PRINT(c_iflag, ICRNL);
    PRINT(c_iflag, IGNBRK);
    PRINT(c_iflag, IGNCR);
    PRINT(c_iflag, IMAXBEL);
    PRINT(c_iflag, INLCR);
    PRINT(c_iflag, INPCK);
    PRINT(c_iflag, ISTRIP);
    PRINT(c_iflag, IUCLC);
    PRINT(c_iflag, IUTF8);
    PRINT(c_iflag, IXANY);
    PRINT(c_iflag, IXOFF);
    PRINT(c_iflag, IXON);
    puts("");

    PRINT(c_oflag, BSDLY);
    PRINT(c_oflag, CRDLY);
    PRINT(c_oflag, FFDLY);
    PRINT(c_oflag, NLDLY);
    PRINT(c_oflag, OCRNL);
    PRINT(c_oflag, OFDEL);
    PRINT(c_oflag, OFILL);
    PRINT(c_oflag, OLCUC);
    PRINT(c_oflag, ONLCR);
    PRINT(c_oflag, ONLRET);
    PRINT(c_oflag, ONOCR);
    PRINT(c_oflag, OPOST);
    PRINT(c_oflag, TABDLY);
    PRINT(c_oflag, VTDLY);
    puts("");

    PRINT(c_cflag, CBAUD);
    PRINT(c_cflag, CBAUDEX);
    PRINT(c_cflag, CIBAUD);
    PRINT(c_cflag, CLOCAL);
    PRINT(c_cflag, CMSPAR);
    PRINT(c_cflag, CREAD);
    PRINT(c_cflag, CRTSCTS);
    PRINT(c_cflag, CSIZE);
    PRINT(c_cflag, CSTOPB);
    PRINT(c_cflag, HUPCL);
    /* PRINT(c_cflag, LOBLK); */
    PRINT(c_cflag, PARENB);
    PRINT(c_cflag, PARODD);
    puts("");

    PRINT(c_lflag, ISIG);
    PRINT(c_lflag, ICANON);
    PRINT(c_lflag, XCASE);
    PRINT(c_lflag, ECHO);
    PRINT(c_lflag, ECHOE);
    PRINT(c_lflag, ECHOK);
    PRINT(c_lflag, ECHONL);
    PRINT(c_lflag, ECHOCTL);
    PRINT(c_lflag, ECHOPRT);
    PRINT(c_lflag, ECHOKE);
    /* PRINT(c_lflag, DEFECHO); */
    PRINT(c_lflag, FLUSHO);
    PRINT(c_lflag, NOFLSH);
    PRINT(c_lflag, TOSTOP);
    PRINT(c_lflag, PENDIN);
    PRINT(c_lflag, IEXTEN);
    PRINT(c_lflag, VDISCARD);
    /* PRINT(c_lflag, VDSUSP); */
    PRINT(c_lflag, VEOF);
    PRINT(c_lflag, VEOL);
    PRINT(c_lflag, VEOL2);
    PRINT(c_lflag, VERASE);
    PRINT(c_lflag, VINTR);
    PRINT(c_lflag, VKILL);
    PRINT(c_lflag, VLNEXT);
    PRINT(c_lflag, VMIN);
    PRINT(c_lflag, VQUIT);
    PRINT(c_lflag, VREPRINT);
    PRINT(c_lflag, VSTART);
    /* PRINT(c_lflag, VSTATUS); */
    PRINT(c_lflag, VSTOP);
    PRINT(c_lflag, VSUSP);
    /* PRINT(c_lflag, VSWTCH); */
    PRINT(c_lflag, VTIME);
    PRINT(c_lflag, VWERASE);
    puts("");

    return 0;
}
