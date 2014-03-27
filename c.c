/*
ANSI C cheat.

Small comments on comparing ANSI C with extensions are acceptable.

#sources

    - <http://c-faq.com/index.html>

        Good straight to the point faq, covers specially confusing points

    - <http://www.open-std.org/jtc1/sc22/wg14/www/standards>

        Official directory containing the latest free draft versions of the ANSI c specs

        The latest is: <http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf>

        The closest to the ANSI standard that you can get for free (it is a paid standard...)

        This should be quite close to the actual speficications

        Quite readable, and fun to find obscure features which you had never heard of before!

    - <http://locklessinc.com/articles/obscurec/>

        Obscure only stuff. Cool.

#motivation

    C is amazingly important as it is used to implement:

    - Linux kernel
    - Windows kernel
    - Python and Ruby reference implementations
    - opengl

    And the list goes on and on...

    The reason for this is that C:

    - is quite low level, so you can do low level things other languages can't
    - is low level, so it can be very fast (if you program it correctly)
    - is robust and easy to understand.

#standards

    #ANSI C

        Language and standard library (libc) are standardized by an organization named ANSI

        ANSI is american, and it represents the USA for ISO and IEC

        You must pay to have the latest standards, but C99 seems to be available for free [here](http://www.open-std.org/jtc1/sc22/wg14/www/standards.html)
        (unlike C90, which has larger library support).

        Drafts are also available for free, and are very close to the actual standards.

        A list of links to the standards can be found at: <http://stackoverflow.com/questions/81656/where-do-i-find-the-current-c-or-c-standard-documents>
        Interestinly, as of 2013, C90 costs 141 dollars, but C11 only 30.

        However you can get for free:

        - drafts of the latest standard which are quite close to the actual specifications.

            It is strongly recommended that you download this now and try as much as you can to get familiar with it,
            as it is *the* official source.

        - older standards

        - compiler documentations

        ANSI only specifies language and the library interfaces:
        what functions, variables etc. are contained in each file,
        but it does not specify how that should be implemented.

        Some features are even left for the implementors to decide such as
        the behavoiur of [system][]

        New features are often based on extension of
        major implementations such as gnu's or microsoft's

        #C89

            ANSI ratified the standard in 89, and ISO in 90 with formatting changes,
            C89 and C90 are almost the same.

        #C90

            See C89

        #C99

            <http://en.wikipedia.org/wiki/C99>

            - large support, but not 100% by many compilers

            - <http://en.wikipedia.org/wiki/C99>

            - support for // comments

            - long long, bool, complex numbers

            - gcc flag: add `-std=c99`

            - microsoft stated that they will not update their compilers
                to C99 and futher.

                They use c as an inner language, and think
                it would be too delicate/costly to change it.

                They have decided to maintain only c++ and c# up to date.

                Therefore you will not get those working on ms compiler anytime soon.

        #C11

            <http://en.wikipedia.org/wiki/C11_%28C_standard_revision%29>

            - latest standard, but very limited support in most compilers as of 2013.

            - previously known as c1x

            - supported on gcc 4.6>. Flag: `-std=c1x`.
                It is not recommended to use this yet as support is low.

            - threads spported

    #ANSI extensions

        Beside ANSI language and libraries, you should also know about the existense of other
        standards which extend it:

        - posix c library. Offers many functions for posix compliant systems (linux, mac, not windows)

        - compiler and libc extensions

            Every compiler has certain language extensions which may be fundamenta for certain project.

            For example: gnu c is used on the linux kernel One major reason is support for inline assembly,
            which lacks in ANSI c.

        If possible you should avoid relying on those since they are less portable.

    #glibc

        Name for the gnu implementation of the c standard library

#K&R #The C Programming Language

    <http://en.wikipedia.org/wiki/The_C_Programming_Language>

    First edition 1978.

    De facto standard for the C language and style for many years.

    You will still hear about it in discussions, or even to describe some ANSI C
    concepts like K&R function declaration.

#libs

    this section is a list of whose main interface is c or which have a good c interface

    #petcs

        <http://www.mcs.anl.gov/petsc/documentation/index.html>

    #multithreading ipc concurrency.

        - c11 supports it, c99 not

            glibc 2.x still does not have it.

        - c++11 supports it, c++03 not

        - openMP is is a library supported on C, C++, Fortran, Windows, Linux MacOS

#compilers

    Most of those compilers work for multiple related languages such as C, C++, etc.

    #gcc

        Most popular Linux compiler.

        Open source.

        Does C, C++, etc.

        Used to compile the Linux kernel (relies on its extensions).

    #clang

        Based on llvm.

        Open source.

        As of 2013:

        - better error messages than gcc, specially for C++.
        - smaller stdlib and C++11 support than gcc

        Best support for objective C, and therefore loved by Apple.

    #icc

        Intel C compiler.

        Closed source.

#doxigen

    Documentation generation from comments. De-facto stadnard for C++.

    <http://www.stack.nl/~dimitri/doxygen/docblocks.html>

#funny

    <http://www.ioccc.org/>

    <http://www.ioccc.org/years.html>. Amazing.

    IOCCC entry explained in detail: <http://stackoverflow.com/questions/15393441/obfuscated-c-code-contest-2006-please-explain-sykes2-c>
*/

/*
#preprocessor

    Loes simple stuff *before* compilation.

    Ly simple understand non-turing complete.

    #include

        Look in standard dirs directly:

            #include <file.h>

        Looks in current dir first:

            #include "file.h"
*/

#include <assert.h>
#include <complex.h>   //complex constnats and arithemtic. c99.
#include <ctype.h>     //isspace
#include <errno.h>
#include <fenv.h>
#include <float.h>     //
#include <iso646.h>    //and, or, etc macros
#include <inttypes.h>  //PRIxPTR
#include <limits.h>    //*_MAX, *_MIN for integer types
#include <locale.h>
#include <setjmp.h>    //setjmp, longjmp
#include <signal.h>
#include <stdarg.h>    //..., va_list, va_start, va_arg, va_end
#include <stdbool.h>   //true, false. c99
#include <stddef.h>    //offsetof, type_t
#include <stdint.h>    //uint32_t, etc.
#include <stdlib.h>    //malloc, EXIT_SUCCESS, EXIT_FAILURE:
#include <stdio.h>     //printf, puts
#include <string.h>    //sprintf, strlen, strcpy, memset
#include <math.h>
//#include <tgmath.h>    //
#include <time.h>      //time()
#include <wchar.h>
//#include <thread.h>             //c99 but not yet implemented for me

/*
one way to define constant is with preprocessor directives

however using a const may be a better idea because:

- constants have scope
- produce meaningful error messages

*/

#define PI 3.14

/*
example where this would cause problems:

    int PI = 3.14;

PI expands to 3.14

compiler reads

    int 3.14 = 3.14;

but it will be hard to figure error msg

compare this with the very simple message generated if PI were a constant
*/

#define PI_PLUS_ONE (3.14 + 1)
    //use parenthesis or order of operation might destroy you

//common recipe to control compilation:

#define DEBUG
#ifdef DEBUG
int debugVar;
#endif

//##line

//from now on, counts from given line to report errors:

//#line 1

//}

//#global scope

    int global = 1;
        //this is a global variable: can be accessed and modified everywhere

    //OK!
    int global2 = 1+1;


    int ret1()
    {
        int i;
        //before main!
        return 1;
    }
    //ERROR: only var declarations with const initialization allowed
        //int global2 = global+1;  //non const
        //puts("asdf");           //func call
        //if(1){}                 //branching
        //int global3 = ret1();   //functions

    //{}
        //ERROR
        //Cannot create scopes here like that
        //They'd be useless anyways.

//pointer array

    int* get_arr(int i)
    {
        //int is[] = {i};
        //return is;
            //WARN
            //return adress of local var
            //data is destroyed on return!

        int* ip = (int*) malloc(sizeof(int) * 1);
        return ip;
    }

    //cheatsheet on pointers and arrays
    void print_array(int **mat, int m, int n)
    {
        int i, j;
        for (i = 0; i < m; i++) {
            for (j = 0; j < n; j++) {
                printf("%d ", mat[i][j]);
            }
            printf("\n");
        }
    }

int goto_func(int i) {
    /*goto goto_func_after;*/
    in_func_label:
    return 1;
}

int setjmp_func(bool jmp, jmp_buf env_buf)
{
    if (jmp)
        longjmp(env_buf, 1);
    else
        return 1;
}

//#functions

    /*
    #declaration vs definition
    */

        /*
            Declaration can happen many times.

            Definition no.
        */

            void decl_def();
            void decl_def();

            void decl_def(){;}
            //ERROR redefine
            //void decl_def(){;}

        /*
        Declarations don't need argment names.

        If those are used for documentation purposes, they don't need to match those of the definition.
        This is highly confusing however.

        Definitions need parameter names. This rule changes in C++.
        */

            void decl_def_args(int,   float,   char c);
            void decl_def_args(int i, float f, char d){}

            //void def_no_argname(int){}

        /* One major application of forward declarations is to break loops */

            int factorial2Funcs1(int);

            int factorial2Funcs0(int n){
                if (n != 1) {
                    return n*factorial2Funcs1(n - 1);
                }
                return 1;
            }

            int factorial2Funcs1(int n){
                if (n != 1) {
                    return n*factorial2Funcs0(n - 1);
                }
                return 1;
            }

        //Two decls on the same line, with same return type:

            int decl_1(), decl_2();
            int decl_1(){ return 1; }
            int decl_2(){ return 2; }

            //int decl_3(){return 3;}, decl_4(){return 4;};
                //ERROR
                //cannot define on same line

        //Can declare a function that returns int and a int var with the same `int`.
        //Very confusing!

            int decl_and_int_func(), decl_and_int;
            int decl_and_int_func(){ return 0; }

        int k_and_r(a, p)
            int a;
            char *p;
        {
            return 0;
        }

        /*
        #[*]

            The "[*]" declaration syntax is possible to avoid naming parameters.
        */
        void vla_arg(size_t, int vla[*]);
        void vla_arg(size_t size, int vla[size]) {}

        void vla_arg_k_and_r(size, vla)
            //int vla[size]; //ERROR: must come after
            size_t size;
            int vla[size];
        {}

    /*
    #overload

        No func overload in C.
    */

        void overload(int n){}

        //ERRORS:

            //void overload(float n){}
            //void overload(int n, int o){}

    int * int_ptr_func_int_ptr(int *ip){
        (*ip)++;
        return ip;
    }
    int int_func_int(int i){
        return i;
    }

    void func_int(int i){}
    void func_float(float f){}
    void func_double(double d){}

    void func_string_abc(char s[]){ assert(strcmp(s, "abc") == 0); }
    void func_string_const_abc(char const s[]){ assert(strcmp(s, "abc") == 0); }
    void func_string_modify(char s[]){ s[0] = '0'; }

    void func_array(int a[]){
        assert(a[0] == 1);
    }

    void func_array_modify(int a[]){
        a[0] = -1;
    }

    struct struct_func_struct
    {
        int i;
        int j;
    };

    struct struct_func_struct struct_func()
    {
        return (struct struct_func_struct){ 0, 1 };
    }

    struct func_struct { int i; };

    void func_struct_1(struct func_struct s)
    {
        assert(s.i == 1);
    }

    void func_int_ptr (int *i){}
    void func_int_arr (int i[]){}

    void with_static_var(int *i_out, int *si_out)
    {
        int i = 0;

        //static initialization is evaluated only once
        //the first time this function is called
        static int si = 0;

        i++;
        si++;
        *i_out = i;
        *si_out = si;
    }

    int add_int(int n, int m)
    {
        return n+m;
    }

    int sub_int(int n, int m)
    {
        return n-m;
    }

    int int_int_int_func(int m, int n) {
        return m + n;
    }

    int int_func_func_int_int(int (*function_ptr)(int, int), int m, int n)
    {
        return (*function_ptr)(m, n);
    }

    /*
    function struct args

        how to deal with passing structs to/from functions
    */

        struct FuncReturn { int i; };

        struct FuncReturn structReturn(struct FuncReturn sIn)
        {
            struct FuncReturn s_out;
            s_out.i = sIn.i + 1;
            return s_out;
        }

    /*
    #variadic functions

        these are functions with a variable number or arguments, just like `printf`.

    #va_start

            va_start(varname, last_argname)

        Initialize va_list variable varname. Indicates that varargs come after numargs.
    */

        int variadic_add(int numargs, ...)
        {
            va_list args;
            va_start(args, numargs);
            int sum = 0;
            for(int i = 0 ; i < numargs; i++)
            {
                int arg = va_arg(args, int);
                sum += arg;
            }

            //you MUST do this
            va_end(args);

            return sum;
        }

        /*
        This function illustrates how to va args from one function to another.

        #vprintf

            This is the raison d'etre for the `vprintf` family, which takes a va_list argument.
        */
        int sprintf_wrapper(char *s, const char *fmt, ...)
        {
            int ret;
            va_list args;

            va_start(args, fmt);
            ret = vsprintf(s, fmt, args);
            va_end(args);
            return ret;
        }

    /* #return const from func */

        const int const_int_func(){
            return 0;
        }

        const int* const_int_ptr_func_int_ptr(int *ip){
            (*ip)++;
            return ip;
        }

        const struct struct_func_struct const_struct_func(){
            return (struct struct_func_struct){ 0, 1 };
        }

#if __STDC_VERSION__ >= 199901L
        void const_array_size_argument(int is[const]) {
            is[0] = 1;
            int j;
            // Compilation ERROR: assignment of read-only parameter is:
                //is = &j;
        }
#endif

    //restrict

        void restrict_double_add(int * restrict i, int * restrict j, int * restrict add)
        {
            *i += *add;
            *j += *add;
        }

        void double_add(int *i, int *j, int *add)
        {
            *i += *add;
            *j += *add;
        }

        /**
        It makes no sense to mark a single pointer as restricted.
        */
        void restrict_double_add_one_restrict(int * restrict i, int *j, int *add)
        {
            *i += *add;
            *j += *add;
        }

#if __STDC_VERSION__ >= 199901L
        int static_array_argument(int is[static 3]) {
            return is[3];
        }
#endif

#ifdef PROFILE

    const static int n_prof_runs = 100000000;

    //only the loop.
    //discount this from every other profile run
    void loop_only_prof(int n)
    {
        int i;
        for(i=0; i<n; i++);
    }

    void while_only_prof(int n)
    {
        int i = 0;
        while(i < n)
        {
            ++i;
        }
    }

    void int_assign_prof(int n)
    {
        int i,j;
        for(i=0; i<n; i++)
            j=1;
    }

    void do_nothing(){}

    void func_all_prof(int n)
    {
        int i;
        for(i=0; i<n; i++)
            do_nothing();
    }

    static inline void inline_do_nothing(){}

    void inline_func_call_prof(int n)
    {
        int i;
        for(i=0; i<n; i++)
            inline_do_nothing();
    }

    void int_sum_prof(int n)
    {
        int i, j = 0;
        for(i=0; i<n; i++)
            j = j + 0;
    }

    void int_sub_prof(int n)
    {
        int i, j = 0;
        for(i=n; i>0; i--);
            j = j - 0;
    }

    void int_mult_prof(int n)
    {
        int i, j = 1;
        for(i=0; i<n; i++)
            j = j * 1;
    }

    void int_div_prof(int n)
    {
        int i, j = 1;
        for(i=0; i<n; i++)
            j = j / 1;
    }

    void float_sum_prof(int n)
    {
        float f;
        int i;
        for(i=0; i<n; i++)
            f = f + 0.0;
    }

    void float_sub_prof(int n)
    {
        float f;
        int i;
        for(i=0; i<n; i++)
            f = f - 0.0;
    }

    void float_mult_prof(int n)
    {
        int i;
        float j;
        for(i=0; i<n; i++)
            j = j * 1.0;
    }

    void float_div_prof(int n)
    {
        int i;
        float j;
        for(i=0; i<n; i++)
            j = j / 1.0;
    }

    void putsProf(int n)
    {
        int i;
        for(i = 0; i < n; ++i)
            puts("a");
    }

    void stack1b_prof(int n)
    {
        int is[1];
        int i;
        for(i = 0; i < n; ++i)
        {
            int is[1];
        }
    }

    void stack1kb_prof(int n)
    {
        int is[1];
        int i;
        for(i = 0; i < n; ++i)
        {
            int is[0x800];
        }
    }

    void stack1mb_prof(int n)
    {
        int is[1];
        int i;
        for(i = 0; i < n; ++i)
        {
            int is[0xF0000];
        }
    }

    void heap1b_prof(int n)
    {
        char* cp;
        int i;
        for(i = 0; i < n; ++i)
        {
            cp = (char*) malloc(sizeof(char) * 1);
            free(cp);
        }
    }

    void heap1kb_prof(int n)
    {
        char* cp;
        int i;
        for(i = 0; i < n; ++i)
        {
            cp = (char*) malloc(sizeof(char) * 0x800);
            free(cp);
        }
    }

    void heap1mbProf(int n)
    {
        char* cp;
        int i;
        for(i = 0; i < n; ++i)
        {
            cp = (char*) malloc(sizeof(char) * 0xF0000);
            free(cp);
        }
    }

#endif

//#algorithms

    //simple fun algorithms

    //random
    //{
        float rand_range(float a, float b)
        { //float in a range
            return ((b - a) * ((float)rand() / RAND_MAX)) + a;
        }
    //}

    //a pow b
    int pow2(int a, int b)
    {
        int res = 1;
        int i;
        for(i=0; i<b; i++){
        res = res*a;
        }
        return res;
    }

    //TODO does not work
    float pow2f(float a, float b)
    {
        float res = 1.f;
        float i;
        for(i=0; i<b; i++){
        res = res*a;
        }
        return res;
    }

//file io

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
    long fget_get_file_size(FILE *fp)
    {
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
        //retore old position
        if (fseek(fp, oldpos , SEEK_SET) != 0) {
            return -1L;
        }
        return return_value;
    }

    /*
    Same as `get_file_size`, but takes the path instead of a `FILE*`.
    */
    long get_file_size(char *path)
    {
        FILE *fp;
        long retur_value;
        fp = fopen(path, "r");
        if (fp == NULL){
            return -1L;
        }
        retur_value = fget_get_file_size(fp);
        if (fclose(fp) == EOF){
            return -1L;
        }
        return retur_value;
    }

    /*
    Read the entire file to a char[] dynamically allocated inside this function.

    Returns a pointer to the start of that array.

    In case of any error, returns NULL.

    The entire file must fit into the memory avilable to the program.
    */
    char *file_read(char *path)
    {
        FILE *fp;
        char *buffer;
        long fsize;
        fp = fopen (path , "rb");
        if (fp==NULL) {
            return NULL;
        }
        fsize = fget_get_file_size(fp);
        if (fsize < 0){
            fprintf(stderr, "could not determine lenght of:\n%s\n", path);
            return NULL;
        }
        buffer = (char*)malloc(fsize);
        if (buffer == NULL) {
            return NULL;
        }
        if (fread (buffer, 1, fsize, fp) != fsize) {
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
    int file_write(char *path, char *write_string)
    {
        long len;
        char *buffer;
        FILE *fp;

        fp = fopen(path, "wb");
        if (fp == NULL) {
            return -1;
        }
        len = strlen(write_string);
        // copy the file into the buffer:
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
    int write_int_arr_file(char * path, int *arr, int len)
    {
        int i;
        FILE * fp = fopen(path,"w");

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

    //same as int, saved in exp notation,
    //    with precision (deciamal places) precision
    int write_float_arr_file(char * path, float *arr, int len, int precision)
    {
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

        //+1 for the null char
#define PRIxPTR_WIDTH ((int)(sizeof(void*)*2))

//process address space

    int BSS;
    int DATA = 1;

int post_inc_global()
{
    global++;
    return global - 1;
}

int asm_precalc(int i)
{
    return i + 1;
}

int asm_precalc_inline(int i)
{
    return i + 1;
}

/*
#exit

    Exit program at any point, including outside of the main function.

    Gets return value as an argument.
*/
void exit_func() {
    exit(EXIT_FAILURE);
    exit(EXIT_SUCCESS);
}

/*
#atexit

    Function gets called when process ends via `exit` or a `return` on the `main` function.
*/
void atexit_func() {
    printf("atexit\n");
}

/*
#abort

    man abort

    Sources:

    - <http://stackoverflow.com/questions/397075/what-is-the-difference-between-exit-and-abort>
    - <http://stackoverflow.com/questions/3676221/when-abort-is-preferred-over-exit>

    Differences from exit:

    - does not call `atexit` function.
    - raises `SIGABRT`
    - does not call C++ destructors
*/

void abort_func()
{
    abort();
}


/*
#main signature

    <http://stackoverflow.com/questions/204476/what-should-main-return-in-c-and-c>

    Valid signatures:

        int main()

    and

        int main(int argc, char* argv[])

    which is the same as:

        int main(int argc, char** argv)
*/
int main(int argc, char **argv)
{
    /*
    #scope of brace pairs inside a function #braces

        Every pair of braces, or constructs that uses braces such as `if`
        create a new scope

        You may define variables in that scope with the same names as external ones,
        but if you do so the external ones will become completelly invisible
    */
    {
        {
            int i = 0;
            //int i; //ERROR redeclaration
            {
                int i = 1;
                /* impossible to access the outer `i` from now on in this scope! */
                //assert(i_outter == 0);
            }
            assert(i == 0);
        }

        /*
        If a variable is declared in a scope (between a pair of braces),
        there is no guarantee that it outlives that scope.

        Nothing however prevents the compiler from leaving it around and occupying space,
        this is implementation specific.

        <http://stackoverflow.com/questions/2759371/in-c-do-braces-act-as-a-stack-frame>
        */
        {
            int *ip;
            {
                int i = 1;
                ip = &i;
            }
            //assert(*ip == 1); //BAD undetermined behaviour
        }

        /*
        Undefined behaviour, because the rhs `i` is already the inner i
        */
        {
            int i = 1;
            {
                int i = i;
                //assert(i == 1);
            }
        }
    }

    /*
    #base types

        types like `int`, `char`, `float` that are reserved language words
        with fixed meanings.
    */

    /*
    #identifiers.

        Identifiers are names either for variables, functions, structs or enums.

    */
    {

        /*
        Allowed identifiers follow the regex: _[a-Z0-9_]*
        */
        {
            //ERROR name cannot start with digit.

                //int 0a;
        }

        /*
        C99 specifies that:

            All identifiers that begin with an underscore and either an uppercase letter
            or another underscore are always reserved for any use.

            All identifiers that begin with an underscore are always reserved
            for use as identifiers with file scope in both the ordinary and tag name spaces.

        TODO0 understand what `identifiers with file scope` mean.

        Which means that: while it is possible for users to define (multichar) identifiers that start with underscore,
        they should never do it for forward compatibility, as those variables may acquire special values in the future.

        POSIX adds many further per header reserved names which it would be wise to follow even on ANSI C:
        <http://pubs.opengroup.org/onlinepubs/9699919799/functions/V2_chap02.html> section "The Name Space".

        The following compile for now, but may break in any future version of the standard.
        */
        {
            int _not_yet_a_keyword;
            int _Not_yet_a_keyword;
            int __not_yet_a_keyword;
        }

        /*
        Standard seems to say nothing of this edge case, since `_` is not followed by any letter TODO0 confirm

        Still, it would be very cryptic to use such an identifier (it is used in Python / Django!)
        */
        {
            int _;
        }
    }

    //#variables
    {
        {
            int i;
            i = 5;
        }

        {
            int i = 5;
            int j = 7;
        }

        {
            int i = 5, j = 7;
                //31 bit + 1 sign bit integer
        }
    }

    /*
    #literals

        *literals* are values known at compile time
        often used to initialize variables. Ex:

        - int: `1`
        - long: `1L`
        - float: `1.0f`
        - double: `1.0`and their
        - char: `'a'`
        - string: `"abc"`

        C99 introduces compound literals, which allow creation of literals for

        - arrays
        - structs
        - unions.
    */

    /*
    #integer types

        Types that represent integer numbers are called integer types.

        This classification is explicitly used on the C specification,
        some operations or rule of the c language are only valid for integer types,
        while others work also for floating point types.

        `char` is also an integer type
    */
    {
        //#char
        {
            //char has fixed size 1 byte:

                assert(sizeof(char) == 1);

            //char literals are specified by single quotes

                { char c = 'a'; }

            //char literals can be cast to integers by replacing them with
            //their corresponding ascii integer value for example, 'a' == 97:

                assert('a' == 97);

            /*
            char literals can contain any byte even those which have
            no corresponding ASCII value such as say, `130`.

            To get those literal values, the only way is to typecast from `int` as:
            */

                { char c = (char)130; }

            //TODO possible via escape seqs like in strings?

            //TODO how to make a literal backslash char?
        }

        /*
        #short

            short has no specific literals, must typecast.
        */

        { short si = 1; }
        { short si = (short int)1; }
        { int i = 1; }
        { long li = (long)1l; }
        { long li = (long)1L; }

        //long long int is C99

            { long long lli = 8ll; }
            { long long lli = 8LL; }

        //ERROR: mixed cases not allowed

            //{ long long lli = 8Ll; }

        //short, long and long long are the same as the int versions:

            assert(sizeof(short) == sizeof(short int));
            assert(sizeof(long) == sizeof(long int));
            assert(sizeof(long long) == sizeof(long long int));

        //unsigned:

            { unsigned char uc = (unsigned char)1; }
            { unsigned short usi = (unsigned short int)1u; }
            { unsigned int ui = 1u; }
            { unsigned int ui = 1U; }
            { unsigned long uli = 1lu; }
            { unsigned long uli = 1LU; }
            { unsigned long long ulli = 1llu; }
            { unsigned long long ulli = 1LLU; }

            //The following are not recommended unless you are into code obfsucation:

                { unsigned long uli = 1Lu; }
                { unsigned long uli = 1lU; }
                { unsigned long long ulli = 1LLu; }
                { unsigned long long ulli = 1llU; }

            //ERROR:

                //{ unsigned long long ulli = 1Llu; }

        //#bases for integer literals
        {
            //hexadecimal
            {
                assert(16 == 0x10   );
                assert(16 == 0x10   );
                assert(16 == 0x10l  );
                assert(16 == 0x10ll );
                assert(16 == 0x10u  );
                assert(16 == 0x10ul );
                assert(16 == 0x10ull);

                //case does not matter
                assert(0xaB == 0xAb );
            }

            //octal:

                assert(16 == 020);

            //binary: no ANSI way
        }

        /*
        #integer representation

            C does not fix the binary representation for integers,
            it only states which properties represenations must have.

            As an example, the C standard explicitly mentions that the following
            representations (but there may be more) are compatible with the standard:

            - 2’s complement
            - 1’s complement
            - signed magnitude

            <http://stackoverflow.com/questions/12125650/what-do-the-c-and-c-standards-say-about-bit-level-integer-representation-and-m>
        */
    }

    //#floating point types and literals
    {
        float f = 1.23f;
            //1 signal 23 number 8 exponent
        float f1 = 1.23e-10f;
        float f2 = 1.f;

        //ERROR: there must be a dot

            //float f = 1f;

        { double d = 1.23; }
        { long double ld = 1.23l; }
        { long double ld = 1.23L; }

#if __STDC_VERSION__ >= 199901L
        /*
        #float hex literal

            C99.

            Ex:

                0xA.8p10

            Equals:

                1010.1000 * 2^3 = 10.5 x 2^10

            The exponent is given *in decimal*.
        */
        {
            assert(0xA.0p0  ==   10.0);
            assert(0xA.8p0  ==   10.5);
            assert(0x1.8p1  ==    3.0);
            assert(0x1.0p10 == 1024.0);
        }

        //no octal float literal
        {
            //float f = 01.2p3;
        }
#endif
    }

#if __STDC_VERSION__ >= 199901L
    /*
    #compound literals

        C99.

        Before C99 there were no literals for arrays, structs or unions,
        while literals existed for ints, chars and even strings (which are arrays of chars...)

        Compound literals are exactly that: literals for types that are made up of many smaller
        pieces, thus compounded.

        Great source: <www.drdobbs.com/the-new-c-compound-literals/184401404>
    */
    {
        //#compound literals for arrays
        {
            int *is;

            is = (int[2]){ 0, 1 };
            assert(is[0] == 0);
            assert(is[1] == 1);

            //reassign is to a new array
            //old memory becomes innacessible
            is = (int[2]){ 2, 3 };
            assert(is[0] == 2);
            assert(is[1] == 3);

            //the effect is the same as `int is[] = { 1 }`
            //that is: fill with zeroes.
            is = (int[2]){ 1 };
            assert(is[0] == 1);
            assert(is[1] == 0);

            //Major application: pass initialized arrays and structs to functions.
            {
                func_array((int[]){ 1 });
                func_struct_1((struct func_struct){ .i = 1 });
            }
        }

        /*
        address

            Compound literals yield lvalues.

            It is possible to take the address of compound literals.

            Unlike string literals, array literals can be modified.

            This means that the compound literal is an unnamed stack variable,
            and takes stack space.
        */
        {
            int *ip;
            ip = &(int){1};
            ip[0]++;
            assert(*ip == 2);
        }

        //int useless examples
        {
            int i;

            i = (int){1};
            assert(i == 1);

            i = (int){1} + (int){1};
            assert(i == 2);

            // Any expression is fine
            {
                i = 0;
                i = (int){i + 1};
                assert(i == 1);
            }
        }

        //struct: see compound literal for struct

        /*
        scope

        Just like for normal variable declaration,
        compound literal memory can only be accessed in the scope in which it is declared.

        <http://stackoverflow.com/questions/14955194/lifetime-of-referenced-compound-array-literals>
        */
        {
            int *p;
            {
                p = (int[]){1, 2};
                assert(p[0] == 1);
            }
            //assert(p[0] == 1); //BAD *p is undefined
        }
    }
#endif

    /*
    #sizeof

        Gives the size of the RAM representation of types in bytes.

        The return type is `size_t.

    #size_t

        `size_t` is the data type that specifies data sizes in libc.

        `size_t` is large enough to represent any array index.

        Always use it in your code instead of `int` to have greater portability.

        Can be printed in `printf` with `%zu`.

    #size of base types

        base types like int of float don't have fixed ANSI sizes: only a minimum value is specified.
        so machines are free to take optimal values in terms of speed/storage

        `char` is an exception as it has a fized size of one byte.

        for most modifier os similar types (ex: short int, int, long, long long)
        the ANSI also guarantees size inequalities (equality is possible)

    #fixed size types

        besides the base times with nonfixed sizes, c99 ANSI libc also furnishes
        fixed sized types. See

        you should only use those when having a fixed size is crucial,
        otherwise just use the base c types which are optimized for speed
        according to each architecture.
    */
    {

        size_t size = sizeof(int);

        puts("sizeof (bytes):");
        printf("char        = %zu\n",  sizeof(char)         );
        printf("int         = %zu\n",  sizeof(int)          );
        printf("long int    = %zu\n",  sizeof(long int)     );
        printf("long long   = %zu\n",  sizeof(long long)    );
        printf("float       = %zu\n",  sizeof(float)        );
        printf("double      = %zu\n",  sizeof(double)       );
        printf("long double = %zu\n",  sizeof(long double)  );
        printf("wchar_t     = %zu\n",  sizeof(wchar_t)      );
        printf("size_t      = %zu\n",  sizeof(size_t)       );

        //char has fixed size:

            assert(sizeof(char)      == 1                       );

        //size equality is always possible:

            assert(sizeof(short int  ) <= sizeof(int           ));
            assert(sizeof(int        ) <= sizeof(long int      ));
            assert(sizeof(long int   ) <= sizeof(long long int ));

            assert(sizeof(float      ) <= sizeof(double        ));
            assert(sizeof(double     ) <= sizeof(long double   ));

        //unsigned does not change sizeof:

            assert(sizeof(unsigned int) == sizeof(int));
            assert(sizeof(unsigned long int) == sizeof(long int));
    }

    /*
    #typecast

        Transformation of one datatype to another.

        Can be done either implicitly or explicitly via a typecast operator.

        Some convertions may be possible to do implicitly
        but generate compiler warnings when done implicitly.
        this may depend on the compilation flags used.

        Some convertions always generate compilation errors.
    */
    {
        // Implicit typecasts done on operations
        {
            // On assignment, the value is cast to the type of the variable assigned to.
            {
                int i;
                // A typecast to int is done because `i` is `int`.
                i = 0.1;
                // SAME:
                i = (int)0.1;
                assert(i == 0);
            }

            // If an operation involves an integer type and a floating type,
            // TODO the integer type is cast to the floating type.
            {
                assert(1/2 == 0);
                assert(1/2.0 == 0.5);

                // Typecasts happen on the same order that the operations are evaluated.
                assert(2.0*(1/2) == 0.0);
                assert((2.0*1)/2 == 1.0);
            }

            // If an operation involves a smaller integer type and a larget integer type
            // TODO the smaller type is first cast to the larger type
            {
                assert((char)CHAR_MAX + 1 == ((int)(char)CHAR_MAX + 1));
            }
        }

        // integers and floating point types.
        {
            // float to int rounds towards 0.
            {
                assert((int)0.5 == 0);
                assert((int)-0.5 == 0);
            }

            // int to float can cause loss of precision if the int does not fit
            // in the fp mantissa.
            {
            }
        }

        // Typecasts without data modification
        {
            //Integer type to larger integer type (int -> long)
            {
                int i = 1;
                assert((int)(long)i == i);
            }

            // Floating type to larger floating type (float -> double)
            {
                float f = 1.0f;
                assert((float)(double)f == f);
            }

        }

        // Typecast of a value outside of range is undefined behaviour
        // (could return any value or raise any signal).
        if (0) {
            unsigned char uc = 256;

            char c = 1e1000;
        }

        // Array to pointer of same type:
        {
            int is[] = {0, 1, 2};
            int *is2 = is;
            assert(is2[0] == 0);
        }

        //#impossible typecats
        {

            //certain typecasts always generates compilation errors

            //implicit pointer to int is impossible:

                //{
                //    int* ip;
                //    int i;
                //    i = ip;
                //}

            //pointer to float is impossible even with explicit typecast:

                //{
                //    int* ip;
                //    float f;
                //    f = (float)ip;
                //}

            //pointers of different types,
            //even if types for which data can be converted like floats and doubles:

                //{
                //    float* fp;
                //    double* dp;
                //    dp = fp;
                //}

            //the big exception to this are void pointers, which can be converted
            //to/from any other type

            //array to array of different size:

                //{
                //    int is1[1];
                //    int is2[2];
                //    is2 = (int[])is1;
                //}
        }
    }

    /*
    #overflow

        Overflow has two meanings:

        - mathemtaical definition: making an operation in which the result
            is larger than the maximum value or smaller than the minimum value.

            This is the more common meaning of the term *overflow* outside of this context.

            In this section this will be called *mathematical overflow*.

            There is no automatic overflow check on operations
            except at initialization and assignment by constants
            at compile time.

            Operations that can overflow mathematically but never overflow include:

            - unsigned integer sum or multiplication

        - flag definition: raising the overflow FLAG on a x86 processor or analogous.

            This is the meaning of overflow in the ANSI C definition.

            Therefore, in this section this will be called simply *overflow*.

            Overflow always implies undefined behaviour. This could include a program crash!

            Therefore, is something overflows,
            it just silently overflows, possibly causing a hard to find bug.

            Operations that may overflow include:

            - signed integer sum or multiplication

            Since this kind of overflow modifies an observable processor state,
            it is possible for compilers to detect this situation.

        Flag overflow always implies mathematical overflow, but not the converse.
        For instance, unsigned integer overflow never raises the overflow flag of an x86
        processor: it just wraps around.
        Therefore, unsigned integer multiplication never overflows.

        #gcc overflow specifics

            gcc 4.8 is smart enough to warn in many cases with `-Woverflow`:
            which is part of `-Wall`. We have turned it off so it wont annoy us on our tests.

            `-ftrapv` causes gcc to detect an overflow and raise a `SIGABRT`,
            this making their behaviour defined.
    */
    {
        //integer overflow
        {
            // The same holds true for unsigned integer type.
            {
                unsigned int ui;
                ui = UINT_MAX + 1;
                assert(ui == 0);
            }

            // This could crash due to undefined behaviour.
            if (0) {
                int i;
                i = INT_MAX + 1;
                printf("signed integer sum overflow = %x\n", i);
            }

            // Detect if integer sum overflow would happen
            // http://stackoverflow.com/questions/199333/best-way-to-detect-integer-overflow-in-c-c

            // Unsigned multiplication does modulo:
            {
                unsigned char uc = 255;
                uc *= 2;
                assert(uc == 254);
            }

            // Signed multiplication undefined.
            // This could crash due to undefined behaviour.
            if (0) {
                char c = 0x8FFF;
                c *= -2;
                printf("char 0x8FFF * -2 = %x\n", c);
            }

            // Detect if integer multiplication overflow would happen:
            //http://stackoverflow.com/questions/1815367/multiplication-of-large-numbers-how-to-catch-overflow
        }

        //floating point
        {
            // TODO what happens? how to detect?

            assert(1.00000000000000000000000000000000000000000000001 == 1.0);
        }
    }

    //#const
    {
        int i = 0;
        const int ic = 0;
        //int const ic = 0
            //exact same thing!
        const int ic2 = i;

        const int ic3;
            //BAD
            //compiles without warning, but is bad since ic3 cannot get a value
            //unless you typecast its pointer with a warning. Consts should normally
            //have a value at initialization time.

        /*
        ERROR: consts are... almost consts!

        almost because you can change them with only a warning
        */
        {
            //const int ic = 0;
            //ic = 1;
        }

        /*
        WARN: discards const. in c++, error!

        we changed the const with only a warning

        this is why you can't int is[constint]; unless you have VLA
        */
        {
            //const int ic = 0
            //int* ip = &ic;
            //*ip = 1;
            //assert(ic == 1):
        }

        /*
        #const pointers

            There are 3 types of const pointers:

            - `const X *` or `X const *`    : cannot change the data of the thing pointer points to
            - `X * const`                   : cannot change which thing the pointer points to
            - `const X * const` or `X const * const` : both of the above
        */
        {
            //const int *
            //int const *
            {
                int i = 0;
                int j = 0;

                const int *cip = &i;
                int const *icp = &i;

                cip = &j;
                icp = &j;
                    //can change which opbject it points to

                //*cip = 2;
                //*icp = 2;
                    //ERROR: const * prevents from changing the data of the object pointed to
            }

            //int * const
            {
                int i = 0;
                int j = 0;
                int *const ipc = &i;

                *ipc = 1;
                assert(i == 1);

                //ipc = &j;
                    //ERROR
                    //cannot change what is being pointed to

                /*
                single line declaration of multiple const pointers

                    Just like `*` must be repeated once per variable, `*const` must also be repeated.
                */
                {
                    int i = 0;
                    int *const ipc2, *const ipc3, *ipcBad;
                    //               ^^^^^^
                    //               must repeat the `iconst` for each variable declared!

                    i = 0;
                    ipcBad = &i;
                    *ipcBad = 1;
                }

                {
                    const int ic = 0;
                    //int *const ipc = &ic;
                        //WARN
                        //initialization discards const
                        //it would be possible to change the value of the const
                    //*ipc = 1;
                        //BAD: we changed the value!
                }
            }

            const int* const cipc = &ic;

            const int cis2[2] = { 1, 2 };
            //cis2[0] = 1;
                //ERROR

            /*
            #const pointers to pointers

                There are 7 possibilities at level 2 already!

                To not mix up:

                - const always applies to the pointer at its left.
                - if there is no such pointer, it applies to the data
            */
            {
                int const ** icpp;
                int * const * ipcp;
                int ** const ippc;

                int const * const * icpcp;
                int const ** const icppc;
                int * const * const ipcpc;

                int const * const * const icpcpc;
            }

                /*
                #add const is not possible

                    `const int * = int *` is possible, but it is not possible to do `const int ** = int **`.

                    This is a bit counter-intuitive at first since:

                    - we feel like we are adding a `const` qualifier increases restrictoins.

                        However, when it may lead to const modification, it is not acceptable.

                    - the phenomenon only appears at level 2 pointers to pointers, not with simple pointers

                    Similar considerations apply to the `volatile` qualifier.

                    <http://stackoverflow.com/questions/1468148/initialization-between-types-const-int-const-and-int-is-not-allowed-why>
                */
                {
                    //if `const int ** = int **` were possible then we could change constants
                    {
                        /*
                        int* p = 0;
                        int const** pp = &p;    // (1) THIS cannot be done: `const int ** = int **`
                        int const c = 123;
                        *pp = &c;               // OK, &c is int const*, and *p is int const* lvalue. p points to c now!
                        *p = 666;               // OK: p is not const. We changed c!
                        */
                    }

                    //the problem only arises in multidimensional cases.
                    //here it is impossible to change a const
                    {
                        int i = 0;
                        int const * p = &i;
                    }
                }
        }

        /*
        #const struct
        */
        {
            /*
            entire struct

            members of a const struct cannot be modified.
            */
            {
                struct s { int i; };
                const struct s s = { 1 };
                //s.i = 2;
                    //ERROR
            }

            //single memebers can be declared const
            {
                struct s {
                    int i;
                    const int j;
                };
                struct s s = { 0, 1 };
                s.i = 2;
                //s.j = 2;
                    //ERROR
            }

            //entire structs cannot be declared const
            {
                //const struct s { int i; };
                    //WARN
                    //useless type qualifier
            }
        }

        /*
        #return const from func

            <http://stackoverflow.com/questions/8716330/purpose-of-returning-by-const-value>
            <http://stackoverflow.com/questions/8406898/benefits-of-using-const-with-scalar-type-e-g-const-double-or-const-int?lq=1>
        */
        {
            /*
            USELESS

            There seem to be no noticeable effect of returning const for non pointer scalars.
            */
            {
                //int_func();
                //const_int_func();
            }

            /*
            For pointer types this has a noticeable effect
            */
            {
                //possible
                {
                    int i = 0;
                    (*int_ptr_func_int_ptr(&i)) = 2;
                    assert(i == 2);
                }

                //ERROR
                {
                    int i = 0;
                    //(*const_int_ptr_func_int_ptr(&i)) = 2;
                    //assert(i == 2);
                }
            }

            /*
            For structs this also has a noticeable effect.

            In C++ however there can be noticeable effect
            because the returned object may have a non-const function that changes it
            so that the following is possible:

                objFunc().nonConst();

            but the following would not be:

                constObjFunc().nonConst();
            */
            {
                //struct_func
                //const_struct_func
            }
        }

#if __STDC_VERSION__ >= 199901L
        /*
        #const in array size function argument

            Same effect as declaring `int *const`, but without cast to pointer.
        */
        {
            int is2[2];
            is2[0] = 0;
            const_array_size_argument(is2);
            assert(is2[0] == 1);
        }
#endif
    }

    /*
    #static

        The static keyword has many uses in C.

        Multifile scope usage shall not be described here.
    */
    {
        /*
        #static variable in functions

            It is as if the variable were a global.

            Use with caution:

            - hard to understand
            - not thread safe
        */
        {
            int i;
            int si;

            with_static_var(&i, &si);
            assert(i == 1);
            assert(si == 1);

            with_static_var(&i, &si);
            assert(i == 1);
            assert(si == 2);
        }

#if __STDC_VERSION__ >= 199901L
        /*
        #static in function argument array size

            Specifies the minimum size of the array to be passed.

            Can be used by the compiler for optimization

            <http://stackoverflow.com/questions/3693429/c-parameter-array-declarators>

            Not enforced by the compiler and does not alter any behaviour
            except for the exact generated assembly code.

            If the contract is not followed by the programmer, undefined behaviour.
        */
        {
            // Undefined behaviour:
            int is2[2];
            //static_array_argument(is2);

            int is4[4];
            static_array_argument(is4);
        }
#endif
    }

    /*
    #automatic

        is the name for the default way to declare var
        that is not volatile neither register
    */
    {
        //SAME:

            int i;
            auto int i2;

        //ERROR:

            //auto i3;
    }

    /*
    #volatile

        Compiler will not store this value in cpu registers or cache as speed optimization
        instead of in RAM.

        Applications:

        - allow access to memory mapped devices
        - allow uses of variables between setjmp and longjmp
        - allow uses of sig_atomic_t variables in signal handlers.
        - multithreading, where variable may to change value at any time on another thread.

            For example on global scope:

                int other_task_finished;

            And on some function which must wait for another thread to finish a task:

                other_task_finished = 0;
                while(other_task_finished == 0){
                    yield();
                }
                //continue

            If the value were stored in register, other threads in other processes may never see an update.

            Concurrent operations on volatile variables are not guaranteed to be atomic.

            Unfortunatelly, this cannot be demonstrated as of ANSI C99 since there is no multithread support.
    */
    {
        volatile int vi;
    }

    /*
    #register

        hint to compiler that ri be stored in register
        instead of in RAM

        not necessarily honored

        almost always done without a hint if possible
    */
    {
        {
            register int ri;
        }

        //ERROR: cpu registers don't have addresses!
        {
            register int ri;
            //int* ip = &ri;
        }

        /*
        BAD: impossible to store compound types in registers
        compiler will certainly not honor `register` hint
        */
        {
            struct S { int i; };
            register struct S s;
        }
    }

    /*
    #inline keyword

        Signals the compiler that it may be worth to copy paste the function instead of calling it.

        The compiler is not obliged

        effects:

        - avoids function call, thus potentially faster
        - code gets larger
        - function pointer comparisons may differ for the same function
        - instruction cache might be come less efficient making thigs slower

        sources:

        - <http://www.greenend.org.uk/rjk/tech/inline.html>

            some warnings about inline and its usage
    */

    /*
    #typedef

        Create new types based on old ones

        On libc, the convention append `_t` to typedefs is used
        ex: `size_t`, `wchar_t`, etc.

        Some of those macros are defined to be strcitly integer types (like size_t)
        while others can be either integer or floating points according to the implementation.

        To print integer typedefs such with `printf`, see `printf`.
    */
    {

        {
            typedef int Newint;
            Newint i = 1;
            assert(sizeof(Newint) == sizeof(int));
        }


        //ERROR: unlike macros, typedef has scope just like that of variables:

            //Newint i = 1;

        /*
        typedef position is very flexible.

        Only use the first though if you want to be sane.
        */
        {
            typedef unsigned int uint;
            unsigned typedef int vint;
            unsigned int typedef wint;

            /* This is the only one that fails: */

                /*unsigned int xint typedef;*/
        }
    }

    //#enum
    {
        // Basics.
        {
            enum E
            {
                E1,
                E2,
                E3,
                E4,
            };

            enum E e = E1;

            //int E1 = 1;
                //ERROR
                //redeclartion of a

            //E1 = 2;
                //ERROR
                //can't change value of enums
                //this is why you can use them for array sizes

            //by default, values start from 0 and increase

                assert(E1 == 0);
                assert(E2 == 1);
                assert(E3 == 2);
                assert(E4 == 3);
        }

        //Typedef combo. No need to type enum everywhere.
        {
            // Multi line
            enum E { E1, E2};
            typedef enum E E;
            E e;

            // Single line
            typedef enum F {g1, g2} F;
            F f;
        }

        //you can choose the values explicitly
        {
            enum E
            {
                E1 = 1,
                E2 = 2,
                E3,
                E4 = 2, //equal values compile
            };

            assert(E1 == 1);
            assert(E2 == 2);
            assert(E4 == 2);

            //if you don't give a value
            //it gets a value different from all others

                assert(E3 != E1);
                assert(E3 != E2);
                assert(E3 != E4);
                printf("enum E3 = %d\n", E3);
        }

        // ERROR: only const expressions allowed
        //
        // This is why enum values are a good choice for array sizes.
        {
            const int i = 0;
            //enum Constexpr { N = i };
            //int is[N];
        }

        // It seems that it is not possible to control the size of an enum
        // without extensions.
        //
        // Compilers could make them smaller than int if there are less than INT_MAX
        // values in the enum, but gcc 4.8 -O0 does not do that.
        //
        // <http://stackoverflow.com/questions/4879286/specifying-size-of-enum-type-in-c>
        {
            {
                enum E { E1, E2, };
                printf("sizeof(enum E) = %zu\n", sizeof(enum E));
            }

            // The largest value that can be portably stored is INT_MAX.
            //
            // <http://stackoverflow.com/questions/366017/what-is-the-size-of-an-enum-in-c>
            {
                enum E { E1 = INT_MAX };
                //enum E_BAD { E1 = INT_MAX + 1};
            }
        }
    }

    /*
    #struct

        Application:

        - declare lots of data in one go

        - pass lots of data in one go to functions

        - avoid changing function signatures if you add a new field
            to your struct.

        Typedef: C structs are flawed in the sense that you must preffix
        it is common to give typedefs to structs, so that if someday you
    */
    {
        struct S
        {
            int i;
            float f;
        };

        //initialize by order
        {
            struct S s = { 1, 1.0 };
            assert(s.i == 1);
            assert(s.f == 1.0);

            s.i = 2;
            s.f = 2;
            assert(s.i == 2);
            assert(s.f == 2.0);
        }

        //define and initialize at the same time
        {
            struct S { int i; int j; } s0 = { 0, 1 }, s1 = { 2, 3 };
            assert(s0.i == 0);
            assert(s1.i == 2);

            struct S s2 = { 4, 5 };
        }

#if __STDC_VERSION__ >= 199901L

        /*
        #designated initializer for structs

            C99.

            Allows to struc values by their name instead of order.

            Sources:

            - oracle tutorial with examples: <http://docs.oracle.com/cd/E19205-01/819-5265/bjazo/index.html>
        */
        {
            {
                struct S s = {
                    .f = 1.0,
                    .i = 1
                };
                assert(s.i == 1);
                assert(s.f == 1.0);
            }

            //can be mixed with array designated initializers
            {
                struct S { int a[2]; int i; };

                struct S ss[] = {
                    [0].a = {0, 1},
                    [0].i = 2,
                    [1].a[0] = 3,
                    [1].a[1] = 4,
                    [1].i = 5
                };

                assert(ss[0].a[0] == 0);
                assert(ss[0].a[1] == 1);
                assert(ss[0].i == 2);

                assert(ss[1].a[0] == 3);
                assert(ss[1].a[1] == 4);
                assert(ss[1].i == 5);
            }
        }

#endif

        {
            /*
            assignment only works for initialization,
            unless use a c99 compound literal
            */
            {
                struct S { int i; };
                struct S s;
                //s = { 1 };
                //s = { .i = 1 };
            }

            /*
            #compound literals for structs

                c99 compound literals allow to assign structs to struct literals.
            */
            {
                struct S { int i; int j; };

                {
                    struct S s;
                    s = (struct S){ 1, 2 };
                    assert(s.i == 1);
                    assert(s.j == 2);
                }

                {
                    struct S s;
                    s = (struct S){ .j = 2, .i = 1 };
                    assert(s.i == 1);
                    assert(s.j == 2);
                }
            }
        }

        //pointer to struct
        {
            struct S s;
            struct S* sp;

            sp = &s;

            //equivalent `a->b` equals `(*a).b`

                sp->i = 1;
                //(*sp).i = 1;

            assert(s.i == 1);
        }

        //array of structs initialization
        {
            struct S
            {
                int i;
                int j;
            };

            //non designated
            {
                struct S ss[] = {
                    { 0, 1 },
                    { 2, 3 },
                };

                assert(ss[0].i == 0);
                assert(ss[0].j == 1);
                assert(ss[1].i == 2);
                assert(ss[1].j == 3);
            }

#if __STDC_VERSION__ >= 199901L

            //designated
            {
                struct S ss[] = {
                    { .j = 1, .i = 0 },
                    { .j = 3, .i = 2 },
                };

                assert(ss[0].i == 0);
                assert(ss[0].j == 1);
                assert(ss[1].i == 2);
                assert(ss[1].j == 3);
            }
        }

#endif

        /*
        array fields

            length must be specified,
            allocates that many objects of the given type
        */
        {
            {
                struct S
                {
                    //ERROR:
                        //int is[];
                    int is0[2];
                    int is1[2];
                };

                struct S s = { { 0, 1 }, { 2, 3 } };
                assert(s.is0[0] == 0);
                assert(s.is0[1] == 1);
                assert(s.is1[0] == 2);
                assert(s.is1[1] == 3);

                //non designated init
                {
                    struct S ss[] = {
                        { { 0, 1 }, { 2, 3 } },
                        { { 4, 5 }, { 6, 7 } }
                    };
                    assert(ss[0].is0[0] == 0);
                    assert(ss[0].is0[1] == 1);
                    assert(ss[0].is1[0] == 2);
                    assert(ss[0].is1[1] == 3);
                    assert(ss[1].is0[0] == 4);
                    assert(ss[1].is0[1] == 5);
                    assert(ss[1].is1[0] == 6);
                    assert(ss[1].is1[1] == 7);
                }

#if __STDC_VERSION__ >= 199901L

                //designated init
                {
                    struct S ss[] = {
                        { .is0 = { 0, 1 }, .is1 = { 2, 3 } },
                        { .is0 = { 4, 5 }, .is1 = { 6, 7 } },
                    };
                    assert(ss[0].is0[0] == 0);
                    assert(ss[0].is0[1] == 1);
                    assert(ss[0].is1[0] == 2);
                    assert(ss[0].is1[1] == 3);
                    assert(ss[1].is0[0] == 4);
                    assert(ss[1].is0[1] == 5);
                    assert(ss[1].is1[0] == 6);
                    assert(ss[1].is1[1] == 7);
                }

#endif

            }

            //works for strings
            {
                struct S
                {
                    char cs[3];
                    int i;
                };

                {
                    struct S s = { .cs = "ab", .i = 1 };
                    assert(strcmp(s.cs, "ab") == 0);
                    assert(s.i == 1);
                }

                {
                    struct S s = { "ab", 1 };
                    assert(strcmp(s.cs, "ab") == 0);
                    assert(s.i == 1);
                }

                //struct S s = { "ab" };
            }
        }

        /* substructure init: it all works as expected */
        {
            struct S1 { int i; int j; };
            struct S0 { struct S1 s; };

            //non-designated init
            {
                struct S0 s = { { 1, 2 } };
                assert(s.s.i == 1);
                assert(s.s.j == 2);
            }

#if __STDC_VERSION__ >= 199901L

            //designated init
            {
                struct S0 s = {
                    .s = {
                        .j = 2,
                        .i = 1
                    }
                };
                assert(s.s.i == 1);
                assert(s.s.j == 2);
            }

#endif

        }

        /*
        #incomplete type cycles

            Incomplete types are types which only have a declaration but no definition.
        */
        {
            /*
            It is impossible to do the following, because that would create an infinite loop:

            - each S contains one S. and one i.
            - therefore the size of each S must be 2 ints:

                    size of S + size of int =
                            1 +           1 =
                                          2

            - but then the size of S must be 3 ints:

                    size of S + size of int =
                            2 +           1 =
                                          3
            */
            {
                //ERROR s has incomplete type
                {
                    /*
                    struct S {
                        struct S s;
                        int i;
                    };
                    */
                }

                {
                    /*
                    struct S0 { struct S1 s1; };
                        //ERROR
                        //struct s1 undefined
                    struct S1 { struct S0 s0; };
                    */
                }

                {
                    /*
                    struct S1;
                    struct S0 { struct S1 s1; };
                        //ERROR
                        //s1 has incomplete type
                    struct S1 { struct S0 s0; };
                    */
                }
            }

            /*
            can have incomplete type pointers

            forward declaration of S1 makes it makes it alright.
            */
            {
                struct S1;
                struct S0 { struct S1 *s1; };
                struct S1 { struct S0 *s0; };
            }
        }

        /*
        assign

            Assigns fields one by one.
        */
        {
            struct S s  = { 1, 1.0 };
            struct S s2 = { 2, 2.0 };
            s = s2;
            assert(s.i == 2);
            assert(s.f == 2.0);
        }

        //equality `==` does not exist. There have been failed proposals.
        {
            struct S { int i; };
            struct S s  = { 1 };
            struct S s2 = { 1 };
            //assert(s == s2);
        }

        /*
        Inequalities do not exist: `<` `>` `<=` `>=`

        Possible rationale: if `s.a < s2.a` and `s.b > s2.b`, what does `s < s2` eval to?
        */

        /*
        typedef struct combo: avoid typing struct all over
        */
        {
            typedef struct
            {
                int i;
            } S;

            S s = {1};
            S* sp = &s;
        }

        /*
        struct size

            the way data is packed in a struct is not specified in the standard

            common compiler strategy: align data to 32 bits
            which makes acess faster, using slightly more memory
        */
        {
            struct S
            {
                char c;
                int i;
            };

            //likelly to be 8 on a 2013 32 bit machine:
            printf("struct sizeof = %d\n", sizeof(struct S));

            assert(sizeof(char) + sizeof(float) <= sizeof(struct S));
        }

        /*
        #anonymous structure

            It is possible to crate structs which don't have a name.

            Only the structs declared immediatiely after definition can be used.
        */
        {
            //basic
            {
                struct { int i; int j; } s;
                s.i = 0;
                assert(s.i == 0);
            }

            //initialize
            {
                struct { int i; int j; } s = { 0, 1 };
                assert(s.i == 0);
                assert(s.j == 1);
            }

            //initialize array good style
            {
                struct { int i; int j; } s[] = { { 0, 1 }, { 2, 3 } };
                assert(s[0].i == 0);
                assert(s[0].j == 1);
                assert(s[1].i == 2);
                assert(s[1].j == 3);
            }

            /*
            initialize array bad style

                Generates a warning on gcc 4.7 and is horrible to read.
            */
            {
                //struct { int i; int j; } s[] = { 0, 1, 2, 3 };
                //assert(s[0].i == 0);
                //assert(s[0].j == 1);
                //assert(s[1].i == 2);
                //assert(s[1].j == 3);
            }
        }

#if __STDC_VERSION__ >= 201112L

        /*
        #anonymous substructure and union

            C11

            <http://stackoverflow.com/questions/1972003/how-to-use-anonymous-structs-unions-in-c>
        */
        {
            //TODO0
        }

#endif

        /*
        #bitfields

            Gives support for fields which contain a single bit in the language.
        */
        {
            struct S
            {
                unsigned b1 : 1;
                unsigned b2 : 2;
                unsigned b3 : 3;

                //padding untill next int is added automatically because
                //next data is not a bitfield and accesses is faster if it is aligned

                    int i;

                unsigned b4 : 1;

                //manually adds padding untill next field
                //even if it is a bitfield

                    unsigned : 0;

                unsigned b5 : 1;
            } s ;

            assert(sizeof(struct S) == 16);

            s.b1 = 1;
            assert(s.b1 == 1);

            //s.b1 = 2;
                //WARN
                //overflow
                //truncate

            int i = 2;
            s.b1 = i;
            assert(s.b1 == 0);

            i = 3;
            s.b1 = i;
            assert(s.b1 == 1);
                //only takes lsb
        }

        /*
        #offsetof

            get distance of member variable from the start of the struct

            appliction: get the struct that corresponds to a given pointer to a field.
            this is used in the kernel via `container_of`, and can be used to implement
            linked lists in ANSI c: <http://stackoverflow.com/questions/10269685/kernels-container-of-any-way-to-make-it-iso-conforming>
        */
        {
            struct foo
            {
                char a;
                char b[2];
                int c;
                char d;
            };

            printf("offsetof(struct foo, a) = %zu\n", offsetof(struct foo, a));
            printf("offsetof(struct foo, b) = %zu\n", offsetof(struct foo, b));
            printf("offsetof(struct foo, c) = %zu\n", offsetof(struct foo, c));
            printf("offsetof(struct foo, d) = %zu\n", offsetof(struct foo, d));
        }
    }

    /*
    #union

        like struct, but all fields share the same data space

        if there are several data sizes, the struct has the size of the largest

        TODO applications: <http://stackoverflow.com/questions/4788965/c-c-when-would-anyone-use-a-union-is-it-basically-a-remnant-from-the-c-only>
    */
    {
        {
            union U
            {
                int i;
                int j;
            } u;
            u.i = 0;
            u.j = 1;
            assert(u.i == 1);
        }
    }

    /*
    #order of evaulation

        The order of evaluation for expressions that are arguments of functions or operators is not specified.

        For example, it is undetermined behaviour in `f1() * f2()` if `f1` or `f2` is evaluated first.

        The same goes for `g(f1(), f2())`.

        Also note that there is a further separation between evaluation (getting the value to pass forward),
        and side effects which this evaulation may have (increasing `i` on an `i++`).
        See sequence point` for that.

    #sequence point

        <http://stackoverflow.com/questions/10782863/what-is-the-correct-answer-for-cout-c-c>
        <http://stackoverflow.com/questions/3575350/sequence-points-in-c>
        <http://stackoverflow.com/questions/4176328/undefined-behavior-and-sequence-points>

        Some language features force side effects of an expression evaluation
        to happen before continuing while others don't.

        A typical example of a side effect is the increment of `i` on `i++`,
        being the main effect the returning of the value of `i` before the increment.

        Sequence points are the operations which enforce order of evaulation.

        A full list is given here: <http://en.wikipedia.org/wiki/Sequence_point>

        Since operators such as `*` or `+` are not on the sequence point list,
        it is undetermined behaviour in `f1() * f2()` if `f1` or `f2` is evaluated first.
        The same goes for `-`, `/` and the evaulation of arguments of a function.

        Other operators however do create sequence points, for example the comma operator.

        In simple cases, gcc 4.7 is smart enough to notice undefiened behaviour and emmits a warning.
        This warning has been ignored for test purposes by a test only `-Wno-sequence-point` flag.
    */
    {
        /*
        Undefined behaviour.

        `=`does not create sequence points, to it is not possible to know if the side effect of `++`
        will happen before or after the assigment.

        Therefore, it is possible that this gives either:

            post_increment_return = 0;
            i = post_increment_return;
            i++;

        or

            post_increment_return = 0;
            i++;
            i = post_increment_return;
        */
        {
            int i = 0;
            i = i++;
            printf("i = i++ = %d\n", i);
            assert(i == 0 || i == 1);
        }

        /*
        Defined behaviour because the return statement guarantees that all side effects have happened.

        Contrast with `i = i++`, which has no return statement.
        */
        {
            global = 0;
            global = post_inc_global();
            assert(global == 0);
        }

        /*
        `+` does not specify a sequence point between its two sides.

        Therefore, the side effect of either `++` (incrementing i) may or may not happen before the other `++` is evaluated.

        This allows for the following outputs:

            0 + 0           (neither side effect happened before the other)
            1 + 0 or 0 + 1  (one side effect happened before the other)
        */
        {
            int i = 0;
            int j = i++ + i++;
            printf("i++ + i++ = %d\n", j);
            assert(j == 0 || j == 1);
        }

        /*
        Undefined behaviour.

        The return statements are full expressions,
        so they guarantee that either one or the other function call happens first.

        However, it is not possible to know which side of `-` is evaulated first.

        Ouptput depends on evaulation order, giving either:

            0 - 1 = -1

        if the first `post_inc_global()` is evaluated first or

            1 - 0 = 1

        if the second `post_inc_global()` is evaluated first.
        */
        {
            global = 0;
            int j = post_inc_global() - post_inc_global();
            printf("post_inc_global() - post_inc_global() = %d\n", j);
            assert(j == -1 || j == 1);
        }

        /*
        Defined behaviour because of the commutativity of addition and because the return statements guarantees
        that all side effects are done with.

        Constrast with `++global + ++global`, which is undefined because there are no return statements.

        This may give either:

            0 + 1 = 1

        or

            1 + 0 = 1

        so both are the same by coincidence.
        */
        {
            global = 0;
            assert(post_inc_global() + post_inc_global() == 1);
        }

        /*
        Comma operator introduces a sequence point.
        */
        {
            int i = 0;
            assert((i++, i++) == 1);
        }

        /* declarators in declarator sequence instroduce sequence points */
        {
            int i = 0, j = i;
            assert(j == 0);
        }

        /*
        Boolean operators `||` and `&&` introduce a sequence point.
        */
        {
            /*
            The following happens:

            - the first i++ returns 0
            - since this is false, the second side is evaulated
            - since `||` adds a sequence point, the increment side effect must happen
            - i now equals one, and `||` evals true
            */
            {
                int i = 0;
                assert(i++ || i);
            }

            /* same as for `||` */
            {
                int i = 1;
                assert(! (i-- && i));
            }
        }
    }

    //#operators
    {
        //#arithmetic
        {
            assert((1 + 2) == 3 );
            assert((2 * 3) == 6 );

            /*
            #division

                Division is the most complex of the basic operations.

                Integer division and floating point division are different
                operations, which translate to different CPU instructions!

                Remember that if an operation involves a floating point and an integer,
                C first casts the integer type to a floating point type, then does
                the floating point operation.

                Division by `0` leads to different problems, which are also different
                on the floating point and integer cases.

            #INT_MIN / -1

                `INT_MIN / -1` is undefined in 2's complement,
                and 2's complement is explicitly said to be compliant to the C
                integer representation standard.
            */
            {
                assert((4 / 2)         == 2  );

                /* integer division */
                assert((1 / 2)         == 0  );

                /* floating poitn division */
                assert((1.0 / 2.0)     == 0.5);

                /* floating poitn division. `1` is cast to `double` point */
                assert((1 / 2.0)       == 0.5);

                /* same as above */
                assert((1 / (double)2) == 0.5);
            }

            assert((3 % 3) == 0);
            assert((4 % 3) == 1);
            assert((5 % 3) == 2);
            assert((6 % 3) == 0);
        }

        //#boolean
        {
            assert((1 == 1) == 1);
            assert((0 == 1) == 0);

            assert((0 >  1) == 0);
            assert((0 >  0) == 0);
            assert((0 > -1) == 1);
            assert((0 <  1) == 1);
            assert((0 <  0) == 0);
            assert((0 < -1) == 0);

            assert((0 >=  1) == 0);
            assert((0 >=  0) == 1);
            assert((0 >= -1) == 1);
            assert((0 <=  1) == 1);
            assert((0 <=  0) == 1);
            assert((0 <= -1) == 0);

            assert((0 || 0) == 0);
            assert((0 || 1) == 1);
            assert((1 || 0) == 1);
            assert((1 || 1) == 1);

            assert((0 && 0) == 0);
            assert((0 && 1) == 0);
            assert((1 && 0) == 0);
            assert((1 && 1) == 1);

            /*
            #short circuit evaluation

                For operators `||`, `&&` and `?`, the second side is only evaluated if needed.

                On this example:

                - 1 is evaulated to true
                - || does not need to go any further, so i++ is not evaluated
            */
            {
                int i = 0;
                if (1 || i++);
                assert(i == 0);
            }
        }

        //#bitwise
        {
            //#NOT
            assert((~(char)0x00) == (char)0xFF);
            assert((~(char)0xFF) == (char)0x00);

            //#OR
            assert(((char)0x00 & (char)0x00) == (char)0x00);
            assert(((char)0xFF & (char)0x00) == (char)0x00);
            assert(((char)0xFF & (char)0xFF) == (char)0xFF);

            //#XOR
            assert(((char)0x00 ^ (char)0x00) == (char)0x00);
            assert(((char)0xFF ^ (char)0x00) == (char)0xFF);
            assert(((char)0xFF ^ (char)0xFF) == (char)0x00);

            /*
            #shift operators

                Low level bit shifting.

                Undefined behaviour occurs if *any* of the inputs is signed.

                For the right input, the result would
                depend on which integer representation is being used,
                which is not fixed by the C standard.
            */
            {
                assert((1u << 0u) == 1u);
                assert((1u << 1u) == 2u);
                assert((1u << 2u) == 4u);
                assert((1u << 3u) == 8u);

                assert((8u >> 0) == 8u);
                assert((8u >> 1) == 4u);
                assert((8u >> 2) == 2u);
                assert((8u >> 3) == 1u);
                assert((8u >> 4) == 0u);
                assert((5u >> 1) == 2u);

                /* Undefined behaviour, likely warnings: */

                    /*printf("2u << -1 = %d\n", 2u << -1);*/
                    /*printf("-1 << 1u = %d\n", -1 << 1u);*/
            }
        }

        /*
        #assign
        */
        {
            {
                int i = 0;
                i = 1;
                assert(i == 1);
            }

            /*
            = returns rvals
            */
            {
                int i;
                assert((i = 1) == 1);

                /*
                This is why this works (and probably why it is made behave like this.
                */
                {
                    int i, j, k;
                    i = j = k = 1;
                    //i = (j = (k = 1))
                    assert(i == j && j == k && k == 1);
                }
            }

            /*
            #self assign initialization

                Good old undefined behaviour through innocent statements.

                <http://stackoverflow.com/questions/11186261/why-is-int-i-i-legal>
            */
            {
                int self_assign_init = self_assign_init;
                printf("self_assign_init = %d\n", self_assign_init);
            }

            /*
            #lvalue

                Something that can be on the left side of an assign, such as a variable.

                Every lvalue is a rvalue.

            #rvalue

                Something that can only be used on the right side of an assign,
                but not on the left side.
            */
            {
                /*
                In C, assign does not return lvalues.

                In C++ it does.
                */
                {
                    int i = 0, j = 1, k = 2;
                    //(i = j) = k;
                }

                /*
                Function returns are rvalues.

                In C++, this has an exception: functions that return references return lvalues
                */
                {
                    //int_func_int(1) = 1;
                    //struct_func().i = 1;
                }

                /*
                A dereferenced pointer becomes an lvalue.
                */
                {
                    int i = 0;
                    (*int_ptr_func_int_ptr(&i)) = 2;
                    assert(i == 2);
                }
            }
        }

        /*
        #increment

            #pre increment vs post increment

                <http://stackoverflow.com/questions/24886/is-there-a-performance-difference-between-i-and-i-in-c>

                which is faster?

                - in c, equal
                - in c++, ++i potentially if i is a complex object

            #why increment operators exit

                why it exists if equivalent to x=x+1?

                because there is an x86 instruction for that

                why?

                - because it takes less program memory `inc eax`, instead of `sum eax,1`
                - and is a *very* common instruction

                what about +=, -=, etc. ?

                same thing: `ax = ax + bx` == `sum ax,bx`
        */
        {
            int i;

            i=0;
            assert(i++ == 0);
            assert(i == 1);

            i=0;
            assert(++i == 1);
            assert(i == 1);

            i=1;
            assert(i-- == 1);
            assert(i == 0);

            i=1;
            assert(--i == 0);
            assert(i == 0);

            double f = 0.0;
            assert(f++ == 0.0);
            assert(f == 1.0);
        }

        /*
        Composite operators

            Do an operation and an assign at the same time.

            Exist for many operators.

            Why do they exist? Assemby support probably,
            as many assembly operations overwrite one of the operands.
        */
        {
            int i;

            i = 0;
            assert((i += 1) == 1);
            assert(i == 1);

            i = 1;
            assert((i -= 1) == 0);
            assert(i == 0);

            i = 1;
            assert((i *= 2) == 2);
            assert(i == 2);

            i = 2;
            assert((i /= 2) == 1);
            assert(i == 1);

            i = 3;
            assert((i %= 2) == 1);
            assert(i == 1);

            i = 0xFF;
            assert((i &= (char)0x00) == (char)0x00);
            assert(((char)i == (char)0x00));

            //same others bitwise, except ~=
        }

        /*
        #ternary operator #question mark #?

            Called ternary operator since it is the only operator that
            takes 3 inputs.

            It seems that the only use for the ternary operator is writing less,
            so it is completely redundant with and if else:
            <http://stackoverflow.com/questions/758849/the-ternary-conditional-operator-in-c>
        */
        {
            assert((1 < 2 ? 3 : 4) == 3);
            assert((1 > 2 ? 3 : 4) == 4);

            /* The ternary operator can also yield lvalues. */
            {
                int x = 0, y = 1, *xp = &x, *yp = &y;
                *(1 ? xp : yp) = 10;
                assert(x == 10);
            }

            /* The possible to initialize consts with the ternary operator. */
            {
                const int i = 0 ? 1 : 2;
                char *s = 0 ? "a" : "b";
            }
        }

        /*
        #comma operator

            Obscure and almost useless C operator.
        */
        {
            /*
            Commas here are part of the declarator sequence,
            just like in functions calls/defs. They are not
            comma operators!
            */

                int i=0, a=1, b=2, c=3;

            /*
            ignores values on left
            takes only last value on right

            BAD: operations on left has no effect
            */

                assert((i = 0, 1       ) == 1);
                assert((i = 0, i = 1, 2) == 2);

            /*
            assign has precedence over comma
            BAD: operation on right has no effect
            */
            {
                i = 2;
                (i = 0), 1;
                i = 0, 1;
                assert(i == 0);
            }

            //int j=0, 1;
                //ERROR
                //declaration int j does not return a value

            //operation on left comes first
            {
                i=2;
                assert((i=0, i) == 0);
                i=2;
                assert((i=0, i++, i) == 1);
            }

            //must be parenthesis protected when passesd as function argument
            //to differentiate from argument separtor comma
            {
                int i = 0;
                assert(int_func_int((i++, i)) == 1);
            }
        }
    }

    /*
    #pointer

        pointers contain addresses of variables instead of the value

        using the dereference operator `*`, you can get the value from the address
    */
    {
        int i;
        int *pi, *pi2;
        //*pi = 7;
            //BAD
            //you are modifying some random piece of memory!!!!
            //must declare like that: multiple stars
        pi = &i;
        *pi = 1;
        assert(i == 1);
        assert(*pi == 1);
        i = 2;
        assert(i == 2);
        assert(*pi == 2);

        printf("(void*)pi = %p\n", (void*)pi);
        printf("(void*)(pi+1) = %p\n",(void*)(pi+1));

        //OK: implicit conversion * -> int:

            pi2 = pi + 1;
            printf("(void*)(pi2-pi) = %p\n", (void*)(pi2-pi));
            assert(pi2 - pi == 1);

        //ERROR: incompatible pointer type

            //float* fp = &i;

        //OK: works with explicit cast:

            float* fp = (float*)&i;

        /*
        #single line multiple pointer declaration

            You must put an asterisk for each pointer, or they are not taken to be pointers!

            This is not very intuitive since the asterisk is part of the type, not of the variable.
        */
        {
            //correct
            {
                int i, *ip ;
                ip = &i;
            }

            //ERROR: ip2 is not a pointer, but an int!
            {
                //int i;
                //int* ip, ip2;
                //ip = &i;
                //ip2 = &i;
            }
        }

        /*
        #NULL pointer

            good source: <http://c-faq.com/null/macro.html>

            basic usage: indicate error as return value from function
        */
        {
            /*
            why it works: it never points to any possible valid memory location.
            (`&` operator never gives anything equal to it).
            this is so guaranteed that gcc emmits a warning in the following code
            */
            {
                int i = 0;
                //assert(&i != NULL);
                    //gcc 4.7 warning: &i will never be null. Smart.
            }

            //how it prints like:

                printf("NULL = %p\n", NULL);

            //`if(NULL)` and `if(!NULL)` in error checking code always work as expected

                assert(!NULL);

            /*
            #null macro vs 0

                Relationship to 0: `(int*)0`, `(char*)0` or any other pointer type followed by zero
                is always converted internally to the null pointer

                This is a valid way of representing the null pointer,
                but it is better style to always use the `NULL` macro

                The exact definition of `NULL` is implementation dependant.
                A very common implementation is as `(void*)0`.

                C++11 introduces nullptr, which is a much cleaner solution.
            */
            {
                assert(NULL == (int*)0);
                assert(NULL == (char*)0);
                printf("sizeof(NULL) = %zu\n", sizeof(NULL));
            }

            //ERROR: comparison of distinct pointer types requires a cast:
            {
                //assert((int*)0 == (char*)0);
            }

            /*
            Never dereference the NULL pointer since it is guaranteed to point to nothing.

            TODO0 to ANSI C, undefined behaviour? or guaranteed error?

            May lead to a Segmentation fault.
            */
            {
                //volatile int i = *(int*)NULL;
            }
        }

        /*
        #void pointer

            Cannot be dereferenced without typecast.

            Can be typecast to/from anything TODO confirm.
        */
        {

            void* vp;
            int* ip;
            int i = 0;

            /*
            There is no corresponding data type.

            Since there is no data, there is no data size.

            This means that `sizeof(void)` is not possible, nor is pointer arithmetic operations.
            */
            {
                /*ERROR*/
                //void v;

                //ERROR: invalid application of sizeof to void type

                    //printf("sizeof (void) = %d\n", sizeof(void));

                //it is however possible to get the size of a `void*` TODO0 it is the same size of all other pointers

                    printf("sizeof (void*) = %d\n", sizeof(void*));

                //ERROR: invalid application of sizeof to void type

                    //vp = vp + 1;
            }

            //int* to void*:

                vp = (void*)&i;

            //void* to int*:

                ip = (int*)vp;

            //void* to int:

                i = (int)vp;

        }

            /*
                #usage of the void pointer type

                    should almost never be used since it gives little information to the compiler
                    and code readers about the function of the variable.

                    one libc ocurrence of void pointers is the return type of `malloc`:
                    it is not aware of the type of data it returns, and it is usually typecast
                    to whatever datatype needed.

                    another possibility functions which require arguments where it is impossible to
                    determine the type of the argument. For example, a function that takes a function,
                    and parameters to that function. Here, the parameters are arbitrary. This is used
                    on the ODE solver of the gnu project GSL.

                    TODO add simple examples of valid usage
            */
    }

    /*
    #array

        c arrays are simply lots of values put side by side on memory

        because they are side by side, it is simple to get the nth value
        quickly (random access), unless like, say, a linked list, in which
        you have to go follow lots of links before you reach the searched value.

        no bound check is done to avoid overhead.
    */
    {
        {
            int is[3];
            is[0] = 0;
            is[1] = 1;
            is[2] = 2;
            assert(is[0] == 0);
            assert(is[1] == 1);
            assert(is[2] == 2);
        }

        {
            int is[] = { 0, 1, 2 };
            assert(is[0] == 0);
            assert(is[1] == 1);
            assert(is[2] == 2);
                //allocates exact size
            //is = {3,4,5};
                //ERROR
        }

        {
            int is[4] = { 1, 2 };
            assert(is[0] == 1);
            assert(is[1] == 2);
            assert(is[2] == 0);
            assert(is[3] == 0);
        }

        {
            int is[4]  = { 1, 2 };
            int is2[4] = { 1, 2 };
            //is = is2; //ERROR incompatible pointer types
        }

        /*WARN array too small*/
        {
            //int is[2] = { 1, 3, 2 };
        }

        /* ERROR no negative sized array! */
        {
            //int is[-1];
        }

        /*
        ERROR no 0 size array

        Possible as a gcc extension.
        */
        {
            //int is[0];
        }

#if __STDC_VERSION__ >= 199901L
        /*
        #designated initializer for arrays

            C99

            Allows to initialize array elements in any order.
        */
        {
            {
                int is[] = {
                    [1] = 1,
                    [0] = 0,
                };
                assert(is[0] == 0);
                assert(is[1] == 1);
            }

            //missing elements are zeroed
            {
                int is[2] = {
                    [1] = 1,
                };
                assert(is[0] == 0);
                assert(is[1] == 1);
            }

            /*
            Multiple assignments for a single int.

            BAD but possible.x

            Only last takes effect.
            */
            {
                int is[1] = {
                    [0] = 0,
                    [0] = 1,
                };
                assert(is[0] == 1);
            }

            //arrays of structs can refer multiple times to the same struct
            {
                struct S { int i; int j; };

                struct S ss[] = {
                    [0].i = 0,
                    [0].j = 1,
                    [1].i = 2,
                    [1].j = 3,
                };

                assert(ss[0].i == 0);
                assert(ss[0].j == 1);
                assert(ss[1].i == 2);
                assert(ss[1].j == 3);
            }

            /*
            mix designated and non designated initialization

            non deignated pick off where the last designated left

            non specified ones are zero.
            */
            {
                {
                    int is[4] = {
                        -1,             //[0]
                                        //[1] was not specified, so it is 0.
                        [2] = 1,
                        2,              //[3], because it comes after [2]
                    };
                    assert(is[0] == -1);
                    assert(is[1] == 0);
                    assert(is[2] == 1);
                    assert(is[3] == 2);
                }

                //possible to overwrite values
                {
                    int is[2] = {
                        0,          //[0] first assign
                        1,          //[1] first assign
                        [0] = 2,    //[0] second assign, overwrites first
                        3,          //[1] because comes after [0], second assign, overwrites first
                    };
                    assert(is[0] == 2);
                    assert(is[1] == 3);
                }
            }
        }
#endif

        /*
        Obscure and confusing access syntax that you should never use except to surprise your friends.

        All that the standard says is that: a[b] = *(a + b). If a is the int and b the pointer or the contrary
        does not matter: all that matters is that one is an int and the other a pointer.

        This seems to have been left like this since it is easier to compile.

        <http://stackoverflow.com/questions/381542/in-c-arrays-why-is-this-true-a5-5a>
        */
        {
            int is[] = { 1, 3, 2 };
            assert(is[1] == 1[is]);
        }

        /*
        #store array length in variables

            Before C99, it was not possible to store array length in variables,
            not even if they are const.

            The two workarounds were:

            - enum
            - macros

            C99 introduces VLA which allows that.

            In C++ it is possible to store array sizes inside const variables,
            and this is even more explicit with C++11 `constexpr` keyword.
        */
        {
            {
                //int n = 2;
                //int isVla[n] = { 1, 2 };
                    //ERROR
                    //cannot be initialized
            }

            {
                //const int n = 2;
                //int isVla[n] = { 1, 2 };
                    //ERROR
                    //cannot be initialized
            }

            //enum. Seems to be the best solution.
            {
                enum Constexpr { N = 3 };
                int is[N];
                is[2] = 1;
            }

            /*
            macro

                Shares the disadvantage of every macro of having no scope.

                Use enum instead.
            */
            {
#define DEFINESIZE 3
                int is[DEFINESIZE];
                is[2] = 1;
            }

#if __STDC_VERSION__ >= 199901L
            /*
            #vla #variable length array

                C99

                Implementation:

                - increase/decrease stack pointer
                - requires one addition and one multiplication per declaration

                Pros and cons:
                <http://stackoverflow.com/questions/3082126/c99-faq-and-variable-length-arrays>
            */
            {
                srand(time(NULL));
                int size = 1 + (rand() % 10);
                int vla[size];

                /* sizeof is evaluated at runtime for VLAs */
                assert(sizeof(vla) == size * sizeof(int));

                /*
                VLAs can be passed to functions.

                <http://stackoverflow.com/questions/17371645/parameter-of-a-function?lq=1>
                */
                {
                    size_t size = 2;
                    int vla[size];
                    vla_arg(size, vla);
                }

                /*
                If the size must come after the vla (for example, to interface witha FORTRAN
                interface that does so), the only possibility is to use K&R function definition syntax!

                This is one of the very few application of K&R syntax to C99.
                */
                {
                    size_t size = 2;
                    int vla[size];
                    vla_arg_k_and_r(vla, size);
                }
            }
        }
#endif

        //pointers and arrays are different
        {
            puts("pointers and arrays are different types:");
            printf("sizeof(int) = %d\n",sizeof(int));
            printf("sizeof(int*) = %d\n",sizeof(int*));
            printf("sizeof(int[3]) = %d\n",sizeof(int[3]));
            /*ERROR: incomplete type*/
            //printf("sizeof(int[]) = %d\n",sizeof(int[]));
        }


        //locations in memory of an array
        {
            int is[3];
            puts("locations of array:");
            printf("(void*)is = %p\n",(void*)is);
            printf("(void*)&is[0] = %p\n",(void*)&is[0]);
            printf("(void*)&is[1] = %p\n",(void*)&is[1]);
            printf("(void*)&is[2] = %p\n",(void*)&is[2]);
        }

        //for combo
        {
            int is[] = {0,1,2};
            int i;
            for(i=0; i<3; i++)
            {
                printf("%d ",is[i]);
            }
        }

        /*
        #bounds breaking

            Time to break down the program by making this access memory
            locations it should not try to access! =)

            The C standard specifies that such actions lead to unspecified behaviour.

            It may lead to Segmentation faults or not.

            Note however that this does not always happen, as a program may
            just access another location inside its legal memory address space
            but in a completelly unpredicatable manner, and the os has no way to it did this

            This leads to very hard to debug errors, but is invitable if you want
            to avoid the overhead of checking arrays bounds on every dereference
        */
        {

            int is[2] = { 0, 1 };
            volatile int j;
            size_t i;

            /*
            GCC 4.7 is smart enough to warn agains this one.
            */
            {
                //j = is[2];
            }

            /*
            GCC 4.7 is not smart enough to warn agains this one!

            May lead to segmentation faults, but this is unlikely.

            Unspecified behaviour.
            */
            if (0) {
                srand(time(NULL));
                i = rand() % 2;
                printf("overflow = %d\n", is[2 + i]);
            }

            //this will amost certainly lead to a segmentation fault
            if (0) {
                for (size_t i = 0; i < SIZE_MAX; i++) {
                    is[i] = 0;
                    //j = is[i];
                }
                assert(is[0] == 0);
            }
        }

        /*
        #memcmp

            Compare arrays like strcmp

            memcmp may be is faster than for loop because the compiler may optimize it better.

            One catch: float NaN.
        */
        {
            int is[]  = { 0, 1, 2 };
            int is2[] = { 0, 1, 2 };

            assert(is != is2);
                //compares addresses, not data!

            assert(memcmp(is, is2, 3 * sizeof(int)) == 0);
            is[1] = 0;
            assert(memcmp(is, is2, 3 * sizeof(int)) < 0);
            is[1] = 2;
            assert(memcmp(is, is2, 3 * sizeof(int)) > 0);

#if __STDC_VERSION__ >= 199901L
            /* memcmp with compound literals. */
            {
                int is[] = { 2, 0, 1 };
                assert(memcmp(is, &(int [3]){ 2, 0, 1 }, 3 * sizeof(int)) == 0);
            }
#endif
        }

        /*
        #memcpy

            Copy one array into another.

            Potentially faster than a for loop like:

                for(i=0; i<3; i++){
                    is2[i] = is[i];
                }

            Since in some architectures this can be implemented with more efficient instructions
            than a naive for, and your compiler may not be smart enough to optimize this if you use a for.
        */
        {
            int is[] = { 0, 1, 2 };
            int is2[3];

            memcpy(is2, is, 3 * sizeof(int));
            assert(memcmp(is, is2, 3 * sizeof(int)) == 0);

#if __STDC_VERSION__ >= 199901L
            //C99 compound literals copy
            {
                memcpy(&is, &(int [5]){ 0, 1, 2 }, sizeof(is));
                assert(memcmp(is, &(int [5]){ 0, 1, 2 }, 3 * sizeof(int)) == 0);
            }
#endif

        }

        /*
        #memset

            Set memory block to a single value.

            Like memcpy, potentially more efficient than a for loop.
        */
        {
            char cs[] = "abcdef";
            memset(cs + 2, '0', 3);
            assert(strcmp(cs, "ab000f") == 0);
        }

        /*
        #multidimentional arrays

            before using this, always consider using single dimentional arrays,
            which are much simpler to handle.

            cases where this would be a better design choice:

            TODO
        */
        {
            int *m1[2];
            int m11[] = { 1, 2, 3    };
            int m12[] = { 4, 5, 6, 7 };
            m1[0] = m11;
            m1[1] = m12;

            //error: cannot know    how much memory to allocate!
                //int m31[][3];

            //error: = {...} works only at declaration
                //int m111[2][3];
                //m111[0] = &(int*[3]){1,2,3};

            int m2[][3] =
            {
                { 1, 2, 3 },
                { 4, 5, 6 }
            };
            //allocates the exact ammount: 2 pointeres to int[3]

            int m3[3][3] =
            {
                { 1, 2, 3 },
                { 4, 5, 6 }
            };
            //allocates 3x3, fills only 2x3. the rest is 0 or m3[0] gets a NULL pointer?

            //error: last must be there
                //int m3[][] =
                //{
                //    { 1, 2, 3    },
                //    { 4, 5, 6, 7 }
                //};
                //
                //reason:
                //    this is array of m[3] arrays!!
                //    the data on an array is sequentially written to RAM
                //    and all of its elements have a fixed size (so they can be indexed!)
                //
                //    if you don't know the sizeof(m[3]), (and you don't know the sizeof(m[]!))
                //    you can't put all those m[3] sequentially on the RAM.
                //
                //    the compiler could look at each element of the initialization
                //    and ensure they all have the *same size*, and then take that size,
                //    but this would take a long time, so it just forces the user to input this

                    {
                        //pass multidimentional arrays to functions
                        puts("\npass multidim to func:");
                        //*never do that*: pass an array, and give m and n
                        //this is just to understand arrays better.
                        enum { mc=2 };
                        int* mat[mc]; //two int pointers
                        int mat1[][3] =
                        {
                            { 1, 2, 3 },
                            { 4, 5, 6 }
                        };
                        int i;
                        for(i = 0; i < mc; i++)
                        {
                            mat[i] = mat1[i]; //first points to the int at address 0 of the matrix mat1
                        }
                        print_array(mat,2,3);
                    }

            //multidimentional > 2

                int m4[][2][3] =
                {
                    { { 1, 2, 3 }, { 4 , 5,  6 } },
                    { { 7, 8, 9 }, { 10, 11, 12} }
                };
                //allocates exact amount for first: 2x2x2

                int m41[3][2][3] =
                {
                    { { 1, 2, 3 }, { 4 , 5,  6 } },
                    { { 7, 8, 9 }, { 10, 11, 12} }
                };
                //allocates one extra for first dimension

                //error: only first can be empty
                    //int m4[][][2] = {
                    //    {{1,2},{3,4}},
                    //    {{5,6},{7,8}}
                    //};

            enum { mc=2, nc=4 };
            int m5[mc][nc];

            //error: TODO ? why
                //int m6[][nc] = {
                //    {1,2,3},
                //    {4,5,6}
                //};

                //int m7[mc][nc] = {
                //    {1,2,3},
                //    {4,5,6}
                //};

            //matrix pattern
            {
                int i, j;
                for(i = 0; i < 2; i++)
                {
                    printf("\n");
                    for(j = 0; j < 3; j++)
                    {
                        printf("%d ", m1[i][j]);
                    }
                }
                printf("\n\n");
            }
        }

        /*
        #string

            by convention, *c strings* are simply char arrays
            terminated by the null character

            this convention is used throughout libc string functions,
            such as `printf`, `strcmp` and others
            so that you don't have to pass an additional size parameter to them
            (those functions stop operating when they see the first null char)

            nothing prevents you from making a "string" that contains a null char,
            except that you will break a very well stabilished convention,
            and libc functions will not work properly with it...

            if you absolutelly need a "string" with a null char, just use regular
            array functions to manipulate it, and pass string lengths around
        */
        {
            {
                char cs[] = "abc";

                //this is exactly equivalent to:

                    //char cs[] = { 'a', 'b', 'c', '\0' }

                //but much harder to write
                //and you may forget the terminating '\0'

                assert(cs[0] == 'a' );
                assert(cs[1] == 'b' );
                assert(cs[2] == 'c' );
                assert(cs[3] == '\0');

                cs[0] = 'A';
                assert(strcmp(cs, "Abc") == 0);

                //ERROR: you cannot assign a tring to memory like this,
                //except at initialization

                    //cs = "Abc";

                //you probably want [strcpy][]
            }

            /*
            #text segment

                c allows you to point directly to the text segment

                in short, the text segment is the part of RAM memory reserved to a process
                that contains the instructions of the process, and not, say, regular variables.

                process are not allows to modify those intructions at runtime,
                and therefore you cannot modify strings that point to the text segment.

                using text segment pointers has the upside of being memory efficient as you
                don't copy the text from

                note however that you cannot modify that string
            */
            {
                //to create a pointer to text segment, initialize it as follows:

                    char* cs = "abc";
                    assert(cs[0] == 'a');

                //segmentation fault: text segment cannot be modified
                {
                    //cs[0] = '0';
                }

                //TODO why can't you do the same thing with integers? ex:
                {
                    //int * is = { 1, 3, 2 };
                }
            }

            //#string literals
            {
                //escape chars in string conts
                {
                    puts("escape chars:");
                    puts(">>>\"<<< double quotes");
                    puts(">>>\\<<< backslash");
                    puts(">>>\n<<< new line");
                    puts(">>>\t<<< tab char");
                    puts(">>>\f<<< feed char");
                    puts(">>>\v<<< vertical tab");
                    puts(">>>\r<<< carriage return");
                    puts(">>>\a<<< alert (your terminal may interpret this as a sound beep or not)");
                    printf(">>>%c<<< null char\n",'\0');
                    puts(">>>\x61<<< a in hexadecimal");
                    puts(">>>\xe4\xb8\xad<<< zhong1, chinese for \"middle\" in utf8");  //chinese utf8
                }

                //string literals may be concatenated
                //no spaces are implied
                {
                    char cs[] = "ab" "cd";
                    assert(strcmp(cs, "abcd") == 0);

                    //this cannot be done with variables,
                    //but can be useful if you have a string that is defined in a macro:
                    {
#define STRING_AB "ab"
                        char cs[] = STRING_AB "cd";
                        assert(strcmp(cs, "abcd") == 0);
                    }

                    //another application is to break a long string literal over severl lines
                    //no newline is implied
                    {
                        char cs[] = "ab"
                                    "cd";
                        assert(strcmp(cs, "abcd") == 0);
                    }

                    // It is not possible to break a string literal on multiple lines.
                    /*
                    {
                        char cs[] = "ab
                                    cd";
                        assert(strcmp(cs, "abcd") == 0);
                    }
                    */
                }
            }

            /*
            #string.h

                String operations.

                Uses '\0' to see ther string ends so callers don't need to give lengths.
            */
            {
                /*
                #sprintf

                    Same as printf, but stores result in a given string.

                    Make sure that the string is large enough to contain the output.

                    If this is a hard and important task, consider `snprintf` + malloc.
                */
                {
                    char cs[] = "123";
                    char cs2[4];
                    sprintf(cs2, "%s", cs);
                    assert(strcmp(cs, cs2) == 0);
                }

#if __STDC_VERSION__ >= 199901L

                /*
                #snprintf

                    Like `sprintf`, but writes at most n bytes, so it is safer,
                    because it may not be possible or easy to calculate the resulting
                    size of a formated string.

                    The size given *includes* the null terminator.

                    C99
                */
                {
                    char cs[] = "123";
                    char cs2[3];
                    snprintf(cs2, 3, "%s", cs);
                    assert(strcmp(cs2, "12") == 0);
                }
#endif

                /*
                #strlen

                    Get string length (up to first '\0').
                */
                {
                    char cs[] = "abc";
                    assert(strlen(cs) == 3);
                }

                /*
                #strcpy

                    Copy one string (up to first '\0') into another location.

                    If they overlap, undefined behaviour.

                    Could be more efficient than a for loop since it could
                    tell the compiler to use a better specialized instruction.
                */
                {
                    char cs[] = "abc";
                    char cs2[4];
                    char cs3[1];

                    strcpy(cs2, cs);
                    strcpy(cs2, "abc");

                    //BAD: no born checking as always

                        //strcpy(cs3, "abc");
                }

                /*
                #strncpy

                    strcpy with maximum chars to copy.
                */

                /*
                #strcmp

                    Compare two strings
                */
                {
                    char cs[] = "abc";
                    char cs2[] = "abc";

                    assert(strcmp(cs, cs2) == 0);
                    assert(strcmp(cs, "abc") == 0);
                        //equality
                    cs[1] = 'a';
                    assert(strcmp(cs, cs2) < 0);
                        //smaller
                    cs[1] = 'd';
                    assert(strcmp(cs, cs2) > 0);
                        //larget
                }

                /*
                #strcat

                    Concatenate two strings.
                */
                {

                    char s1[5];
                    strcpy(s1, "ab");
                    char s2[] = "cd";
                    strcat(s1, s2);
                    assert(strcmp(s1, "abcd") == 0);
                    assert(strcmp(s2, "cd"  ) == 0);
                }

                /*
                #strchr

                    Search for char in string.

                    Return pointer to that char if found.

                    Return null if not found.
                */
                {
                    {
                        char cs[] = "abcb";
                        assert(strchr(cs, 'b') == cs + 1);
                        assert(strchr(cs, 'd') == NULL);
                    }

                    /*
                    find all occurences of c in cs

                    no direct libc function for this
                    */
                    {
                        char cs[] = "abcb";
                        char* cp;
                        char c = 'b';
                        int is[] = { 1, 3 };

                        int i = 0;
                        cp = strchr(cs, c);
                        while(cp != NULL)
                        {
                            assert(cp - cs == is[i]);
                            cp = strchr(cp + 1, c);
                            ++i;
                        }
                    }
                }


                /*
                #split

                    See strtok

                #strtok

                    split string at a given character sequence.

                    <http://en.cppreference.com/w/c/string/byte/strtok>
                */

                /*
                #ctype.h

                    character classficiation functions
                */
                {
                    //#isspace
                    {
                        assert( isspace(' ' ));
                        assert( isspace('\n'));
                        assert(! isspace('a' ));
                    }

                    //#isdigit
                    {
                        assert( isdigit('0'));
                        assert(! isdigit('a'));
                    }
                }

                /*
                #strerror

                    returns a readonly pointer to the description of the error with the given number:

                        char *strerror(int errnum);

                    Also consider perror if you want to print those error messages to stderr.
                */
                {
                    printf("strerror(EDOM) = \"%s\"\n", strerror(EDOM));
                }
            }

            /*
            #unicode

                Use wchar.

            #wchar
            */
            {
                char cs[] = "汉语";
                printf("%s\n",cs);

                //cs[0] = 'a';
                //printf("%s\n",cs);
                    //BAD
                    //only changes first byte
                    //you get trash all over

                //WARN

                    //cs[0] = '英';

                //you *need* setlocale to print correctly:

                    setlocale(LC_CTYPE, "");

                wchar_t  wcs[] = L"汉语";

                printf("%ls\n", wcs);

                wcs[0] = L'英';
                printf("%ls\n", wcs);

                wcs[0] = L'a';
                printf("%ls\n", wcs);

                //ERROR: non wide init

                    //wchar_t  wideString2[] = "asdf";
            }

            /*
            #strcoll
            */
            {
                //TODO0 example
            }

            /*
            #strcspn

                How many characters in s1 are there before the first character present in s2.
            */
            {
                assert(strcspn("ab01", "10") == 2);
                assert(strcspn("a0b1", "10") == 1);
            }

            /*
            #strpbrk

                Point to the first character in s1 that is in s2.
            */
            {
                char *s1 = "ab01";
                assert(strpbrk(s1, "10") - s1 == 2);
            }
        }
    }

    //#branching
    {
        //#if
        {
            // Only 0 counts as false.
            if (0) {
                assert(0);
            }

            if (1){
                assert(1);
            }

            if (-1) {
            } else {
                assert(0);
            }

            if (-1) {
            } else if (0) {
                assert(0);
            } else {
                assert(0);
            }

            //can ommit braces for single statements
            {
                {
                    if (0) assert(0);
                    if (0)
                        assert(0);
                    if (0) { assert(0); }
                }

                {
                    if (0)
                        assert(0);
                    else
                        assert(1);
                }

                //possible but very ugly to use only one pair of braces
                {
                    if (0) {
                        assert(0);
                    } else
                        assert(1);

                    if (0)
                        assert(0);
                    else {
                        assert(1);
                    }
                }
            }

            //scope
            {
                int i = 0;
                if (1) {
                    int i = 1;
                    assert(i == 1);
                }
            }
        }

        /*
        #stdbool.h

            defines bool, true and false

            c99
        */
        {

            bool b = true;
            bool b2 = false;
            assert(true  == 1);
            assert(false == 0);
        }

        /*
        #switch

            Why does this exists (could be done with if):

            - readability
            - not repeating the deciding variable / expression many times
            - TODO is there no compilation preformance gain via special assembly instructions?).

        #case

            See switch.
        */
        {
            int i, j;
            for(i = -1; i < 6; i++)
            {
                switch (i)
                {
                    case 0:

                        assert(i == 0);

                        int j;
                            //OK
                            //new inner scope

                        //int i = 1;
                            //ERROR
                            //redeclaration

                    break;

                    case 1:

                        assert(i == 1);

                        //int j;
                            //ERROR
                            //single inner scope

                    break;

                    case 2:
                    case 3:

                        //same action for multiple cases

                        assert(i == 2 || i == 3);

                    break;

                    //Google C++ style recommends the following style.
                    case 4: {
                        assert(i == 4);
                        break;
                    }
                    case 5: {
                        assert(i == 5);
                        break;
                    }

                    default:
                        assert(i != 0 && i != 1);
                    break;
                }
            }

            /*
            - case statements are just like GOTO labels
            - break is like a jump
            - each case does not need a corresponding break
            - and switch statements can contain any other construct like `if` or `while`
                even outside of a case break pair.

            The major application of this is to impress your friends
            with your mastery of C obscurantism.

            However there is a classic optimization trick that relies on that:
            <http://en.wikipedia.org/wiki/Duff%27s_device>

            #duffs device
            */
            {
                int i = 0;
                switch (2) {
                    while (i < 2) {
                    label_switch_in_while:
                    case 0:
                        i++;
                    }
                    case 1:
                        i++;
                        break;
                    case 2:
                        goto label_switch_in_while;
                }
                printf("%d\n", i);
                assert(i == 3);
            }
        }

        /*
        #for vs while

            In theory, whatever you can to with for you can do with while.

            However x86 has a loop instruction that increments and
            contional jumps in a single step.

            Therefore, using a simple for is a better hinto to your
            compiler to use this more efficient looping instruction.

            Moral: if you when know how many loops you will do, use `for`,
            otherwise use `while`.

            Using for also serves as self documentation telling readers that you know
            beforehand how many times the loop will execute.
        */

        //#for
        {
            //basic example
            {

                int i;
                int is[] = { 0, 1, 2 };
                for (i = 0; i < 3; ++i) {
                    assert(i == is[i]);
                    int i;
                        //OK new scope
                }
                assert(i == 3);
            }

            //single line
            {
                int i;
                int is[] = { 0, 1, 2 };
                for (i = 0; i < 3; ++i)
                    assert(i == is[i]);
                    //int i;
                        //ERROR
                        //redeclaration
                        //note different if bracketes used
            }

#if __STDC_VERSION__ >= 199901L
            // Putting `int i = 0` inside for is only possible in C99.
            {
                int is[] = {0, 1, 2};
                for (int i = 0; i < 3; ++i) {
                    assert(i == is[i]);
                    //int i;
                        //ERROR
                        //redeclaration
                }
            }
#endif

            // Multiple loop variables: one of the few uses of the comma operator
            {
                int is[] = {0, 1, 2};
                int js[] = {0, 1, 2};
                for (int i = 0, j = 0; i * j < 5; i++, j++) {
                    assert(i == is[i]);
                    assert(i == js[i]);
                }
            }

            // Nested loops
            {
                int n = 0;
                int is[] = {0, 0, 1, 1};
                int js[] = {0, 1, 0, 1};
                for (int i = 0; i < 2; i++) {
                    for (int j = 0; j < 2; j++) {
                        assert(i == is[n]);
                        assert(j == js[n]);
                        n++;
                    }
                }
            }

            // Different loop step.
            {
                int n = 5;
                int step = 2;
                int is[] = {0, 1, 2, 3, 4};
                int js[] = {0, 2, 4};
                int js2[] = {1, 3};
                int j = 0;
                for (int i = 0; i < n; i += step) {
                    assert(js[j] == is[i]);
                    if (i < n - step + 1)
                        assert(js2[j] == is[i + 1]);
                    j++;
                }
            }

            // Backward loops.
            {
                int n = 3;
                int is[] = { 0, 1, 2 };
                int js[] = { 2, 1, 0 };
                int j = 0;
                for (int i = n - 1; i >= 0; --i) {
                    assert(is[i] == js[j]);
                    j++;
                }

                /*
                #backward loops with unsined loop variables

                    Here things get messy: <http://stackoverflow.com/questions/665745/whats-the-best-way-to-do-a-reverse-for-loop-with-an-unsigned-index>

                    It becomes clear why the google c++ style recommends not to use unsigned,
                    but how can that be avoided for example for `size_t`?
                */
                {
                    // Infinite loop, since `i >= 0` always holds!
                    /*
                    {
                        int n = 3;
                        int is[] = { 0, 1, 2 };
                        int js[] = { 2, 1, 0 };
                        int j = 0;
                        for (unsigned int i = n - 1; i >= 0; --i) {
                            assert(is[i] == js[j]);
                            j++;
                        }
                    }
                    */

                    // Two variables solution.
                    // Downside: one more variable, one extra operation per loop.
                    // Upside: very clear.
                    {
                        unsigned int n = 3;
                        int is[] = { 0, 1, 2 };
                        for (unsigned int i_fake = n; i_fake > 0; --i_fake) {
                            unsigned int i = i_fake - 1;
                            assert(is[i] == i);
                        }
                    }

                    // Module madness solution.
                    //
                    // Downside: mind twisting.
                    // Upside: efficient: no extra var or operation.
                    {
                        unsigned int n = 3;
                        int is[] = { 0, 1, 2 };
                        for (unsigned int i = n - 1; i < n; --i) {
                            assert(i == is[i]);
                        }
                    }

                    // Post increment solution.
                    //
                    // Mnemonic: the goes to operator `-->`
                    //
                    // Downside: only works for step of 1.
                    // Upside: efficient: no extra var or operation.
                    {
                        unsigned int n = 3;
                        int is[] = { 0, 1, 2 };
                        for (unsigned int i = n - 1; i-- > 0;) {
                            assert(i == is[i]);
                        }
                    }
                }
            }
        }

        //#while
        {
            {
                int i = 0;
                int is[] = { 0, 1, 2 };
                while (i < 3) {
                    assert(i == is[i]);
                    i++;
                }
                assert(i == 3);
            }

            //#do-while
            {
                int i = 0;
                int i2;
                int is[] = { 0, 1, 2 };
                do
                {
                    i2 = 2*i*i + 3*i + (i % 2);
                    assert(i == is[i]);
                    i++;
                } while (i2 < 7);
                    //don't forget the ';' !

                //application:

                    //loop must execute at least once
                    //to know if it will continue

                    //without do-while, you would have to either:

                        //write:
                        //`int i2 = 2*i*i + 3*i + (i % 2);`
                        //so you have to type this huge expression twice!
                        //so if you change one you have to change the other
                        //and you risk to forget creating a hard to find bug

                        //write a function that does 2*i*i + 3*i + (i % 2);
                        //this function is almost useless (used only twice)
                        //adding needless boilerplate to your code

                    //both of which are not very attractive alternatives
            }
        }

        /*
        #function

            A function is basically a branch, but in which you have to:

            - know where to jump back to after return
            - pass arguments
            - get back a return value
        */
        {
            {
                func_int(1.1);
                func_float(1);
            }

            //return value is not an lval, so one cannot get its address
            {
                int *ip;
                //ip = &int_func_int(1);
                    //ERROR
            }

            /*
            pass string literals to functions

                The following works.

                It initializes the string on stack and then passes a pointer to it.

                String literals should only be passed to `const char *` arguments,
                since string literals cannot be modified, possibly leading to segfaults.

                Ideally, all calling functions that can receive such strings should be const.

                This is not however enforced by the compiler.
            */
            {
                func_string_abc("abc");
                func_string_const_abc("abc");

                //func_string_modify("abc");
            }

            //two decls on the same line
            {
                assert(decl_1() == 1);
                assert(decl_2() == 2);
            }

#if __STDC_VERSION__ >= 199901L

            /*
            Pass struct and array literals to function
            using C99 compound literals.

            Unlike string literals, array and struct literals can be modified on the function.
            */
            {
                func_array((int[]){ 1 });

                func_array_modify((int[]){ 1 });

                int is[] = { 1 };
                func_array_modify(is);
                assert(is[0] == -1);

                func_struct_1((struct func_struct){ .i = 1 });
            }
#endif

            /*
            #return struct from function.

                Behaviour defined by the standards.

                assembly implementation is not specified by ANSI C, but common techiques used in cdecl like conventions:

                - put struct into several registers

                - automatically add a hidden argument to functions that return structs,
                    allocated data on caller and pass a pointer to the struct,
                    and let the callee modify that pointer to return it.

                Ex: definition

                    struct struct_func_struct struct_func()
                    {
                        struct struct_func_struct s = { 0, 1 };
                        return s;
                    }

                gets converted to:

                    void struct_func(struct struct_func_struct* sp)
                    {
                        struct struct_func_struct s = { 0, 1 };
                        *sp = s;
                    }

                And calls:

                    s = struct_func();

                Get converted to:

                    struct struct_func_struct temp;
                    struct_func(&temp);
                    s = temp;

                or simply:

                    struct_func(&s);

                In C it is not possible to detect which convertion was made by the compiler.

                In C++ however, constructors and destructors allow to differenciate between the two above cases,
                and RVO specifies that both are valid options that the compiler may take, and that the actual
                results are unpredictable.
            */
            {
                struct struct_func_struct s;
                s = struct_func();
                assert(s.i == 0);
                assert(s.j == 1);
            }

            /*
            #declaration vs definition

                Declaration can be done inside other functions.

                Definitions not.

                Functions definition inside functions (known as local functions to gcc)
                exist only as extensions in certain compilers such as gcc if ANSI is not enforced.
            */
            {
                void func();

                //void func(){}
                    //ERROR
                    //no definition inside another function

                decl_and_int = 0;
                assert(decl_and_int_func() == 0);
            }

            /*
            #K&R function declaration

                This form of funciton declaration, while standard,
                is almost completely obsolete and forgotten today.

                It is however still ANSI C.

                There seems to be only one case in which it may allow for something
                that ANSI C declarations don't: <http://locklessinc.com/articles/obscurec/>
            */
            {
                char c = 0;
                assert(k_and_r(1, &c) == 0);
            }

            /*
            #function pointers

                Functions can be stored in pointers and used through them.

                This is spcially useful to many related lots of functions inside a single
                struct to achieve a similar effect to that found on object oriented programming.
            */
            {
                /*
                Basic usage.

                Declare a function pointer named `f` that points to functions that take 2 ints
                and return one int.
                */
                {
                    int (*f)(int n, int m);
                    f = add_int;
                    assert((*f)(1, 2) == 3);
                    f = sub_int;
                    assert((*f)(1, 2) == -1);
                }

                assert(add_int != sub_int);

                // Function pointers can also be passed to functions of course.
                {
                    assert(int_func_func_int_int(add_int, 2, 1) == 3);
                    assert(int_func_func_int_int(sub_int, 2, 1) == 1);
                }

                // Array of function pointers.
                //
                // The array indication goes after the name of the array!
                {
                    int (*fs[])(int n, int m) = {add_int, sub_int};
                    assert((*fs[0])(1, 2) == 3);
                    assert((*fs[1])(1, 2) == -1);
                }

                /*
                There are multiple ways to initialize and use function pointers because of implicit conversions.

                <http://stackoverflow.com/questions/6893285/why-do-all-these-crazy-function-pointer-definitions-all-work-what-is-really-goi>
                */
                {
                    // Alternative initialization methods.
                    int (*fs[])(int n, int m) = {
                        &add_int,
                        add_int,
                        *add_int,
                        **********************add_int,
                    };

                    // Alternative call methods.
                    for (int i = 0; i < 4; i++) {
                        assert((    fs[i])(1, 2) == 3);
                        assert((   *fs[i])(1, 2) == 3);
                        assert((******fs[i])(1, 2) == 3);
                        //assert((&fs[i])(1, 2) == 3);
                    }

                    // ERROR no alternative for the declaration.
                    {
                        //int (f)(int n, int m) = add_int;
                    }
                }
            }

            /*
            #variadic function

                Takes a variable number of arguments.

                Used for example on `printf`.

                Possible to implement efficiently because of C 's calling convention.
            */
            {
                assert(variadic_add(3, 1, 2, 3)       == 6);
                assert(variadic_add(5, 1, 2, 3, 4, 5) == 15);

                char s[32];
                sprintf_wrapper(s, "%c", 'a');
                assert(s[0] == 'a');

                /*
                The only problem with the wrapper is that compile time error checking is not done.

                This could be achieved via the gcc `__attribute__((format,X,Y))` extension
                */
                {
                    //error checking is not done for the wrapper
                    //might segfault at runtime
                    if (0) {
                        sprintf_wrapper(s, "%s" /*missing arg*/);
                        printf("sprintf_wrapper wrong = %s\n", s);
                    }

                    //sprintf(s, "wrong %s");
                        //WARN
                        //type error checking is done for sprintf
                }
            }

#if __STDC_VERSION__ >= 199901L

            /*
            #restrict keyword

                C99

                Says to the compiler that every pointers passed to a function that is marked restrictd
                does not refer to the same element.

                Can only qualify pointers. The most common use case is to qualify pointers passed to functions.

                Programmers must ensure that temselves. if they don't, undefined behaviour.

                No behaviour change, but allows for further compiler optimization,
                so it should be used whenever possible. See generated assembly to spot the difference.

                Great example showing how restrict could help optimize things: <http://en.wikipedia.org/wiki/Restrict>
            */
            {
                {
                    int i = 0;
                    int j = 0;
                    int add = 1;
                    double_add(&i, &j, &add);
                    assert(i == 1);
                    assert(j == 1);
                }

                {
                    int i = 0;
                    int j = 0;
                    int add = 1;
                    restrict_double_add(&i, &j, &add);
                    assert(i == 1);
                    assert(j == 1);
                }

                /*
                BAD: undefined behaviour, because the same pointer is passed twice

                The compiler should be able to spot that one... but gcc 4.7 did not.
                */
                {
                    int i = 1;
                    int j = 1;
                    restrict_double_add(&i, &j, &i);
                    if (i != 2)
                        printf("restrict i = %d\n", i);
                    if (j != 3)
                        printf("restrict j = %d\n", j);
                }

                //OK not restrict
                {
                    int i = 1;
                    int j = 1;
                    double_add(&i, &j, &i);
                    assert(i == 2);
                    assert(j == 3);
                }

                //outside functions
                //TODO what does it mean then? On the current
                {
                    int i;
                    int * restrict ip;
                }

                //int restrict ip;
                    //ERROR: can only qualify pointers
            }

#endif
        }

        /*
        #goto

            One of the most basic loops: tranlates to `jmp` in x86.

            However, avoid using this as it may generate unreadable code.

            One of the few generally accepted use cases is error handling inside a large function,
            where if a test fails, jump to the end of the function which deals with each type of error.
        */
        {
            goto a;
                assert(0);
            a:
                assert(1);

            /*
            goto cannot cross functions.

            Use `setjmp` for that.
            */
            {
                int i;
                goto_func_after:
                    i = 1;
                /*goto in_func_label;*/
            }

            /* Labels cannot be at the end of compound statments */
            {
                { /*label_end_compound:*/ }
                { label_end_compound: 1; }
            }

            // Labels and loops
            {
                int i;
                for ( /*label_in_for:*/ i = 0; i < 2; i++)
                label_after_if:
                {
                    label_after_if2: 1;
                }
            }

            // Labels and switch.
            {
                int a = 1;
                switch (a) {
                    case 0:
                    label_case_0:
                        assert(a == 1);
                    break;
                    case 1:
                        goto label_case_0;
                    break;
                }
            }
        }

        /*
        #setjmp.h

            Jumps without scope restrictions of goto labels.

            #setjmp

                Saves register states, including instruction and pointer registers.

                Return value:

                - 0 if did not return from longjmp
                - != 0 if just returned from a lonjmp

                Application: error handling a la exception. Return val encodes the exception type.

            #longjmp

                Restores register states.

            #longjmp and signals

                If you longjmp from a signal handler you can recatch the signal afterwards.
        */
        {
            jmp_buf env_buffer;
            int val;

            val = setjmp(env_buffer);
            printf("setjmp = %i\n", val);
            if (val != 0) {
                //returned from longjmp
                //val encodes the error code
            } else {

                //this is evaulated normally
                assert(setjmp_func(false, env_buffer) == 1);

                //this assert is never evaluated
                assert(setjmp_func(true, env_buffer) * 0 == 1);
            }
        }
    }

    //#command line args
    {
        printf("argv[0] = %s\n", argv[0]);
        int i = 0;
        if (argc > i) {
            i++;
            printf("argv[%d] = %s\n", i, argv[0]);
        }
        if (argc > i) {
            i++;
            printf("argv[%d] = %s\n", i, argv[0]);
        }
    }

    /*
    #environment variables

        #getenv

            Returns NULL if not found.

        TODO: setenv in POSIX but not in ANSI C?
    */
    {
        printf("getenv\n");
        printf("  HOME = %s\n", getenv("HOME"));
        printf("  USERPROFILE = %s\n", getenv("USERPROFILE"));
    }

    //#preprocessor
    {
        /*
        ##define

            You can put preprocessor directives anywhere
            but putting on global scope is the more standard and simple approach

            Use defines with discretion: they make it much harder to debug!
        */
        {
            //constants
            {
#define A B
#define B 1
                assert(A == 1);
            }

            //cannot redefine macros
            {
//#define A 1
//#define A 2
                //assert(A == 2);
            }

            //functions
            {
                {
#define SUM(x, y) x + y

                /*
                generates:

                    assert(1 + 1 == 2);

                not:

                    assert(2 == 2);
                */
                assert(SUM(1, 1) == 2);
                }

                //no overloading
                {
//#define SUM(x) x + 1
                //assert(SUM(1) == 2);
                }

                /*
                #macro comma protection

                    The macro engine has to do some kind of parsing to determine that
                    the comma of the function (1) is not the comma of the macro (2).

                    What it seems to do is simply check if the comma is between pairs of:

                    - parenthesis
                    - double quotes

                    and if yes ignore it.

                    This does not however cover C++ template parameters, and `assert` + template is a common break case
                    <http://stackoverflow.com/questions/4496842/pass-method-with-template-arguments-to-a-macro>

                    Pure C also has cases in which it is necessary to use parenthesis, for exapmle when the comma operator is used.

                    A more complicated case in which protecting parenthesis break:
                    <http://stackoverflow.com/questions/9187614/how-do-i-have-a-comma-inside-braces-inside-a-macro-argument-when-parentheses-cau>
                */
                {
                    assert(SUM(int_int_int_func(1, 1), 1) == 3);
                    //                              ^    ^
                    //                              1    2

                    int i = 1;
                    assert(SUM((i++, i), 1) == 3);
                    //               ^
                    //               comma operator

                    //assert(SUM(i++, i, 1) == 3);
                        //ERROR
                        //must protect the comma operator

#define CAT(x, y) x y
                    assert(strcmp(CAT("1,", "2"), "1,2") == 0);
                    //                     ^ ^
                    //                     1 2
                }

                assert(SUM(int_int_int_func(1, 1), 1) == 3);

#if __STDC_VERSION__ >= 199901L

                //#variadic macro functions
                {
                    char s[4];
#define SPRINTF(string, format, ...) sprintf(string, format, __VA_ARGS__)
                    SPRINTF(s, "%c%c", 'a', 'b');
                    assert(strcmp(s, "ab") == 0);
                }

#endif
            }

            /*
            ##include

                It is possible, and very confusing, to include any type of file,
                not just header files.
            */
            {
                int i = 0;
#include "i_plus_one"
                assert(i == 1);
            }
        }

        /*
        #double hash

        ###

            `##` allows to concatenate two preprocessor function arguments without spaces between them.
        */
        {
            //basic
            {
#define CAT_NO_SPACE(x, y) x ## y
                int CAT_NO_SPACE(c_, d) = 1;
                assert(c_d == 1);
            }

            //preprocessor variable gotcha: <http://stackoverflow.com/questions/1489932/c-preprocessor-and-concatenation>
            {
                {
#define VAR 3
#define CAT_VAR_FAIL(x) x ## _ ## VAR
                    int CAT_VAR_FAIL(b) = 1;
                    assert(b_VAR == 1);
                }

                //solution
                {
#define VAR 3
#define PASTER(x,y) x ## _ ## y
#define EVALUATOR(x,y)  PASTER(x,y)
#define CAT_VAR(x) EVALUATOR(x, VAR)
                    int CAT_VAR(b) = 1;
                    assert(b_3 == 1);
                }
            }
        }

        //##ifdef
        {
#ifdef COMMANDLINE
            //gcc -DCOMMANDLINE c.c
            puts("C");
#else
            //gcc c.c
            puts("no C");
#endif
        }

	/*
        ##if

	    The preprocessor can do certain integer arithmetic operations such as:
	    +, -, ==, <.
        */
	{
#define INIF 1
#if INIF + 1 == 2
#else
            assert(false);
#endif

#if 16 == 0x10
#else
            assert(false);
#endif
	}

        //#&&
#define C 1
#if defined(C) && C > 0
#else
    assert(false);
#endif

        /*
        ##error

            Print an error message to stderr and stop compilation.

            Useful to enforce preprocessor conditions.
        */
        {
//#error "the error message"
        }

        /*
        #null directive

            A `#` followed by newline is ignored.
        */
        {
#
        }

        /*
        #pragma

            C99 specifies that:

                #pragma X Y Z ...

            - if `X != STDC`, does something implementation defined, and therefore not portable.

                Examples: `#pragma once`

            - else, then the statement must take a form:

                    #pragma STDC FP_CONTRACT on-off-switch
                    #pragma STDC FENV_ACCESS on-off-switch
                    #pragma STDC CX_LIMITED_RANGE on-off-switch

                all of which are portable.
        */

        /*
        #standard preprocessor defines

            some preprocessor vars are automatically defined by certain compilers
            although they are not c standards. Those are not discussed here.

            List of standard defines: <http://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html>
        */
        {
            /*
            #__stdc_version__

                String representing version of the c std lib. Format: yyyymm (base 10).

                Some values:

                - C11: 201112L
                - C99: 199901L
            */
            {
                printf("__STDC_VERSION__ = %li\n", __STDC_VERSION__);
            }

            /*
            #__cplusplus

                Defined only if using C++ compiler.
            */
#ifdef __cplusplus
            printf("__cplusplus\n");
#endif

                //absolute or relative path of current file:

            printf("__FILE__ = %s\n", __FILE__);

            /*
            #LINE

                Current source code line.

                Useful for debugging.

                If in a `.h`, position inside the `.h` before inclusion.
            */
            {
                printf("__LINE__ = %d\n", __LINE__);
            }

            /*
            # __func__

                if inside a function, the name of that function.

                this is not a normal macro, since the preprocessor cannot know
                the current function name, because the preprocessor does not parse

                c99
            */
            {
                printf("__func__ = %s\n", __func__);
            }

            printf("__DATE__ = %s\n", __DATE__);

            printf("__TIME__ = %s\n", __TIME__);

        //automatically defined by certain compilers on windows:
        //TODO0 gcc specific or not? if yes move out of here.

#ifdef __WIN32__
            puts("__WIN32__");
#endif

        //TODO0 what is this
        //TODO0 gcc specific or not? if yes move out of here.

#ifdef _LIBC
        puts("_LIBC");
#endif

    //TODO0 what is this
    //TODO0 gcc specific or not? if yes move out of here.

#ifdef __ILP32__
        puts("__ILP32__");
#endif

    //TODO0 what is this
    //TODO0 gcc specific or not? if yes move out of here.

#ifdef ___X32_SYSCALL_BIT
        puts("___X32_SYSCALL_BIT");
#endif

        }
    }

    /*
    #trigraphs

        Absolutelly obscure feature for very old systems which do not support certain
        characters or because of keyboards which don't support them easily

        It is so obscure that gcc even emmits a warning if you use those!!

        Is the first substitution made to source, even before the preprocessor.

        They are commented out here so that compilers like
        gcc won't annoy us with warnings.
    */
    {
            //assert('??=' == '#');
            //assert('??(' == '[');
            //assert('??/' == '\');   //TODO0 literal backslash?
            //assert('??)' == ']');
            //assert('??'' == '^');
            //assert('??<' == '{');
            //assert('??!' == '|');
            //assert('??>' == '}');
            //assert('??-' == '~');

        //TODO0 how to escape a trigraph on a string literal, say: `??=` ?
        //is it necessary to use `\x`?

            //printf("??")
    }

    /*
    #dynamic allocation

        Allocates ammounts of memory that are only known at runtime,
        not compile time.

        #malloc

            The main way to get new dynamic memory.

            Returns a `void*` which can be used for any type.

            Typecast from `void*` is implicitly done without warning.


        #dynamic allocation vs VLA

            Dynamic memory has the following characteristics which VLA does not:

            - no scope

                therefore can be allocated in functions
                and returned to caller

            - heap much larger than stack

            So it is more flexible, at the cost of some runtime speed.
    */
    {
        /* basic usage */
        {
            size_t bytes = sizeof(int) * 2;
            int* is = malloc(bytes);
            if (is == NULL) {
                printf("malloc failed\n");
            } else {
                is[0] = 1;
                assert(is[0] == 1);
                free(is);
            }
        }

        /*
        #free

            Main way to free dynamic memory after you are done with it.

            Freeing a NULL pointer does nothing:
            <http://stackoverflow.com/questions/1938735/does-freeptr-where-ptr-is-null-corrupt-memory>
        */
        {
            free(NULL);

            /*
            WARN attempted to free a non heap object.

            If this compiled, it could lead to segfault.
            */
            {
                int i;
                //free(&i);
            }

            /* freeing a pointer twice leads to a segfault */
            {
                int *ip = malloc(sizeof(int));
                free(ip);
                //free(ip);
                    //RUNTIME ERROR
                    //segmentation fault
            }
        }

        /*
        #realloc

            Change size of allocated memory with malloc.

            If you already have allocated some memory, it might be faster to enlargen it
            rather than to free it and reallocate.

            The library may however choose to move your memory somewhere else if not enough is available

            You must use a second pointer to get its value, because in case the reallocation fails,
            you still need the old pointer to clear up old memory.
        */
        {
            size_t bytes = sizeof(int) * 2;
            int* is = malloc(bytes);
            if (is == NULL) {
                printf("malloc failed\n");
            } else {
                is[1] = 1;
                //you must use a second pointer here
                int* is2 = realloc(is, sizeof(int) * 4);
                if (is2 == NULL) {
                    printf("realloc failed\n");
                } else {
                    is = is2;
                    is[3] = 1;
                    //old values are untouched:
                    assert(is[1] == 1);
                    assert(is[3] == 1);
                }
                free(is);
            }
        }

        /*
        #calloc

            Like malloc but initializes allocated bytes to zero.

            why calloc? <http://www.quora.com/C-programming-language/What-does-the-c-stand-for-in-calloc>
            Clear seems most likely.

            Takes number of elements and elemetn size separately.
        */
        {
            int* is = calloc(2, sizeof(int));
            if (is == NULL) {
                printf("calloc failed\n");
            } else {
                assert(is[0] == 0);
                assert(is[1] == 0);
                free(is);
            }
        }

        /*
        malloc multi dimensional arrays

            For a 2D N x M array, there are two solutions:

            - N mallocs of size M
            - one malloc of size N x M

            <http://stackoverflow.com/questions/1970698/c-malloc-for-two-dimensional-array>

            In C++, using vectors of vectors is an easier solution.
        */
        {
            // One malloc.
            {
            }
        }

        /*
        #allocate too much memory

            if you try to allocate too much memory,
            `malloc` may fail, or your os will eventually decide to kill your naughty program

            time to try that out!

            TODO0 how to pass more than INT_MAX to malloc to break it? =)
        */
        {
            if (0) {
                size_t n = 1024 * 1024 * 1024;
                int* ip = malloc(n);
                if (ip == NULL) {
                    printf("could not allocate %zu bytes", n);
                }
                free(ip);
            }

            /*
            allocate 1024 Petabytes of RAM in 1 gb chunks!!!
            someday this will be possible and people will laugh at this...
            generates a segfault
            */
            if (0) {
                const size_t GB = 1024 * 1024 * 1024;
                for (int i = 0; i < GB; i++) {
                    int* ip = malloc(GB);
                    ip[0] = 0;
                    if (ip == NULL) {
                        printf("could not allocate %zu bytes", GB);
                    }
                }
            }
        }
    }

    /*
    #assert.h

        Defines the assert *macro*, which exits 1 and prints out the expression that caused the error.

    #NDEBUG

        If defined *before assert.h* is included, asserts do nothing.
    */
    {
        //assert(1 + 1 == 2);
    }

    /*
    #errno.h

        Used for error handling.

        Defines `errno`, which can be set by user or library functions to indicate the error type.

        It is commonly used in operations such as file IO.

        Also define a few possible values which libc may set `errno` to:

        - EDOM. Domain error. Generated for example on `sqrt(-1.0)` of `math.h`.
        - EILSEQ
        - ERANGE

        *Many* more such errors are defined for example by POSIX.

        Each error has an error message string associated to it.
        To get that error message, consider using `strerror`.
        To print an error message to stderr, consider using `perror`.
    */
    {
        errno = 0;      //no error
        errno = EDOM;   //EDOM error
    }

    /*
    #stdlib.h
    */
    {
        /*
        #system

            executes command in a shell and waits for it to end before continuing current program

            the shell is implementation dependant

            - linux: `/bin/sh`

            so in the end what you write with this is not very portable

            return value is also implementation dependant but is often the command exit status
            or an error reserved value
        */
        {
            //linux test:

                //int r = system("echo a | grep b");
                //assert(r == 1);
        }
    }

    /*
    #stdio.h

        stream Input and Output
    */
    {
        /*
        #stream

            An stream is an abstraction over different input/output methods
            such as regular files, stdin/stdout/stderr (pipes in linux), etc.
            so that all of them can be treated on an uniform basis once you opened the stream.

            Most functions have a form which outputs only to stdout,
            and most input functions have a form which reads only from sdtin
            coupled with a general form that outputs to any stream.

            Unfortunatelly, sometimes there are subtle differences between those two
            forms, so beawere!

        #FILE

            FILE is a macro that represents a stream object

            Its name is FILE of course because files are one of the main types of streams.

            However, streams can represent other resources in the filesystem in general
            such as Linux FIFOs or sockets.

        #stream vs file descriptors

            A file descriptor is a POSIX concept and thus shall not be discussed here.
        */

        /*
        #BUFSIZ

        TODO
        */
        {
            printf("BUFSIZ = %ju\n", (uintmax_t)BUFSIZ);
            assert(BUFSIZ >= 256);
        }

        /*
        #EOF

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
        #stderr

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
        #stdout

            Sames as stderr but for stdout.

            Less useful than `stderr` since most IO functions have a convenience form that writes to stdout.
        */
        {
            fputs("stdout\n", stdout);
        }

        /*
        #stdin

            be careful!! stdin won't return EOF automatically

            for a tty you can tell the user to input a EOF (ctrl d in linux, ctrl z in windows)
            but as you see this is system dependent. for pipes I am yet to find how to do this,
            might be automatic when process closes only.

            the best way to know that a stdin ended is recognizing some specific
            pattern of the input, such as a newline with fgets, or the end of a
            number with scanf

            before this comes, the program just stops waiting for the stdin to
            produce this, either from user keyboard input, or from the program
            behind the pipe.
        */

        //#stream output
        {
            /*
            #putchar

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
            #putc

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
            #puts

                Write to stdout.

                Newline appended at end.
            */
            {
                puts("puts");
            }

            /*
            #fputs

                Write to any stream.

                Unlike puts, *no* newline is automatically appended at end!

                Very confusing.
            */
            {
                fputs("fputs\n", stdout);
            }

            /*
            #printf

                Write formated string to sdtout.

                Does not automaticaly append newlines.

                It is very useful to learn the format strings,
                since this has become a de facto standard and is also used
                for example in python format strings and bash `printf` command.

                html readable documentation on the c++11 printf format strings <http://www.cplusplus.com/reference/clibrary/cstdio/printf/>
                should be close to the latest C, and backwards compatible

                Since the formatting behaviour is identical to that of sprintf,
                sprintf tests may be used here if the output is predictable so that output can be asserted.
            */
            {
                char s[256];

                //typecasts in printf
                {
                    // In most cases, gcc 4.8 can emmit warning for wrong types.

                    // TODO what happens when a wrong type is passed? Typecast? Undefined?

                        printf("u UINT_MAX = %u\n", UINT_MAX);

                        sprintf(s, "%d", UINT_MAX);
                        assert(strcmp(s, "-1") == 0);
                }

                //char:

                    sprintf(s, "%c", 'a');
                    assert(strcmp(s, "a") == 0);

                //int:

                    printf("d INT_MAX = %d\n", INT_MAX);

                //long int:

                    printf("d LONG_MAX = %ld\n", LONG_MAX);

                //long long (int):

                    printf("lld LLONG_MAX = %lld\n", LLONG_MAX);

                //#floating point numbers
                {
                    //float and double both use the the same char `f` char:

                        printf("printf float = %f\n", 1.0f);
                        printf("printf double = %f\n", 1.0);

                    //long double:

                        printf("f = %Lf\n", (long double)1.0);

                    //#control number of zeros after dot
                    {
                        //#fixed number
                        {
                            sprintf(s, "%.2f", 1.0f);
                            assert(strcmp(s, "1.00") == 0);
                        }

                        //#given by variable
                        {
                            sprintf(s, "%.*f", 2, 1.0f);
                            assert(strcmp(s, "1.00") == 0);
                        }
                    }
                }

                //#control minimum number chars to output
                {
                    /*
                    Pad with spaces, right align.

                    Useful to output nicely formatted tables.

                    Ugly:

                        12345 1
                        1 1

                    Beautiful:

                        12345 1
                        1     1
                    */
                    {
                        sprintf(s, "%6.2f", 1.0f);
                        assert(strcmp(s, "  1.00") == 0);
                    }

                    /*
                    Pad with zeros

                    Useful for naming files: with `0`

                    - "10" comes after  "09" ('1' > '0')
                    - "10" comes before "9"  ('1' < '0')!
                    */
                    {
                        sprintf(s, "%06.2f", 1.0f);
                        assert(strcmp(s, "001.00") == 0);
                    }

                    /*
                    Left align with `-`
                    */
                    {
                        sprintf(s, "%-6s", "abc");
                        assert(strcmp(s, "abc   ") == 0);

                        // Does not work with zeros. gcc 4.8.1 gives a warning.

                        // sprintf(s, "%-06s", "abc");
                        // printf("%s\n", s);
                        // assert(strcmp(s, "abc   ") == 0);
                    }
                }

                //#scientific
                {
                    char s[10];
                    sprintf(s, "%.3e", 1.0f);
                    assert(strcmp(s, "1.000e+00") == 0);
                }

                //srings
                {
                    char s[4];
                    sprintf(s, "%s", "abc");
                    assert(strcmp(s, "abc") == 0);

                    /*
                    still not possible to print a null char with this
                    substitution is done before
                    */
                    {
                        char s[] = "000";
                        sprintf(s, "%s", "a\0b");
                        //TODO0 why does this fail?
                        //assert(memcmp(s, "a\00", 3) == 0);
                    }
                }

                //hexadecimal integer output (unsigned):
                {
                    printf("16  in hex = %x\n", 16);

                    //case control

                        printf("0xA in hex = %x\n", 0xA);
                        printf("0xA in hex upper case = %X\n", 0xA);

                    printf("-1  in hex = %x\n", -1);
                    printf("16l in hex = %lx\n", 0x16l);
                }

#if __STDC_VERSION__ >= 199901L
                //hexadecimal scientific float output. C99
                {
                    printf("0x1.Ap11           = %a\n", 0x1.Ap11);
                    printf("0x1.Ap11 uppercase = %A\n", 0x1.Ap11);
                    printf("0x10.Ap11          = %a\n", 0x10.Ap11);
                }
#endif

                /*
                pointers

                    prints the hexadeciamal linear address.

                    %p excpects a `void*`.
                */
                {
                    char s[ PRIxPTR_WIDTH + 3 ]; //2 for "0x" and one for trailling '\0'

                    /*
                    non null pointers are printed in a (bad?) notation starting with `0x`

                    Also, trailling zeroes on the number are removed,
                    so address 16 is represented as `0x10`
                    */
                    {
                        sprintf(s, "%p", (void*)16);
                        assert(strcmp(s, "0x10") == 0);
                    }

                    /* NULL pointer has a special representation as `(nil)` */
                    {
                        sprintf(s, "%p", NULL);
                        assert(strcmp(s, "(nil)") == 0);
                    }

#if __STDC_VERSION__ >= 199901L

                    /*
                    #PRIxPTR

                        0 pad pointers.

                        To print pointers and line them up nicely, one must take into account that trailling zeroes are ommited.

                        One option is to space pad:

                            %10

                        But this produces:

                                  0x10
                            0x10000000

                        which is still ugly.

                        The ideal would then be to pad with zeros as in:

                            0x00000010
                            0x10000000

                        The notation:

                            %010p

                        is not supported TODO0 why not?

                        The solution to this introduced in C99 is to use `uintptr + PRIxPTR`:
                        <http://stackoverflow.com/questions/1255099/whats-the-proper-use-of-printf-to-display-pointers-padded-with-0s>

                        There seems to be no convenient way to take into account pointer sizes except defining thingg manually:
                        For example, x32 uses 4 bytes, x64 8, etc.

                    */
                    {
                        printf("PRIxPTR usage = %0*" PRIxPTR "\n", PRIxPTR_WIDTH, (uintptr_t)(void*)1);
                    }
                }
#endif

                /*
                #escape percentage.

                    Note that `%` is printf specific,
                    not string literal specific,
                    since percentages only have special meanings on strings passed to `printf`.
                */
                {
                    char s[2];
                    sprintf(s, "%%");
                    assert(strcmp(s, "%") == 0);
                }

                /*
                typedefs

                    How to printf standard typedefs.
                */
                {
                    //If they have specific format strings. Just use them.
                    {
                        printf("printf size_t    = %zu\n", (size_t)1);
                        printf("printf intmax_t  = %jd\n", (intmax_t)1);
                        printf("printf uintmax_t = %ju\n", (uintmax_t)1);
                    }

                    //If there is no format string, but the type is assured to be an integer type,
                    //typecast to the largest possible integer type and use `%jd` or `%ju`.
                    {

                        /* Supppose that the API states that `integer_t` is a signed integer type. */
                        //typedef int integer_t;
                        printf("printf integer_t = %jd\n", (intmax_t)1);
                    }

                    /*
                    There are some cases in which there is no specific printf format,
                    but there is a macro that expands to part of a format string that allows to print it correctly.
                    */
                    {
#if __STDC_VERSION__ >= 199901L
                        printf("printf PRIxPTR uintptr_t = %" PRIxPTR "\n", (uintptr_t)16);
                        printf("printf PRIdPTR uintptr_t = %" PRIdPTR "\n", (uintptr_t)16);

                        /*
                        sprintf has a different macro defined for it!
                        */
                        {
                            char s[256];
                            sprintf(s, "%" SCNxPTR, (uintptr_t)1);
                            printf("sprintf uintptr_t = %s\n", s);
                        }
#endif
                    }


                    /*
                    If a typedef is not guaranteed to be either an integer type or a floating point type,
                    such as `clock_t`, there seems to be no ideal solution as of C99 <http://stackoverflow.com/questions/1083142/whats-the-correct-way-to-use-printf-to-print-a-clock-t/17190680#17190680>

                    The best solution is to just cast it to the largest floating point type possible

                    Unfortunatelly, as of c11 there is no way to get the largets floating point type
                    as can be done for integers: <http://stackoverflow.com/questions/17189423/how-to-get-the-largest-precision-floating-point-data-type-of-implemenation-and-i/17189562>
                    */
                    {
                        printf("printf clock_t = %Lf\n", (long double)(clock_t)1);
                        printf("printf time_t  = %Lf\n", (long double)(clock_t)1);
                    }
                }

                //Return value: number of bytes written, negative if error.
                //for string versions, excludes traling '\0'.

                    assert(sprintf(s, "%c", 'a') == 1);
            }

            /*
            #fprintf

                Same as printf, but to an arbitrary stream
            */
            {
                assert(fprintf(stdout, "fprintf = %d\n", 1) == 12);
            }

            /*
            large strings to stdout

                stdout it line buffered

                if you fill up the buffer without any newlines
                it will just print

                buffer size cannot be accessed programatically

                TODO0 what is the bin buffer size?
                in practice, 1024 works just fine
                it may be much larger than BUFSIZ
            */
            {
                const int bufsiz = 100000;
                char buf[bufsiz];
                memset(buf, 'z', bufsiz);
                buf[bufsiz] = '\0';
                buf[bufsiz/2] = '\n';
                //printf("%s\n", buf); //large amount of 'z's verywhere!
            }
        }

        //#stream input
        {
            /*
            #getchar

                getchar == getc(stdin)

            #getc

                get single char from given stream (should be called fgetc...)

                it blocks until any char made available.

                whatever char entered including on a tty is made available immediatelly.
            */
            if (0) {

                //echo a | c.out
                    //a
                //sleep 3 | c.out
                    //EOF after 3 secs

                fputs("enter a char (on linux, ctrl+d EOF): ", stderr);
                //fputc('a', stdin);
                    //BAD
                    //does not work
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
            #gets

                Deprecated, removed in C11.

                dangerous:
                no size checking possible
                if too much input, just seg faults
            */
            if (0) {
                //printf("enter a string terminated by newline: (max %d chars, newline will be included in the string)\n", sn);
                //gets(s);
                //printf("you entered:\n%s\n\n",s);
            }
#endif

            /*
            #fgets

                reads up to whichever comes first:

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
                    if (feof(fp)) {
                        fprintf(stderr, "fgets was already at the end of the stream and read nothing");
                    }
                    else if (ferror(fp))
                    {
                        fprintf(stderr, "fgets error reading from stream");
                    }
                }
                //some bytes are left in the buffer, may want to reread it.
                else if (! feof(fp))
                {
                    //TODO why does this not work with stdin from a tty nor pipe?
                    //why is eof not reached even if user inputs 1 single char?

                        //fprintf(stderr, "you entered more than the maximum number of bytes\n");

                    //TODO why does this not work? why is eof not reached even if user inputs 1 single char?
                }
                fprintf(stderr, "you entered:\n%s", buff);
            }

            /*
            #scanf

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
                //stuff is space separated
                //try 123 456 789 at once. 456 789 stay in the buffer, and are eaten by the second scanf

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
            #fscanf

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
        #file streams #file io

            To get streams that deal with files, use `fopen`.

            To close those streams after usage, use `fclose`.

            #fopen

                Open file for read/write

                Don't forget to fclose after using! open streams are a process resource.

                Modes:

                - r: read. compatible with a,w
                - w: read and write. destroy if exists, create if not.
                - a: append. write to the end. creates if does not exist.
                - +: can do both input and output. msut use flush or fseek
                - x: don't destroy if exist (c11, not c++!)
                - b: binary. means nothing in POSIX systems,
                    on our dear DOS must be used for NL vs NLCR problems
                    there are two different modes there
                    Therefore, for portability, make this difference.

                In case of error:

                - return `NULL` and set `errno`.

            #text io vs #binary io

                #text vs binary for numerical types

                    Example: an int 123 can be written to a file in two ways:

                    - text: three bytes containing the ascii values of `1`, `2` and then `3`

                    - binary: as the internal int representation of the c value, that is 4 bytes,
                        with `123` in binary and zeroes at the front.

                    Advantages of text:

                    - it is human readable since it contains only ASCII or UTF values

                    - for small values it may be more efficient (123 is 3 bytes in ascii instead of 4 in binary)

                    Advantages of binary:

                    - it is shorter for large integers

                    - inevitable for data that cannot be interpretred as text (images, executables)

                #newline vs carriage return newline

                    Newline carriage return realated TODO confirm

                    For portability, use it consistently.

                    In linux the difference between text methods and binary methods is only conceptual:
                    some methods output human readable text (`fprintf`) and can be classified as text,
                    while others output binary, no difference is made at file opening time

            #fclose

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
            FILE* fp;
            char path[] = "fwrite.tmp";

            /*
            #fwrite

                Returns number of elements written.

                If less elements are written than required an erro ocurred.

                Why take both bytes per item and items instead of just total bytes:
                <http://stackoverflow.com/questions/295994/what-is-the-rationale-for-fread-fwrite-taking-size-and-count-as-arguments>

                It seems that no less than size per item can be writen, so we are guaranteed
                that some object will not be half writen.
            */
            {
                fp = fopen(path, "wb");
                if (fp == NULL) {
                    io_error("fopen", path);
                }
                else {
                    if (fwrite(elems_write, sizeof(elems_write[0]), nelems, fp) < nelems) {
                        io_error("fwrite", path);
                    }
                    if (fclose(fp) == EOF) {
                        io_error("fclose", path);
                    }
                }
            }

            /*
            #fread

                Returns number of *elements* written, not bytes.

                If less elements are returned than required then either:

                - an error ocured
                - the end of file was reached.

                It is only possible to distinguish between those cases by using
                the `feof` and `ferror` functions.

            #ferror
            #feof
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
        }

        /*
        #freopen

            Open a given `FILE*` again but as a different file.
        */
        {
            //this will discard stdin on linux
            //freopen("/dev/null", "r", stdin);
        }

        //#reposition read write
        {
            /*
            For new code, always use `fgetpos` and `fsetpos` unless you absolutely
            need `SEEK_END` because ftell and fseek
            must return `long` which may limit the maximum file to be read,
            while `fgetpos` uses a typedef `fpos_t`

            #ftell

                Get current position of `FILE*`.

            #fseek

                Set current position in `FILE*` relative to:

                - SEEK_SET: relative to beginning of file
                - SEEK_CUR: relative to current position
                - SEEK_END: relative to end of file

                It seems that seeking after the eof is undefined behaviour in ANSI C:
                <http://bytes.com/topic/c/answers/219508-fseek-past-eof>

                This contrasts with POSIX lseek + write, in which the unwriten gap is 0.
            */
            {
                //long int curpos = ftell(pf)
                //if (curpos == -1L){
                //  //ERROR
                //}

                //FILE* fp;
                //if (fseek (fp, 0 , SEEK_SET) != 0) {
                //  //ERROR
                //}
            }

            /*
            #rewind

                Same as therefore useless.

                    fseek(stream, 0L, SEEK_SET)
            */

            /*
            Like ftell/fseek except that:

            - the return is a typedef `fpos_t`, so it may represent larger files.
            - there is a single possible reference position equivalent to `SEEK_SET`.
                This makes sence since that argument was only useful for convenience.

            Always use it instead of ftell/fseek.

            #fgetpos

                Get a position in stream that is later usable with a later call to `fsetpos`.

            #fsetpos

                Set position to a point retreived via fgetpos.
            */
            {
            }
        }

        /*
        #flush(fp)

            For output streams only.

            Makes sure all the data is put on the stream.

            May be necessary as the data may be in a buffer.
        */
        {
            // if (flush(fp) == EOF){
            //        //error
            // }

            /* debugging application: your program segfaults

            To find where, you put printf everywhere.

            However nothing shows on screen.

            Solution: flush immediatelly after the printf and add a newline at the end of the printed string.
            This should ensure that your string gets printed.
            */
        }

        //#applications
        {
            {
                char path[] = "str_file.tmp";
                char input[] = "asdf\nqwer";

                // Write entire string to file at once.
                {
                    if (file_write(path, input) == -1) {
                        io_error("file_write", path);
                    }
                }

                // Read entire file at once to a string.
                {
                    char *output = file_read(path);
                    if (output == NULL) {
                        io_error("file_read", path);
                    }
                    assert(strcmp(input, output) == 0);
                    free(output);
                }

                // Get file size:
                {
                    long size = get_file_size(path);
                    if (size == -1) {
                        io_error("get_file_size", path);
                    }
                    assert(size == strlen(input));
                }
            }

            /*
            Process a file linewise.

            Allows one to read files larger than RAM, suppposing that
            each line is smaller than RAM.

            glibc offers the `getline` function.
            */
            {
                FILE* fp;
                // Maximum accepted line length is buf_size including the newline.
                enum Constexpr {buffer_size = 4};
                char buffer[buffer_size];
                size_t last_newline_pos, current_pos;
                int linenum = 0;
                long file_size;
                long nbytes_read;

                char path[] = "cat.tmp";
                char file_data[] = "abc\nde\nfgh";
                size_t file_data_size = strlen(file_data);
                char lines[3][4] = {"abc\n", "de\n", "fgh\n"};
                size_t current_line;

                // Prepare test.
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

                /*
                // The actual cat.
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

            // Simple write arrays to file
            {
                FILE* fp;
                char path[16];

                int arri[] = { 0, 1, -1, 12873453 };
                float arrf[] = { 1.1f, 1.001f, -1.1f, 1.23456e2 };

                strcpy(path, "arri.tmp");
                write_int_arr_file(path, arri, 4);

                strcpy(path, "arrf.tmp");
                write_float_arr_file(path, arrf, 4, 2);
            }
        }

        /*
        #file operation

            A few file operations are available in ANSI C.

            They are present in <stdio.h> mainly to support file io.

            There seems to be no directory operations however.

        #remove

            Remove a file.

                int remove(const char *filename);

            ANSI C does not way what happen if it does not exist.

            If the file is open, the behaviour is undefined.

        #rename

            Rename a file.

                int rename(const char *old, const char *new);

            If the new file exists, undefined behaviour.
        */

        /*
        #perror

            Print description of errno to stderr with given prefix appended, `NULL` for no prefix.

            Basic way to print error messages after error on a posix function
        */
        {
            errno = EDOM;
            perror("perror test EDOM");
        }
    }

    //#time.h
    {
        /*
        #time()

            A representation of absolute time.

            Returns a time_t type.

            The interpretation of the return is implementation defined,
            and therefore cannot be relied directly upon.

            Traditionally, implementations use the number of seconds since 1970.

        #time_t

            All that is required is that `time_t` be an arithmetic type, either integer or floating point.

            See printf for a discussion of how to print time_t.
        */
        {
            time_t t = time(NULL);
        }

        //#CLOCKS_PER_SEC

            printf("CLOCKS_PER_SEC = %ld\n", CLOCKS_PER_SEC);

        /*
        #clock()

            Program virtual time in number of processor clock clicks

            Precision is quite limited, and if too few clicks pass, it may return 0.

        #clock_t

            Type returned by `clock()`.

            Like `time_t`, all that is required is that `time_t` be an arithmetic type,
            either integer or floating point.

            See printf for a discussion of how to print a `clock_t`.
        */
        if (0) {
            clock_t t;
            int i = 0;
            t = clock();

            /*
            busy waiting

            WARNING: optimizer may simply skip your useless test operations
            and very little time will have passed
            */
                int j = 0;
                for (int i = 0; i < CLOCKS_PER_SEC * 10; i++) { j++; }

            t = clock() - t;

            //there is no printf specifier for `clock_t`
            //so cast to largest possible integer type:

                printf("clicks = %llu\n", (intmax_t)t);

            printf("seconds = %f\n", ((float)t) / CLOCKS_PER_SEC);
        }

        /*
        #strftime

            Convert time to a formatted string.
        */
        {
        }
    }

    /*
    #math.h

        Mathematical functions.

        C99 made many improvements to it. It seems that the C community is trying to replace FORTRAN by C
        for numerical computations, which would be a blessing as it would mean that the system programming
        croud (C) would be closer to the numerical programming one (FORTRAN).

    #redundant mathematical functions

        Many functions are redundant, but are furnished because of possible speedups and better precision.

        For exapmle, `sqrt` and `pow` are redundant since in theoryin theory `sqrt(x) == pow(x,0.5)`.

        However, many hardware platforms such as x86 implement a `sqrt` as a single instruction,
        if you use `sqrt` it will be simpler for the compiler to use the x86 sqrt instruction
        if it is available.

        Using the hardware instruction may be faster.

        It will also possibly be more precise since it is likelly that sqrt
        would need several floating point operations to implement, each one meaning a loss of precision,
        while the hardware can do them a single operation.

        I guess however that good compilers will optimize `pow(x, 0.5)` to `sqrt(x)`.

        Anyways, it is better to play on the safe side, and always use the most specific operation possible.

    #errors

        The following errors exist:

        #domain error

            Value outside of function domain. Ex: `sqrt(-1.0)`.

            Return value: implementation defined.
            In other words, undefined behaviour to ANSI C, so never rely on it.

            Detection: if `math_errhandling & MATH_ERRNO != 0`, `errno = ERANGE`
            and a "divide-by-zero" floating point exception is raised.

        #pole error

            Function has a pole at a point. Ex: `log(0.0)`, `tgamma(-1.0)`.

            Return value: HUGE_VAL.

            Detection if `math_errhandling & MATH_ERRNO != 0`, `errno = ERANGE`
                and a "divide-by-zero" floating point exception is raised.

        #range errors

            Occur if the result is too large or too small to fint into the return type.

            There are two types of range errors overflow and underflow.

            In both cases, if `math_errhandling & MATH_ERRNO != 0`,
            `errno = ERANGE` and a "divide-by-zero" floating point exception is raised.

            #overflow

                For exapmle, around poles, functions can have arbitrarily large values,
                so it is possible that for a given input close enough to the pole that the output is too large to reprent.

                Return value: HUGE_VAL, HUGE_VALF, or HUGE_VALL, acording to function's return type.

            #underflow

                The output is too small to represent

                Return value: an implementation-defined value whose magnitude is no greater than the smallest
                normalized positive number in the specified type;
    */
    {
        const double err = 10e-6;

        printf("math_errhandling & MATH_ERRNO = %d\n", math_errhandling & MATH_ERRNO);

        //#abs
        {
            //absolute values, integer version:

                assert(abs(-1.1) == 1);

            //absolute values, float version:

                assert(fabsl(-1.1) == 1.1);
        }

        /*
        Max and min for floats (C99):

        Don't forget to use the float versions which starts with f when you want floating operations!
        */
        {
            assert(fminl(0.1, 0.2) == 0.1);
            assert(fmaxl(0.1, 0.2) == 0.2);
        }

        /*
        #rounding

            //many more: rint, lrint
        */
        {
            assert(fabs(floor(0.5) - 0.0 ) < err);
            assert(fabs(ceil(0.5)  - 1.0 ) < err);

            /*
            #trunc

                Never raises any errors because the new result always fits in the data type (magnitide decresases).
            */
            {
                assert(fabs(trunc(1.5)  -  1.0) < err);
                assert(fabs(trunc(-1.5) - -1.0) < err);
            }

            /*
            #round

                Away from 0 on mid case.
            */
            {
                assert(fabs(round( 1.25) -  1.0) < err);
                assert(fabs(round( 1.5 ) -  2.0) < err);
                assert(fabs(round( 1.75) -  2.0) < err);
                assert(fabs(round(-1.5 ) - -2.0) < err);
            }

            /*
            #modf

                Decompose into fraction and integer parts.
            */
            {
                double d;
                assert(fabs(modf(3.25, &d) - 0.25) < err);
                assert(fabs(d              - 3.00) < err);
            }
        }

        /*
        #fma

            Fused multiple add or floating point multiply and add.

            Does addition and multiplication on one operation,
            with a single rounding, reduncing rounding errors.

            Has hardware implementations on certain platforms.
        */
        {
            assert(fabs(fma(2.0, 3.0, 4.0) - (2.0 * 3.0 + 4.0)) < err);
        }

        //#exponential functions
        {
            //#exp
            {
                assert(fabs(exp(1.0) - 2.71) < 0.01);
            }

            /*
            #ln

                See log.

            #log

                Calculates the ln.
            */
            {
                assert(fabs(log(exp(1.0)) - 1.0) < err);
                assert(fabs(log2(8.0)     - 3.0) < err);
                assert(fabs(log10(100.0)  - 2.0) < err);
            }

            /*
            #sqrt

                Range is positive or zero. Negatives are a range error.

                To get complex on negative values, use `csqrt`.
            */
            {
                assert(fabs(sqrt(4.0) - 2.0) < err);

                //GCC 4.7 -O3 is smart enough to see that this is bad:
                {
                    float f = -4.0;
                    //printf("sqrt(-4.0) = %f\n", sqrt(f));
                }

                {
                    float f;
                    volatile float g;

                    if (true) f = -4.0;
                    errno = 0;
                    g = sqrt(f);
                    if (math_errhandling & MATH_ERRNO)
                        assert(errno == EDOM);
                    printf("sqrt(-4.0) = %f\n", f);
                }
            }

#if __STDC_VERSION__ >= 199901L

            /*
            #hypot

                Hypotenuse: sqrt(x^2 + y^2)
            */
            {
                assert(fabs(hypot(3.0, 4.0) - 5.0) < err);
            }
#endif

#if __STDC_VERSION__ >= 199901L
            /*
            #cbrt

                CuBe RooT
            */
            {
                assert(fabs(cbrt(8.0 ) -  2.0) < err);
                assert(fabs(cbrt(-8.0) - -2.0) < err);
            }
#endif

            //#pow
            {
                assert(fabs(pow(2.0, 3.0) - 8.0 ) < err);
            }
        }

        //#trig
        {
            float f = sin(0.2);
            assert(fabs(sin(0.0) - 0.0) < err);
            assert(fabs(cos(0.0) - 1.0) < err);

            /*
            #PI

                There is no predefined macro for PI. TODO0 why not? so convenient...

                This is a standard way to get PI.

                The only problem is a possible slight calculation overhead.
                But don't worry much about it. For example in gcc 4.7, even with `gcc -O0` trigonometric functions
                are calculated at compile time and stored in the program text.
            */
            {
                assert(fabs(acos(-1.0) - 3.14)    < 0.01);
            }
        }

        //#erf: TODO0 understand

        /*
        #factorial

            There seems to be no integer factorial function,
            but `gamma(n+1)` coincides with the factorials of `n` on the positive integers,
            and may be faster to compute via analytic approximations that can be done to gamma
            and/or via a hardware implementation, so just use gamma.

        #gamma

            Wiki link: <http://en.wikipedia.org/wiki/Gamma_function>

            Extension of the factorials to the real numbers because:

            - on the positive integergs:

                gamma(n+1) == n!

            - on the positive reals:

                gamma(x+1) == x * gamma(x)

            Has a holomorphic continuation to all imaginary plane, with poles on 0 and negative integers.

            Implemented in C as `tgamma`.

        #tgamma

            True Gamma function. TODO0 Why True?

            Computes the gamma function.

            ANSI C says that it gives either domain or pole error on the negative integers.

        #lgamma

            lgamma = ln tgamma
        */
        {
            assert(fabs(tgamma(5.0) - 4*3*2 ) < err);
            assert(fabs(tgamma(3.5) - 2.5 * tgamma(2.5) ) < err);

            errno = 0;
            volatile double d = tgamma(-1.0);
            if (math_errhandling & MATH_ERRNO) {
                if (errno == ERANGE)
                    assert(d == HUGE_VAL);
                else
                    assert(errno == EDOM);
            }

            assert(fabs(lgamma(3.5) - log(tgamma(3.5))) < err);
        }

        //floating point manipulation functions
        {
            /* #ldexp(x, y) = x * 2 ^ y */
            {
                assert(fabs(ldexp(1.5, 2.0) - 6.0 ) < err);
            }

            /*
            #nextafter

                Return the next representable value in a direction.

                If both arguments equal, return them.

            #nexttowards

                TODO0 diff from nextafter
            */
            {
                printf("nexttowards(0.0, 1.0) = %a\n", nexttoward(0.0, 1.0));
                assert(nexttoward(0.0, 0.0) == 0.0);
                printf("nextafter  (0.0, 1.0) = %a\n", nextafter(0.0, 1.0));
            }
        }

        /*
        #random

        #srand

            See random number generator.

            It is very common to seed with `time(NULL)`.

        #rand

            Get a uniformly random `int` between 0 and RAND_MAX.
        */
        {
            srand(time(NULL));

            //integer between 0 and RAND_MAX:
            {
                int i = rand();
            }

            // int between 0 and 99:
            {
                int i = rand() % 99;
            }

            //float between 0 and 1:
            float f = rand()/(float)RAND_MAX;
        }

        /*
        #IEEE-754

            IEC 60559 has the same contents as the IEEE 754-2008,
            Outside of the C standard it is commonly known by the IEEE name, or simply as IEEE floating point.

            IEEE dates from 1985.

        #__STDC_IEC_559__

        #IEC 60599

            Standard on which floating point formats and operations should be available
            on an implementation, and how they should work.

            Good overview wiki article: <http://en.wikipedia.org/wiki/IEEE_floating_point>

            Many CUPs implement large parts of IEC 60599, which C implementations can use if available.

            The C standard specifies that implementing the IEC 60599 is not mandatory.

            If the macro `__STDC_IEC_559__` is defined this means that the implementation is compliant
            to the interface specified in Annex F of the C11 standard.

            C99 introduced many features which allow greater conformance to IEC 60599.
        */
        {
#ifdef __STDC_IEC_559__
        puts("__STDC_IEC_559__");

        /*
        C float is 32 bits, double 64 bits.

        long double extende precision, and could be one of the format not spceified by IEC.

        IEC explicitly allows for extended formats, and makes basic restrictions such that
        its exponent should have more bits than the preceding type.

        This is probably the case to accomodate x86's 80 bit representation.
        */
        {
            assert(sizeof(float) == 4);
            assert(sizeof(double) == 8);
        }
#endif
        }

        /*
        #division by 0

            Time to have some fun and do naughty things.

            The outcome of a division by zero depends on wether it is an integer of floating operation.

        #isfinite
        #isinf
        #isnan
        #isnormal
        #fpclassify

            FP_INFINITE, FP_NAN, FP_NORMAL, FP_SUBNORMAL, FP_ZERO
        */
        {
            /*
            #floating point exception

                In x86, the following generates a floating point exception,
                which is handled by a floating point exception handler function.

                In Linux the default handler is implemented by the OS and sends a signal to our application,
                which if we don't catch will kill us.
            */
            if (0) {
                //gcc 4.7 is smart enough to warn on literal division by 0:
                {
                    //int i = 1 / 0;
                }

                //gcc 4.7 is not smart enough to warn here:
                {
                    volatile int i = 0;
                    printf("int 1/0 = %d\n", 1 / i);

                    //on gcc 4.7 with `-O3` this may not generate an exception,
                    //as the compiler replaces 0 / X by 0
                    printf("int 0/0 = %d\n", 0 / i);
                }
            }

            /*
            #HUGE_VAL

                Returned on overflow.

                Can equal `INFINITY`.
            */
            {
                printf("HUGE_VAL = %f\n", HUGE_VAL);      //double
                printf("HUGE_VALF = %f\n", HUGE_VALF);    //float
                printf("HUGE_VALL = %Lf\n", HUGE_VALL);   //long double
            }

            /*
            #INFINITY

                Result of operations such as:

                    1.0 / 0.0

                Type: float.

                There are two infinities: positive and negative.

                It is possible that `INFINITY == HUGE_VALF`.
            */
            {
                printf("INFINITY = %f\n", INFINITY);
                printf("-INFINITY = %f\n", -INFINITY);

                volatile float f = 0;
                assert(1 / f == INFINITY);
                assert(isinf(INFINITY));
                assert(! isnan(INFINITY));

                assert(INFINITY + INFINITY == INFINITY);
                assert(INFINITY + 1.0      == INFINITY);
                assert(INFINITY - 1.0      == INFINITY);
                assert(isnan(INFINITY - INFINITY));

                assert(INFINITY *  INFINITY    ==  INFINITY);
                assert(INFINITY * -INFINITY    == -INFINITY);
                assert(INFINITY *  2.0         ==  INFINITY);
                assert(INFINITY * -1.0         == -INFINITY);
                assert(isnan(INFINITY * 0.0));

                assert(1.0 / INFINITY == 0.0);
                assert(isnan(INFINITY / INFINITY));

                //compairisons with INFINITY all work as expected
                assert(INFINITY == INFINITY);
                assert(INFINITY != - INFINITY);
                assert(-INFINITY < - 1e100);
                assert(1e100 < INFINITY);
            }

            /*
            #NAN

                Not a number.

                Result of operations such as:

                    0.0 / 0.0
                    INFINITY - INFINITY
                    INFINITY * 0.o
                    INFINITY / INFINITY

                And any operation involving NAN.

                The sign of NAN has no meaning.
            */
            {
                printf("NAN = %f\n", NAN);
                printf("-NAN = %f\n", -NAN);

                //TODO0 why do both fail
                    //assert(0 / f == -NAN);
                    //assert(0 / f == NAN);

                volatile float f = 0;
                assert(isnan(0 / f));
                assert(isnan(NAN));
                assert(! isinf(NAN));

                assert(isnan(NAN));
                assert(isnan(NAN + 1.0));
                assert(isnan(NAN + INFINITY));
                assert(isnan(NAN + NAN));
                assert(isnan(NAN - 1.0));
                assert(isnan(NAN * 2.0));
                assert(isnan(NAN / 1.0));
                assert(isnan(INFINITY - INFINITY));
                assert(isnan(INFINITY * 0.0));
                assert(isnan(INFINITY / INFINITY));

                /*
                NAN is not ordered. any compairison to it yields false!

                This is logical since 0 is neither smaller, larger or equal to NAN.
                */
                {
                    assert(! (0.0 < NAN));
                    assert(! (0.0 > NAN));
                    assert(! (0.0 == NAN));
                }
            }
        }
    }

#if __STDC_VERSION__ >= 199901L
    /*
    #stdint.h

        contains several types of ints, including fixed size
        and optimal for speed types

        c99

        all macros with numbers are defined for N = 8, 16, 32, 64
    */
    {

        //exactly 32 bits:

            assert(sizeof(int32_t) == 4);

        //all have unsigned verions prefixed by 'u'

            assert(sizeof(uint32_t) == 4);

        //at least 32 bits:

            assert(sizeof(int_least32_t) >= 4);

        //fastest operations with at least 32 bits:

            assert(sizeof(int_least32_t) >= 4);

        /*
        #intptr_t

            An integer type large enough to hold a pointer.

            Could be larger than the minimum however.

        #uintptr_t

            Unsigned version.

        TODO0 example of real life application?
        */
        {
            assert(sizeof(void*) == sizeof(intptr_t));
            assert(sizeof(void*) == sizeof(uintptr_t));
        }

        //uniquelly defined by machine address space

        /*
        #intmax_t #uintmax_t

            int with max possible width

            [there is no floating point version](http://stackoverflow.com/questions/17189423/how-to-get-the-largest-precision-floating-point-data-type-of-implemenation-and-i/17189562?noredirect=1#comment24893431_17189562)
            for those macros
        */
        {
            assert(sizeof(intmax_t) >= sizeof(long long));
            assert(sizeof(uintmax_t) >= sizeof(unsigned long long));
        }

        //inttypes also includes limits for each of the defined types:
        {
            {
                int32_t i = 0;
                assert(INT32_MIN < i);
                assert(INT32_MAX > i);
            }

            {
                int_fast32_t i = 0;
                assert(INT_FAST32_MIN < i);
                assert(INT_FAST32_MAX > i);
            }
        }
        //all have max/min ranges
        //"_t" removed, "_max" or "_min" appended, all uppercased
    }

#endif

    /*
    #limits.h

        Gives the maximum and minimum values that fit into base integer types
        in the current architecure
    */
    {
        //#INT_MAX #UINT_MAX
        printf("CHAR_MAX = %d\n", CHAR_MAX);
        assert(CHAR_MAX == 127);
        printf("INT_MAX = %d\n", INT_MAX);
        printf("INT_MIN = %d\n", INT_MIN);
        printf("LONG_MAX = %ld\n", LONG_MAX);
        printf("LLONG_MIN = %lld\n", LLONG_MIN);

        /*
        Unsigned versions are prefiexed by `U`.

        There is no MIN macro for unsigned versions since it is necessarily `0`.
        */

        printf("UINT_MAX = %u\n", UINT_MAX);
    }

    /*
    #float.h

        gives characteristics of floating point numbers and of base numerical operations
        for the current architecture

        All macros that start with FLT have versions starting with:

        - DBL   for `double`
        - LDBL  for `long double`
    */
    {

        /*
        #FLT_ROUNDS

            rounding method of sums

            values:

            - -1: indeterminable
            - 0:  toward zero
            - 1:  to nearest
            - 2:  toward positive infinity
            - 3:  toward negative infinity

            TODO0 can it be changed?
        */
        {
            printf("FLT_ROUNDS = %d\n", FLT_ROUNDS);
        }

        /*
        #FLT_EVAL_METHOD

            Precision to which floating point operations are evaluated

            it seems that floating operations on, say, floats can be evaluated
            as long doubles always.

            TODO0 understand better
        */
        {
            printf("FLT_EVAL_METHOD = %d\n", FLT_EVAL_METHOD);
        }

        /*
        #FLT_MIN

            Smalles positive number closes to zero that can be represented in a normal float.

            Any number with absolute value smaller than this is subnormal,
            and support is optional.
        */
        {
            printf("FLT_MIN = %a\n", FLT_MIN);
            printf("DBL_MIN = %a\n", DBL_MIN);
            printf("LDBL_MIN = %La\n", LDBL_MIN);
        }

        /*
        #FLT_RADIX

            several other macros expand to the lengths of the representation

            useful terms:

                1.01_b * b ^ (10)_b

            - radix:

            TODO0 wow, there are non radix 2 representation implementations?!
        */
        {
            printf("FLT_RADIX = %d\n", FLT_RADIX);
        }

#if __STDC_VERSION__ >= 201112L

        /*
        #subnormal numbers

            C11

            Defined in IEC 60599.

            Ex:

                0.01

            Is represented as:

                1 * 10^-2

            However the exponent has a fixed number of bits, so if the exponent is too small.

            A solution to incrase that exponent is to allow number that start with 0.

            So if for example -4 is the smallest possible exponent, 10^-5 could be represented as:

                0.1 * 10^-4

            Such a number that cannot be represented without trailling zeroes is a subnormal number.

            The tradeoff is that subnormal numbers have limited precision.

            C11 specifies that the implementation of such feature is options,
            and oe can check if those are supported in the implementation via the `HAS_SUBNORM` macros.

            As of 2013 hardware support is low but starting to appear.
            Before this date, implementations are done on software, and are therefore slow.

            The smallest floating normal number is `FLT_MIN`.

            Values:

            - -1: undeterminable
            - 0: no
            - 1: yes
        */
        {
            printf("FLT_HAS_SUBNORM = %d\n",     FLT_HAS_SUBNORM);
            printf("DBL_HAS_SUBNORM = %d\n",     DBL_HAS_SUBNORM);
            printf("LDBL_HAS_SUBNORM = %d\n",    LDBL_HAS_SUBNORM);

            assert(isnormal(LDBL_MIN));

            if (LDBL_HAS_SUBNORM) {
                long double ldbl_min_2 = LDBL_MIN / 2.0;
                printf("LDBL_MIN / 2.0 = %La\n", ldbl_min_2);
                assert(ldbl_min_2 != 0);
                assert(ldbl_min_2 != LDBL_MIN);
                assert(! isnormal(ldbl_min_2));
            }
        }

#endif

    }

    /*
    #fenv.h

        contains flags that indicate the status of floating point related registers

        TODO get some interesting and basic samples working
    */

    /*
    #unsigned

        C has unsigned versions of all built-in data types.

        These basically have more or less double the maximum size
        of the signed version, and are always positive.

        You should always use unsigned sizes for quantities which must be positive such as:

        - array indexes
        - memory sizes (size_t)

        As this will give clues to the compiler
        and humans about the positive quality of your number
    */
    {
        // True in 2's complement. Modulo arithmetic holds.
        {
            assert((char)-1 == (char)255);
            assert((unsigned char)-1 == (unsigned char)255);
            assert((unsigned char)-2 == (unsigned char)254);
        }

        {
            assert((char)0 > (char)255);
            assert((unsigned char)0 < (unsigned char)255);
        }
    }

#if __STDC_VERSION__ >= 199901L

    /*
    #complex.h

        C99. Possible insertion rationale: replace FORTRAN for numerical computations.

        There is no direct printf way to print complex numbers:
        <http://stackoverflow.com/questions/4099433/c-complex-number-and-printf>

        All functions provided by this header are prefixed by `c`.

        Quick func list: <http://en.wikipedia.org/wiki/Tgmath.h#Complex_numbers>
    */
    {
        const double err = 10e-6;

        assert(sizeof(float complex ) <= sizeof(double complex));
        assert(sizeof(double complex) <= sizeof(long double complex));

        const double complex zd =  1.0 + 2.0*I;
        const double complex zd2 = 1.0 + 1.0*I;

        //addition
        assert(creal(zd + zd) == 2.0);
        assert(cimag(zd + zd) == 4.0);

        //subtraction
        assert(creal(zd - zd2) == 0.0);
        assert(cimag(zd - zd2) == 1.0);

        //multiplication
        assert(creal(zd * zd) == -3.0);
        assert(cimag(zd * zd) ==  4.0);

        //division
        assert(creal(zd / zd) == 1.0);
        assert(cimag(zd / zd) == 0.0);

        //conjugation
        assert(creal(conj(zd)) ==  1.0);
        assert(cimag(conj(zd)) == -2.0);

        //absolute value == norm == module
        assert(abs(cabs(3.0 + 4.0 * I) - 5.0) < err);

        /*
        #csqrt

            Unlike sqrt, can return imaginary outputs and take imaginary inputs.
        */
        {
            assert(cabs(csqrt(-1.0) - I) < err);
        }

        //cproj
        //TODO0 understand

        //csin
        //TODO0 predict result and assert it
        //assert(cabs(csin(I) - ) < err);

        /*
        #complex integer

            complex integer types are not specified.

            GCC adds them as an extension.
        */
        {
            //int complex zi = 1 + 1*I;
        }
    }

#endif

    /*
    #iso646.h

        obscure header with macros that avoid using characters such as `|` or '~'
        which may be hard to type on certain international keyboards

        full list:

        - and:      &&
        - and_eq:   &=
        - bitand:   &&
        - bitor:    &
        - compl:    |
        - not:      !
        - not_eq:   !=
        - or:       ||
        - or_eq:    |=
        - xor:      ^
        - xor_eq:   ^=
    */
    {
        assert(true and true);
    }

    /*
    #tgmath.h

        TODO

        http://libreprogramming.org/books/c/tgmath/
        http://carolina.mff.cuni.cz/~trmac/blog/2005/the-ugliest-c-feature-tgmathh/
    */
    {
    }

#ifdef PROFILE

    //- turn off optimization if you want results to make evident sense
    //- even without optimization, cache access speed is hard to predict
    //   so what you expect may be false

    loop_only_prof(n_prof_runs);
    while_only_prof(n_prof_runs);

    int_assign_prof(n_prof_runs);
    int_sum_prof(n_prof_runs);
    int_sub_prof(n_prof_runs);
    int_mult_prof(n_prof_runs);
    int_div_prof(n_prof_runs);

    float_sum_prof(n_prof_runs);
    float_sub_prof(n_prof_runs);
    float_mult_prof(n_prof_runs);
    float_div_prof(n_prof_runs);

    func_all_prof(n_prof_runs);
    inline_func_call_prof(n_prof_runs);

    stack1b_prof(n_prof_runs);
    stack1kb_prof(n_prof_runs);
    stack1mb_prof(n_prof_runs);

    heap1b_prof(n_prof_runs);
    heap1kb_prof(n_prof_runs);

    //by far the slowest

        //heap1mbProf(n_prof_runs);

    //BAD:
    //don't do stdout on profiling
    //system time is not counted anyways

        //putsProf(n_prof_runs);

#endif

    /*
    #process address space

        Lets have some fun reverse engeneering the process memory space modeul used on your OS!

        This is all undefined behaviour on ANSI C, but the test code is the same on all OS.

        All of this reflects how the process is represented in main memory.

        Check cheats on each OS to understand the results.
    */
    {
        int stack1;
        int stack2;
        void *heap;
        char *text = "abc";

        printf("PRIxPTR usage = %0*" PRIxPTR "\n", PRIxPTR_WIDTH, (uintptr_t)(void*)1);

#if __STDC_VERSION__ >= 199901L

        printf("processs address space\n");
        printf("  &env    = %0*" PRIxPTR "\n", PRIxPTR_WIDTH, (uintptr_t)getenv("HOME"));
        printf("  &argv   = %0*" PRIxPTR "\n", PRIxPTR_WIDTH, (uintptr_t)argv);
        printf("  &argc   = %0*" PRIxPTR "\n", PRIxPTR_WIDTH, (uintptr_t)&argc);
        printf("  &stack1 = %0*" PRIxPTR "\n", PRIxPTR_WIDTH, (uintptr_t)&stack1);
        printf("  &stack2 = %0*" PRIxPTR "\n", PRIxPTR_WIDTH, (uintptr_t)&stack2);
        heap = malloc(1);
        printf("  &heap   = %0*" PRIxPTR "\n", PRIxPTR_WIDTH, (uintptr_t)heap);
        free(heap);
        printf("  &BSS    = %0*" PRIxPTR "\n", PRIxPTR_WIDTH, (uintptr_t)&BSS);
        printf("  &DATA   = %0*" PRIxPTR "\n", PRIxPTR_WIDTH, (uintptr_t)&DATA);

        //TODO0 why on linux this is not on the text setment,
        //even if modification gives segfault?
            printf("  &text   = %0*" PRIxPTR "\n", PRIxPTR_WIDTH, (uintptr_t)&text);
            //fflush(stdout);
            //text[0] = '0';
#endif

    }

    /*
    #generated code

        The following tests are only interesting to interpret
        the generated assembly code to see how you compiler does things.
    */
    {
        /*
        Does the compiler precalculate values at compile time or not?

        gcc 4.7, O0:

        - asm_precalc:          no
        - asm_precalc_inline:   no
        - sin:                  yes TODO0 why, but not for my funcs?
        */
        {
            int i;
            float f;
            i = asm_precalc(0);
            i = asm_precalc_inline(0);
            f = sin(0.2);
        }
    }

    atexit(atexit_func);
    if (0) exit_func();
    if (0) abort_func();

    /*
    #main return

        Valid returns are:

        - `EXIT_SUCCESS` or `0` to indicate success
        - `EXIT_FAILURE`        to indicate failure

        C99: return is optional. If omited a `return 0` is added to the program.
    */

    // Main returns status:

        return EXIT_SUCCESS;
        return EXIT_FAILURE;
}
