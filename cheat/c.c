/*

#c

* download compiler
* add to path

* memory structure of program
* assembler

* hello world
* spaces, indenting
* comments
* main
* string: "a" == a\0 != 'a'
    * printf("%c<<< null char", '\0');
    * \n, \t, \\, \xnn, \unnnn

* int, float, declare before and after

* printf
    * %%, %d, %f, %.2f, %df, %%

* scanf

* arrays
    * char[] (string, why name)
    * for array
    * array copy function
    * array print func
    * matrix
    * organizatoin on memory: address, operational system division. overflow
    * why not blow up with is[10000000] (< 32 bits, but larger than my RAM!)

* flow control
    * if
    * goto
    * for
        * for inside for (classic)
    * while
    * for vs while

* function
    * return value

* variable types and their computer representation
    * naming rules
    * int 31 bits + sign (binary numbers)
    * float 8 exp + 23 mantissa + 1 sign
    * same name bad

- include

    look in standard dirs directly

    include <file.h>

    look in current dir first:

    include "file.h"

- define, ifded

    debug/multi-platform

#gcc

- warning vs error

- debugging:

    - gdb

        <http://www.dirac.org/linux/gdb/>

- profiling/benchmarking

    - which tool to use
    
        <http://stackoverflow.com/questions/375913/what-can-i-use-to-profile-c-code-in-linux>

    - candidates tools:

        - gdb

            somewhat improvised

        - gprof

            <http://kuscsik.blogspot.com.br/2007/08/how-to-benchmark-c-code-using-gcc.html>

            classical tool

            flat and call graph

        - valgrind
        - google-perftools.
        - oprofile
        - perftools
                sudo aptitude install linux-tools
        - callgrind + KCacheGrind

- optimizations

- language versions

    #ANSI

        language is standardized by an organization named ANSI

        ansi is american, and it represents the USA for ISO and IEC

        you must pay to have the latest standards

        however you can always check open source documentation of compiler/stdlib
        implementations
        
        - C11
            - previously known as c1x
            - current standard, but very limited support in many compilers
            - supported on gcc 4.6> std=c1x
            - threads spported
        - C99
            - not 100% support by many compilers
            - http://en.wikipedia.org/wiki/C99 
            - support for // comments
            - long long, bool, complex numbers
            - gcc: add -std=c99
        - C90
            - microsoft stated that they will not update their compilers
                to C99 and futher. They use c as an inner language, and think
                it would be too delicate/costly to change it. Therefore,
                you will not get those working on ms compiler anytime soon.

    #glibc

        std lib does not come with gcc.

        on default on linux, it comes with glibc, gnu implementation of the c
        stdlib.

        - ubuntu

            - headers for glibc are on ``/usr/include``. do ``locate /stdio.h``

            - lib for glibc are on ``/usr/lib/i386-linux-gnu``. do ``locate /libc.a``

            - the ubuntu package is called ``libc6-dev``. ``dpkg -l | grep libc``

        - docs

           <http://www.gnu.org/software/libc/manual/html_mono/libc.html>

- multithreading/ipc/concurrency

    - c11 supports it, c99 not

        glibc 2.x still does not have it.

    - c++11 supports it, c++03 not

    - openMP is is a library supported on C, C++, fortran, windows, linux macos

    - file io
    - documentation: doxigen

        <http://www.stack.nl/~dimitri/doxygen/docblocks.html>

    - inline

        function is copied pasted instead of called

        effects:

        - avoids function call, thus potentially faster
        - code gets larger
        - function pointer comparisons may differ for the same function
        - instruction cache might be come less efficient making thigs slower

        sources:

        - <http://www.greenend.org.uk/rjk/tech/inline.html>
            
            some warnings about inline and its usage

#hot libraries

    #opengl

        sudo aptitude install freeglut3-dev

    #opencv

        #install ubuntu 12.04

            sudo aptitude install build-essential
            sudo aptitude install libopencv-dev opencv-doc

        not sure the following    are needed in general

            sudo aptitude install libavformat-dev
            sudo aptitude install ffmpeg
            sudo aptitude install libcv2.1 libcvaux2.1 libhighgui2.1 python-opencv opencv-doc libcv-dev libcvaux-dev libhighgui-dev

        now copy the examples and compile run them:

            cp -r /usr/share/doc/opencv-doc/examples ./

        with
        
            opencv2 is the second version released in 2009,

            this is why you have both folders /usr/include/opencv and opencv2

##numerical computation

    - blas/lapack

        fortran converted. de facto basis of current linalg computations
    
    - eigen

        http://eigen.tuxfamily.org/index.php?title=Main_Page

        linear algebra, eqdiffs

    - blitz++

        http://blitz.sourceforge.net/

        linear algebra

    - armadillo

        http://arma.sourceforge.net/

        linear algebra

##scientific computation

that is, applied to specific domains of science

- ODE

    physical engine

        sudo aptitude install libode-dev

- tokamak

    physical engine

- tokamak
*/

//preprocessor
//{
    //does simple stuff *before* compilation
#include <assert.h>
#include <complex.h>
#include <ctype.h>
    //isspace and family
#include <locale.h>
#include <stdarg.h>
    //... variable num of args
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
    //malloc, EXIT_SUCCESS, EXIT_FAILURE
#include <stdio.h>
    //printf, puts
#include <string.h>
    //strlen
#include <math.h>
#include <time.h>
#include <wchar.h> 
//#include <thread.h>
    //not yet implemented for me

#ifdef POSIX
    //POSIX is an operating system standardization by IEEE.
    //followed by Linux and OSX, but not by windows.

    //there are POSIX headers which allow c to do direct system calls
    //on POSIX compliant systems.
    //
    //they allow operations such as:

    //- threads
    //- ipc
    //- filesystem operations
    //- user/group info

    //check: <http://en.wikipedia.org/wiki/C_POSIX_library>
#include <libgen.h>
    //basename, dirname
    //whithout this, one gets the glib.c version
#include <regex.h>
#include <sys/socket.h>
#include <sys/stat.h>    
#include <sys/types.h>
    //lots of typedef types
    //to printf them:
#include <sys/wait.h>
#include <unistd.h>
    //sleep: no portable way
#endif

//#include <linux/limits.h>
    //PATH_MAX max path length on system
 
#define PI 3.14
//BAD
    //use constants instead of defines unless you want to control compilation
    //- constants have scope
    //- produce meaningful error messages
//int PI = 3.14;
    //ERROR
    //PI expands to 3.14
    //compiler reads
    //int 3.14 = 3.14;
    //hard to figure error msg

//GOOD
const int M_PI = 3.14;

#define PI_PLUS_ONE (3.14 + 1)
    //use parenthesis or order of operation might destroy you

//control compilation
#define DEBUG
#ifdef DEBUG
int debugVar;
#endif

#define WINDOWS
#ifdef WINDOWS
int windowsVar;
#endif

//}

//global scope
//{

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
        //cannot create scopes here like that
        //they'd be useless
//}

//pointer array
//{
    int* getArr(int i)
    {
        //int is[] = {i};
        //return is;
            //WARN
            //return adress of local var
            //data is destroyed on return!

        int* ip = (int*) malloc (sizeof(int)*1);
        return ip;
    }

    //cheatsheet on pointers and arrays
    void print_array(int **mat, int m, int n)
    {
        int i, j;
        for(i=0; i<m; i++ )
        {
            for(j=0; j<n; j++ )
            {
                printf("%d ", mat[i][j]);
            }
            printf("\n");
        }
    }
//}

//functions
//{
    //void overload(int n){}
    //void overload(float n){}
        //ERROR no func overload in c

    void fInt(int i){puts("fInt");}
    void fFloat(float f){puts("fInt");}

    void fIntPtr (int *i){}
    void fIntArr (int i[]){}

    //exact same thing

    void withStaticVar()
    {
        int a = 1;
        static int sa = 1;
            //BAD
            //- not thread safe
            //- hard to understand

        a++;
        sa++;

        printf("a = %d, sa = %d\n", a, sa);
    }

    int addInt(int n, int m)
    {
        return n+m;
    }

    int subInt(int n, int m)
    {
        return n-m;
    }

    int intFuncIntInt(int (*functionPtr)(int, int), int m, int n)
    {
        return (*functionPtr)(m, n);
    }

    //struct args
    //{
        struct FuncReturn { int i; };

        struct FuncReturn structReturn( struct FuncReturn sIn )
        {
            struct FuncReturn sOut;
            sOut.i = sIn.i + 1;
            return sOut;
        }
    //}

    int variadicAdd( int numargs, ... )
    {
        va_list listPointer;
        va_start( listPointer, numargs );
        int sum = 0;
        for( int i = 0 ; i < numargs; i++ )
        {
            int arg = va_arg( listPointer, int );
            sum += arg;
        }
        va_end( listPointer );
            //you MUST do this
        return sum;
    }
//}

#ifdef PROFILE

    const static int nProfRuns = 100000000;

    //only the loop.
    //discount this from every other profile run
    void loopOnlyProf(int n)
    {
        int i;
        for( i=0; i<n; i++ );
    }

    void whileOnlyProf(int n)
    {
        int i = 0;
        while( i < n )
        {
            ++i;
        }
    }

    void intAssignProf(int n)
    {
        int i,j;
        for( i=0; i<n; i++ )
            j=1;
    }

    void doNothing(){}

    void funcCallProf(int n)
    {
        int i;
        for( i=0; i<n; i++ )
            doNothing();
    }

    static inline void inlineDoNothing(){}

    void inlineFuncCallProf(int n)
    {
        int i;
        for( i=0; i<n; i++ )
            inlineDoNothing();
    }

    void intSumProf(int n)
    {
        int i, j = 0;
        for( i=0; i<n; i++ )
            j = j + 0;
    }

    void intSubProf(int n)
    {
        int i, j = 0;
        for( i=n; i>0; i-- );
            j = j - 0;
    }

    void intMultProf(int n)
    {
        int i, j = 1;
        for( i=0; i<n; i++ )
            j = j * 1;
    }

    void intDivProf(int n)
    {
        int i, j = 1;
        for( i=0; i<n; i++ )
            j = j / 1;
    }

    void floatSumProf(int n)
    {
        float f;
        int i;
        for( i=0; i<n; i++ )
            f = f + 0.0;
    }

    void floatSubProf(int n)
    {
        float f;
        int i;
        for( i=0; i<n; i++ )
            f = f - 0.0;
    }

    void floatMultProf(int n)
    {
        int i;
        float j;
        for( i=0; i<n; i++ )
            j = j * 1.0;
    }

    void floatDivProf(int n)
    {
        int i;
        float j;
        for( i=0; i<n; i++ )
            j = j / 1.0;
    }

    void putsProf(int n)
    {
        int i;
        for( i = 0; i < n; ++i )
            puts("a");
    }

    void stack1bProf(int n)
    {
        int is[1];
        int i;
        for( i = 0; i < n; ++i )
        {
            int is[1];
        }
    }

    void stack1kbProf(int n)
    {
        int is[1];
        int i;
        for( i = 0; i < n; ++i )
        {
            int is[0x800];
        }
    }

    void stack1mbProf(int n)
    {
        int is[1];
        int i;
        for( i = 0; i < n; ++i )
        {
            int is[0xF0000];
        }
    }
    
    void heap1bProf(int n)
    {
        char* cp;
        int i;
        for( i = 0; i < n; ++i )
        {
            cp = (char*) malloc( sizeof( char ) * 1 );
            free(cp);
        }
    }

    void heap1kbProf(int n)
    {
        char* cp;
        int i;
        for( i = 0; i < n; ++i )
        {
            cp = (char*) malloc( sizeof( char ) * 0x800 );
            free(cp);
        }
    }

    void heap1mbProf(int n)
    {
        char* cp;
        int i;
        for( i = 0; i < n; ++i )
        {
            cp = (char*) malloc( sizeof( char ) * 0xF0000 );
            free(cp);
        }
    }

#endif

//algorithms
//{
    //simple fun algorithms

    //random
    //{
        float rand_range(float a, float b)
        { //float in a range
            return ((b-a)*((float)rand()/RAND_MAX))+a;
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
//}

//file io
//{
    void report_cant_open_file (char * path){
        fprintf(stderr, "could not read from:\n%s\n", path);
    }

    void report_cant_read_file (char * path){
        fprintf(stderr, "could not read from:\n%s\n", path);
    }

    void report_cant_move_file (char * path){
        fprintf(stderr, "could not move in file:\n%s\n", path);
    }

    void report_cant_write_file (char * path){
        fprintf(stderr, "could not write to:\n%s\n", path);
    }

    void report_cant_close_file (char * path){
        fprintf(stderr, "could not close from:\n%s\n", path);
    }

    void report_cant_allocate_file (size_t bytes){
        fprintf(stderr, "could not allocate %zu bytes", bytes);
    }

    //opens file at given path, calculates its size, and closes and returns size
    long file_size_open(char *path)
    {
        FILE *fp = fopen(path, "r");
        if (fp == NULL){
            report_cant_open_file(path);
            return -1L;
        }
        if ( fseek (fp, 0 , SEEK_END) != 0 ){
            report_cant_move_file(path);
            return -1L;
        }
        long l = ftell (fp);
        if ( l == -1L ){
            report_cant_move_file(path);
            return -1L;
        }
        if ( fclose(fp) == EOF ){
            report_cant_close_file(path);
            return -1L;
        }
        return l;
    }

    //returns the size of the given open file pointer
    long file_size(FILE *fp)
    {

        long oldpos = ftell (fp);
        if ( oldpos == -1L ){
            return -1L;
        }

        if ( fseek (fp, 0 , SEEK_END) != 0 ){
            return -1L;
        }

        long l = ftell (fp);
        if ( l == -1L ){
            return -1L;
        }

        //retore old position
        if ( fseek (fp, oldpos , SEEK_SET) != 0 ){
            return -1L;
        }

        return l;

    }

    //reads the entire file to a char[]
    //returns a pointer to the start of that array 
    //memory is dynamically allocated, so caller must free it!
    //if any problem happens, returns NULL
    char * file_read(char *path)
    {
        FILE * fp;
        long l;
        char * buffer;
        size_t bytes;

        fp = fopen ( path , "rb" );
        if (fp==NULL) {
            report_cant_open_file(path);
            return NULL;
        }

        // obtain file size:
        l = file_size(fp);
        if (l < 0){
            fprintf(stderr, "could not determine lenght of:\n%s\n", path);
            return NULL;
        }

        // allocate memory to contain the whole file:
        bytes = sizeof(char)*l;
        buffer = (char*) malloc (bytes);
        if (buffer == NULL) {
            report_cant_allocate_file(bytes);
            return NULL;
        }

        // copy the file into the buffer:
        if ( fread (buffer,1,l,fp) != l ) {
            report_cant_read_file(path);
            return NULL;
        }

        /* the whole file is now loaded in the memory buffer. */

        if ( EOF == fclose (fp) ){
            report_cant_close_file(path);
            return NULL;
        }

        return buffer;
    }


    //write null terminated string to file
    //returns -1 on fail
    int file_write(char *path, char *s)
    {
        FILE * fp;
        long l;
        char * buffer;
        size_t bytes;

        fp = fopen ( path , "wb" );
        if (fp==NULL) {
            report_cant_open_file(path);
            return -1;
        }

        l = strlen(s);

        // copy the file into the buffer:
        if ( fwrite (s,1,l,fp) != l ) {
            report_cant_write_file(path);
            return -1;
        }

        if ( EOF == fclose (fp) ){
            report_cant_close_file(path);
            return -1;
        }

        return 0;
    }

    //writes an array of ints to a file
    //
    //ints are space separated, with a trailling space
    //
    //on errror, returns, -1, succes 0
    int write_int_arr_file(char * path, int *arr, int len)
    {
        int i;
        FILE * fp = fopen(path,"w");

        if (fp == NULL)
        {
            report_cant_open_file(path);
            return -1;
        }

        for(i=0; i<len; i++ ){
            if ( fprintf(fp,"%d ", arr[i]) < 0 ){
                report_cant_write_file(path);
                return -1;
            }
        }
            
        if ( EOF == fclose (fp) ){
            report_cant_close_file(path);
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
            report_cant_open_file(path);
            return -1;
        }

        for(i=0; i<len; i++ ){
            /*if ( fprintf(fp,format, arr[i]) < 0 ){*/
            if ( fprintf(fp,"%.*e", precision, arr[i]) < 0 ){
                report_cant_write_file(path);
                return -1;
            }
        }
            
        if ( EOF == fclose (fp) ){
            report_cant_close_file(path);
            return -1;
        }

        return 0;
    }
//}

int main(int argc, char** argv)
{
    //base types and variables
    {
        //inner scopes inside functions
        {
            int i;
            //int i;
                //ERROR redeclaration
            {
                int i;
                //NOTE
                    //impossible to access the outer i now
            }
        }

        //variable declare/init
        {
            //allowed variable/function/struct,enum names: _[a-Z0-9_]*
            {
                int _;
                //int 0a;
                    //ERROR
            }
            
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

        //base types and their constants
        {
            //integer types
            {
                char c = 'a';
                char c1 = (char)1;
                unsigned char uc = (unsigned char)1;
                    //must typecast

                short int si = (short int)1;
                int i = 1;
                long int li = (long int)1l;
                long long lli = 8ll;
                    //C99

                unsigned short int usi = (unsigned short int)1u;
                    //must typecast
                unsigned int ui = 1u;
                unsigned long int uli = 1lu;
                unsigned long long int ulli = 1llu;

                //integer constants
                //{
                    //by default, are of the first of the following types
                    //that can represent the value (this is machine dependant):
                    //
                    //int
                    //unsigned int
                    //long int
                    //unsigned long int
                    //long long int
                    //unsigned long long int
                    //ERROR
                //}
            }

            //float types
            {
                float f = 1.23f;
                    //1 signal 23 number 8 exponent
                float f1 = 1.23e-10f;
                float f2 = 1.f;
                //float f = 1f;
                    //ERROR
                    //there must be a dot

                double d = 1.23;
                long double ld = 1.23;
            }
        }

        //sizeof
        {
            //stardard does not specifies exact sizes
            //for machine indepencence

            size_t size = sizeof(int);
 
            puts("sizeof (bytes):");
            printf( "char        = %zu\n",  sizeof(char)        );
            printf( "int         = %zu\n",  sizeof(int)         );
            printf( "long int    = %zu\n",  sizeof(long int)    );
            printf( "long long   = %zu\n",  sizeof(long long)   );
            printf( "float       = %zu\n",  sizeof(float)       );
            printf( "double      = %zu\n",  sizeof(double)      );
            printf( "long double = %zu\n",  sizeof(long double) );
            printf( "wchar_t     = %zu\n",  sizeof(wchar_t)     );
            printf( "size_t      = %zu\n",  sizeof(size_t)      );

            assert( sizeof( short int ) <= sizeof( int )            );
            assert( sizeof( int )       <= sizeof( long int )       );
            assert( sizeof( long int )  <= sizeof( long long int )  );

            assert( sizeof( float )     <= sizeof( double )         );
            assert( sizeof( double )    <= sizeof( long double )    );
                //equality is always possible!
            
            assert( sizeof( unsigned int ) == sizeof( int ) );
            assert( sizeof( unsigned long int ) == sizeof( long int ) );
                //unsigned does not change sizeof
        }

        //unsigned
        {
            //applications:
                //array indexes
                //memory sizes (size_t)

            assert( (char)-1 == (char)255 );
            assert( (unsigned char)-1 == (unsigned char)255 );
                //true in 2's complement

            assert( (char)0 > (char)255 );
                //true in 2's complement
            assert( (unsigned char)0 < (unsigned char)255 );
                //what we really want
        }

        //overflow
        {
            //there is no automatic overflow check on operations
            //except at initialization

            //char c = 256;
            //char c = 255+1;
            //unsigned char c = 257;
                //WARN
            
            //lli = 0x10000000000000000;
                //WARN constant too large (even for long long, the largest type)

            //char c = 255;
            //c++;
                //WARN

            assert( 1.00000000000000000000000000000000000000000000001 == 1.0 );
                //OK
                //lost of precision is not checked
        }

        //other bases for integers
        {
            assert( 16 == 0x10    );
            assert( 16 == 0x10    );
            assert( 16 == 0x10l   );
            assert( 16 == 0x10ll  );
            assert( 16 == 0x10u   );
            assert( 16 == 0x10ul  );
            assert( 16 == 0x10ull );
                //hexa
            assert( 16 == 020 );
                //octal
            //assert( 16 == 0b10000 );
                //GCC
                //binary
        }

        //typecast
        {
            float f = 1.0;
            float f2 = (float)1.0;
            double d;
            d = f;
            f = d;

            printf("(double).1f = %f\n", (double).1f); //float to double
                //WARN possible
            printf("(float).1 = %f\n", (float).1); //double to float
                //WARN possible
            printf("(int).1f = %d\n", (int).1f);
                //WARN possible
            printf("(int)1L = %d\n", (int)1L); //long to int
            printf("(long)1 = %ld\n", (long)1); //int to long

            printf("(int*)&f = %p\n", (void*)&f); //any pointer typecast is ok to compiler
            printf("(int)&f = %d\n", (int)&f);   //memory address of pointer

            int is3[3];
            int is4[4];
            int* ip = (int*)is3; //is[3] to int*
            //ERROR
                //is3=(int[3])is4;
            //ERROR pointer to int[]
                //is3=is4;
        }
        
        //const
        {
            int i = 0;
            const int ic = 0;
            //int const ic = 0
                //exact same thing!
            const int ic2 = i;

            //ic = 1;
                //ERROR
                //consts are... almost consts!
                //(you can change them with a warning)
            
            //int i = 0;
            //const int i = 0;
                //ERROR
                //i already defined

            //ip = &ic;
            //*ip = 2;
                //WARN: discards const. in c++, error!
                //we changed the const!
                //this is why you can't int is[constint]; !!
                //because you can compile with only a warning and change a const
                
            //const pointers
            {
                //3 types:
                    //const*
                    //*const
                    //const*const
            
                const int* cip = &ic;
                //SAME
                    //int const* icp = &ic;
                cip = &ic2;
                //ERROR: const prevents from changing value
                    //*cip = 2;

                const int ic3;
                    //BAD
                    //compiles without warning, but is bad since ic3 cannot get a value
                    //unless you typecast its pointer with a warning

                //int * const ipc = &ic;
                    //WARN

                //ipc = &ic2;
                    //ERROR: this time what the address the pointer points to is constant
                    //not its value!
                //*ipc = 2;
                    //BAD: we changed the value!
                
                const int* const cipp = &ic;

                const int cis2[2] = {1,2};
                //ERROR
                    //cis2[0] = 1;
            }

            {
            //scanf("%d",&i);
            //const 
                //NOTE
                //consts are *not* "compile time constants"
                //they are only constant after they are declared
                //this is another reason why you can't use them
                //as arrays sizes without VLA
            }
        }

        //automatic
        {
            //no keyword, but is the name for the default way to declare var
            //that is not volatile neither register
            int i;
        }
        //volatile
        {
            volatile int vi;
                //compiler will not store this value in cpu registers as optimization
                //instead of in RAM
                //application:
                    //multithreading, where variable may to change value at any time
                    //if value were stored in register, other threads could not modify it
        }

        //register
        {
            {
                register int ri;
                    //hint to compiler that ri be stored in register
                    //instead of in RAM
                    //
                    //not necessarily honored
                    //
                    //almost always done without a hint if possible
            }
            
            {
                //register int ri;
                //int* ip = &ri;
                    //ERROR
                    //cpu registers don't have addresses!
            }

            {
                struct S { int i; };
                register struct S s;
                    //BAD
                    //impossible to store compound type in registers
                    //compiler will certainly not honor ``register`` hint
            }
        }
    }

    //typedef
    {
        //on stdlib, convention append "_t" to typedefs is used
        //ex: ``size_t``, ``wchar_t``, etc
        
        {
            typedef int NEWINT;
            NEWINT i = 1;
            assert( sizeof(NEWINT) == sizeof(int) );
        }

        //NEWINT i = 1;
            //typedef has scope
    }

    //enum
    {
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

            //typedef combo
                typedef enum E F;
                F f;

                typedef enum G {g1,g2} G;
                G g;

            //by default, values start from 0 and increases
                assert( E1 == 0);
                assert( E2 == 1);
                assert( E3 == 2);
                assert( E4 == 3);
        }

        {
            enum E        
            {
                E1 = 1,   
                E2 = 2,
                E3 = 2, //equal values are ok
                E4,
            };
                //you can choose the values

            assert( E1 == 1);
            assert( E2 == 2);
            assert( E3 == 2);

            //if you don't give a value
            //it gets a value different from all others
                assert( E4 != E1);
                assert( E4 != E2);
                assert( E4 != E3);
        }
    }

    //struct
    {
        //application:
            //delcare/pass to funcs
            //lots of different typed data
            //in one go
        struct S
        {
            int i;
            float f;
        };

        {
            struct S s = { 1, 1.0 };
                //- list init
                //- only possible for contiguous (non pointer) data
                //- overwrides outter struct
            assert( s.i == 1 );
            assert( s.f == 1.0 );

            s.i = 2;
            s.f = 2;
            assert( s.i == 2 );
            assert( s.f == 2.0 );
        }

        {
            struct S s = { .f = 1.0, .i = 1 };
            assert( s.i == 1 );
            assert( s.f == 1.0 );
        }

        //pointer to struct
        {
            struct S s;
            struct S* sp;
            sp = &s;
            (*sp).i = 1;
            assert( s.i == 1 );
        }

        //arrays
        {
            struct S
            {
                //char cs[];
                    //ERROR
                char cs[4];
            };

            //struct S = { .cs = "abc" }
                //ERROR
        }

        {
            struct S {int i;} s = {1}, s2 = {2};
            int               i = 1  , i2 = 2;
        }

        //assign
        {
            struct S s  = { 1, 1.0 };
            struct S s2 = { 2, 2.0 };
            s = s2;
            assert( s.i == 2 );
            assert( s.f == 2.0 );
        }

        //typedef
        {
            typedef struct
            {
                int i;
            } S;

            S s = {1};
            S* sp = &s;
        }

        //struct size
        {
            //the way data is packed in a struct is not specified in the standard
            //common compiler strategy: put one data per 32 bits
            //makes acess faster, using slightly more memory
            assert( sizeof(int) + sizeof(float) <= sizeof(struct S) );

            struct S
            {
                char c1;
                char c2;
            };
        }

        //bitfields
        {
            //*i think* enforces the field size
            
            struct S
            {
                unsigned b1 : 1;
                unsigned b2 : 2;
                unsigned b3 : 3;
                    //adds padding to next int
                int i;
                unsigned b4 : 1;
                unsigned : 0;
                    //adds padding to next int
                unsigned b5 : 1;
            } s ;
            assert( sizeof(struct S) == 16 );

            s.b1 = 1;
            assert( s.b1 == 1 );

            //s.b1 = 2;
                //WARN
                //overflow
                //truncate
            
            int i = 2;
            s.b1 = i;
            assert( s.b1 == 0 );

            i = 3;
            s.b1 = i;
            assert( s.b1 == 1 );
                //only takes lsb
        }
    }
    
    //operators
    {
        //arithmetic
        {
            assert( ( 1 + 2 )        == 3   );
            assert( ( 2 * 3 )        == 6   );
            assert( ( 4 / 2 )        == 2   );
            assert( ( 1 / 2 )        == 0   );
            assert( ( 1.0 / 2.0 )    == 0.5 );
            assert( ( 1 / 2.0 )      == 0.5 );
            assert( ( 1 / (double)2) == 0.5 );

            assert( ( 3 % 3 ) == 0 );
            assert( ( 4 % 3 ) == 1 );
            assert( ( 5 % 3 ) == 2 );
            assert( ( 6 % 3 ) == 0 );
        }

        //boolean
        {
            assert( ( 1 == 1 ) == 1 );
            assert( ( 0 == 1 ) == 0 );

            assert( ( 0 >  1 ) == 0 );
            assert( ( 0 >  0 ) == 0 );
            assert( ( 0 > -1 ) == 1 );
            assert( ( 0 <  1 ) == 1 );
            assert( ( 0 <  0 ) == 0 );
            assert( ( 0 < -1 ) == 0 );

            assert( ( 0 >=  1 ) == 0 );
            assert( ( 0 >=  0 ) == 1 );
            assert( ( 0 >= -1 ) == 1 );
            assert( ( 0 <=  1 ) == 1 );
            assert( ( 0 <=  0 ) == 1 );
            assert( ( 0 <= -1 ) == 0 );
        }

        //bitwise
        {
            //NOT
            assert( (~(char)0x00) == (char)0xFF );
            assert( (~(char)0xFF) == (char)0x00 );

            //OR
            assert( ((char)0x00 & (char)0x00 ) == (char)0x00 );
            assert( ((char)0xFF & (char)0x00 ) == (char)0x00 );
            assert( ((char)0xFF & (char)0xFF ) == (char)0xFF );

            //XOR
            assert( ((char)0x00 ^ (char)0x00 ) == (char)0x00 );
            assert( ((char)0xFF ^ (char)0x00 ) == (char)0xFF );
            assert( ((char)0xFF ^ (char)0xFF ) == (char)0x00 );

            //shift
            assert( ( 1 << 0 ) == 1 );
            assert( ( 1 << 1 ) == 2 );
            assert( ( 1 << 2 ) == 4 );
            assert( ( 1 << 3 ) == 8 );

            assert( ( 8 >> 0 ) == 8 );
            assert( ( 8 >> 1 ) == 4 );
            assert( ( 8 >> 2 ) == 2 );
            assert( ( 8 >> 3 ) == 1 );
            assert( ( 8 >> 4 ) == 0 );
            assert( ( 5 >> 1 ) == 2 );
        }

        //assign
        {
            int i = 0;
            assert( (i=1) == 1 );
            //= returns right side
            assert( i == 1 );

            //increment
                //http://stackoverflow.com/questions/24886/is-there-a-performance-difference-between-i-and-i-in-c
                //which is faster?
                //- in c, equal
                //- in c++, ++i potentially if i is a complex object
                //why it exists if equivalent to x=x+1?
                //- because there is an x86 instruction for that
                //why?
                //- because it takes less program memory ``inc eax``, instead of ``sum eax,1``
                //- and is a *very* common instruction
                //what about +=, -=, etc. ?
                //- same thing: ``ax = ax + bx`` == ``sum ax,bx``

                i=0;
                assert( i++ == 0 );
                assert( i == 1 );

                i=0;
                assert( ++i == 1 );
                assert( i == 1 );

                i=1;
                assert( i-- == 1 );
                assert( i == 0 );

                i=1;
                assert( --i == 0 );
                assert( i == 0 );

                double f = 0.0;
                assert( f++ == 0.0 );
                assert( f == 1.0 );

                i=0;
                assert( ( i += 1 ) == 1 );
                assert( i == 1 );

                i=1;
                assert( ( i -= 1 ) == 0 );
                assert( i == 0 );

                i=1;
                assert( ( i *= 2 ) == 2 );
                assert( i == 2 );

                i=2;
                assert( ( i /= 2 ) == 1 );
                assert( i == 1 );

                i=3;
                assert( ( i %= 2 ) == 1 );
                assert( i == 1 );

                i=0xFF;
                assert( ( i &= (char)0x00 ) == (char)0x00 );
                assert( ( (char)i == (char)0x00 ) );

                //same others bitwise, except ~=
        }

        //question mark
        {
            assert( ( 1 < 2 ? 3 : 4 ) == 3 );
            assert( ( 1 > 2 ? 3 : 4 ) == 4 );
        }

        //pointer
        {
            int i;
            int* pi, *pi2;
            //*pi = 7;
                //BAD
                //you are modifying some random piece of memory!!!!
                //must declare like that: multiple stars
            pi = &i;
            *pi = 1;
            assert( i == 1 );
            assert( *pi == 1 );
            i = 2;
            assert( i == 2 );
            assert( *pi == 2 );

            printf("(void*)pi = %p\n",(void*)pi);
            printf("(void*)(pi+1) = %p\n",(void*)(pi+1));
            printf("NULL = %p\n",NULL);

            pi2 = pi + 1;
            printf("(void*)(pi2-pi) = %p\n",(void*)(pi2-pi));
            assert( pi2 - pi == 1 );
                //OK
                //implicit conversion * -> int

            //float* fp = &i;
                //ERROR
                //incompatible pointer type
        }

        //array
        {
            {
                {
                    int is[3];
                    is[0] = 0;
                    is[1] = 1;
                    is[2] = 2;
                    assert( is[0] == 0 );
                    assert( is[1] == 1 );
                    assert( is[2] == 2 );
                }

                {
                    int is[] = {0,1,2};
                    assert( is[0] == 0 );
                    assert( is[1] == 1 );
                    assert( is[2] == 2 );
                        //allocates exact size
                    //is = {3,4,5};
                        //ERROR
                }
                
                {
                    int is[4] = {1,2};
                    assert( is[0] == 1 );
                    assert( is[1] == 2 );
                    assert( is[2] == 0 );
                    assert( is[3] == 0 );
                }
                
                {
                    //int is[2] = {1, 3, 2};
                        //WARN too small
                }

                //variable length
                {
                    //enum
                    {

                        enum M {M=3};
                        int is[M];
                        is[2] = 1;

                    }

                    //define
                    {
#define DEFINESIZE 3
                        //BAD
                        //*no scope*, so you can't use N anymore.
                        //use enum instead
                        int is[DEFINESIZE];
                        is[2] = 1;
                    }

                    //VLA
                    {
                        //- C99
                        //- implementation:
                            //increase/decrease stack pointer
                            //requires one addition and one multiplication per declaration
                        {
                            int n = 2;
                            //scanf( "%d", &n );
                                //OK
                            int isVla[n];
                        }

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
                    }
                }
            }
    
            //pointers and arrays are different
            {
                puts("pointers and arrays are different types:");
                printf("sizeof(int) = %d\n",sizeof(int));
                printf("sizeof(int*) = %d\n",sizeof(int*));
                printf("sizeof(int[3]) = %d\n",sizeof(int[3]));
                //printf("sizeof(int[]) = %d\n",sizeof(int[]));
                    //ERROR
                    //incomplete type!
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
                for(i=0; i<3; i++ )
                {
                    printf("%d ",is[i]);
                }
            }

            {
            //BAD
                //overflow

                //printf("%d\n",is[3]);
                //is[3]=0;
                //printf("%d\n",is[1000000]);
                //is[1000000]=0;

                //for(i=0; i<=1000000000; i++ ){
                //        printf("%d\n",i);
                //        j=is[i];
                //}
                //    segmentation fault
                
                /*printf("%d\n",is[100000]);*/
                //might run: only get segmentation fault if you hit exactly the last position!
            }

            //compare
            {
                //memcmp is faster than for loop
                //one catch: float NaN

                int is[]  = { 0, 1, 2 };
                int is2[] = { 0, 1, 2 };

                assert( is != is2 );
                    //compares addresses, not data!
                
                assert( memcmp( is, is2, 3 * sizeof(int)) == 0 );
                is[1] = 0;
                assert( memcmp( is, is2, 3 * sizeof(int)) < 0 );
                is[1] = 2;
                assert( memcmp( is, is2, 3 * sizeof(int)) > 0 );
            }

            //copy
            {
                int is[] = {0,1,2};
                int is2[3];

                //for(i=0; i<3; i++ ){
                //    is2[i] = is[i];
                //}
                    //SLOW
                    //use memcpy insted

                memcpy(is2,is,3*sizeof(int));
                    //copy 3*4 bytes from one is7 to is
                    //more efficient than for: direct memory copyint, no i++ or i<n? check
                assert( memcmp( is, is2, 3 * sizeof(int)) == 0 );
        
                memcpy(&is, &(int [5]){ 0,1,2 }, sizeof(is) );
                    //C99
                assert( memcmp( is, &(int [5]){ 0,1,2 }, 3 * sizeof(int)) == 0 );
            }

            //multidim
                //BAD
                //never use this
                //always use single dim
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
                            for( i = 0; i < mc; i++ )
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
                    for( i = 0; i < 2; i++ )
                    {
                        printf( "\n" );
                        for( j = 0; j < 3; j++ )
                        {
                            printf( "%d ", m1[i][j] );
                        }
                    }
                    printf( "\n\n" );
                }
            }

            //string
            {
                {
                    char cs[] = "abc";
                    //char cs[] = {'a','b','c','\0'}
                        //SAME
                        //BAD
                        //harder to write
                        //you may forget the '\0'
                    assert( cs[0] == 'a'  );
                    assert( cs[1] == 'b'  );
                    assert( cs[2] == 'c'  );
                    assert( cs[3] == '\0' );
                        //NOTE
                        //use '\0' always
                        //c std functions use that to see where string ends
                    
                    cs[0] = 'A';
                    assert( strcmp(cs,"Abc") == 0 );

                    //cs = "Abc";
                        //ERROR
                }

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
                    printf(">>>%c<<< null char\n",'\0');
                    puts(">>>\x61<<< a in hexadecimal");
                    puts(">>>\xe4\xb8\xad<<< chinese for \"middle\" in utf8");
                        //chinese utf8
                }

                //can create use across lines.
                //no newline added.
                {
                    char cs[] = "ab"
                                "cd";
                    assert( strcmp( cs, "abcd" ) == 0 );
                }

                //std string functions
                {
                    //use '\0' to see ther string ends

                    //printf, sprintf
                    {
                        char cs[] = "abc";
                        char cs2[4];
                        sprintf(cs2, "%s", cs );
                        assert( strcmp( cs, cs2 ) == 0 );
                    }

                    //length
                    {
                        char cs[] = "abc";
                        assert( strlen(cs) == 3 );
                    }

                    //copy
                    {
                        char cs[] = "abc";
                        char cs2[4];
                        char cs3[1];

                        strcpy( cs2, cs );
                            //more efficient than for loop
                        strcpy( cs2, "abc" );
                            //OK
                        //strcpy( cs3, "abc" );
                            //BAD
                            //no born checking as always
                    }

                    //compare
                    {
                        char cs[] = "abc";
                        char cs2[] = "abc";
                        assert( strcmp( cs, cs2 ) == 0 );
                        assert( strcmp( cs, "abc" ) == 0 );
                            //equality
                        cs[1] = 'a';
                        assert( strcmp( cs, cs2 ) < 0 );
                            //smaller
                        cs[1] = 'd';
                        assert( strcmp( cs, cs2 ) > 0 );
                            //larget
                    }
    
                    //cat
                    {
                        
                        char s1[5];
                        strcpy( s1, "ab" );
                        char s2[] = "cd";
                        strcat( s1, s2 );
                        assert( strcmp( s1, "abcd" ) == 0 );
                        assert( strcmp( s2, "cd"   ) == 0 );
                    }
                        
                    //strchr
                    {
                        //search for char in string
                        //return pointer to that char if found
                        //return null if not found
                        {
                            char cs[] = "abcb";
                            assert( strchr( cs, 'b' ) == cs + 1 );
                            assert( strchr( cs, 'd' ) == NULL );
                        }
                    
                        //find all occurences of c in cs
                        {
                            //no direct std for this
                            
                            char cs[] = "abcb";
                            char* cp;
                            char c = 'b';
                            int is[] = { 1, 3 };

                            int i = 0;
                            cp = strchr( cs, c );
                            while( cp != NULL )
                            {
                                assert( cp - cs == is[i] );
                                cp = strchr( cp + 1, c );
                                ++i;
                            }
                        }
                    }

                    //isspace
                    {
                        assert(   isspace( ' '  ) );
                        assert(   isspace( '\n' ) );
                        assert( ! isspace( 'a'  ) );
                    }

                    //isdigit
                    {
                        assert(   isdigit('0') );
                        assert( ! isdigit('a') );
                    }
                }
        
                //text segment
                {
                    char* cs = "abc";
                    assert( cs[0] == 'a' );
                        //NOTE
                        //points to the text segment
                        //very memory efficient
                    
                    //cs[0] = 'a';
                        //ERROR
                        //text segment cannot me modified
                    
                    //int * is = {1, 3, 2};
                        //WARN
                        //can't do this
                        //think:
                        //- chars are exactly as in the text segment
                        //- integer 1 is not represented as a single byte char '1'
                        //    but as 4 bytes
                }

                //unicode
                {
                    char cs[] = "汉语";
                    printf("%s\n",cs);

                    //cs[0] = 'a';
                    //printf("%s\n",cs);
                        //BAD
                        //only changes first byte
                        //you get trash all over
                    
                    //cs[0] = '英';
                        //WARN

                    setlocale( LC_CTYPE, "" );
                        //NOTE
                        //need this to print correctly

                    wchar_t  wcs[] = L"汉语";

                    printf( "%ls\n", wcs );

                    wcs[0] = L'英';
                    printf( "%ls\n", wcs );

                    wcs[0] = L'a';
                    printf( "%ls\n", wcs );

                    //wchar_t  wideString2[] = "asdf";
                        //ERROR
                        //non wide init
                }
            }
        }

        //dynamic
        {
            //vs VLA
            //- no scope
            //
            //      therefore can be allocated in functions
            //      and returned to caller
            //
            //- heap much larger than stack

            int i = 8;
            size_t bytes = sizeof(char)*i;
            char* cp = (char*) malloc (bytes);
            if( cp == NULL )
            {
                printf("could not allocate %zu bytes", bytes);
            }
            free(cp);
        }

        //comma operator
        {
            //almost useless
            int i=0, a=1, b=2, c=3; //comma here is separator, not operator. same comma in functions calls/defs

            assert( ( i = 0, 1        ) == 1 );  
            assert( ( i = 0, i = 1, 2 ) == 2 );             
                //ignores values on left
                //takes only last value on right
                //
                //WARN
                //operations on left has no effect

            i = 2;
            (i = 0), 1;
            i = 0, 1;
            assert( i == 0);
                //assign has precedence
                //
                //WARN
                //operation on right has no effect

            //int j=0, 1;
                //ERROR
                //declaration int j does not return a value

            i=2;
            assert( (i=0, i) == 0);
            i=2;
            assert( (i=0, i++, i) == 1);
                //operation on left comes first
        } 
    }

    //branching
    {

        //goto
        {
            //never use this
            //tranlates to ``jmp`` in x86 isa

            goto a;
                assert(0);
            a:
            assert(1);
        }

        //if
        {
            if(-1)
            {
                assert(1);
            } 
            if(0)
            {
                assert(0);
            } 
            if(1)
            {
                assert(1);
            } 

            //scope
            {
                int i = 0;
                if(1)
                {
                    int i = 1;
                    assert( i == 1 );
                }
            }

            //stdbool.h
            {
                //C99

                //bool b = true;
                    //ERROR
                    //no booleans true false in c, ints only! c++ only.
                    //can use stdbool.h

                bool b = true;
                bool b2 = false;
                assert( true  == 1 );
                assert( false == 0 );
            }

            //stdint.h
            {
                //c99
                //N = 8, 16, 32, 64

                { int32_t i; }
                //exactly 32 bits

                { int_least32_t i; }
                //at least 32 bits
            
                { int_fast32_t i; }
                //fastest operations with at least 32 bits
                
                { intptr_t i; }
                //can hold pointer
                //uniquelly defined by machine address space
                
                { intmax_t i; }
                //max possible width

                { uint32_t i; }
                //all have unsigned verions prefixed by 'u'
                
                {
                    {
                        int32_t i = 0;
                        assert( INT32_MIN < i );
                        assert( INT32_MAX > i );
                    }

                    {
                        int_fast32_t i = 0;
                        assert( INT_FAST32_MIN < i );
                        assert( INT_FAST32_MAX > i );
                    }
                }
                //all have max/min ranges
                //"_t" removed, "_max" or "_min" appended, all uppercased

            }
        }

        //switch
        {
            int i, j;
            for( i=-1; i<3; i++ )
            {
                switch(i)
                {
                    case 0:

                        assert(i==0);

                        int j;
                            //OK
                            //new inner scope
                        
                        //int i = 1;
                            //ERROR
                            //redeclaration

                        break;

                    case 1:

                        assert(i==1);

                        //int j;
                            //ERROR
                            //single inner scope

                        break;

                    default:
                        assert( i!=0 && i!=1 );
                        break;
                }
            }
        }

        //for
        {
            //basic
            {
                //in theory, whatever you can to with for you can do with while
                //
                //why it exists then?
                //- because x86 has a loop instruction that increments and
                //   contional jumps in a single step
                //
                //   therfore, using a simple for is more likely to tell your
                //   compiler to use this more efficient looping instruction
                //
                //moral:
                //if you when know how many loops you will do, use ``for``
                //otherwise use ``while``

                int i;
                int is[] = { 0, 1, 2 };
                for( i = 0; i < 3; ++i )
                {
                    assert( i == is[i] );
                    int i;
                        //OK new scope
                }
                assert( i == 3 );
            }

            //single line
            {
                int i;
                int is[] = { 0, 1, 2 };
                for( i = 0; i < 3; ++i )
                    assert( i == is[i] );
                    //int i;
                        //ERROR
                        //redeclaration
                        //note different if bracketes used
            }

            //putting int i=0 inside for
            {   
                //C99
                int is[] = {0,1,2};
                for( int i = 0; i < 3; ++i )
                {
                    assert( i == is[i] );
                    //int i;
                        //ERROR
                        //redeclaration
                }
            }
            
            //one of the few uses of the comma operator
            {
                int is[] = {0,1,2};
                int js[] = {0,1,2};
                for( int i=0, j=0; i*j<5; i++, j++ )
                {
                    assert( i == is[i] );
                    assert( i == js[i] );
                }
            }
            
            //nested loops
            {
                int n = 0;
                int is[] = {0,0,1,1};
                int js[] = {0,1,0,1};
                for( int i=0; i<2; i++ )
                {
                    for( int j=0; j<2; j++ )
                    {
                        assert( i == is[n] );
                        assert( j == js[n] );
                        n++;
                    }
                }
            }
        }

        //while
        {
            {
                int i=0;
                int is[] = {0,1,2};
                while(i<3)
                {
                    assert( i == is[i] );
                    i++;	    
                }
                assert( i == 3 );
            }

        }

        //functions
        {
            //automatic conversions
            {
                fInt(1.0);
                fFloat(1);
            }

            puts("static variable in functions");
            {
                withStaticVar();
                    //a = 2, sa = 2
                withStaticVar();
                    //a = 2, sa = 3
            }

            puts("func pointers");
            {
                assert( addInt != subInt );
                assert( intFuncIntInt(&addInt,2,1) == 3 );
                assert( intFuncIntInt(&subInt,2,1) == 1 );
            }

            //func in func
            {
                //UNPORTABLE
                //gnu extension
                //not standard
                //printf("fOut() = %d",fOut());
            }

            //variable num of args ...
            {
                assert( variadicAdd( 3, 1, 2, 3 )       == 6 );
                assert( variadicAdd( 5, 1, 2, 3, 4, 5 ) == 15 );
            }
        }
    }

    puts("command line args");
    {
        printf("%s",argv[0]);
        int i = 0;
        if ( argc > i )
        {
            i++;
            printf( "%s", argv[i]);
        }
        if ( argc > i )
        {
            i++;
            printf( "%s", argv[i]);
        }
    }

    //preprocessor
    {
        {
#define A B
#define B 1
            //BAD
                //you can put preprocessor directives anywhere
                //but putting on global scope is the more standard and simple approach
            assert( A == 1 );
        }

        {
#ifdef COMMANDLINE
            //gcc -DCOMMANDLINE c.c
            puts("C");
#else
            //gcc c.c
            puts("no C");
#endif
        }
    }

    //stdlib
    {
        //complex.h
        {
            //C99
            //int complex zi = 1 + 1*I;
                //GCC
            assert( sizeof( float complex  ) <= sizeof( double complex ) );
            assert( sizeof( double complex ) <= sizeof( long double complex ) );

            const double complex zd =  1.0 + 2.0*I;
            const double complex zd2 = 1.0 + 1.0*I;

            assert( creal( zd + zd ) == 2.0 );
            assert( cimag( zd + zd ) == 4.0 );

            assert( creal( zd - zd2 ) == 0.0 );
            assert( cimag( zd - zd2 ) == 1.0 );

            assert( creal( zd * zd ) == -3.0 );
            assert( cimag( zd * zd ) ==  4.0 );

            assert( creal( zd / zd ) == 1.0 );
            assert( cimag( zd / zd ) == 0.0 );

            assert( creal( conj(zd) ) ==  1.0 );
            assert( cimag( conj(zd) ) == -2.0 );
        }

        puts("stdlib");
        {
            int r = system("echo a | grep b");
            //assert( r == 1 );
                //executes command in shell
                //return value is system dependant
                    //but often the command exit status
        }

        puts("stdio.h");
        {
            //stdin, stdout, stderr
            {
                //puts
                {
                    //write to stdout
                    //newline added!
                    puts("puts");
                }

                //printf
                {
                    //write formated to sdtout
                    //newline not added
                    
                    //<http://www.cplusplus.com/reference/clibrary/cstdio/printf/>
                    
                    puts("printf:\n");
                    printf("d 1 = %d\n", 1);
                    printf("d 0xFFFFFFFF = %d\n", 0xFFFFFFFF);
                        //-1
                    printf("u 0xFFFFFFFF = %u\n", 0xFFFFFFFF);
                        //max unsigned int
                    //printf("u -1 = %u\n", -1);
                        //WARN expects unsigned int, found int
                    printf("ld 1L = %ld\n", 1L);
                    //printf("u -1 = %lu\n", -1);
                        //WARN expects unsigned int, found int
                    printf("lld = %lld\n", 0x100000000LL); //long long (int)
                    printf("%d %d\n",1,2);

                    printf("f = %f\n", 1.0f);
                    printf(".2f = %.2f\n", 1.0f);
                    printf("0.2f = %.0f\n", 1.0f);
                    printf("7.2f = %7.2f\n", 1.0f); //at least 7 chars: add spaces. used to make tables.
                    printf(".2e = %.2e\n", 1.0f);
                    printf(".*e = %.*e", 2, 1.0f); //treat precision as a parameter

                    printf("%s\n", "a string");
                    printf("%s\n", "\t<<< \\t tab char");
                    printf("%s\n", "\0<<< \\0 null char");

                    printf("%c\n", 'a');
                    printf("%d\n", 'a');

                    printf("%x\n", 16);

                    float f;
                    printf("(void*)&f = %p\n",(void*)&f);
                        //prints the 0x address.
                        //%p must get a void pointer
                        //void* is a type, different than void. doing type cast to it.

                    printf("%%<<< escaping percentage\n");
                }

                //fputs, fprintf
                {
                    //puts and printf to any fd, not just stdout
                    
                    fputs( "stdout", stdout );
                    fputs( "stderr", stderr );
                    fprintf( stdout, "%d", 1 );
                    fprintf( stderr, "%d", 1 );
                        //*always* put user messages on stderr
                        //even if they are not errors:
                        //stdout is just for *program to program* output
                        //not program to human messages
                    //fputs( "stderr", stdin  );
                        //TODO what happens?
                }

                //read from stdin
                if(0)
                {
                    //gets
                    {
                        //deprecated c11
                        //dangerous: no size checking possible
                
                        //printf("enter a string terminated by newline: (max %d chars, newline will be included in the string)\n", sn);
                        //gets(s);
                        //printf("you entered:\n%s\n\n",s);
                    }

                    //scanf
                    {
                        //complicated behaviour
                            //input is space separated regardless of scanf string
                        
                        //no error checking possible
                    
                        int i, j;
                        unsigned int ui;
                        float f;
                        printf("enter an integer in decimal and a newline (max 32 bits signed):\n");
                        i = scanf("%d", &i);
                        printf("you entered:\n%d\n\n", i);
                        i++;
                        //stuff is space separated
                        //try 123 456 789 at once. 456 789 stay in the buffer, and are eaten by the second scanf
                        
                        printf("enter an integer, a space, an integer and a newline (max 32 bits signed):\n");
                        i = scanf("%d %d", &i, &j);
                        printf("you entered:\n%d %d\n\n", i, j);

                        printf("enter a float and a newline:\n");
                        i = scanf("%f", &f);
                        printf("you entered:\n%.2f\n\n", f);

                        printf("enter an integer in hexadecimal and a newline: (max 32 bits signed)\n");
                        i = scanf("%x", &ui);
                        printf("you entered (in decimal):\n%d\n\n", i);
                    }

                    //fgets + error checking: best method
                }
            }

            //files
            {
                FILE *fp;
                int err, had_error, fi;
                float ff;
                char c1;
                char *cp1;

                const int buff_size = 16, nelems = 4;

                char path[buff_size], buff[buff_size];
                int elems_write[] = {1,2,3,4};
                int elems_read[nelems];

                //std in/out/err
                //stdin
                    //be careful!! stdin won't return EOF automatically
                    //
                    //for a tty you can tell the user to input a EOF (ctrl d in linux, ctrl z in windows)
                    //but as you see this is system dependent. for pipes I am yet to find how to do this,
                    //might be automatic when process closes only.
                    //
                    //the best way to know that a stdin ended is recognizing some specific
                    //pattern of the input, such as a newline with fgets, or the end of a
                    //number with scanf
                    //
                    //before this comes, the program just stops waiting for the stdin to
                    //produce this, either from user keyboard input, or from the program
                    //behind the pipe.

                //fopen
                {
                    //open file for read/write
                    //don't forget to fclose after using!
                    //modes:
                        //r: read. compatible with a,w
                        //w: read and write. destroy if exists, create if not.
                        //a: append. write to the end. creates if does not exist.
                        //+: can do both input and output. msut use flush or fseek
                        //x: don't destroy if exist (c11, not c++!, posix only)
                        //b: binary. means nothing in POSIX systems,
                            //on our dear DOS must be used for NL vs NLCR problems
                            //there are two different modes there
                            //Therefore, for portability, make this difference.
                    strcpy( path, "f.tmp" );
                    fp = fopen( path, "w" );
                    if ( fp == NULL )
                    {
                        report_cant_open_file(path);
                        exit( EXIT_FAILURE );
                    }
                    else
                    {
                        //fputc
                        if ( fputc( 'a', fp ) == EOF )
                        {
                            report_cant_write_file( path );
                            exit( EXIT_FAILURE );
                        }

                        //fputs
                        {
                            //newline not appended
                            if ( fputs("bc", fp) == EOF )
                            {
                                report_cant_write_file(path);
                                exit(EXIT_FAILURE);
                            }
                        }

                        //fprintf
                        {
                            // http://www.cplusplus.com/reference/clibrary/cstdio/fprintf/
                            if ( fprintf( fp, "%d\n%.2e\n", 123, 12.3f ) < 0 )
                            {
                                report_cant_write_file(path);
                            }
                        }
                    }
                }
                if( fclose(fp) == EOF )
                {
                    fprintf(stderr, "could not close:\n%s\n", path);
                }
                //don't forget to close!
                //* there is a limited ammount of open files at a time by the os
                //* buffered output may not have been saved before closing
                
                //text mode

                    //read from a file
                        fp = fopen(path,"r");
                        if (fp==NULL)
                        {
                            report_cant_open_file(path);
                        }
                        else
                        {
                            c1 = fgetc(fp);
                            if (c1 == EOF)
                            {
                                if (feof(fp))
                                {
                                    fprintf(stderr, "fgetc end of file:\n%s\n", path);
                                }
                                else if (ferror(fp))
                                {
                                    fprintf(stderr, "fgetc error reading from:\n%s\n", path);
                                }
                            }
                            fprintf(stderr, "c1 = %c\n",c1);
                            fgetc(fp);

                            //fgets
                                //http://www.cplusplus.com/reference/clibrary/cstdio/fgets/
                                //reads up to:
                                //* newline
                                //* buff_size-1 chars
                                //* EOF
                                //saves result in buff, '\0' terminated
                                if ( fgets( buff, buff_size, fp ) == NULL )
                                {
                                    if ( feof(fp) )
                                    {
                                            fprintf(stderr, "fgets reached the of file and read nothing:\n%s\n", path);
                                    }
                                    else if ( ferror(fp) )
                                    {
                                            fprintf(stderr, "fgets error reading from:\n%s\n", path);
                                    }
                                }
                                else if ( feof(fp) )
                                {
                                        fprintf( stderr, "fgets reached the of file and read some chars before that:\n%s\n", path );
                                }
                                fprintf(stderr, "buff = %s",buff);
                                fgets(buff, buff_size, fp);
                                fprintf(stderr, "buff = %s",buff);

                            //fscanf
                                //complicated like scanf
                                if ( fscanf(fp, "%d\n%e\n",&fi,&ff) != 2 )
                                {
                                    if (feof(fp))
                                    {
                                        fprintf(stderr, "fscanf reached the of file and read nothing:\n%s\n", path);
                                    } else if (ferror(fp)) {
                                        fprintf(stderr, "fscanf error reading from:\n%s\n", path);
                                    }
                                }
                                fprintf( stderr, "%d %.2e\n", fi, ff );
                        }

                        if ( fclose(fp) == EOF )
                        {
                            fprintf(stderr, "could not close:\n%s\n", path);
                        }

                        //binary io
                            //notice how inneficient this is for ints! 1 occupies 4 bytes and not 1!
                            //    mostly useful for data that cannot be interpretred as text (images, executables)
                            //better performance only on large chunks
                            //good when you know the size of the entire input/output
                            //including the 'b' option only makes a difference for DOS. use for compatibility (or maybe don't!)

                            strcpy( path, "b.tmp" );
                            fp = fopen( path, "wb" );
                            if ( fp == NULL )
                            {
                                fprintf(stderr, "could not open:\n%s\n", path);
                            }
                            else
                            {

                                //fwrite
                                    //nelems=sizeof(buff)/sizeof(buff[0]);
                                    //nelems=strlen(buff)+1

                                    if ( fwrite(elems_write, sizeof(elems_write[0]), nelems, fp) < nelems ){ //returns number of elements written
                                        fprintf(stderr, "could not write all the data:\n%s\n", path);
                                    }

                            }
                            if ( fclose(fp) == EOF )
                            {
                                fprintf(stderr, "could not close:\n%s\n", path);
                            }

                        //read
                            fp = fopen(path,"rb");
                            if (fp==NULL)
                            {
                                fprintf(stderr, "could not open:\n%s\n", path);
                            }
                            else
                            {
                                    if ( fread( elems_read, sizeof(elems_read[0]), nelems, fp) < nelems )
                                    { //returns number of elements written
                                        fprintf(stderr, "could not read all the data:\n%s\n", path);
                                    }
                            }

                            if ( fclose(fp) == EOF )
                            {
                                fprintf(stderr, "could not close:\n%s\n", path);
                            }

                            fprintf(stderr, "elems_read[0] = %d\n", elems_read[0]);
                            fprintf(stderr, "elems_read[1] = %d\n", elems_read[1]);
                            fprintf(stderr, "elems_read[2] = %d\n", elems_read[2]);
                            fprintf(stderr, "elems_read[3] = %d\n", elems_read[3]);

                //write entire string to file at once
                    
                    strcpy(path,"f.tmp");
                    if ( file_write(path,"asdf\nqwer") == -1 )
                    {
                        report_cant_write_file(path);
                    }

                //read entire file at once to a string
                //
                    char *s = file_read(path);
                    if (s == NULL )
                    {
                        report_cant_read_file(path);
                    }
                    fprintf(stderr, "contents of \"%s\":\n\n%s\n", path, s);
                    free(s);

                    int arri[] = { 0, 1, -1, 12873453 };
                    float arrf[] = { 1.1f, 1.001f, -1.1f, 1.23456e2 };

                    strcpy( path, "arri.tmp" );
                    write_int_arr_file( path, arri, 4 );

                    strcpy( path, "arrf.tmp" );
                    write_float_arr_file( path, arrf, 4, 2 );

                //reposition read write
                
                    //ftell
                        //long int curpos = ftell(pf)
                        //if ( curpos == -1L ){
                        //    report_cant_move_file();
                        //}
                
                    //fseek
                        //http://www.cplusplus.com/reference/clibrary/cstdio/fseek/
                        //
                        //SET: beginning
                        //CUR: current
                        //END: end
                        //
                        //for binary, n bytes, for read, no necessarily
                        //
                        //if ( fseek ( pf, 0 , SEEK_SET ) != 0 ) {
                        //    report_cant_move_file();
                        //}

                    //flush(fp)
                        //for output streams only.
                        //makes sure all the data is put on the stream.
                        //
                        // if (flush(fp) == EOF){
                        //        //error
                        // }
                        
                    //freopen
                        //freopen("/dev/null", "r", stdin);
                        //this will discard stdin on linux

                    //TODO ? fgetpos, fsetpos, rewind
                    //

                    //TRY: echo "123" | ./c_cheatsheet.out
                        //this will use stdin from a pipe! no user input
            }
        }

        puts("time.h");
        {
            printf( "%ld seconds since 1970-01-01:\n", time(NULL) );
                //real world time

            puts("program virtual time:\n");
                clock_t t;
                int i = 0;
                t = clock();
                i++;
                    //NOTE
                    //optimizer may simply skip your useless test operations
                    //and very little time will have passed
                    //
                    //clock() is only an approximation, and if too little time
                    //passes, it may return 0
                t = clock() - t;
                printf( "clicks %llu\n", (unsigned long long)t );
                    //no specifier for this
                    //so cast to largest thing possible and print
                printf( "clocks per sec %ld\n", CLOCKS_PER_SEC );
                printf( "seconds %f\n", ((float)t)/CLOCKS_PER_SEC );
        }

        //math.h
        {
            //constants
            {
                //printf("M_PI = %.2f\n", M_PI);
                //printf("M_PI_2 = %.2f\n", M_PI_2);
                //printf("M_PI_4 = %.2f\n", M_PI_4);
                    //DEPRECATED
                    //C99
                    //used to be in math.h
                    //better off with const int
            }

            assert( fminl(0.1,0.2) == 0.1 );
            assert( fmaxl(0.1,0.2) == 0.2 );
                //C99
            
            assert( abs(-1.1)  == 1 );
            assert( fabsl(-1.1) == 1.1 );

            puts("random");
            {

                srand ( time(NULL) );
                int i = rand();
                    //integer between 0 and RAND_MAX
                float f = rand()/(float)RAND_MAX;
                    //float between 0 and 1
            }
        }
    }

#ifdef PROFILE
        
        //- turn off optimization if you want results to make evident sense
        //- even without optimization, cache access speed is hard to predict
        //   so what you expect may be false
        
        loopOnlyProf(nProfRuns);
        whileOnlyProf(nProfRuns);

        intAssignProf( nProfRuns);
        intSumProf(nProfRuns);
        intSubProf(nProfRuns);
        intMultProf(nProfRuns);
        intDivProf(nProfRuns);

        floatSumProf(nProfRuns);
        floatSubProf(nProfRuns);
        floatMultProf(nProfRuns);
        floatDivProf(nProfRuns);

        funcCallProf(nProfRuns);
        inlineFuncCallProf(nProfRuns);

        stack1bProf(nProfRuns);
        stack1kbProf(nProfRuns);
        stack1mbProf(nProfRuns);

        heap1bProf(nProfRuns);
        heap1kbProf(nProfRuns);
        //heap1mbProf(nProfRuns);
            //by far the slowest

        //putsProf(nProfRuns);
            //BAD
            //don't do stdout on profiling
            //system time is not counted anyways

#endif

#ifdef POSIX

        //sleep
        {
            for(int i=0; i<3; i++)
            {
                printf("%d",i);
                //sleep(1);
                    //sleep for 1 sec
            }
        }

        //memory usage
        {
            /*struct rusage {*/
                /*struct timeval ru_utime; [> user time used <]*/
                /*struct timeval ru_stime; [> system time used <]*/
                /*long   ru_maxrss;        [> maximum resident set size <]*/
                /*long   ru_ixrss;         [> integral shared memory size <]*/
                /*long   ru_idrss;         [> integral unshared data size <]*/
                /*long   ru_isrss;         [> integral unshared stack size <]*/
                /*long   ru_minflt;        [> page reclaims <]*/
                /*long   ru_majflt;        [> page faults <]*/
                /*long   ru_nswap;         [> swaps <]*/
                /*long   ru_inblock;       [> block input operations <]*/
                /*long   ru_oublock;       [> block output operations <]*/
                /*long   ru_msgsnd;        [> messages sent <]*/
                /*long   ru_msgrcv;        [> messages received <]*/
                /*long   ru_nsignals;      [> signals received <]*/
                /*long   ru_nvcsw;         [> voluntary context switches <]*/
                /*long   ru_nivcsw;        [> involuntary context switches <]*/
            /*};*/
            /*int getrusage(rusage_self, *usage);*/
            //RUSAGE_CHILDREN
                //cur process only
            //RUSAGE_CHILDREN
                //children that terminated and have been waited for
        }

        //pathname operations
        {
            //realpath
            //{
            //    //resolves symlinks recursivelly
            //    char rp[PATH_MAX+1];
            //    char *r = realpath( ".", rp );
            //    if ( r )
            //    {
            //        printf( "realpath(\".\") = %s", rp );
            //    }
            //    else
            //    {
            //        assert(false);
            //    }
            //}
            
            //dirname basename 
            {
                //p may be modified

                //memory is statically allocated
                //and may change on next dirname/basename call
            
                //behaviour:
                    //path         dirname    basename
                    //"/usr/lib"    "/usr"    "lib"
                    //"/usr/"       "/"       "usr"
                    //"usr"         "."       "usr"
                    //"/"           "/"       "/"
                    //"."           "."       "."
                    //".."          "."       ".."
                
                char p[1024];
                char* res;

                strcpy( p, "a/b" );
                res = dirname( p );
                assert( strcmp( res, "a" ) == 0 );

                strcpy( p, "a/b" );
                res = basename( p );
                assert( strcmp( res, "b" ) == 0 );
            }
        }
        
        //directory operations
        {
            //no standard portable way!
                //<http://www.devarticles.com/c/a/Cplusplus/Directories-in-Cplusplus/>
            //posix alternatives:
                //windows: direct.h
                //portable heavyweight: booost: #include <boost/filesystem/operations.hpp>
                //portable lightweight: dirent.h
            
            if(0)
            {
                //mkdir
                {
                    if( mkdir( "newdir", 0777 ) == -1 )
                    {
                        puts("could not create newdir");
                    }
                    else
                    {
                        puts("newdir created");
                    }
                }
                //rmdir
                {
                    puts("press any key to remove newdir:");
                    getchar();
                    
                    if( rmdir("newdir") == -1 )
                    {
                        puts("could not remove newdir");
                    }
                    else
                    {
                        puts("newdir removed");
                    }
                }
            }
        }

        //process
        {
            int status;
            int i = 0;
            
            puts("fork");
            {
                //makes a copy of this process
                //``sys_fork`` call

                pid_t pID = fork();
                if (pID == 0)
                {
                    puts("child");
                        //you won't see this
                        //different file pointers
                    i++;
                }
                else if (pID < 0)
                {
                    puts("failed to fork");
                    exit(1);
                }
                else
                {
                    puts("parent");
                }

                puts("child and parent");
                printf("pid = %d, i = % d\n", pID, i);

                wait(&status);
                if( pID == 0 )
                {
                    return EXIT_SUCCESS;
                }

                //no more child process
                puts("parent after child");

                assert( status == EXIT_SUCCESS );
                assert( i == 0 );
                    //memory was cloned, parent i unchanged
            }

            /*puts("clone");*/
            /*{*/
                /*TODO*/
                /*implicit? with unistd.h?*/
                /*i = 0;*/
                /*pid_t pID = clone();*/
                /*if (pID == 0)*/
                /*{*/
                    /*i++;*/
                /*}*/
                /*else if (pID < 0)*/
                /*{*/
                    /*exit(1);*/
                /*}*/
                /*wait(&status);*/
                /*if( pID == 0 )*/
                /*{*/
                    /*return EXIT_SUCCESS;*/
                /*}*/

                /*//no more child process*/
                /*assert( status == EXIT_SUCCESS );*/
                /*assert( i == 1 );*/
            /*}*/

            /*puts("vfork");*/
            /*{*/
                /*TODO*/
                /*implicit? with unistd.h?*/
                /*//makes a copy of this process*/
                /*i = 0;*/
                /*pid_t pID = vfork();*/
                /*if (pID == 0)*/
                /*{*/
                    /*i++;*/
                /*}*/
                /*else if (pID < 0)*/
                /*{*/
                    /*exit(1);*/
                /*}*/
                /*wait(&status);*/
                /*if( pID == 0 )*/
                /*{*/
                    /*return EXIT_SUCCESS;*/
                /*}*/

                /*//no more child process*/
                /*assert( status == EXIT_SUCCESS );*/
                /*assert( i == 1 );*/
            /*}*/

            //vfork
                //fork with shared memory
            //clone
                //fork with shared memory and open file descriptors
            //wait()
                //wait for first child to terminate
            //waitpid()
                //wait for child with given PID to terminate
        }

        //ids
        {
            //every posix process has the folloing info associated to it:
                //real and effective userid and groupid
                //real is always of who executes the program
                //effective may be different depending on the suid and sgid bits
            //process are free to change those ids with system calls
            uid_t uid  = getuid();
            uid_t euid = geteuid();
            gid_t gid  = getgid();
            gid_t egid = getegid();
            printf( "uid:  %llu\n", (long long unsigned)uid  );
            printf( "euid: %llu\n", (long long unsigned)euid );
            printf( "gid:  %llu\n", (long long unsigned)gid  );
            printf( "egid: %llu\n", (long long unsigned)egid );
        }
#endif

#ifdef __GNUC__
        //automatically defined on gcc even if ``-std -pedantic``

        puts("__GUNC__");

#endif

    puts("");
    puts("==================================================");
    puts("= ALL ASSERTS PASSED");
    puts("==================================================");

    //main returns status
    return EXIT_SUCCESS;
    return EXIT_FAILURE;
}
