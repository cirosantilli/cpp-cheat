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
    * \n, \t, \\, \xnn, \unnnn TODO

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
    * TODO: why not blow up with is[10000000] (< 32 bits, but larger than my RAM!)

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

* gcc warning vs error
- debugging:
    - gdb
- profiling/benchmarking
    - gprof
    http://kuscsik.blogspot.com.br/2007/08/how-to-benchmark-c-code-using-gcc.html


TODO
    - memory segments/layout : text data heap stack command line
    - make, ./config, 
    - file/stream io
    - multifiles/headers, where looks for them
        raison detre:
            - precompiled libraries.
                only definitions are needed for using code,
                or else would have to recompile everythins,
                and precompiling would be useless.
    - .a, .so
    - struct
    - enum
    - typedef
    - multithreading/ipc
    - static
    - const
    - volatilal erre
    - documentation: doxigen
        <http://www.stack.nl/~dimitri/doxygen/docblocks.html>

#hot libraries

- opengl

    sudo aptitude install freeglut3-dev

- opengl

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




*/

//preprocessor
    //does simple stuff *before* compilation

#include <stdio.h>
//printf, puts

#include <stdlib.h>
//malloc, EXIT_SUCCESS

//define
    //define constants, or control compilation
 
    //BAD
#define PI 3.14
#define PI_PLUS_ONE (3.14 + 1)
//use parenthesis or order of operation might destroy you
    //does not evaluate: only copy pastes

//control compilation
#define DEBUG
#ifdef DEBUG
int debugVar;
#endif

#define WINDOWS
#ifdef WINDOWS
int windowsVar;
#endif

int global = 12;
    //this is a global variable: can be accessed and modified everywhere

//ERROR: only declarations (vars, funcs, enums, ...) outside functions (main)
    //
    //puts("asdf");
    //
    //if(1){}
 
//function
    void f(){ puts("f()"); }

    void fOut()
    {
        //ERROR: cannot def funcs inside funcs
            /*void fIn(){}*/
    }
    
    //ERROR: cannot have func with same name as var
        //int anInt = 1;
        //void anInt(){}

    //ERROR: no overloading in c! c++ only
        //void f(int i){}
        //void f(float i){}

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

int main(){

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

        size_t size = sizeof(int);
        printf("sizeof(int) = %zu\n",sizeof(int)); //how many bytes per int
        //4
        printf("sizeof(long int) = %zu\n",sizeof(long int)); //int and long int may be equal!!!!!! this is plataform dependent
        //4
        printf("sizeof(long long) = %zu\n",sizeof(long long)); //int and long int may be equal!!!!!! this is plataform dependent
        //8

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

            i = 0xFFFFFFFF; //max unsigned int
            printf("i = %d\n", i);
            //-1. too large for int!
            i++;
            printf("i = %d\n", i);
            //0

            ui = 0xFFFFFFFF;
            printf("ui = %u\n", ui);

            //SAME
            ui = -1;
            printf("ui = %u\n", ui);

            //TODO what is the difference between declaring a variable signed an unsigned?
                //all that matters is the %u or %d in the printf?

            //WARN overflow
                //i = 0x100000000; //max int+1

            //WARN constant too large (even for long long)
                //lli = 0x10000000000000000; //max long long+1

        //bases for integers
            printf("16 = %d\n", 16);
            printf("0x10 = %d\n", 0x10);
            //16
            printf("020 = %d\n", 020);
            //16
            printf("0b10000 = %d\n", 0b10000);
            //16
        
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

    //write to stdout

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

        printf("%s\n", "Hello World");
        printf("%s\n", "Hello\0World");

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
    
        printf("enter an integer in decimal and a newline (max 32 bits signed):\n");
        scanf("%d", &i);
        printf("you entered:\n%d\n\n", i);
        //stuff is space separated
        //try 123 456 789 at once. 456 789 stay in the buffer, and are eaten by the second scanf
        
        printf("enter an integer, a space, an integer and a newline (max 32 bits signed):\n");
        scanf("%d %d", &i, &j);
        printf("you entered:\n%d %d\n\n", i, j);

        printf("enter a float and a newline:\n");
        scanf("%f", &f);
        printf("you entered:\n%.2f\n\n", f);

        printf("enter an integer in hexadecimal and a newline: (max 32 bits signed)\n");
        scanf("%x", &i);
        printf("you entered (in decimal):\n%d\n\n", i);

    //fgets + error checking: best method
 
    }

    //directory operations
    //no standard portable way! http://www.devarticles.com/c/a/Cplusplus/Directories-in-Cplusplus/
    //linux: sys/stat.h, unistd.h
    //windows: direct.h
    //portable heavyweight: booost: #include <boost/filesystem/operations.hpp>
    //portable lightweight: dirent.h
    
    //linux only if you don't care!
    if(0)
    {
        #include <sys/stat.h>    
        if( mkdir("newdir",0777) == -1 )
        {
            puts("could not create newdir");
        }
        else
        {
            puts("newdir created");
        }

        puts("enter to remove newdir:");
        gets(s);
        
        #include <unistd.h>
        if( rmdir("newdir") == -1 )
        {
            puts("could not remove newdir");
        }
        else
        {
            puts("newdir removed");
        }
    }

    puts("");

    //path operations
    //puts(realpath("."));

    //TRY: echo "123" | ./c_cheatsheet.out
        //this will use stdin from a pipe! no user input
    
    //operators
    
    //math
        printf("2+1 = %d\n", 2+1);
        printf("high+4 = %d\n", i+j);
        printf("4*8 = %d\n", 4*8);

        //TODO teach
        printf("4/2 = %d\n", 4/2);
        printf("2/4 = %d\n", 2/4);
        printf("2/4 = %f\n", 2.f/4.f);
        printf("2/4 = %f\n", 2/4.f);
        printf("2/4 = %f\n", 2/(float)4); //type casting
        printf("2/4 = %f\n", ((float)2)/4);
        printf("2/4 = %f\n", (float)(2/4));

        //printf("4^2 = %d\n", 4^2); It's not exponation! not basic operation
        
        printf("10%%8 = %d\n", 10%8);
        //rest of division (modulo)

    // flow control

    //if
        if(1>2){
        printf("true 1>2\n");
        } 
        if(1<2){ 
        printf("true 1<2\n");
        }
        
        if(1<=2){ 
        printf("true 1<=2\n");
        } else {
        printf("true 1>2\n");
        }
        
        if(1>=2){ 
        printf("true 1=>2\n");
        } else {
        printf("true 1<2\n");
        }
        
        if(1>2){ 
        printf("true 1>2\n");
        } else if(1==2){
        printf("true 1==2\n");	
        }else {
        printf("true 1<2\n");
        }
     
    //no booleans true false in c, ints only! c++ only.
        //ERROR
            //bool b = true;
        printf("1==1 = %d\n", 1==1);
        printf("1==0 = %d\n", 1==0);

        //negation only as ==0
        i=1;
        printf("not i = %d\n", 1==0);

        //from <stdbool>
#include <stdbool.h>
            int b = true;
            printf("true = %d\n", true);
            printf("false = %d\n", false);

    //goto: don't use, but his is how the processor works!
    goto a;
    printf("no");
    a: printf("yes");
    printf("\n\n");
    
    //while
    i=0;
    while(i<10){
        printf("%d ",i);
        i++;	    
    }
    printf("\n");

    //for
    for(i=0; i<10; i++ ){//only when know how many times
        printf("%d ",i);
    }
    printf("\n");
    
    printf("\n");
    for(i=0; i<3; i++ ){ //only when know how many times
        for(j=0; j<3; j++ ){ //only when know how many times
        printf("%d %d\n",i,j);
        }
    }
    printf("\n");
    
    //functions
    printf("%d\n", pow2(1000,2) );
    printf("%.f\n", pow2f(2.f,2.5f) );

    //math
    puts("math");

#include <math.h>
#include <time.h>

    //constants
    printf("M_PI = %.2f\n", M_PI);
    printf("M_PI_2 = %.2f\n", M_PI_2);
    printf("M_PI_4 = %.2f\n", M_PI_4);
    
    //absolute value
    abs(-1.1); //1, abs returs INTEGER!!!!!
    fabs(-1.1); //1.1, fabs returs float

    //random values
        puts("random");
        srand ( time(NULL) );
        i = rand(); //integer between 0 and RAND_MAX
        f = rand()/(float)RAND_MAX; //float between 0 and 1

        float rand_range(float a, float b){ //float in a range
            return ((b-a)*((float)rand()/RAND_MAX))+a;
        }

    //enum
    enum DAY            /* Defines an enumeration type    */
    {
        saturday,         /* Names day and declares a         */
        sunday = 0,     /* variable named workday with    */ 
        monday,         /* that type                        */
        tuesday,
        wednesday,        /* wednesday is associated with 3 */
        thursday,
        friday
    };

    enum DAY today = wednesday;

    if(saturday<tuesday)
        puts("sturday < tuesday");

    enum escapes { BELL = '\a', BACKSPACE = '\b', HTAB = '\t',
                            RETURN = '\r', NEWLINE = '\n', VTAB = '\v' };

    //typedef combo
        typedef enum {RANDOM, IMMEDIATE, SEARCH} strategy;
        strategy my_strategy = IMMEDIATE;

    //main returns status
    return EXIT_SUCCESS;
    return EXIT_FAILURE;

}
