/*
# Feature macros

# XOPEN_SOURCE

# GNU_SOURCE

    Most glibc extensions are contained inside existing POSIX headers.

    To enable them, you must define a feature macro.

    There are different feature macros, each anabling a different set of functions,

    You can get info on those macros with:

        man feature_test_macros

    Some common ones are:

    - `_XOPEN_SOURCE`: enables a given POSIX version. Defined in POSIX
    - `_GNU_SOURCE`: enables everyting on the GLIBC.

    The feature macro definition *must* come before includes header so that the
    preprocessor can see it when it inteprets the header.

# LSB

    Linux standard base seems to require only the two following gnu extensions to be available:

    - gnu_get_libc_version() returns a string that identifies the version of the C library running the program making the call.
    - gnu_get_libc_release()

    All the other functions seem to be present on all Linux distros only because glibc is a de-facto standard. TODO any others?

# glibc vs gnulib

    gnulib seems is meant to be a source of code to be copied pasted, not preinstalled.

    However some stuff such as `gnu_get_libc_release` seems to be only documented there,
    and comes with glibc. TODO I'm confused.

    <http://stackoverflow.com/questions/2240120/glibc-glib-and-gnulib>
*/

#include "common.h"

int main() {
    printf("gnu_get_libc_version() = %s\n", gnu_get_libc_version());

    /*
    # string.h
    */
    {
        /*
        # strfry

            Create anagrams inplace.

            Return the string itself.
        */
        {
            char s[] = "abcd";
            puts("strfry(\"abcd\")");
            printf("  %s\n", strfry(s));
            printf("  %s\n", strfry(s));
        }
    }

    /*
    # sched.h

        More scheduling policies are defined.

        Those constants have the same meaning as in the kernel code versions.
    */
    {
        printf("SCHED_BATCH = %d\n", SCHED_BATCH);
        printf("SCHED_IDLE  = %d\n", SCHED_IDLE );

        /* Called SCHED_NORMAL in the kernel: */
        printf("SCHED_OTHER = %d\n", SCHED_OTHER);

        /*
        # sched_getaffinity

            view in which cpu's the given process can run

            Linux keeps track of this, and this can be set with appropriate premissions

        # sched_setaffinity

            set for getaffinity

        # cpu_set_t

            a bitmap with a field per cpu
        */
        {
            cpu_set_t mask;
            if (sched_getaffinity(0, sizeof(cpu_set_t), &mask) == -1) {
                perror("sched_getaffinity");
                exit(EXIT_FAILURE);
            } else {
                printf("sched_getaffinity = ");
                unsigned int i;
                for (i = 0; i < sizeof(cpu_set_t); i++) {
                    printf("%d", CPU_ISSET(0, &mask));
                }
                printf("\n");
            }
        }
    }

    /*
    # unistd.h
    */
    {
        /*
        # sysconf

            Sysconf extensions.
        */
        {
            /*
            Find the number of processors.
            Seems not to be possible in POSIX:
            http://stackoverflow.com/questions/2693948/how-do-i-retrieve-the-number-of-processors-on-c-linux

            - conf: configured on kernel.
            - onln: online, that is currently running. Processors can be disabled.

            */
            {
                printf("_SC_NPROCESSORS_ONLN = %ld\n", sysconf(_SC_NPROCESSORS_ONLN));
                printf("_SC_NPROCESSORS_CONF = %ld\n", sysconf(_SC_NPROCESSORS_CONF));
            }
        }
    }

    /*
    # readline

        Read one line from a file:
        <http://stackoverflow.com/questions/3501338/c-read-file-line-by-line>
    */

    /*
    # stime

        Set time retreived by time system call.
    */

    /*
    # acct

        Write acconting information on process that start and end to given file.

        Given file must exist.

        Must be sudo to do it.

        Description of output under:

            man 5 acct
    */
    {
        char *fname = "acct.tmp";
        if (creat(fname, S_IRWXU) == -1) {
            /* May fail because the file was owned by root. */
            perror("creat");
        }
        if (acct(fname) == -1) {
            perror("acct");
            /* May happen if we are not root. */
        }
    }

    /*
    # uselib

        Load dynamic library.
    */
    {
        /* TODO */
    }

    /*
    # swapon

        Manage in shich devices swap memory can exist.

    # swapoff
    */
    {
        /* TODO */
    }

    return EXIT_SUCCESS;
}
