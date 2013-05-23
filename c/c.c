/*

ansi c, no extensions

#motivation

c is amazingly important as it is used to implement:

- linux kernel
- windows kernel
- python and ruby reference implementation
- opengl

and the list goes on and on

the reason for this is that c is low level and fast

#language versions

    #ANSI C

        language is standardized by an organization named ANSI

        ansi is american, and it represents the USA for ISO and IEC

        you must pay to have the latest standards

        however you can always check open source documentation of compiler/stdlib
        implementations

        drafts are also free, and quite close to the actual specifications

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

        gnu implementation of the c standard library

        is very dominant on linux

        the standards only specifies the interface, not exact implementation algorithms

        stdlib does not come with gcc: you could in theory choose between different implementations.

        - ubuntu

            - headers for glibc are on ``/usr/include``. do ``locate /stdio.h``

            - lib for glibc are on ``/usr/lib/i386-linux-gnu``. do ``locate /libc.a``

            - the ubuntu package is called ``libc6-dev``. ``dpkg -l | grep libc``

        - docs

           <http://www.gnu.org/software/libc/manual/html_mono/libc.html>

#multithreading ipc concurrency

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

#libs

    this section is a list of whose main interface is c or which have a good c interface

    #petcs

        <http://www.mcs.anl.gov/petsc/documentation/index.html>
*/

//#preprocessor
//{
    //does simple stuff *before* compilation

    //#include

        //look in standard dirs directly:

            //#include <file.h>

        //look in current dir first:

            //#include "file.h"

#include <assert.h>
#include <complex.h>

    //isspace, etc:

#include <ctype.h>

#include <locale.h>

    //... variable num of args

#include <stdarg.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>

    //malloc, EXIT_SUCCESS, EXIT_FAILURE:

#include <stdlib.h>

    //printf, puts:

#include <stdio.h>

    //strlen, strcpy:

#include <string.h>
#include <math.h>
#include <time.h>
#include <wchar.h>
//#include <thread.h>
    //not yet implemented for me

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

#define PI_PLUS_ONE (3.14 + 1)
    //use parenthesis or order of operation might destroy you

//control compilation
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
        //cannot create scopes here like that
        //they'd be useless

//#pointer array

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

//#functions

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

    //#struct args

        struct FuncReturn { int i; };

        struct FuncReturn structReturn( struct FuncReturn sIn )
        {
            struct FuncReturn sOut;
            sOut.i = sIn.i + 1;
            return sOut;
        }

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

//#algorithms

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

//#file io

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
            printf("(float).1 = %f\n", (float).1); //double to float
                //WARN possible
            printf("(int).1f = %d\n", (int).1f); //float to int
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

        //#const
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
                    //works
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

        //#array
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
                    int is[4]  = {1,2};
                    int is2[4] = {1,2};
                    //is = is2;
                        //ERROR
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

            //#memcpy
            {
                //copy memory

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

            //#memset
            {
                //set memory block to a single value

                char cs[] = "abcdef";
                memset( cs + 2, '0', 3 );
                assert( strcmp( cs, "ab000f" ) == 0 );
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

            //#string
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

                    //#sprintf
                    {
                        //for the possible formatrings, see <#printf>

                        char cs[] = "abc";
                        char cs2[4];
                        sprintf( cs2, "%s", cs );
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

        //#switch
        {
            int i, j;
            for( i=-1; i<3; i++ )
            {
                switch(i)
                {
                    case 0:

                        assert( i == 0 );

                        int j;
                            //OK
                            //new inner scope

                        //int i = 1;
                            //ERROR
                            //redeclaration

                        break;

                    case 1:

                        assert( i == 1 );

                        //int j;
                            //ERROR
                            //single inner scope

                        break;

                    default:
                        assert( i != 0 && i != 1 );
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
                for ( int i = 0; i < 2; i++ )
                {
                    for ( int j = 0; j < 2; j++ )
                    {
                        assert( i == is[n] );
                        assert( j == js[n] );
                        n++;
                    }
                }
            }
        }

        //#while
        {
            {
                int i=0;
                int is[] = { 0, 1, 2 };
                while ( i < 3 )
                {
                    assert( i == is[i] );
                    i++;
                }
                assert( i == 3 );
            }

            //#do-while
            {
                int i = 0;
                int i2;
                int is[] = { 0, 1, 2 };
                do
                {
                    i2 = 2*i*i + 3*i + ( i % 2 );
                    assert( i == is[i] );
                    i++;
                } while ( i2 < 7 );
                    //don't forget the ';' !

                //application:

                    //loop must execute at least once
                    //to know if it will continue

                    //without do-while, you would have to either:

                        //write:
                        //``int i2 = 2*i*i + 3*i + ( i % 2 );``
                        //so you have to type this huge expression twice!
                        //so if you change one you have to change the other
                        //and you risk to forget creating a hard to find bug

                        //write a function that does 2*i*i + 3*i + ( i % 2 );
                        //this function is almost useless (used only twice)
                        //adding needless boilerplate to your code

                    //both of which are not very attractive alternatives
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

    //#preprocessor
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

        //#&&
#define C 1
#if defined(C) && C > 0
#else
    assert(false);
#endif

        //#standard ifdefs
        {

#if defined (__STDC_VERSION__)
        printf( "__STDC_VERSION__ = %li", __STDC_VERSION__ );
#endif

//some vars are automatically defined by certain compilers:
//although they are not c standards
#ifdef __WIN32__
        puts("__IN32__");
#endif

#ifdef __GNUC__
        //automatically defined on gcc even if ``-std -pedantic``
        puts("__GUNC__");
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
            //#system
            {
                int r = system( "echo a | grep b" );
                //assert( r == 1 );
                    //executes command in a shell
                    //and waits for it to end

                    //on linux
                        //does: /bin/sh -c
                        //this could be written with the posix
                        //fork + execl + wait

                    //on windows uses nother shell

                    //so in the end what you write with this is not easily portable

                    //return value is system dependant
                        //but often the command exit status
            }
        }

        //#stdio
        {
            //#general notes

                //#EOF

                    //TODO what is EOF on a system level
                    //what happens when I hit ctrl+d on bash + getchar?
                    //current guess: a pipe close

                    //in linux, EOF does not exist

                    //the only way to know if a file is over is to make a ``sys_read`` call
                    //and check if you get less bytes than you ask for
                    //(``sys_read`` returns the number of bytes read)

                    //alternativelly, for fds that are files, you can use ``sys_stat`` in linux,
                    //but there is no portable stat func

                    //what was said for linux is similar for windows
                    //and similar for c thus

                    //EOF is a c concept

                    //EOF works because there are only 256 bytes you can get from an fd
                    //so EOF is just some int outside of the possible 0-255 range, tipically -1

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

            //TODO
                //setvbuf: set io buffer size, must be used on open stream
                //flush:    flush io buffer
                //freopen

            //#stdout
            {
                //#putchar
                {
                    //write single char to stdout

                    //basically useless

                    putchar('1');
                    putchar('c');
                    putchar('\n');
                }
                //#puts
                {
                    //write to stdout
                    //newline added!
                    puts("puts");
                }

                //#printf
                {
                    //write formated to sdtout

                    //newline not added at end

                    //ref: <http://www.cplusplus.com/reference/clibrary/cstdio/printf/>

                    //very useful to learn, since this is also used in python and bash `printf` command.

                    char s[256];

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

                    //#float and double
                    {
                        //both the same char

                        printf("f = %f\n", 1.0f);

                        //#control number of zeros after dot
                        {
                            //#fixed number
                            {
                                sprintf( s, "%.2f", 1.0f );
                                char s2[] = "1.00";
                                assert( strcmp( s, s2 ) == 0 );
                            }

                            //#given by variable
                            {
                                sprintf( s, "%.*f", 2, 1.0f );
                                char s2[] = "1.00";
                                assert( strcmp( s, s2 ) == 0 );
                            }
                        }

                        //#control minimum number chars to output
                        {
                            //#pad with spaces
                            {
                                //useful to output text tables:
                                //
                                //ugly:
                                //
                                //12345 1
                                //1 1
                                //
                                //beautiful:
                                //
                                //12345 1
                                //1     1

                                sprintf( s, "%6.2f", 1.0f );
                                char s2[] = "  1.00";
                                assert( strcmp( s, s2 ) == 0 );
                            }

                            //#pad with zeros
                            {
                                //useful for naming files:
                                //"10" comes after  "09" ('1' > '0')
                                //"10" comes before "9"  ('1' < '0')!

                                sprintf( s, "%06.2f", 1.0f );
                                char s2[] = "001.00";
                                assert( strcmp( s, s2 ) == 0 );
                            }
                        }

                        //#scientific
                        {
                            sprintf( s, "%.3e", 1.0f );
                            char s2[] = "1.000e+00";
                            assert( strcmp( s, s2 ) == 0 );
                        }
                    }

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
                        //note that this is printf specific
                        //not string specific
                }

                //large strings to stdout
                {
                    //stdout it line buffered


                    //if you fill up the buffer without any newlines
                    //it will just print

                    //buffer size cannot be accessed programatically

                    //TODO what is the bin buffer size?
                    //in practice, 1024 works just fine
                    //it may be much larger than BUFSIZ

                    const int bufsiz = 100000;
                    char buf[bufsiz];
                    memset( buf, 'z', bufsiz );
                    buf[bufsiz] = '\0';
                    buf[bufsiz/2] = '\n';
                    //printf("%s\n", buf); //large amount of 'z's verywhere!
                }
            }

            //#stderr
            {
                //#fputs, fprintf
                {
                    //puts and printf to any fd, not just stdout

                    fputs( "stdout", stdout );
                    fputs( "stderr", stderr );
                    fprintf( stdout, "%d\n", 1 );
                    fprintf( stderr, "%d\n", 1 );
                        //*always* put user messages on stderr
                        //even if they are not errors:
                        //stdout is just for *program to program* output
                        //not program to human messages
                    //fputs( "stderr", stdin  );
                        //TODO what happens?
                }
            }

            //#stdin tty
            {
                //#getc, getchar
                if(0)
                {
                    //getchar == getc(stdin)

                    //it blocks until any char is read

                    //echo a | c.out
                        //a
                    //sleep 3 | c.out
                        //EOF after 3 secs

                    fputs( "enter a char (on linux, ctrl+d EOF): ", stderr );
                    //fputc( 'a', stdin );
                        //BAD
                        //does not work
                    char c = getchar();
                    if ( c != EOF )
                    {
                        fprintf( stderr, "you entered:\n%c|<<<\n", c );
                    }
                    else
                    {
                        fprintf( stderr, "EOF\n" );
                    }
                }

                //#gets
                if(0)
                {
                    //BAD
                    //deprecated c11
                    //dangerous
                        //no size checking possible
                        //if too much input, just seg faults

                    //printf("enter a string terminated by newline: (max %d chars, newline will be included in the string)\n", sn);
                    //gets(s);
                    //printf("you entered:\n%s\n\n",s);
                }

                //#scanf
                if(0)
                {
                    //BAD

                    //complicated behaviour
                        //input is space separated regardless of scanf string

                    //hard to errot check

                    //stops reading at newline

                    int i, j;
                    unsigned int ui;
                    float f;
                    printf("enter an integer in decimal and <enter> (max 32 bits signed):\n");
                    i = scanf("%d", &i);
                    printf("you entered:\n%d\n\n", i);
                    i++;
                    //stuff is space separated
                    //try 123 456 789 at once. 456 789 stay in the buffer, and are eaten by the second scanf

                    printf("enter an integer, a space, an integer and a <enter> (max 32 bits signed):\n");
                    i = scanf("%d %d", &i, &j);
                    printf("you entered:\n%d %d\n\n", i, j);

                    printf("enter a float and a newline:\n");
                    i = scanf("%f", &f);
                    printf("you entered:\n%.2f\n\n", f);

                    printf("enter an integer in hexadecimal and a <enter>: (max 32 bits signed)\n");
                    i = scanf("%x", &ui);
                    printf("you entered (in decimal):\n%d\n\n", i);
                }

                //#fgets
                if(0)
                {
                    //together with error checking, best method formatted input method
                    /*fgets*/
                }
            }

            //#file io
            {
                FILE* fp;
                    //#FILE is a macro for a stream object

                        //a strem object is higher level than a file descriptor

                        //it uses file descriptors as backend in linux

                        //linux file descriptors are identified simply by integers

                        //by using streams you get the classical high level/low level tradeoff:

                            //higher portability
                                //since working with fds is posix

                            //more convenience
                                //since each function on streams may do lots of
                                //operations at once on the underlying fds

                            //less control

                                //since OS certain specific operatins are not available

                                //with fds in linux you can do file/pipe/FIFO/socket specific operations
                                //for example

                int err, had_error, fi;
                float ff;
                char c1;
                char *cp1;

                const int buff_size = 16;
                char path[buff_size], buff[buff_size];

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
                            //newline not automatically appended
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
                    // there is a limited ammount of open files at a time by the os
                    // buffered output may not have been saved before closing

                //text io
                {
                    //read from a file
                    {
                        fp = fopen(path,"r");
                        if (fp==NULL)
                        {
                            report_cant_open_file(path);
                        }
                        else
                        {
                            c1 = fgetc(fp);
                            if ( c1 == EOF )
                            {
                                if ( feof( fp ) )
                                {
                                    fprintf( stderr, "fgetc end of file:\n%s\n", path );
                                }
                                else if (ferror(fp))
                                {
                                    fprintf( stderr, "fgetc error reading from:\n%s\n", path );
                                }
                            }
                            fprintf( stderr, "c1 = %c\n",c1 );
                            fgetc( fp );

                            //fgets
                                //http://www.cplusplus.com/reference/clibrary/cstdio/fgets/
                                //reads up to:
                                //* newline
                                //* buff_size-1 chars
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
                                    if ( feof( fp ) )
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
                    }
                }

                //#binary io
                {
                    //notice how inneficient this is for small ints!
                    //1 int occupies 4 bytes and not 1!

                    //mostly useful for data that cannot be interpretred as text (images, executables)

                    //better speed performance only on large chunks

                    //good when you know the size of the entire input/output

                    //including the 'b' option only makes a difference for DOS. use for compatibility (or maybe don't!)

                    int elems_write[] = { 1, 2, 3 };
                    const int nelems = sizeof(elems_write) / sizeof(elems_write[0]);
                    int elems_read[nelems];

                    //#fwrite
                    {
                        strcpy( path, "b.tmp" );
                        fp = fopen( path, "wb" );
                        if ( fp == NULL )
                        {
                            fprintf( stderr, "could not open:\n%s\n", path );
                            exit(EXIT_FAILURE);
                        }
                        else
                        {
                            //returns number of elements written

                            //common nelems source
                                //nelems=sizeof(buff)/sizeof(buff[0]);
                                //nelems=strlen(buff)+1

                            if ( fwrite( elems_write, sizeof(elems_write[0]), nelems, fp ) < nelems )
                            {
                                fprintf(stderr, "could not write all the data:\n%s\n", path);
                            }
                        }
                        if ( fclose(fp) == EOF )
                        {
                            fprintf( stderr, "could not close:\n%s\n", path );
                        }
                    }

                    //#fread
                    {
                        fp = fopen( path, "rb" );
                        if ( fp == NULL )
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
                    }

                    assert( memcmp( elems_read, elems_write, nelems ) == 0);
                }

                //#reposition read write
                {
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

                //#applications
                {
                    //write entire string to file at once

                        char cs[] = "asdf\nqwer";
                        strcpy(path,"f.tmp");
                        if ( file_write( path, cs ) == -1 )
                        {
                            report_cant_write_file(path);
                        }

                    //read entire file at once to a string

                        char* cp = file_read(path);
                        if ( cp == NULL )
                        {
                            report_cant_read_file(path);
                        }
                        assert( strcmp( cs, cp ) == 0 );
                        free(cp);

                    //simple write arrays to file

                        int arri[] = { 0, 1, -1, 12873453 };
                        float arrf[] = { 1.1f, 1.001f, -1.1f, 1.23456e2 };

                        strcpy( path, "arri.tmp" );
                        write_int_arr_file( path, arri, 4 );

                        strcpy( path, "arrf.tmp" );
                        write_float_arr_file( path, arrf, 4, 2 );
                }
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

        //#math.h
        {
            //C99:
                assert( fminl(0.1,0.2) == 0.1 );
                assert( fmaxl(0.1,0.2) == 0.2 );

            //exponential:
                assert( fabs( exp(1.0) - 2.71 )     < 0.01 );
                assert( fabs( cos(0.0) - 1.0 )      < 0.01 );
                assert( fabs( acos(-1.0) - 3.14 )   < 0.01 ); //PI

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

    puts("\nALL ASSERTS PASSED\n");

    //main returns status
    return EXIT_SUCCESS;
    return EXIT_FAILURE;
}
