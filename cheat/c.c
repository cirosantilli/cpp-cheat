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

    - volatile

        http://en.wikipedia.org/wiki/Volatile_variable

        prevents funcion optimization

        useful for multithreading

TODO
    - file io
    - struct
    - typedef
    - documentation: doxigen

        <http://www.stack.nl/~dimitri/doxygen/docblocks.html>

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

//POSIX
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

//random
    float rand_range(float a, float b)
    { //float in a range
        return ((b-a)*((float)rand()/RAND_MAX))+a;
    }

//profiling

    const int nProfRuns = 1000000;

    void intAssignProf(int n)
    {
        int i,j;
        for( i=0; i<n; i++ )
            j=1;
    }

    void intSumProf(int n)
    {
        int i;
        for( i=0; i<n; i++ );
    }

    void intSubProf(int n)
    {
        int i;
        for( i=n; i>0; i-- );
    }

    void intMultProf(int n)
    {
        int i,j;
        for( i=0; i<n; i++ )
            j=j*1;
    }

    void intDivProf(int n)
    {
        int i,j;
        for( i=0; i<n; i++ )
            j=j/1;
    }

    void floatSumProf(int n)
    {
        float f;
        int i;
        for( i=0; i<n; i++ )
            f=f+0.0;
    }

    void floatSubProf(int n)
    {
        float f;
        int i;
        for( i=0; i<n; i++ )
            f=f-0.0;
    }

    void floatMultProf(int n)
    {
        int i;
        float j;
        for( i=0; i<n; i++ )
            j=j*1.0;
    }

    void floatDivProf(int n)
    {
        int i;
        float j;
        for( i=0; i<n; i++ )
            j=j/1.0;
    }

    void putsProf(int n)
    {
        int i;
        for( i=0; i<n; i++ )
            puts("");
    }

int main(int argc, char** argv)
{
    //base types and vars
        //allowed variable names: _,[a-Z],[0-9], canot start with number
        
        puts("\nbase types");
        int i=5,j=7; //31 bit + 1 sign bit integer
        int* ip = &i;
        //int i;
        //i = 5;
        //
        //int i=5;
        //int j=7;
        unsigned int ui;
        //applications:
            //array indexes
            //size_t
        long int li = 8L;
        long long lli = 8LL; //64 bit int. defined in C99
        float f = 1.2345f;    //1 signal 23 number 8 exponent
        float f1 = 1.2345e-10f;
        float f2 = 1.f;
        //float f = 1f; //there must be a dot
        double d = 6.789;
        char c = 'a';
        char *cp;
        char s[8] = "s";
        int sn = 8;

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

        size_t size = sizeof(int);
        printf( "sizeof(int) = %zu\n", sizeof(int) ); //how many bytes per int
        //4
        printf( "sizeof(long int) = %zu\n", sizeof(long int) ); //int and long int may be equal!!!!!! this is plataform dependent
        //4
        printf( "sizeof(long long) = %zu\n", sizeof(long long) ); //int and long int may be equal!!!!!! this is plataform dependent
        //8
        printf( "sizeof(wchar_t) = %zu\n", sizeof(wchar_t) ); //compiler specific
        printf( "sizeof(size_t) = %zu\n", sizeof(size_t) );   //compiler specific

        //modifiers for int and float
            //short
            //long
            //signed
            //unsigned 
            
            //stardard specifies not necessarily smaller!!!
                //short int <=    int <= long int
                //float <= double <= long double
            
            //in practice today (could change in the future):
                //short int             2             -32,768 -> +32,767          (16kb)
                //unsigned short int    2                   0 -> +65,535          (32Kb)
                //unsigned int          4                   0 -> +4,294,967,295   ( 4Gb)
                //int                   4      -2,147,483,648 -> +2,147,483,647   ( 2Gb)
                //long int              4      -2,147,483,648 -> +2,147,483,647   ( 2Gb)
                //long long == long int 8      (created in C99)
                //unsigned long long
                //signed char           1                -128 -> +127
                //unsigned char         1                   0 -> +255
                //float                 4    
                //double                8    
                //long double           12   

            //ERROR: unsigned flot does not exist!
                //unsigned float uf = 1.0f;

            {
                int i = 0xFFFFFFFF; //max unsigned int
                printf("i = %d\n", i);
                //-1. too large for int!
                i++;
                printf("i = %d\n", i);
                //0
            }

            {
                unsigned int ui = 0xFFFFFFFF;
                printf("ui = %u\n", ui);

                //SAME
                ui = -1;
                printf("ui = %u\n", ui);
            }

            //TODO what is the difference between declaring a variable signed an unsigned?
            //all that matters is the %u or %d in the printf?

            //WARN overflow
                //i = 0x100000000; //max int+1

            //WARN constant too large (even for long long)
                //lli = 0x10000000000000000; //max long long+1

        //bases for integers
            assert( 16 == 0x10 );
            assert( 16 == 020 );
            assert( 16 == 0b10000 );
        
        //const
            const int ic = 0;
            //int const ic = 0
                //exact same thing!
            const int ic2 = i;

            //ERROR: consts are... almost consts! (you can change them with a warning)
                //ic = 1;
            //ERROR: i already defined
                //int i = 0;
                //const int i = 0;

            //WARN: discards const. in c++, error!
                //ip = &ic;
                //*ip = 2;
                //we changed the const!
                    //this is why you can't int is[constint]; !!
                    //because you can compile with only a warning and change a const
                
            //const pointers
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

                //BAD compiles without warning, but is bad since ic3 cannot get a value
                    //unless you typecast its pointer with a warning
                    const int ic3;

                //WARN
                    //int * const ipc = &ic;
                //ERROR: this time what the address the pointer points to is constant
                //not its value!
                    //ipc = &ic2;
                //BAD: we changed the value!
                    //*ipc = 2;
                
                const int* const cipp = &ic;

            const int cis2[2] = {1,2};
            //ERROR
                //cis2[0] = 1;

            //scanf("%d",&i);
            //const 
                //NOTE consts are *not* "compile time constants"
                //they are only constant after they are declared
                //this is another reason why you can't use them
                //as arrays sizes without VSA

        //typecast
            printf("(double).1f = %f\n", (double).1f); //float to double
            //WARN possible
                printf("(float).1 = %f\n", (float).1); //double to float
            //WARN possible
                printf("(int).1f = %d\n", (int).1f);
            //WARN possible
                printf("(int)1L = %d\n", (int)1L); //long to int
            printf("(long)1 = %ld\n", (long)1); //int to long

            printf("(int*)&f = %p\n", (int*)&f); //any pointer typecast is ok to compiler
            printf("(int)&f = %d\n", (int)&f);   //memory address of pointer

            int is3[3];
            int is4[4];
            ip = (int*)is3; //is[3] to int*
            //ERROR
                //is3=(int[3])is4;
            //ERROR pointer to int[]
                //is3=is4;
    
    puts("operators");
    
        puts("arithmetic");
            assert( (1+2) == 3 );
            assert( (2*3) == 6 );
            assert( (4/2) == 2 );
            assert( (1/2) == 0 );
            assert( (1.0/2.0) == 0.5 );
            assert( (1  /2.0) == 0.5 );
            assert( (1/(double)2) == 0.5 );

            assert( (3%3) == 0 );
            assert( (4%3) == 1 );
            assert( (5%3) == 2 );
            assert( (6%3) == 0 );

        puts("boolean");
            assert( (1==1) == 1 );
            assert( (0==1) == 0 );

            assert( ( 0 >  1 ) == 0 );
            assert( ( 0 >  0 ) == 0 );
            assert( ( 0 > -1 ) == 1 );
            assert( ( 0 <  1 ) == 1 );
            assert( ( 0 <  0 ) == 0 );
            assert( ( 0 < -1 ) == 0 );

            assert( (0 >=  1) == 0 );
            assert( (0 >=  0) == 1 );
            assert( (0 >= -1) == 1 );
            assert( (0 <=  1) == 1 );
            assert( (0 <=  0) == 1 );
            assert( (0 <= -1) == 0 );

        puts("bitwise");

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

        puts("assign");
            {
                int i = 0;
                assert( (i=1) == 1 );
                //= returns right side
                assert( i == 1 );

                //increment
                    //http://stackoverflow.com/questions/24886/is-there-a-performance-difference-between-i-and-i-in-c
                    //which is faster?
                    //in c, equal, in c++, ++i potentially if i is a complex object

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
    
        puts("conditional");
            assert( ( 1<2 ? 3 : 4 ) == 3 );
            assert( ( 1>2 ? 3 : 4 ) == 4 );

        puts("comma");
            //almost useless
            {
                int i=0, a=1, b=2, c=3; //comma here is separator, not operator. same comma in functions calls/defs

                assert( (i=0, 1) == 1 );  
                assert( (i=0, i=1, 2) == 2 );             
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

    puts("if");

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

        puts("complex.h");
            //C99
            {
                const double complex zd = 1.0 + 2.0*I;
                const int complex zi = 1 + 2*I;
                const int complex zi2 = 1 + 1*I;

                assert( creal( zi + zi ) == 2 );
                assert( cimag( zi + zi ) == 4 );

                assert( creal( zi - zi2 ) == 0 );
                assert( cimag( zi - zi2 ) == 1 );

                assert( creal( zi * zi ) == -3 );
                assert( cimag( zi * zi ) == 4 );

                assert( creal( zi / zi ) == 1 );
                assert( cimag( zi / zi ) == 0 );

                assert( creal( conj(zi) ) == 1 );
                assert( cimag( conj(zi) ) == -2 );
            }

        puts("stdbool.h");
            //C99
            {
    
            //bool b = true;
                //ERROR
                //no booleans true false in c, ints only! c++ only.
                //can use stdbool.h

                bool b = true;
                bool b2 = false;
                assert( true  == 1 );
                assert( false == 0 );
            }

        puts("goto");
            {
                goto a;
                    assert(0);
                a:
                assert(1);
            }

    puts("switch");

        {
            int j;
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

    puts("for");

        //no difference from while
        //
        //only use if when know how many times
        //otherwise use ``while``, which is more flexible

        {
            int i;
            int is[] = {0,1,2};
            for( i=0; i<3; i++ )
            {
                assert( i == is[i] );
                //int i;
                    //OK new scope
            }
            assert( i == 3 );
        }

        {   
            //C99
            //putting int i=0 inside for
            int is[] = {0,1,2};
            for( int i=0; i<3; i++ )
            {
                assert( i == is[i] );
                //int i;
                    //ERROR
                    //redeclaration
            }
        }
        
        {
            //one of the few uses of the comma operator
            int is[] = {0,1,2};
            int js[] = {0,1,2};
            for( int i=0, j=0; i*j<5; i++, j++ )
            {
                assert( i == is[i] );
                assert( i == js[i] );
            }
        }
        
        {
            //nested loops
            int n = 0;
            int is[] = {0,0,1,1};
            int js[] = {0,1,0,1};
            for( int i=0; i<2; i++ )
                for( int j=0; j<2; j++ )
                {
                    assert( i == is[n] );
                    assert( j == js[n] );
                    n++;
                }
        }
        
    puts("while");

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

    puts("enum");

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

            //if you don't give a value, it gets a value different from all others
                assert( E4 != E1);
                assert( E4 != E2);
                assert( E4 != E3);
        }


    puts("stdio.h");
        //stdin, stdout, stderr

        //puts: write to stdout.
            //simpler (and faster?) than printf
            //automatically newline terminated!
            //can contain newlines
            puts("puts\nputs\n");

        //printf: write formated to sdtout
            //http://www.cplusplus.com/reference/clibrary/cstdio/printf/

            puts("\nprintf:");
            printf("d 1 = %d\n", 1);
            printf("d 0xFFFFFFFF = %d\n", 0xFFFFFFFF);
            //-1
            printf("u 0xFFFFFFFF = %u\n", 0xFFFFFFFF);
            //max unsigned int
            //WARN expects unsigned int, found int
                //printf("u -1 = %u\n", -1);
            printf("ld 1L = %ld\n", 1L);
            //WARN expects unsigned int, found int
                //printf("u -1 = %lu\n", -1);
            printf("lld = %lld\n", 0x100000000LL); //long long (int)
            printf("%d %d\n",1,2);

            printf("f = %f\n", f);
            printf(".2f = %.2f\n", f);
            printf("0.2f = %.0f\n", f);
            printf("7.2f = %7.2f\n", f); //at least 7 chars: add spaces. used to make tables.
            printf(".2e = %.2e\n", f);
            printf(".*e = %.*e", 2, f); //treat precision as a parameter

            printf("%s\n", "a string");
            printf("%s\n", "\t<<< \\t tab char");
            printf("%s\n", "\0<<< \\0 null char");

            printf("%c\n", 'a');
            printf("%d\n", 'a');

            printf("%x\n", 16);

            printf("(void*)&f = %p\n",(void*)&f);
            //prints the 0x address.
            //%p must get a void pointer
            //void* is a type, different than void. doing type cast to it.

            printf("%%<<< escaping percentage\n");

        //read from stdin
        if(0){ //gets annoying after some time

        //gets: deprecated.
            //dangerous: no size check
    
            //gets is deprecated in c11! http://www.cplusplus.com/reference/clibrary/cstdio/fgets/
            //printf("enter a string terminated by newline: (max %d chars, newline will be included in the string)\n", sn);
            //gets(s);
            //printf("you entered:\n%s\n\n",s);

        //scanf : dangerous
            //input is space separated
            //nothing happens on error
        
            int i;
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
            i = scanf("%x", &i);
            printf("you entered (in decimal):\n%d\n\n", i);

        //fgets + error checking: best method
    
        }

        //TRY: echo "123" | ./c_cheatsheet.out
            //this will use stdin from a pipe! no user input

    puts("time.h");
        {
            //real time
            printf( "%ld seconds since 1970-01-01\n", time(NULL) );

            puts("program virtual time:");
                clock_t t;
                t = clock();
                intSumProf(nProfRuns);
                //NOTE
                    //optimizer may simply skip your useless test operations
                    //and very little time will have passed
                    //
                    //clock() is only an approximation, and if too little time
                    //passes, it may return 0
                t = clock() - t;
                printf( "clicks %d\n", t );
                printf( "clocks per sec %d\n", CLOCKS_PER_SEC );
                printf( "seconds %f\n", ((float)t)/CLOCKS_PER_SEC );
        }

    puts("math.h");
        //constants
 
            /*printf("M_PI = %.2f\n", M_PI);*/
            //printf("M_PI_2 = %.2f\n", M_PI_2);
            //printf("M_PI_4 = %.2f\n", M_PI_4);
            //DEPRECATED
                //C99
                //used to be in math.h
                //better off with const int

        //C99
        assert( fminl(0.1,0.2) == 0.1 );
        assert( fmaxl(0.1,0.2) == 0.2 );
        
        assert( abs(-1.1)  == 1 );
        assert( fabsl(-1.1) == 1.1 );

        //random
            puts("random");

                srand ( time(NULL) );
                i = rand(); //integer between 0 and RAND_MAX
                f = rand()/(float)RAND_MAX; //float between 0 and 1

    puts("preprocessor");

#define A B
#define B 1
        assert( A == 1 );

        //gcc -DCOMMANDLINE c.c
        //gcc c.c
#ifdef COMMANDLINE
        puts("C");
#else
        puts("no C");
#endif

    puts("");

    //libraries
 
    //directory operations
        //no standard portable way! http://www.devarticles.com/c/a/Cplusplus/Directories-in-Cplusplus/
        //linux: sys/stat.h, unistd.h
        //windows: direct.h
        //portable heavyweight: booost: #include <boost/filesystem/operations.hpp>
        //portable lightweight: dirent.h
        
        //linux only if you don't care!
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

        //path operations
        //puts(realpath("."));

#ifdef PROFILE
        intSumProf(nProfRuns);
        intAssignProf(nProfRuns);
        intSubProf(nProfRuns);
        intMultProf(nProfRuns);
        intDivProf(nProfRuns);
        floatSumProf(nProfRuns);
        floatSubProf(nProfRuns);
        floatMultProf(nProfRuns);
        floatDivProf(nProfRuns);
        //putsProf(nProfRuns);
            //BAD
            //don't do stdout on profiling
            //system time is not counted anyways
#endif

    //main returns status
        return EXIT_SUCCESS;
        return EXIT_FAILURE;
}
