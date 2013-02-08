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

#preprocessor

does stuff before the compilation

thats why is is called *pre*

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

    #POSIX

        POSIX is an operating system standardization by IEEE.
        followed by Linux and OSX, but not by windows.

        there are POSIX headers which allow c to do certain system calls
        on POSIX compliant systems.
        
        they allow operations such as:

        - threads
        - ipc
        - filesystem operations
        - user/group info

        check: <http://en.wikipedia.org/wiki/C_POSIX_library>

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

    -  mutable
        TODO

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
    //does simple stuff *before* compilation

#include <stdio.h>
    //printf, puts

#include <stdlib.h>
    //malloc, EXIT_SUCCESS, EXIT_FAILURE

//define
    //define constants, or control compilation

#include <assert.h>
#include <complex.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
//#include <thread.h>
    //not yet implemented for me

#include <stdint.h>

//BEGIN POSIX
#include <sys/stat.h>    
#include <unistd.h>
//END POSIX
 
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

//global scope

    int global = 1;
        //this is a global variable: can be accessed and modified everywhere

    //OK!
    int global2 = 1+1;


    int ret1(){
        puts("before main!");
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
            puts("");
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

        assert( sizeof(int) + sizeof(float) == sizeof(struct S) );

        {
            struct S s = { 1, 1.0 };
                //list init
                //only possible for contiguous (non pointer) data
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
    }
    
    puts("operators");
    {
        puts("arithmetic");
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

        puts("boolean");
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

        puts("bitwise");
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

        puts("assign");
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

        puts("question mark");
        {
            assert( ( 1 < 2 ? 3 : 4 ) == 3 );
            assert( ( 1 > 2 ? 3 : 4 ) == 4 );
        }

        puts("comma operator");
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
        }
    }

    puts("preprocessor");
    {
        {
#define A B
#define B 1
            assert( A == 1 );
        }

        {
            //gcc -DCOMMANDLINE c.c
            //gcc c.c
#ifdef COMMANDLINE
            puts("C");
#else
            puts("no C");
#endif
        }
    }

    puts("stdlib");
    {
        puts("complex.h");
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

        puts("stdio.h");
        {
            //stdin, stdout, stderr

            //puts: write to stdout.
            {
                //simpler (and faster?) than printf
                //automatically newline terminated!
                //can contain newlines
                puts("puts\nputs\n");
            }

            //printf: write formated to sdtout
            {
                //http://www.cplusplus.com/reference/clibrary/cstdio/printf/

                puts("\nprintf:");
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

            //read from stdin
            if(0)
            { //gets annoying after some time

            //gets: deprecated.
                //dangerous: no size check
        
                //gets is deprecated in c11! http://www.cplusplus.com/reference/clibrary/cstdio/fgets/
                //printf("enter a string terminated by newline: (max %d chars, newline will be included in the string)\n", sn);
                //gets(s);
                //printf("you entered:\n%s\n\n",s);

            //scanf : dangerous
                //input is space separated
                //nothing happens on error
            
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

            //fgets + error checking: best method
        
            }

            //TRY: echo "123" | ./c_cheatsheet.out
                //this will use stdin from a pipe! no user input
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

        puts("math.h");
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

        //memory usage
        {
            struct rusage {
                struct timeval ru_utime; /* user time used */
                struct timeval ru_stime; /* system time used */
                long   ru_maxrss;        /* maximum resident set size */
                long   ru_ixrss;         /* integral shared memory size */
                long   ru_idrss;         /* integral unshared data size */
                long   ru_isrss;         /* integral unshared stack size */
                long   ru_minflt;        /* page reclaims */
                long   ru_majflt;        /* page faults */
                long   ru_nswap;         /* swaps */
                long   ru_inblock;       /* block input operations */
                long   ru_oublock;       /* block output operations */
                long   ru_msgsnd;        /* messages sent */
                long   ru_msgrcv;        /* messages received */
                long   ru_nsignals;      /* signals received */
                long   ru_nvcsw;         /* voluntary context switches */
                long   ru_nivcsw;        /* involuntary context switches */
            };
            int getrusage(rusage_self, *usage);
            //RUSAGE_CHILDREN
                //cur process only
            //RUSAGE_CHILDREN
                //children that terminated and have been waited for
        }
        
        //directory operations
        {
            //no standard portable way! http://www.devarticles.com/c/a/Cplusplus/Directories-in-Cplusplus/
            //linux: sys/stat.h, unistd.h
            //windows: direct.h
            //portable heavyweight: booost: #include <boost/filesystem/operations.hpp>
            //portable lightweight: dirent.h
            
            //POSIX only if you don't care!
            if(0)
            {
                if( mkdir("newdir",0777) == -1 )
                {
                    puts("could not create newdir");
                }
                else
                {
                    puts("newdir created");
                }

                puts("enter to remove newdir:");
                char* cp = gets(s);
                
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

        //path operations
        {
            //puts(realpath("."));
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
