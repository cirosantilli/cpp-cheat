/* # stdio.h */

#include "common.h"

int main(void) {
    {
        fputs("stderr\n", stderr);
    }

    /*
    # stdout

        Sames as stderr but for stdout.

        Less useful than `stderr` since most IO functions have a convenience form that writes to stdout.
    */
    {
        fputs("stdout\n", stdout);
    }

    /*
    # stdin

        be careful!! stdin won't return EOF automatically

        For a tty you can tell the user to input a EOF (ctrl d in linux, ctrl z in windows)
        but as you see this is system dependent. for pipes I am yet to find how to do this,
        might be automatic when process closes only.

        The best way to know that a stdin ended is recognizing some specific
        pattern of the input, such as a newline with fgets, or the end of a
        number with scanf

        Before this comes, the program just stops waiting for the stdin to
        produce this, either from user keyboard input, or from the program
        behind the pipe.
    */

    /* # Stream output */
    {
        /*
        # putchar

            Write single char to stdout.

            Basically useless subset of putc which writes to any stream,
            and very slow since it may mean several stream IO operations.
        */
        {
            putchar('p');
            putchar('u');
            putchar('t');
            putchar('c');
            putchar('h');
            putchar('a');
            putchar('r');
            putchar('\n');
        }

        /*
        # putc

            putchar to any stream.

            Why is it not called fputc?
        */
        {
            putc('p', stdout);
            putc('u', stdout);
            putc('t', stdout);
            putc('c', stdout);
            putc('\n', stdout);
        }

        /*
        # puts

            Write to stdout.

            Newline appended at end.
        */
        {
            puts("puts");
        }

        /*
        # fputs

            Write to any stream.

            Unlike puts, *no* newline is automatically appended at end!

            Very confusing.
        */
        {
            fputs("fputs\n", stdout);
        }

        /*
        # sprintf

            Same as printf, but stores result in a given string.

            Make sure that the string is large enough to contain the output.

            If this is a hard and important task, consider `snprintf` + malloc.
        */
        {
            char cs[] = "123";
            char cs2[sizeof(cs)];
            sprintf(cs2, "%s", cs);
            assert(strcmp(cs, cs2) == 0);
        }

        /*
        # fprintf

            Same as printf, but to an arbitrary stream
        */
        {
            assert(fprintf(stdout, "fprintf = %d\n", 1) == 12);
        }

        /*
        Large strings to stdout

            stdout it line buffered

            if you fill up the buffer without any newlines it will just print

            buffer size cannot be accessed programmatically

            TODO what is the bin buffer size? in practice, 1024 works just fine
            it may be much larger than BUFSIZ.
        */
        {
            enum N { N = 100000 };
            char buf[N];
            memset(buf, 'z', N);
            buf[N] = '\0';
            buf[N/2] = '\n';
            /* large amount of 'z's verywhere!  */
            /*printf("%s\n", buf);*/
        }
    }


    /* # stream input */
    {
#if __STDC_VERSION__ < 201112L
        /*
        # gets

            Deprecated, removed in C11.

            Dangerous: no size checking possible
            if too much input, just seg faults.
        */
        if (0) {
            /*printf("enter a string terminated by newline: (max %d chars, newline will be included in the string)\n", sn);*/
            /*gets(s);*/
            /*printf("you entered:\n%s\n\n",s);*/
        }
#endif

        /*
        # fgets

            Reads up to whichever comes first:

            - a newline char
            - buff_size - 1 chars have been read
            - the end of file was reached

            if the input comes from stdin on a tty
            and if user inputs more than the buffer size, this will wait until the user enters
            <enter>, and only at that point will those bytes be made available for `fgets`,
            the exceding chars remaining in the buffer if you try to read again.

            saves result in buff, '\0' terminated

            this is the safest method io method to get a line at time,
            since it allows the programmer to deal with very long lines.

            the trailing newline is included in the input.
        */
        if (0) {
            FILE* fp = stdin;
            const int buff_size = 4;
            char buff[buff_size];
            fprintf(stderr, "enter a string and press enter (max %d bytes):\n", buff_size - 1);
            if (fgets(buff, buff_size, fp) == NULL) {
                if (feof(fp)) { fprintf(stderr, "fgets was already at the end of the stream and read nothing");
                } else if (ferror(fp)) {
                    fprintf(stderr, "fgets error reading from stream");
                }
            }
            /* Some bytes are left in the buffer, may want to reread it. */
            else if (!feof(fp)) {
                /* TODO why does this not work with stdin from a tty nor pipe? */
                /* Why is EOF not reached even if user inputs 1 single char? */
                /*fprintf(stderr, "you entered more than the maximum number of bytes\n");*/
            }
            fprintf(stderr, "you entered:\n%s", buff);
        }

        /*
        # scanf

            complicated behaviour

            input is space separated regardless of scanf string

            hard to do error checking

            stops reading at newline

            use only if error checking is not a priority

            to do proper error checking, try `fgets` and the `strtol` family
        */
        if (0) {
            int i, j;
            unsigned int ui;
            float f;
            printf("enter an integer in decimal and <enter> (max 32 bits signed):\n");
            i = scanf("%d", &i);
            printf("you entered: %d\n", i);
            /* stuff is space separated */
            /* try 123 456 789 at once. 456 789 stay in the buffer, and are eaten by the second scanf */

            printf("enter an integer, a space, an integer and a <enter> (max 32 bits signed):\n");
            i = scanf("%d %d", &i, &j);
            printf("you entered: %d %d\n", i, j);

            printf("enter a float and a newline:\n");
            i = scanf("%f", &f);
            printf("you entered: %.2f\n", f);

            printf("enter an integer in hexadecimal and a <enter>: (max 32 bits signed)\n");
            i = scanf("%x", &ui);
            printf("you entered (in decimal): %d\n", i);
        }

        /*
        # fscanf

            complicated like scanf
        */
        if (0) {
            FILE* fp = stdin;
            int i;
            float f;
            puts("enter a int a space and a float (scientific notation) and then EOF (ctrl-d in linux):");
            if (fscanf(stdin, "%d %e\n", &i, &f) != 2) {
                if (feof(fp)) {
                    fprintf(stderr, "fscanf reached the of file and read nothing\n");
                } else if (ferror(fp)) {
                    fprintf(stderr, "fscanf error reading from stream\n");
                }
            }
            fprintf(stderr, "you entered: %d %.2e\n", i, f);
        }
    }

    /* # File IO */
    {
        int elems_write[] = {1, 2, 3};
        enum constexpr {nelems = sizeof(elems_write) / sizeof(elems_write[0])};
        int elems_read[nelems];
        FILE *fp;
        char path[] = COMMON_TMPFILE_NAMED("fwrite");

        /*
        # fwrite

            Returns number of elements written.

            If less elements are written than required an error occurred.

            Why take both bytes per item and items instead of just total bytes:
            http://stackoverflow.com/questions/295994/what-is-the-rationale-for-fread-fwrite-taking-size-and-count-as-arguments

            It seems that no less than size per item can be written, so we are guaranteed
            that some object will not be half written.

            The byte order is implementation defined.
            This is therefore not a valid way to serialize data across machines.
        */
        {
            fp = fopen(path, "wb");
            if (fp == NULL) {
                COMMON_IO_ERROR("fopen", path);
            } else {
                if (fwrite(elems_write, sizeof(elems_write[0]), nelems, fp) < nelems) {
                    COMMON_IO_ERROR("fwrite", path);
                }
                if (fclose(fp) == EOF) {
                    COMMON_IO_ERROR("fclose", path);
                }
            }
        }

        /*
        # fread

            Returns number of *elements* written, not bytes.

            If less elements are returned than required then either:

            - an error ocured
            - the end of file was reached.

            It is only possible to distinguish between those cases by using
            the `feof` and `ferror` functions.

        # ferror

        # feof
        */
        {
            fp = fopen(path, "rb");
            if (fp == NULL) {
                COMMON_IO_ERROR("fopen", path);
            }
            else {
                if (fread(elems_read, sizeof(elems_read[0]), nelems, fp) < nelems && ferror(fp)) {
                    COMMON_IO_ERROR("fread", path);
                }
            }
            if (fclose(fp) == EOF) {
                COMMON_IO_ERROR("fclose", path);
            }
        }
        assert(memcmp(elems_read, elems_write, nelems) == 0);
    }

    /* # Applications */
    {
        /*
        # Linewise file processing

            Process a file linewise.

            Allows one to read files larger than RAM, suppposing that each line is smaller than RAM.

            glibc and C++ stdlib offer the `getline` function which does it.

            There does not seem to be such a function in C! http://stackoverflow.com/questions/3501338/c-read-file-line-by-line
        */
        {
            FILE* fp;
            /* Maximum accepted line length is buf_size including the newline. */
            enum Constexpr {buffer_size = 4};
            char buffer[buffer_size];
            size_t last_newline_pos, current_pos;
            int linenum = 0;
            long file_size;
            long nbytes_read;

            char path[] = COMMON_TMPFILE_NAMED("cat");
            char file_data[] = "abc\nde\nfgh";
            size_t file_data_size = strlen(file_data);
            char lines[3][4] = {"abc\n", "de\n", "fgh\n"};
            size_t current_line;

            /* Prepare test. */
            fp = fopen(path, "wb");
            if (fp == NULL) {
                COMMON_IO_ERROR("fopen", path);
            } else {
                if (fwrite(file_data, 1, file_data_size, fp) < file_data_size) {
                    COMMON_IO_ERROR("fwrite", path);
                }
                if (fclose(fp) == EOF) {
                    COMMON_IO_ERROR("fclose", path);
                }
            }

            /* The actual cat. */
            /*
            fp = fopen(path, "rb");
            if (fp == NULL) {
                COMMON_IO_ERROR("fopen", path);
            } else {
                nbytes_read = buffer_size;
                last_newline_pos = buffer_size;
                current_line = 0;
                while (fread(buffer, 1, nbytes_read, fp) == nbytes_read) {
                    while (current_pos != last_newline_pos)
                        if (buffer[current_pos] == '\n') {
                            assert(memcmp(&buffer[current_pos], lines[current_line],  ));
                            last_newline_pos = current_pos;
                            cur_line++;
                        }
                        current_pos = (current_pos + 1) % buffer_size;
                    }
                }
                if (feof(fp)) {
                    COMMON_IO_ERROR("fread", path);
                }
                if (fclose(fp) == EOF) {
                    COMMON_IO_ERROR("fclose", path);
                }
            }
            */
        }
    }

    return EXIT_SUCCESS;
}
