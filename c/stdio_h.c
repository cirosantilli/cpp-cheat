/*
# stdio.h

    stream Input and Output

    # stream

        An stream is an abstraction over different input/output methods
        such as regular files, stdin/stdout/stderr (pipes in linux), etc.
        so that all of them can be treated on an uniform basis once you opened the stream.

        Most functions have a form which outputs only to stdout,
        and most input functions have a form which reads only from sdtin
        coupled with a general form that outputs to any stream.

        Unfortunatelly, sometimes there are subtle differences between those two
        forms, so beawere!

    # FILE

        FILE is a macro that represents a stream object.

        Its name is FILE of course because files are one of the main types of streams.

        However, streams can represent other resources in the filesystem in general
        such as Linux FIFOs or sockets.

    # stream vs file descriptors

        A file descriptor is a POSIX concept and thus shall not be discussed here.
*/

#include "common.h"

#define TMPFILE(x) __FILE__ "__" x ".tmp"

/*
Standard action to take in case of an IO error.
*/
void io_error(char *function, char *path){
    fprintf(stderr, "eror: %s errno = %d, path = %s\n", function, errno, path);
    exit(EXIT_FAILURE);
}

/*
Returns the size of the given open `FILE*`.

If an error occurs, returns `-1L`.

Does not work for pipes.
*/
long fget_file_size(FILE *fp) {
    long oldpos;
    long return_value;
    oldpos = ftell(fp);
    if (oldpos == -1L) {
        return -1L;
    }
    if (fseek(fp, 0, SEEK_END) != 0) {
        return -1L;
    }
    return_value = ftell(fp);
    if (return_value == -1L) {
        return -1L;
    }
    /* retore old position */
    if (fseek(fp, oldpos , SEEK_SET) != 0) {
        return -1L;
    }
    return return_value;
}

/*
Same as `file_size`, but takes the path instead of a `FILE*`.
*/
long file_size(char *path) {
    FILE *fp;
    long return_value;
    fp = fopen(path, "r");
    if (fp == NULL) {
        return -1L;
    }
    return_value = fget_file_size(fp);
    if (fclose(fp) == EOF) {
        return -1L;
    }
    return return_value;
}

/*
Read the entire file to a char[] dynamically allocated inside this function.

Returns a pointer to the start of that array.

In case of any error, returns NULL.

The entire file must fit into the memory avilable to the program.

http://stackoverflow.com/questions/174531/easiest-way-to-get-files-contents-in-c
*/
char *file_read(char *path) {
    FILE *fp;
    char *buffer;
    long fsize;

    fp = fopen(path , "rb");
    if (fp==NULL) {
        return NULL;
    }
    fsize = fget_file_size(fp);
    if (fsize < 0){
        fprintf(stderr, "could not determine lenght of:\n%s\n", path);
        return NULL;
    }
    buffer = (char*)malloc(fsize);
    if (buffer == NULL) {
        return NULL;
    }
    if (fread(buffer, 1, fsize, fp) != fsize) {
        return NULL;
    }
    if (fclose(fp) == EOF){
        return NULL;
    }
    return buffer;
}

/*
Write null terminated string to file

Returns `-1` on failulre, 1 on success.
*/
int file_write(char *path, char *write_string) {
    long len;
    char *buffer;
    FILE *fp;

    fp = fopen(path, "wb");
    if (fp == NULL) {
        return -1;
    }
    len = strlen(write_string);
    /* copy the file into the buffer: */
    if (fwrite(write_string, 1, len, fp) != len) {
        return -1;
    }
    if (fclose(fp) == EOF) {
        return -1;
    }
    return 0;
}

/*
writes an array of ints to a file

ints are space separated, with a trailling space

on errror, returns, -1, succes 0
*/
int write_int_arr_file(char * path, int *arr, int len) {
    int i;
    FILE * fp;

    fp = fopen(path,"w");
    if (fp == NULL) {
        return -1;
    }
    for(i=0; i<len; i++){
        if (fprintf(fp,"%d ", arr[i]) < 0){
            return -1;
        }
    }
    if (EOF == fclose (fp)){
        return -1;
    }
    return 0;
}

/* Same as int, saved in exp notation, */
/* with precision (deciamal places) precision */
int write_float_arr_file(char * path, float *arr, int len, int precision) {
    int i;
    FILE * fp;

    fp = fopen(path,"w");
    if (fp == NULL){
        return -1;
    }

    for(i=0; i<len; i++){
        /*if (fprintf(fp,format, arr[i]) < 0){*/
        if (fprintf(fp,"%.*e", precision, arr[i]) < 0){
            return -1;
        }
    }

    if (EOF == fclose (fp)){
        return -1;
    }

    return 0;
}

int main() {
    /*
    # BUFSIZ

    TODO
    */
    {
        printf("BUFSIZ = %ju\n", (uintmax_t)BUFSIZ);
        assert(BUFSIZ >= 256);
    }

    /*
    # EOF

        EOF is a C concept.

        EOF works because there are only 256 bytes you can get from an fd
        so EOF is just some int outside of the possible 0-255 range, tipically -1

        In Linux for example, EOF does not exist.

        The only way to know if a file is over is to make a `sys_read` call
        and check if you get 0 bytes.

        Since `sys_read` returns the number of bytes read, if we get less than we asked for
        this means that the file is over.

        In case more data could become available in the future, for example on a pipe,
        `sys_read` does not return immediately, and the reader sleeps until that data becomes available.
    */

    /*
    # stderr

        The `stderr` macro is a `FILE*` that represents the standard error.

        Is is always open when the program starts.

        The output to stderr may not be synchronized with that of stdout,
        so this message could appear anywhere relative to other things that were
        printed to stdout.
    */
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

#if __STDC_VERSION__ >= 199901L
        /*
        # snprintf

            Like `sprintf`, but writes at most n bytes, so it is safer,
            because it may not be possible or easy to calculate the resulting
            size of a formated string.

            The size given *includes* the null terminator.
        */
        {
            char cs[] = "123";
            char cs2[3];
            snprintf(cs2, 3, "%s", cs);
            assert(strcmp(cs2, "12") == 0);
        }
#endif

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

            buffer size cannot be accessed programatically

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
        /*
        # getchar

            getchar == getc(stdin)

        # getc

            get single char from given stream (should be called fgetc...)

            it blocks until any char made available.

            whatever char entered including on a tty is made available immediatelly.
        */
        if (0) {

            /*
            echo a | c.out
                a
            sleep 3 | c.out
                EOF after 3 secs
            */

            fputs("enter a char (on linux, ctrl+d EOF): ", stderr);
            /* BAD does not work. */
            /*fputc('a', stdin);*/
            char c = getchar();
            if (c != EOF) {
                fprintf(stderr, "you entered:\n%c|<<<\n", c);
            }
            else {
                fprintf(stderr, "EOF\n");
            }
        }

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

            the trailling newline is included in the input.
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

    /*
    # File streams

    # File IO

        To get streams that deal with files, use `fopen`.

        To close those streams after usage, use `fclose`.

        # fopen

            Open file for read/write

            Don't forget to fclose after using! open streams are a process resource.

            Modes:

            -   `r`: read. compatible with a,w

            -   `w`: read and write. destroy if exists, create if not.

            -   `a`: append. write to the end. creates if does not exist.

            -   `+`: can do both input and output. msut use flush or fseek

            -   `x`: don't destroy if exist (c11, not c++!)

            -   `b`: binary.

                Means nothing in POSIX systems.

                On our dear DOS/Windows and Mac OS X, automatically converts between \n and \n\r or \r.
                http://stackoverflow.com/questions/229924/difference-between-files-writen-in-binary-and-text-mode

                Windows also does trailing \z magic for ultra backwards compatibility.

                Therefore for portability, always use this when you are going to do IO
                with binary IO functions such as fwrite.

            In case of error:

            - return `NULL` and set `errno`.

        # Text IO vs Binary IO

            # Text vs binary for numerical types

                Example: an int 123 can be written to a file in two ways:

                - text: three bytes containing the ascii values of `1`, `2` and then `3`
                - binary: as the internal int representation of the c value, that is 4 bytes, with `123` in binary and zeroes at the front.

                Advantages of text:

                - it is human readable since it contains only ASCII or UTF values
                - for small values it may be more efficient (123 is 3 bytes in ascii instead of 4 in binary)
                - it is portable across multiple systems, while binary varies, especially byte ordering.

                Advantages of binary:

                - it much shorter for large integers
                - inevitable for data that cannot be interpretred as text (images, executables)

            # Newline vs carriage return newline

                Newline carriage return realated TODO confirm

                For portability, use it consistently.

                In linux the difference between text methods and binary methods is only conceptual:
                some methods output human readable text (`fprintf`) and can be classified as text,
                while others output binary, no difference is made at file opening time.

        # fclose

            Don't forget to close because:

            - open `FILE*` are a program resource
            - close also flushes

            In case of error:

            - return `EOF`
            - set `errno`

    */
    {
        int elems_write[] = {1, 2, 3};
        enum constexpr {nelems = sizeof(elems_write) / sizeof(elems_write[0])};
        int elems_read[nelems];
        FILE *fp;
        char path[] = TMPFILE("fwrite");

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
                io_error("fopen", path);
            } else {
                if (fwrite(elems_write, sizeof(elems_write[0]), nelems, fp) < nelems) {
                    io_error("fwrite", path);
                }
                if (fclose(fp) == EOF) {
                    io_error("fclose", path);
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
                io_error("fopen", path);
            }
            else {
                if (fread(elems_read, sizeof(elems_read[0]), nelems, fp) < nelems && ferror(fp)) {
                    io_error("fread", path);
                }
            }
            if (fclose(fp) == EOF) {
                io_error("fclose", path);
            }
        }
        assert(memcmp(elems_read, elems_write, nelems) == 0);

        /*
        # Endianess

        # Byte order

            The C standard does not specify how bytes are ordered in memory.

            http://www.ibm.com/developerworks/aix/library/au-endianc/
        */
        {
            /*
            # Fix endianess

                You need this when you want to export data to some format.

                - http://stackoverflow.com/questions/105252/how-do-i-convert-between-big-endian-and-little-endian-values-in-c
                - http://stackoverflow.com/questions/13994674/how-to-write-endian-agnostic-c-c-code
                - http://stackoverflow.com/questions/2182002/convert-big-endian-to-little-endian-in-c-without-using-provided-func
                - http://stackoverflow.com/questions/19275955/convert-little-endian-to-big-endian

                Methods:

                -   binary operations just work, use them

                -   POSIX has the htons family, but I could not find a POSIX quote
                    that says network order is big endian (which seems the default.)
            */

            /*
            Check endianess.

            Works because `short int` is guaranteed to be at least of size 2.

            We must work with pointers, because doing `(char)i` directly is specified ot be 1.
            The compilers produces the assembly code required to do so taking endianess into consideration.
            */
            {
                const short int i = 1;
                if ((*(char*)&i) == 0) {
                    printf("Endianess = big\n");
                } else {
                    printf("Endianess = small\n");
                }
            }
        }
    }

    /*
    # freopen

        Open a given `FILE*` again but as a different file.
    */
    {
        /* This will discard stdin on Linux. */
        /*freopen("/dev/null", "r", stdin);*/
    }

    /* # Reposition read write */
    {
        /*
        For new code, always use `fgetpos` and `fsetpos` unless you absolutely
        need `SEEK_END` because ftell and fseek
        must return `long` which may limit the maximum file to be read,
        while `fgetpos` uses a typedef `fpos_t`

        # ftell

            Get current position of `FILE*`.

        # fseek

            Set current position in `FILE*` relative to:

            - SEEK_SET: relative to beginning of file
            - SEEK_CUR: relative to current position
            - SEEK_END: relative to end of file

            It seems that seeking after the eof is undefined behaviour in ANSI C:
            http://bytes.com/topic/c/answers/219508-fseek-past-eof

            This contrasts with POSIX lseek + write, in which the unwriten gap is 0.
        */
        {
            /*
            long int curpos = ftell(pf);
            if (curpos == -1L){
                ERROR
            }
            */

            /*
            FILE* fp;
            if (fseek (fp, 0 , SEEK_SET) != 0) {
                ERROR;
            }
            */
        }

        /*
        # rewind

            Same as therefore useless.

                fseek(stream, 0L, SEEK_SET)
        */

        /*
        Like ftell/fseek except that:

        - the return is a typedef `fpos_t`, so it may represent larger files.
        - there is a single possible reference position equivalent to `SEEK_SET`.
            This makes sence since that argument was only useful for convenience.

        Always use it instead of ftell/fseek.

        # fgetpos

            Get a position in stream that is later usable with a later call to `fsetpos`.

        # fsetpos

            Set position to a point retreived via fgetpos.
        */
        {
        }
    }

    /*
    # flush(fp)

        For output streams only.

        Makes sure all the data is put on the stream.

        May be necessary as the data may be in a buffer.
    */
    {
        /*
        if (fflush(fp) == EOF) {
            ERROR
        }
        */

        /* debugging application: your program segfaults

        To find where, you put printf everywhere.

        However nothing shows on screen.

        Solution: flush immediatelly after the printf and add a newline at the end of the printed string.
        This should ensure that your string gets printed.
        */
    }

    /* # Applications */
    {
        {
            char path[] = TMPFILE("str_file");
            char input[] = "asdf\nqwer";

            /* Write entire string to file at once. */
            {
                if (file_write(path, input) == -1) {
                    io_error("file_write", path);
                }
            }

            /* Read entire file at once to a string. */
            {
                char *output = file_read(path);
                if (output == NULL) {
                    io_error("file_read", path);
                }
                assert(strcmp(input, output) == 0);
                free(output);
            }

            /* Get file size: */
            {
                long size = file_size(path);
                if (size == -1) {
                    io_error("file_size", path);
                }
                assert(size == strlen(input));
            }
        }

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

            char path[] = TMPFILE("cat");
            char file_data[] = "abc\nde\nfgh";
            size_t file_data_size = strlen(file_data);
            char lines[3][4] = {"abc\n", "de\n", "fgh\n"};
            size_t current_line;

            /* Prepare test. */
            fp = fopen(path, "wb");
            if (fp == NULL) {
                io_error("fopen", path);
            } else {
                if (fwrite(file_data, 1, file_data_size, fp) < file_data_size) {
                    io_error("fwrite", path);
                }
                if (fclose(fp) == EOF) {
                    io_error("fclose", path);
                }
            }

            /* The actual cat. */
            /*
            fp = fopen(path, "rb");
            if (fp == NULL) {
                io_error("fopen", path);
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
                    io_error("fread", path);
                }
                if (fclose(fp) == EOF) {
                    io_error("fclose", path);
                }
            }
            */
        }

        /* Simple write arrays to file */
        {
            FILE* fp;
            char path[256];

            int arri[] = { 0, 1, -1, 12873453 };
            float arrf[] = { 1.1f, 1.001f, -1.1f, 1.23456e2 };

            strcpy(path, TMPFILE("arri"));
            write_int_arr_file(path, arri, 4);

            strcpy(path, TMPFILE("arrf"));
            write_float_arr_file(path, arrf, 4, 2);
        }
    }

    /*
    # file operations

        A few file operations are available in ANSI C.

        They are present in <stdio.h> mainly to support file IO.

    # remove

    # delete file

        Remove a file.

            int remove(const char *filename);

        ANSI C does not way what happen if it does not exist.

        If the file is open, the behaviour is undefined.

    # rename

        Rename a file.

            int rename(const char *old, const char *new);

        If the new file exists, undefined behaviour.

    # directory operations #path

        There seems to be no directory of path operations with system independent separator,
        only with POSIX or Boost.
    */

    /*
    # perror

        Print description of errno to stderr with given prefix appended, `NULL` for no prefix.

        Basic way to print error messages after error on a posix function
    */
    {
        errno = EDOM;
        perror("perror test EDOM");
    }

    return EXIT_SUCCESS;
}
