/*
# Headers

    List of all headers: http://en.wikipedia.org/wiki/C_POSIX_library

    POSIX defines certain things *inside*
    headers with the same name as the ANSI stdlib ones
    which are only activated if you add the defines *before
    including those files*!

    GCC: if you want to access them with the `-ansi -c99` flags,
    you need to define `XXX_XOPEN_SOURCE`

    There are other preprocessor defines which may expose POSIX functions
    such as `_POSIX_C_SOURCE` and `POSIX_SOURCE`

    For the GNU C library, see:

        man feature_test_macros

    for an explanation.

    The actual value of the preprocessor refers to the POSIX version. For example:

    - 500: issue 5, 1995
    - 600: issue 6, 2004
    - 700: issue 7, 2008
*/

#define _XOPEN_SOURCE 700
/*#define _POSIX_C_SOURCE 200112L*/
/*#define POSIX_SOURCE*/

/* ANSI headers to which POSIX adds extensions. */
#include <assert.h>
#include <limits.h> /* NZERO */
#include <math.h> /* M_PI, M_PI_2, M_PI_4 */
#include <stdbool.h>
#include <stdio.h> /* popen(), perror() */
#include <stdint.h>
#include <stdlib.h>
#include <string.h> /* strerror, strdup */
#include <strings.h> /* ffs */

/* POSIX only headers. */
#include <arpa/inet.h>
#include <curses.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h> /* creat, O_CREAT */
#include <libgen.h>
#include <monetary.h> /* strfmon */
#include <netdb.h> /* gethostbyname */
#include <netinet/in.h>
#include <poll.h>
#include <pthread.h>
#include <pwd.h> /* getpwuid, getpwnam, getpwent */
#include <regex.h>
#include <sched.h>
#include <signal.h>
#include <sys/mman.h> /* mmap, munmap */
#include <sys/ipc.h>
#include <sys/resource.h> /* rusage, getrusage, rlimit, getrlimit */
#include <sys/select.h> /* select, FD_ZERO, FD_SET */
#include <sys/sem.h> /* semget, semop, semctl */
#include <sys/shm.h> /* shmget, shmat, etc. */
#include <sys/socket.h>
#include <sys/stat.h> /* S_IRUSR and family, */
#include <sys/types.h> /* pid_t */
#include <sys/utsname.h> /* uname, struct utsname */
#include <sys/wait.h> /* wait, sleep */
#include <syslog.h> /* syslog */
#include <termios.h>
#include <unistd.h> /* read, fork, ftruncate */

#define TMPFILE(x) __FILE__ "__" x ".tmp"

union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                (Linux-specific) */
};
