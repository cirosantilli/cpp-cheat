/* Enable POSIX 7 definitions on the headers.
 *
 * This must come before including any other headers, because POSIX
 * defines extensions inside ANSI C headers.
 *
 * POSIX 7 says http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap02.html:
 *
 * > For the C programming language, shall define _XOPEN_SOURCE to be 700 before any header is included
 *
 * See also: https://stackoverflow.com/questions/5378778/what-does-d-xopen-source-do-mean
 */
#define _XOPEN_SOURCE 700

/* ANSI C, many with POSIX extensions. */
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
#include <semaphore.h>
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
#include <unistd.h> /* read, fork, ftruncate, write */

#define COMMON_UNUSED(x) (void)(x)
#define TMPFILE_EXT ".tmp"
#define TMPFILE(x) __FILE__ "__" x TMPFILE_EXT

union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                (Linux-specific) */
};
