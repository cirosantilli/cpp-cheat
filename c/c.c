/*
main ansi c cheat, no extensions

certain features do not fit nicelly into the assertion format of this
cheat, and may have been moved to separate files.

features that require user input or that make programs wait
shall be put inside `if ( 0 ){ ... }` clauses to be turned on
only when users want to test those features.

#sources

    - <http://c-faq.com/index.html>

        good straight to the point faq, covers specially confusing points

    - <http://www.open-std.org/jtc1/sc22/wg14/www/standards>

        official directory containing the latest free draft versions of the ansi c specs

        the latest is: <http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf>

        the closest to the ansi standard that you can get for free (it is a paid standard...)

        this should be quite close to the actual speficications

        quite readable, and fun to find obscure features which you had never heard of before!

#motivation

    c is amazingly important as it is used to implement:

    - linux kernel
    - windows kernel
    - python and ruby reference implementation
    - opengl

    and the list goes on and on...

    the reason for this is that c:

    - is quite low level, so you can do low level things other languages can't
    - is low level, so it can be very fast (if you program it correctly)

#language versions

    #ANSI C

        language and standard library (libc) are standardized by an organization named ANSI

        ansi is american, and it represents the USA for ISO and IEC

        you must pay to have the latest standards

        however you can get for free:

        - drafts of the latest standard which are quite close to the actual specifications.

            It is strongly recommended that you download this now and try as much as you can to get familiar with it,
            as it is *the* official source.

        - older standards
        - compiler documentations

        ansi only specifies language and the library interfaces:
        what functions, variables etc. are contained in each file,
        but it does not specify how that should be implemented.

        some features are even left for the implementors to decide such as
        the behavoiur of [system][]

        new features are often based on extension of
        major implementations such as gnu's or microsoft's

        some language versions:

        - C11

            - previously known as c1x
            - latest standard, but limited support in most compilers
            - supported on gcc 4.6>. Flag: `-std=c1x`.
                It is not recommended to use this yet as support is low.
            - threads spported

        - C99

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

        besides the versions, ansi may also publishe minor corrections of versions

    #ansi extensions

        beside ansi language and libraries, you should also know about the existense of other
        standards which extend it:

        - posix c library. Offers many functions for posix compliant systems (linux, mac, not windows)

        - compiler and libc extensions

            Every compiler has certain language extensions which may be fundamenta for certain project.

            For example: gnu c is used on the linux kernel One major reason is support for inline assembly,
            which lacks in ansi c.

        if possible you should avoid relying on those since they are less portable.

        they shall not be documented here.

    #glibc

        name for the gnu implementation of the c standard library

#multithreading ipc concurrency

    - c11 supports it, c99 not

        glibc 2.x still does not have it.

    - c++11 supports it, c++03 not

    - openMP is is a library supported on C, C++, fortran, windows, linux macos

#doxigen

    documentation generation from commnets

    <http://www.stack.nl/~dimitri/doxygen/docblocks.html>

#libs

    this section is a list of whose main interface is c or which have a good c interface

    #petcs

        <http://www.mcs.anl.gov/petsc/documentation/index.html>
*/

/*
#preprocessor

    does simple stuff *before* compilation

    by simple understand non-turing complete.

    #include

        look in standard dirs directly:

            #include <file.h>

        looks in current dir first:

            #include "file.h"
*/

#include <assert.h>
#include <complex.h>   //complex constnats and arithemtic. c99.
#include <ctype.h>     //isspace
#include <fenv.h>
#include <float.h>     //
#include <iso646.h>    //and, or, etc macros
#include <limits.h>    //*_MAX, *_MIN for integer types
#include <locale.h>
#include <stdarg.h>    //... variable num of args
#include <signal.h>
#include <stdbool.h>   //true, false. c99
#include <stddef.h>    //offsetof
#include <stdint.h>    //uint32_t, etc.
#include <stdlib.h>    //malloc, EXIT_SUCCESS, EXIT_FAILURE:
#include <stdio.h>     //printf, puts
#include <string.h>    //strlen, strcpy
#include <math.h>
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
        //cannot create scopes here like that
        //they'd be useless

//#pointer #array

    int* get_arr( int i )
    {
        //int is[] = {i};
        //return is;
            //WARN
            //return adress of local var
            //data is destroyed on return!

        int* ip = (int*) malloc( sizeof( int ) * 1 );
        return ip;
    }

    //cheatsheet on pointers and arrays
    void print_array( int **mat, int m, int n )
    {
        int i, j;
        for ( i = 0; i < m; i++ )
        {
            for ( j = 0; j < n; j++ )
            {
                printf( "%d ", mat[i][j] );
            }
            printf( "\n" );
        }
    }

//#functions

    /*
    ERROR no func overload in c:

        void overload(int n){}
        void overload(float n){}
    */

    void func_int(int i){}
    void func_float(float f){}
    void func_double(double d){}

    void func_int_ptr (int *i){}
    void func_int_arr (int i[]){}

    void with_static_var()
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

    int add_int( int n, int m )
    {
        return n+m;
    }

    int subInt(int n, int m)
    {
        return n-m;
    }

    int int_func_int_int( int (*function_ptr)(int, int), int m, int n )
    {
        return (*function_ptr)(m, n);
    }

    /*
    #function struct args

        how to deal with passing structs to/from functions
    */

        struct FuncReturn { int i; };

        struct FuncReturn structReturn( struct FuncReturn sIn )
        {
            struct FuncReturn s_out;
            s_out.i = sIn.i + 1;
            return s_out;
        }

    /*
    #variadic functions

        these are functions with a variable number or arguments, just like `printf`.
    */

        int variadic_add( int numargs, ... )
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

    const static int n_prof_runs = 100000000;

    //only the loop.
    //discount this from every other profile run
    void loop_only_prof(int n)
    {
        int i;
        for( i=0; i<n; i++ );
    }

    void while_only_prof(int n)
    {
        int i = 0;
        while( i < n )
        {
            ++i;
        }
    }

    void int_assign_prof(int n)
    {
        int i,j;
        for( i=0; i<n; i++ )
            j=1;
    }

    void do_nothing(){}

    void func_all_prof(int n)
    {
        int i;
        for( i=0; i<n; i++ )
            do_nothing();
    }

    static inline void inline_do_nothing(){}

    void inline_func_call_prof(int n)
    {
        int i;
        for( i=0; i<n; i++ )
            inline_do_nothing();
    }

    void int_sum_prof(int n)
    {
        int i, j = 0;
        for( i=0; i<n; i++ )
            j = j + 0;
    }

    void int_sub_prof(int n)
    {
        int i, j = 0;
        for( i=n; i>0; i-- );
            j = j - 0;
    }

    void int_mult_prof(int n)
    {
        int i, j = 1;
        for( i=0; i<n; i++ )
            j = j * 1;
    }

    void int_div_prof(int n)
    {
        int i, j = 1;
        for( i=0; i<n; i++ )
            j = j / 1;
    }

    void float_sum_prof(int n)
    {
        float f;
        int i;
        for( i=0; i<n; i++ )
            f = f + 0.0;
    }

    void float_sub_prof(int n)
    {
        float f;
        int i;
        for( i=0; i<n; i++ )
            f = f - 0.0;
    }

    void float_mult_prof(int n)
    {
        int i;
        float j;
        for( i=0; i<n; i++ )
            j = j * 1.0;
    }

    void float_div_prof(int n)
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

    void stack1b_prof(int n)
    {
        int is[1];
        int i;
        for( i = 0; i < n; ++i )
        {
            int is[1];
        }
    }

    void stack1kb_prof(int n)
    {
        int is[1];
        int i;
        for( i = 0; i < n; ++i )
        {
            int is[0x800];
        }
    }

    void stack1mb_prof(int n)
    {
        int is[1];
        int i;
        for( i = 0; i < n; ++i )
        {
            int is[0xF0000];
        }
    }

    void heap1b_prof(int n)
    {
        char* cp;
        int i;
        for( i = 0; i < n; ++i )
        {
            cp = (char*) malloc( sizeof( char ) * 1 );
            free(cp);
        }
    }

    void heap1kb_prof(int n)
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
            return ( ( b - a ) * ( (float)rand() / RAND_MAX) ) + a;
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

int main( int argc, char** argv )
{
    /*
    //#scope inside a function

        every pair of keys, or constructs that uses keys such as `if`
        create a new scope

        you may define variables in that scope with the same names as external ones,
        but if you do so the external ones will become completelly invisible
    */
    {
        int i;

        //ERROR redeclaration

            //int i;

        {
            int i;

            //NOTE: impossible to access the outer `i` from now on in this scope!
        }
    }

    /*
    #base types

        types like `int`, `char`, `float` that are reserved language words
        with fixed meanings.
    */

    //#variables
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
    */

    /*
    #integer types

        types that represnt integer numbers are called integer types

        this classification is explicitly used on the c specification,
        some operations or rule of the c language are only valid for integer types

        `char` is also an integer type
    */
    {
        //#char
        {
            //char has fixed size 1 byte:

                assert( sizeof( char ) == 1 );

            //char literals are specified by single quotes

                { char c = 'a'; }

            //char literals are simply converted to the corresponding ascii integer value
            //for example, 'a' == 97:

                assert( 'a' == 97 );

            //char literals can contain any byte even those which have
            //no corresponding ascii value such as say, `130`.
            //To get those literal values, you should typecast from `int` as:

                { char c = (char)130; }

            //TODO possible via escape seqs?

            //TODO how to make a literal backslash char?
        }

        //short has no specific literals, must typecast:

        { short si = (short int)1; }
        { int i = 1; }
        { long li = (long int)1l; }
        { long li = (long int)1L; }
        { long long lli = 8ll; }
        { long long lli = 8LL; }

        //ERROR: no mixed cases allowed

            //{ long long lli = 8Ll; }

        //short, long and long long are the same as the int versions:

            assert( sizeof( short ) == sizeof( short int ) );
            assert( sizeof( long ) == sizeof( long int ) );
            assert( sizeof( long long ) == sizeof( long long int ) );

        //I prefer the version without `int` at the end

        //unsigned:

            { unsigned char uc = (unsigned char)1; }
            { unsigned short usi = (unsigned short int)1u; }
            { unsigned int ui = 1u; }
            { unsigned int ui = 1U; }
            { unsigned long uli = 1lu; }
            { unsigned long uli = 1LU; }
            { unsigned long long ulli = 1llu; }
            { unsigned long long ulli = 1LLU; }

            //we do not recommend those unless you are into code obfsucation:

                { unsigned long uli = 1Lu; }
                { unsigned long uli = 1lU; }
                { unsigned long long ulli = 1LLu; }
                { unsigned long long ulli = 1llU; }

            //ERROR:

                //{ unsigned long long ulli = 1Llu; }

        //#bases for integer literals
        {
            //hexadecimal:

                assert( 16 == 0x10    );
                assert( 16 == 0x10    );
                assert( 16 == 0x10l   );
                assert( 16 == 0x10ll  );
                assert( 16 == 0x10u   );
                assert( 16 == 0x10ul  );
                assert( 16 == 0x10ull );

            //octal:

                assert( 16 == 020 );

            //binary: no ansi way
        }
    }

    //#floating point types
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
    }

    /*
    #sizeof

        gives the size of the ram representation of types in bytes

        can be printed in printf with `%zu`

    #size_t

        `size_t` is the data type that specifies data sizes in libc

        always use it in your code to have more platform independance

    #size of base types

        base types like int of float don't have fixed ansi sizes: only a minimum value is specified.
        so machines are free to take optimal values in terms of speed/storage

        `char` is an exception as it has a fized size of one byte.

        for most modifier os similar types (ex: short int, int, long, long long)
        the ansi also guarantees size inequalities (equality is possible)

    #fixed size types

        besides the base times with nonfixed sizes, c99 ansi libc also furnishes
        fixed sized types. See

        you should only use those when having a fixed size is crucial,
        otherwise just use the base c types which are optimized for speed
        according to each architecture.
    */
    {

        size_t size = sizeof(int);

        puts( "sizeof (bytes):" );
        printf( "char        = %zu\n",  sizeof( char )          );
        printf( "int         = %zu\n",  sizeof( int )           );
        printf( "long int    = %zu\n",  sizeof( long int )      );
        printf( "long long   = %zu\n",  sizeof( long long )     );
        printf( "float       = %zu\n",  sizeof( float )         );
        printf( "double      = %zu\n",  sizeof( double )        );
        printf( "long double = %zu\n",  sizeof( long double )   );
        printf( "wchar_t     = %zu\n",  sizeof( wchar_t )       );
        printf( "size_t      = %zu\n",  sizeof( size_t )        );

        //char has fixed size:

            assert( sizeof( char )      == 1                        );

        //size equality is always possible:

            assert( sizeof( short int   ) <= sizeof( int            ) );
            assert( sizeof( int         ) <= sizeof( long int       ) );
            assert( sizeof( long int    ) <= sizeof( long long int  ) );

            assert( sizeof( float       ) <= sizeof( double         ) );
            assert( sizeof( double      ) <= sizeof( long double    ) );

        //unsigned does not change sizeof:

            assert( sizeof( unsigned int ) == sizeof( int ) );
            assert( sizeof( unsigned long int ) == sizeof( long int ) );
    }

    /*
    #stdint.h

        contains several types of ints, including fixed size
        and optimal for speed types

        c99

        all macros with numbers are defined for N = 8, 16, 32, 64
    */
    {

        //exactly 32 bits:

            assert( sizeof( int32_t) == 4 );

        //all have unsigned verions prefixed by 'u'

            assert( sizeof( uint32_t) == 4 );

        //at least 32 bits:

            assert( sizeof( int_least32_t ) >= 4 );

        //fastest operations with at least 32 bits:

            assert( sizeof( int_least32_t ) >= 4 );

        //an int with the right size to hold a pointer:

            assert( sizeof( int* ) == sizeof( intptr_t ) );

        //uniquelly defined by machine address space

        /*
        #intmax_t #uintmax_t

            int with max possible width

            [there is no floating point version](http://stackoverflow.com/questions/17189423/how-to-get-the-largest-precision-floating-point-data-type-of-implemenation-and-i/17189562?noredirect=1#comment24893431_17189562)
            for those macros
        */
        {
            assert( sizeof( intmax_t ) >= sizeof( long long ) );
            assert( sizeof( uintmax_t ) >= sizeof( unsigned long long ) );
        }

        //inttypes also includes limits for each of the defined types:
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

    /*
    #limits.h

        gives the maximum and minimum values that fit into base integer types
        in the current architecure
    */
    {

        printf( "INT_MAX = %d\n", INT_MAX );
        printf( "INT_MIN = %d\n", INT_MIN );
        printf( "LONG_MAX = %ld\n", LONG_MAX );
        printf( "LLONG_MIN = %lld\n", LLONG_MIN );

        /*
        unsigned versions start with `U`

        there is no min value for unsigned versions since it is necessarily 0
        */

        printf( "UINT_MAX = %u\n", UINT_MAX );
    }

    /*
    #float.h

        gives characteristics of floating point numbers and of base numerical operations
        for the current architecture
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
        */

        printf( "FLT_ROUNDS = %d\n", FLT_ROUNDS );

        /*
        #FLT_EVAL_METHOD

            precision to which floating point operations are evaluated

            it seems that floating operations on, say, floats can be evaluated
            as long doubles always.

            TODO 0: understand better
        */
        {
            printf( "FLT_EVAL_METHOD = %d\n", FLT_EVAL_METHOD );
        }

        /*
        #subnormal numbers

            one can check if those are supported in the implementation

            c11 feature TODO check. at least only in -std=c1x

            values:

            - -1: undeterminable
            - 0: no
            - 1: yes
        */

            //printf( "FLT_HAS_SUBNORM = %d\n", FLT_HAS_SUBNORM );
            //printf( "DBL_HAS_SUBNORM = %d\n", DBL_HAS_SUBNORM );
            //printf( "LDBL_HAS_SUBNORM = %d\n", LDBL_HAS_SUBNORM );

        /*
        #representation size

            several other macros expand to the lengths of the representation

            useful terms:

                1.01_b * b ^ (10)_b

            - radix:

            TODO lazy
        */

            //wow, there are non radix 2 representation implementations?!

            printf( "FLT_RADIX = %d\n", FLT_RADIX );
    }

    /*
    #fenv.h

        contains flags that indicate the status of floating point related registers

        TODO get some interesting and basic samples working
    */

    /*
    #unsigned

        c has unsigned versions

        these basically have more or less double the maximum size
        of the signed version, and are always positive.

        you should always use unsigned sizes for quantities which must be positive such as:

        - array indexes
        - memory sizes (size_t)

        as this will give clues to the compiler
        and humans about the positive quality of your number
    */
    {

        assert( (char)-1 == (char)255 );
        assert( (unsigned char)-1 == (unsigned char)255 );
            //true in 2's complement

        assert( (char)0 > (char)255 );
            //true in 2's complement
        assert( (unsigned char)0 < (unsigned char)255 );
            //what we really want
    }

    /*
    #overflow

        there is no automatic overflow check on operations
        except at initialization and assignment by constants
        at compile time.

        therefore, is something overflows,
        it just silently fails overflows, possibly causing a hard to find bug

        there is no check because that would cost time on every basice operation.
    */
    {

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

    /*
    #typecast

        transformation of one datatype to another

        can be done either implicitly or explicitly via a typecast operator

        some convertions may be possible to do implicitly
        but generate compiler warnings when done implicitly.
        this may depend on the compilation flags used

        some convertions always generate compilation errors.

        TODO understand this better
    */
    {
        //#typecasts with data modification

            //some typecasts are possible, but may alter the data to fit the new type

            //doubles are rounded down on typecast to int:

                assert( (int)0.1 == 0 );

            //however doubles that are too large to in the int are silently TODO what happens exactly

                printf( "typecast 1e10 = %d\n", (int)1e2 );
                printf( "typecast 1e100 = %d\n", (int)1e100 );

            //so don't rely on typecasting for rounding!

            //implicit typecast based on the variable type:

                {
                    int i;
                    i = 0.1;
                    assert( i == 0 );
                }

            //once again, the double is rounded down

            //long to int: there may be loss of precision if the long is too large to fit into the int

                //assert( (int) 0xFFFFFFFFFFL != 0xFFFFFFFFFF );

            //it is not possible to be sure about the exact values since the size of ints and longs
            //is not fixed by ansi, but they can happen!

        //#typecasts without data modification

            //if you convert a type to a type that is similar (floating point -> floating point)
            //but larger in size, there will be no modification of the data

            //int to long:

                assert( (long) 1 == 1L );

            //float to double:

                assert( (double) 1.0f == 1.0 );

            //array to pointer of same type:

                {
                    int is[3];
                    int* ip = (int*)is;
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

    //#const
    {
        int i = 0;
        const int ic = 0;
        //int const ic = 0
            //exact same thing!
        const int ic2 = i;

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

        this is why you can't int is[constint]; unless you have variable size arrays
        */
        {
            //const int ic = 0
            //int* ip = &ic;
            //*ip = 1;
            //assert( ic == 1 ):
        }

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

    /*
    #automatic

        is the name for the default way to declare var
        that is not volatile neither register
    */
    {
        int i;
    }

    /*
    #volatile

        compiler will not store this value in cpu registers as optimization
        instead of in RAM

        application: multithreading, where variable may to change value at any time
        if value were stored in register, other threads could not modify it
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
            //register int ri;
            //int* ip = &ri;
        }

        /*
        BAD: impossible to store compound type in registers
        compiler will certainly not honor `register` hint
        */
        {
            struct S { int i; };
            register struct S s;
        }
    }

    /*
    #inline keyword

        function is copied pasted instead of called

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
    #restrict keyword

        c99

        <http://en.wikipedia.org/wiki/Restrict>
    */

    /*
    #typedef

        create new types based on old ones

        on libc, convention append `_t` to typedefs is used
        ex: `size_t`, `wchar_t`, etc

        some of those macros are defined to be strcitly integer types (like size_t)
        while others can be either integer or floating points according to the implementation.

        to print integer typedefs such with `printf`, see `printf`
    */
    {

        {
            typedef int NEWINT;
            NEWINT i = 1;
            assert( sizeof(NEWINT) == sizeof(int) );
        }

        //NEWINT i = 1;
            //typedef has scope
    }

    //#enum
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

    /*
    #struct

        application:

        - declare lots of data in one go
        - pass lots of data in one go to functions
        - avoid changing function signatures if you add a new field
            to your struct.
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
            assert( s.i == 1 );
            assert( s.f == 1.0 );

            s.i = 2;
            s.f = 2;
            assert( s.i == 2 );
            assert( s.f == 2.0 );
        }

        //initialize by name
        {
            struct S s = {
                .f = 1.0,
                .i = 1
            };
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

        //array fields
        {
            struct S
            {
                //char cs[];
                    //ERROR
                char cs[4];
            };

            //ERROR

                //struct S = { .cs = "abc" }
        }

        {
            struct S {int i;} s = {1}, s2 = {2};
            int               i = 1  , i2 = 2;
        }

        //struct assign
        {
            struct S s  = { 1, 1.0 };
            struct S s2 = { 2, 2.0 };
            s = s2;
            assert( s.i == 2 );
            assert( s.f == 2.0 );
        }

        //typedef struct combo
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

        //#bitfields
        {
            //*i think* enforces the field size

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

        /*
        #offsetof

            get distance of member variable from the start of the struct

            appliction: get the struct that corresponds to a given pointer to a field.
            this is used in the kernel via `container_of`, and can be used to implement
            linked lists in ansi c: <http://stackoverflow.com/questions/10269685/kernels-container-of-any-way-to-make-it-iso-conforming>
        */
        {
            struct foo
            {
                char a;
                char b[2];
                int c;
                char d;
            };

            printf( "offsetof( struct foo, a ) = %zu\n", offsetof( struct foo, a ) );
            printf( "offsetof( struct foo, b ) = %zu\n", offsetof( struct foo, b ) );
            printf( "offsetof( struct foo, c ) = %zu\n", offsetof( struct foo, c ) );
            printf( "offsetof( struct foo, d ) = %zu\n", offsetof( struct foo, d ) );
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
            assert( u.i == 1 );
        }
    }

    //#operators
    {
        //#arithmetic
        {
            assert( ( 1 + 2 )        == 3   );
            assert( ( 2 * 3 )        == 6   );
            assert( ( 4 / 2 )        == 2   );
            assert( ( 1 / 2 )        == 0   );
            assert( ( 1.0 / 2.0 )    == 0.5 );
            assert( ( 1 / 2.0 )      == 0.5 );
            assert( ( 1 / (double)2) == 0.5 );

            //#division by 0

                //time to have some fun and make the program crash by uncommenting code!

                //WARN: division by 0:

                    //{int i = 1 / 0;}

                //RUNTIME ERROR: floating point exception

                    //{
                    //    int z = 0;
                    //    z = z / z;
                    //}

                    //{
                    //    int z = 0;
                    //    z = 1 / z;
                    //}

                //TODO is it possible to avoid fp exception nicely?

            assert( ( 3 % 3 ) == 0 );
            assert( ( 4 % 3 ) == 1 );
            assert( ( 5 % 3 ) == 2 );
            assert( ( 6 % 3 ) == 0 );
        }

        //#boolean
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

        //#bitwise
        {
            //#NOT
            assert( (~(char)0x00) == (char)0xFF );
            assert( (~(char)0xFF) == (char)0x00 );

            //#OR
            assert( ((char)0x00 & (char)0x00 ) == (char)0x00 );
            assert( ((char)0xFF & (char)0x00 ) == (char)0x00 );
            assert( ((char)0xFF & (char)0xFF ) == (char)0xFF );

            //#XOR
            assert( ((char)0x00 ^ (char)0x00 ) == (char)0x00 );
            assert( ((char)0xFF ^ (char)0x00 ) == (char)0xFF );
            assert( ((char)0xFF ^ (char)0xFF ) == (char)0x00 );

            //#shift
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

        //#assign
        {
            int i = 0;
            assert( (i=1) == 1 );
            //= returns right side
            assert( i == 1 );

            /*
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

        //#question mark #?
        {
            assert( ( 1 < 2 ? 3 : 4 ) == 3 );
            assert( ( 1 > 2 ? 3 : 4 ) == 4 );
        }

        /*
        #comma operator

            almost useless
        */
        {
            //comma here is separator, not operator. same comma in functions calls/defs:
            int i=0, a=1, b=2, c=3;

            /*
            ignores values on left
            takes only last value on right

            BAD: operations on left has no effect
            */
            assert( ( i = 0, 1        ) == 1 );
            assert( ( i = 0, i = 1, 2 ) == 2 );

            /*
            assign has precedence over comma
            BAD: operation on right has no effect
            */
            {
                i = 2;
                (i = 0), 1;
                i = 0, 1;
                assert( i == 0);
            }

            //int j=0, 1;
                //ERROR
                //declaration int j does not return a value

            //operation on left comes first
            {
                i=2;
                assert( (i=0, i) == 0);
                i=2;
                assert( (i=0, i++, i) == 1);
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

        printf( "(void*)pi = %p\n", (void*)pi );
        printf( "(void*)(pi+1) = %p\n",(void*)(pi+1) );

        //OK: implicit conversion * -> int:

            pi2 = pi + 1;
            printf( "(void*)(pi2-pi) = %p\n", (void*)(pi2-pi) );
            assert( pi2 - pi == 1 );

        //ERROR: incompatible pointer type

            //float* fp = &i;

        //OK: works with explicit cast:

            float* fp = (float*)&i;

        /*
        #NULL pointer

            good source: <http://c-faq.com/null/macro.html>

            basic usage: indicate error as return value from function
        */
        {
            //why it works: it never points to any possible valid memory location.
            //(`&` operator never gives anything equal to it).
            //this is so guaranteed that gcc emmits a warning in the following code
            {
                //int i = 0;
                //assert( &i != NULL );
            }

            //how it prints like:

                printf( "NULL = %p\n", NULL );

            //`if(NULL)` and `if(!NULL)` in error checking code always work as expected

                assert( !NULL );

            /*
                relationship to 0: `(int*)0`, `(char*)0` or any other pointer type followed by zero
                is always converted internally to the null pointer

                this is a valid way of representing the null pointer,
                but it is better style to always use the `NULL` macro
            */
            {
                assert( NULL == (int*)0 );
                assert( NULL == (char*)0 );
            }

            //ERROR: comparison of distinct pointer types requires a cast:
            {
                //assert( (int*)0 == (char*)0 );
            }

            //never dereference the NULL pointer since it is guaranteed to point to nothing
            {
                //RUNTIME ERROR: segmentation fault
                    //int i = *(int*)NULL;
            }
        }

        /*
        #void pointer

            special pointer type (since there is no corresponding void data...)

            cannot be dereferenced without typecast (since you don't know its size)

            can be typecast to/from anything TODO confirm
        */
        {
            void* vp;
            int* ip;
            int i = 0;

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

            //#variable length array
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

        /*
        #bounds breaking

            time to break down the program by making this access memory
            locations it should not try to access! =)

            when the os sees that, it may crash down the program with a segmentation fault.

            note however that this does not always happen, as a program may
            just access another location inside its legal memory address space
            but in a completelly unpredicatable manner, and the os has no way to it did this

            this leads to very hard to debug errors, but is invitable if you want
            to avoid the overhead of checking arrays bounds on every dereference
        */
        {

            //printf("%d\n",is[3]);
            //is[3]=0;
            //printf("%d\n",is[1000000]);
            //is[1000000]=0;

            //for(i=0; i<=1000000000; i++ ){
            //        printf("%d\n",i);
            //        j=is[i];
            //}
            //    segmentation fault
        }

        //#compare arrays
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

                assert( cs[0] == 'a'  );
                assert( cs[1] == 'b'  );
                assert( cs[2] == 'c'  );
                assert( cs[3] == '\0' );

                cs[0] = 'A';
                assert( strcmp(cs, "Abc") == 0 );

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
                    assert( cs[0] == 'a' );

                //RUNTIME ERROR: text segment cannot be modified

                    //cs[0] = '0';

                //TODO why can't you do the same thing with integers? ex:

                    //int * is = { 1, 3, 2 };
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
                    printf(">>>%c<<< null char\n",'\0');
                    puts(">>>\x61<<< a in hexadecimal");
                    puts(">>>\xe4\xb8\xad<<< zhong1, chinese for \"middle\" in utf8");  //chinese utf8
                }

                //string literals may be concatenated
                //no spaces are implied
                {
                    char cs[] = "ab" "cd";
                    assert( strcmp( cs, "abcd" ) == 0 );

                    //this cannot be done with variables,
                    //but can be useful if you have a string that is defined in a macro:
                    {
#define STRING_AB "ab"
                        char cs[] = STRING_AB "cd";
                        assert( strcmp( cs, "abcd" ) == 0 );
                    }

                    //another application is to break a long string literal over severl lines
                    //no newline is implied
                    {
                        char cs[] = "ab"
                                    "cd";
                        assert( strcmp( cs, "abcd" ) == 0 );
                    }
                }
            }

            //#libc string functions
            {
                //use '\0' to see ther string ends

                //#sprintf
                {
                    //for the possible formatrings, see [printf][]

                    char cs[] = "123";
                    char cs2[4];
                    sprintf( cs2, "%s", cs );
                    assert( strcmp( cs, cs2 ) == 0 );
                }

                /*
                #snprintf

                    like `sprintf`, but writes at most n bytes, so it is safer,
                    because it may not be possible or easy to calculate the resulting
                    size of a formated string.

                    NOTE: the size given *includes* the null terminator

                    c99
                */
                {
                    char cs[] = "123";
                    char cs2[3];
                    snprintf( cs2, 3, "%s", cs );
                    assert( strcmp( cs2, "12" ) == 0 );
                }

                //#length
                {
                    char cs[] = "abc";
                    assert( strlen( cs ) == 3 );
                }

                //#copy
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

                //#compare
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

                //#concatenate
                {

                    char s1[5];
                    strcpy( s1, "ab" );
                    char s2[] = "cd";
                    strcat( s1, s2 );
                    assert( strcmp( s1, "abcd" ) == 0 );
                    assert( strcmp( s2, "cd"   ) == 0 );
                }

                //#strchr
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

                /*
                #ctype

                    character classficiation functions
                */

                    //#isspace

                        assert(   isspace( ' '  ) );
                        assert(   isspace( '\n' ) );
                        assert( ! isspace( 'a'  ) );

                    //#isdigit

                        assert(   isdigit('0') );
                        assert( ! isdigit('a') );
            }

            //#unicode
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

                    setlocale( LC_CTYPE, "" );

                wchar_t  wcs[] = L"汉语";

                printf( "%ls\n", wcs );

                wcs[0] = L'英';
                printf( "%ls\n", wcs );

                wcs[0] = L'a';
                printf( "%ls\n", wcs );

                //ERROR: non wide init

                    //wchar_t  wideString2[] = "asdf";
            }
        }
    }

    /*
    #dynamic allocation #malloc

        allocates ammounts of memory that are only known at runtime,
        not compile time.

        #dynamic allocation vs VLA

        - no scope

            therefore can be allocated in functions
            and returned to caller

        - heap much larger than stack
    */
    {
        int i = 8;
        size_t bytes = sizeof( char ) * i;
        char* cp = (char*) malloc( bytes );
        if ( cp == NULL )
        {
            printf("could not allocate %zu bytes", bytes);
        }
        free( cp );

        /*
        if you try to allocate too much memory,
        `malloc` may fail, or your os will eventually decide to kill your naughty program

        time to try that out!
        */
        {
            //TODO 0 how to pass more than INT_MAX to malloc to break it? =)

            if ( 0 )
            {
                size_t n = 1024 * 1024 * 1024;
                int* ip = malloc( n );
                if ( ip == NULL )
                {
                    printf( "could not allocate %zu bytes", n );
                }
                free( ip );
            }

            //allocate 1024 Petabytes of RAM in 1 gb chunks!!!
            //someday this will be possible and people will laugh at this...
            //generates a segfault
            if ( 0 )
            {
                const size_t GB = 1024 * 1024 * 1024;
                for ( int i = 0; i < GB; i++ )
                {
                    int* ip = malloc( GB );
                    ip[0] = 0;
                    if ( ip == NULL )
                    {
                        printf( "could not allocate %zu bytes", GB );
                    }
                }
            }
        }
    }

    //#branching
    {

        //#goto
        {
            //never use this
            //tranlates to `jmp` in x86 isa

            goto a;
                assert(0);
            a:
            assert(1);
        }

        //#if
        {
            if ( -1 )
            {
                assert(1);
            }
            if ( 0 )
            {
                assert(0);
            }
            if ( 1 )
            {
                assert(1);
            }

            //#scope
            {
                int i = 0;
                if ( 1 )
                {
                    int i = 1;
                    assert( i == 1 );
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
            assert( true  == 1 );
            assert( false == 0 );
        }

        /*
        #switch

            only exists for readability (TODO 0 check: no preformance gain?)
        */
        {
            int i, j;
            for( i = -1; i < 3; i++ )
            {
                switch ( i )
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

        /*
        #for vs while

            in theory, whatever you can to with for you can do with while

            however x86 has a loop instruction that increments and
            contional jumps in a single step

            therefore, using a simple for is a better hinto to your
            compiler to use this more efficient looping instruction

            moral: if you when know how many loops you will do, use `for`,
            otherwise use `while`
        */

        //#for
        {
            //basic example
            {

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
                        //`int i2 = 2*i*i + 3*i + ( i % 2 );`
                        //so you have to type this huge expression twice!
                        //so if you change one you have to change the other
                        //and you risk to forget creating a hard to find bug

                        //write a function that does 2*i*i + 3*i + ( i % 2 );
                        //this function is almost useless (used only twice)
                        //adding needless boilerplate to your code

                    //both of which are not very attractive alternatives
            }
        }

        /*
        #function

            a function is basically a branch, but in which you have to:

            - know where to jump back to after return
            - pass arguments
            - get back a return value
        */
        {
            //if there is a typecast possible, it all compiles fine
            {
                func_int(1.1);
                func_float(1);
            }

            puts("static variable in functions");
            {
                with_static_var();
                    //a = 2, sa = 2
                with_static_var();
                    //a = 2, sa = 3
            }

            puts("func pointers");
            {
                assert( add_int != subInt );
                assert( int_func_int_int(&add_int,2,1) == 3 );
                assert( int_func_int_int(&subInt,2,1) == 1 );
            }

            //#variadic function
            {
                assert( variadic_add( 3, 1, 2, 3 )       == 6 );
                assert( variadic_add( 5, 1, 2, 3, 4, 5 ) == 15 );
            }
        }
    }

    //#command line args
    {
        printf( "argv[0] = %s\n", argv[0] );
        int i = 0;
        if ( argc > i )
        {
            i++;
            printf( "argv[%d] = %s\n", i, argv[0] );
        }
        if ( argc > i )
        {
            i++;
            printf( "argv[%d] = %s\n", i, argv[0] );
        }
    }

    //#enviroment variables
    {
        //#getenv

            //printf( "getenv( \"HOME\" ) = \"%s\"\n", getenv( "HOME" ) );
            //assert( getenv( "HOME" ) );
            //assert( ! getenv( "IDONTEXIST" ) );

        //TODO: setenv in POSIX but not in ANSI C?
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

        //#standard preprocessor defines
        {

            //some vars are automatically defined by certain compilers
            //although they are not c standards. Those are not discussed here.

            //List of standard defines: <http://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html>

            //string representing version of the c std lib. Format: yyyymm (base 10):

        printf( "__STDC_VERSION__ = %li\n", __STDC_VERSION__ );

            //absolute or relative path of current file:

        printf( "__FILE__ = %s\n", __FILE__ );

            //source code line:

        printf( "__LINE__ = %d\n", __LINE__ );

            //if in a `.h`, position inside the `.h`

        /*
        # __func__

            if inside a function, the name of that function.

            this is not a normal macro, since the preprocessor cannot know
            the current function name, because the preprocessor does not parse

            c99
        */

            printf( "__func__ = %s\n", __func__ );

        printf( "__DATE__ = %s\n", __DATE__ );

        printf( "__TIME__ = %s\n", __TIME__ );

            //cpp compiler is being used:

        printf( "__LINE__ = %d\n", __LINE__ );

#ifdef __cplusplus
        puts("__cplusplus");
#endif

        //automatically defined by certain compilers on windows:
        //TODO gcc specific or not? if yes move out of here.

#ifdef __WIN32__
        puts("__WIN32__");
#endif

        //TODO what is this
        //TODO gcc specific or not? if yes move out of here.

#ifdef _LIBC
        puts("_LIBC");
#endif

    //TODO what is this
    //TODO gcc specific or not? if yes move out of here.

#ifdef __ILP32__
        puts("__ILP32__");
#endif

    //TODO what is this
    //TODO gcc specific or not? if yes move out of here.

#ifdef ___X32_SYSCALL_BIT
        puts("___X32_SYSCALL_BIT");
#endif

        }
    }

    /*
    #trigraphs

        absolutelly obscure feature for very old systems which do not support certain
        characters or because of keyboards which don't support them easily

        it is so obscure that gcc even emmits a warning if you use those!!

        is the first substitution made to source, even before the preprocessor

        they are commented out here so that compilers like
        gcc won't annoy us with warnings
    */
    {
            //assert( '??=' == '#' );
            //assert( '??(' == '[' );
            //assert( '??/' == '\' );   //TODO 0 literal backslash?
            //assert( '??)' == ']' );
            //assert( '??'' == '^' );
            //assert( '??<' == '{' );
            //assert( '??!' == '|' );
            //assert( '??>' == '}' );
            //assert( '??-' == '~' );

        //TODO 0 how to escape a trigraph on a string literal, say: `??=` ?
        //is it necessary to use `\x`?

            //printf( "??" )
    }

    /*
    #complex.h

        C99
    */
    {
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

        /*
        #complex integer

            complex integer types are not specified.

            GCC adds them as an extension
        */

            //int complex zi = 1 + 1*I;
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

                //int r = system( "echo a | grep b" );
                //assert( r == 1 );
        }
    }

    /*
    #stdio

        stream Input and Output
    */
    {
        /*
        #stream

            an stream is an abstraction over different input/output methods
            such as regular files, stdin/stdout/stderr (pipes in linux), etc.
            so that all of them can be treated on an uniform basis once you opened the stream.

            most functions have a form which outputs only to stdout,
            and most input functions have a form which reads only from sdtin
            coupled with a general form that outputs to any stream.

            unfortunatelly, sometimes there are subtle differences between those two
            forms, so beawere!

        #FILE

            FILE is a macro that represents a stream object

            its name is FILE of course because files are one of the main types of streams.

        #stream vs file descriptors

            a file descriptor is a POSIX concept and thus shall not be discussed here.

        //TODO
            //setvbuf: set io buffer size, must be used on open stream
            //flush:    flush io buffer
            //freopen
        */

        /*
        #EOF

            TODO what is EOF on a system level
            what happens when I hit ctrl+d on bash + getchar?
            current guess: a pipe close

            in linux, EOF does not exist

            the only way to know if a file is over is to make a `sys_read` call
            and check if you get less bytes than you ask for
            (`sys_read` returns the number of bytes read)

            alternativelly, for fds that are files, you can use `sys_stat` in linux,
            but there is no portable stat func

            what was said for linux is similar for windows
            and similar for c thus

            EOF is a c concept

            EOF works because there are only 256 bytes you can get from an fd
            so EOF is just some int outside of the possible 0-255 range, tipically -1
        */

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

            /*
            #printf

                write formated to sdtout

                newline not added at end

                it is very useful to learn the format strings,
                since this has become a defacto standard and is also used
                in python format strings and bash `printf` command.

                does may not be up to data with the latest new modifiers.

                # sources

                    readable documentation on the c++11 format strings <http://www.cplusplus.com/reference/clibrary/cstdio/printf/>
                    should be close to the latest c, and backwards compatible
            */
            {
                char s[256];

                //char:

                    printf( "%c\n", 'a' );

                //int:

                    printf("d INT_MAX = %d\n", INT_MAX);

                //long int:

                    printf("d LONG_MAX = %ld\n", LONG_MAX);

                //long long (int):

                    printf("lld LLONG_MAX = %lld\n", LLONG_MAX);

                //you must keep unsigned correctness
                //or prepare to get bitten by overflow problems:

                    printf( "u UINT_MAX = %u\n", UINT_MAX );
                    printf( "d UINT_MAX = %d\n", UINT_MAX ); //-1

                //note how printf treats `UINT_MAX` as a signed integer
                //which in 2's complement equals `-1`.

                //WARN: expects unsigned int, found int
                //that is, you must keep unsigned correctness

                    //printf("u -1 = %u\n", -1);
                    //printf("u -1 = %lu\n", -1);

                printf("%d %d\n",1,2);

                //#floating point numbers
                {
                    //float and double (both the same char, float gets typecast):

                        printf( "printf float = %f\n", 1.0f );
                        printf( "printf double = %f\n", 1.0 );

                    //long double:

                        printf( "f = %f\n", 1.0 );

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

                //srings:

                    printf( "%s\n", "a string" );

                printf( "%s\n", "\t<<< \\t tab char" );
                printf( "%s\n", "\0<<< \\0 null char" );

                //hexadecimal output:

                    printf( "%x\n", 16 );

                //pointers:

                    float f;
                    printf( "(void*)&f = %p\n", (void*)&f );
                        //prints the 0x address.
                        //%p must get a void pointer
                        //void* is a type, different than void. doing type cast to it.

                    printf( "%%<<< escaping percentage\n" );
                        //note that this is printf specific
                        //not string specific

                /*
                #printf typedefs

                    some integer typedefs have a specific printf format, others don't

                    others don't. For those, rirst cast them to `uintmax_t` and then printf with `%ju`
                */
                {
                    //have specific format strings

                        printf( "printf size_t = %zu\n", (size_t)1 );
                        printf( "printf size_t = %jd\n", (intmax_t)1 );
                        printf( "printf size_t = %ju\n", (uintmax_t)1 );

                    //don't have specific format strings: TODO find one, clock_t is not defined integer or float

                        //printf( "printf clock_t = %ju\n", (uintmax_t)(clock_t)1 );

                    /*
                    if a typedef is not guaranteed to be either an integer type or a floating point type,
                    just cast it to the largest floating point type possible

                    unfortunatelly, as of c11 there is no way to get the largets floating point type
                    as can be done for integers: <http://stackoverflow.com/questions/17189423/how-to-get-the-largest-precision-floating-point-data-type-of-implemenation-and-i/17189562>

                    */

                        printf( "printf clock_t = %Lf\n", (long double)(clock_t)1 );
                }
            }

            /*
            #fprintf

                same as printf, but to an arbitrary stream
            */
            {
                FILE* fp = stderr;
                fprintf( stderr, "fprintf = %d\n", 1 );
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

        /*
        #stderr

            the `stderr` stream is open and accessible via `FILE* stderr`,
            so you can output ot it with any function which outputs to a stream such as
            `fputs` or `fprintf`.

            the `stdout` identifier is also made available, but seldom used since
            most functions have a version which by default outputs to stdout.
        */
        {
            {
                //puts and printf to any fd, not just stdout

                fputs( "stdout\n", stdout );
                fputs( "stderr\n", stderr );
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
            if ( 0 )
            {

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

            /*
            #gets

                deprecated c11

                dangerous:
                no size checking possible
                if too much input, just seg faults
            */
            if ( 0 )
            {
                    //printf("enter a string terminated by newline: (max %d chars, newline will be included in the string)\n", sn);
                    //gets(s);
                    //printf("you entered:\n%s\n\n",s);
            }

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
            if ( 0 )
            {
                FILE* fp = stdin;
                const int buff_size = 4;
                char buff[buff_size];
                fprintf( stderr, "enter a string and press enter (max %d bytes):\n", buff_size - 1 );
                if ( fgets( buff, buff_size, fp ) == NULL )
                {
                    if ( feof( fp ) )
                    {
                        fprintf( stderr, "fgets was already at the end of the stream and read nothing" );
                    }
                    else if ( ferror( fp ) )
                    {
                        fprintf( stderr, "fgets error reading from stream" );
                    }
                }
                //some bytes are left in the buffer, may want to reread it.
                else if ( ! feof( fp ) )
                {
                    //TODO why does this not work with stdin from a tty nor pipe?
                    //why is eof not reached even if user inputs 1 single char?

                        //fprintf( stderr, "you entered more than the maximum number of bytes\n" );

                    //TODO why does this not work? why is eof not reached even if user inputs 1 single char?
                }
                fprintf( stderr, "you entered:\n%s", buff );
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
            if ( 0 )
            {
                int i, j;
                unsigned int ui;
                float f;
                printf( "enter an integer in decimal and <enter> (max 32 bits signed):\n" );
                i = scanf( "%d", &i );
                printf( "you entered: %d\n", i );
                //stuff is space separated
                //try 123 456 789 at once. 456 789 stay in the buffer, and are eaten by the second scanf

                printf( "enter an integer, a space, an integer and a <enter> (max 32 bits signed):\n" );
                i = scanf( "%d %d", &i, &j );
                printf( "you entered: %d %d\n", i, j );

                printf( "enter a float and a newline:\n" );
                i = scanf( "%f", &f );
                printf( "you entered: %.2f\n", f );

                printf( "enter an integer in hexadecimal and a <enter>: (max 32 bits signed)\n" );
                i = scanf( "%x", &ui );
                printf( "you entered (in decimal): %d\n", i );
            }

            /*
            #fscanf

                complicated like scanf
            */
            if ( 0 )
            {
                FILE* fp = stdin;
                int i;
                float f;
                puts( "enter a int a space and a float (scientific notation) and then EOF (ctrl-d in linux):" );
                if ( fscanf( stdin, "%d %e\n", &i, &f ) != 2 )
                {
                    if ( feof( fp ) )
                    {
                        fprintf( stderr, "fscanf reached the of file and read nothing\n" );
                    } else if ( ferror( fp ) ) {
                        fprintf( stderr, "fscanf error reading from stream\n" );
                    }
                }
                fprintf( stderr, "you entered: %d %.2e\n", i, f );
            }
        }

        /*
        #file streams

            to get streams that deal with files, use fopen

            to close those streams, use fclose

            #fopen

                open file for read/write

                don't forget to fclose after using! open streams are a process resource.

                modes:

                - r: read. compatible with a,w
                - w: read and write. destroy if exists, create if not.
                - a: append. write to the end. creates if does not exist.
                - +: can do both input and output. msut use flush or fseek
                - x: don't destroy if exist (c11, not c++!, posix only)
                - b: binary. means nothing in POSIX systems,
                    on our dear DOS must be used for NL vs NLCR problems
                    there are two different modes there
                    Therefore, for portability, make this difference.

            #text vs binary

                #text vs binary for numerical types

                    example: an int 123 can be written to a file in two ways:

                    - text: three bytes containing the ascii values of `1`, `2` and then `3`
                    - binary: as the internal int representation of the c value, that is 4 bytes,
                        with `123` in binary and zeroes at the front.

                    advantages of text:

                    - it is human readable since it contains only ASCII or UTF values
                    - for small values it may be more efficient (123 is 3 bytes in ascii instead of 4 in binary)

                    advantages of binary:

                    - it is shorter for large integers
                    - inevitable for data that cannot be interpretred as text (images, executables)

                #newline vs carriage return newline

                    newline carriage return realated TODO confirm

                    for portability, use it consistently.

                    In linux the difference between text methods and binary methods is only conceptual:
                    some methods output human readable text (`fprintf`) and can be classified as text,
                    while others output binary, no difference is made at file opening time

            #fclose

                don't forget to close!

                there is a limited ammount of open files at a time by the os

                buffered output may not have been saved before closing
        */
        {
            FILE* fp;
            int err, had_error, fi;
            float ff;
            char c1;
            char *cp1;

            const int buff_size = 16;
            char path[buff_size], buff[buff_size];

            //simple example of file io:
            {
                strcpy( path, "f.tmp" );
                fp = fopen( path, "w" );
                if ( !fp )
                {
                    report_cant_open_file(path);
                    exit( EXIT_FAILURE );
                }
                else
                {
                    if ( fputc( 'a', fp ) == EOF )
                    {
                        report_cant_write_file( path );
                        exit( EXIT_FAILURE );
                    }
                }
                if( fclose(fp) == EOF )
                {
                    fprintf(stderr, "could not close:\n%s\n", path);
                }
            }
        }

        //#binary io
        {
            int elems_write[] = { 1, 2, 3 };
            const int nelems = sizeof(elems_write) / sizeof(elems_write[0]);
            int elems_read[nelems];

            FILE* fp;
            char path[] = "fwrite.tmp";

            //#fwrite
            {
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
            //#ftell
                //long int curpos = ftell(pf)
                //if ( curpos == -1L ){
                //    report_cant_move_file();
                //}

            //#fseek
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

            //#flush(fp)
                //for output streams only.
                //makes sure all the data is put on the stream.
                //
                // if (flush(fp) == EOF){
                //        //error
                // }

            //#freopen
                //freopen("/dev/null", "r", stdin);
                //this will discard stdin on linux

            //TODO ? fgetpos, fsetpos, rewind
            //

            //TRY: echo "123" | ./c_cheatsheet.out
                //this will use stdin from a pipe! no user input
        }

        //#applications
        {
            //string to from file
            {
                FILE* fp;
                char path[] = "str_file.tmp";
                char cs[] = "asdf\nqwer";

                //write entire string to file at once
                {
                    if ( file_write( path, cs ) == -1 )
                    {
                        report_cant_write_file(path);
                    }
                }

                //read entire file at once to a string
                {
                    char* cp = file_read(path);
                    if ( cp == NULL )
                    {
                        report_cant_read_file(path);
                    }
                    assert( strcmp( cs, cp ) == 0 );
                    free(cp);
                }
            }

            //simple write arrays to file
            {
                FILE* fp;
                char path[16];

                int arri[] = { 0, 1, -1, 12873453 };
                float arrf[] = { 1.1f, 1.001f, -1.1f, 1.23456e2 };

                strcpy( path, "arri.tmp" );
                write_int_arr_file( path, arri, 4 );

                strcpy( path, "arrf.tmp" );
                write_float_arr_file( path, arrf, 4, 2 );
            }
        }
    }

    //#time.h
    {
        /*
        #time()

            seconds since 1970
        */

            printf( "time() = %ld\n", time(NULL) );

        //#CLOCKS_PER_SEC

            printf( "CLOCKS_PER_SEC = %ld\n", CLOCKS_PER_SEC );

        /*
        #clock()

            program virtual time in number of processor clock clicks

            precision is quite limited, and if too few clicks pass, it may return 0.
        */
        if ( 0 )
        {
            clock_t t;
            int i = 0;
            t = clock();

            /*
            busy waiting

            WARNING: optimizer may simply skip your useless test operations
            and very little time will have passed
            */
                int j = 0;
                for ( int i = 0; i < CLOCKS_PER_SEC * 10; i++ ){ j++; }

            t = clock() - t;

            //there is no printf specifier for `clock_t`
            //so cast to largest possible integer type:

                printf( "clicks = %llu\n", (intmax_t)t );

            printf( "seconds = %f\n", ((float)t) / CLOCKS_PER_SEC );
        }
    }

    //#math.h
    {
        //max and min for floats (C99):

            assert( fminl( 0.1, 0.2 ) == 0.1 );
            assert( fmaxl( 0.1, 0.2 ) == 0.2 );

        //exponential:

            assert( fabs( exp(1.0)      - 2.71 )    < 0.01 );

        //trig:

            assert( fabs( cos(0.0)      - 1.0 )     < 0.01 );

        //this is a standard way to get PI. The only problem is the slight calculation overhead.

            assert( fabs( acos(-1.0)    - 3.14 )    < 0.01 );

        //absolute values, integer version:

            assert( abs(-1.1)  == 1 );

        //absolute values, float version:

            assert( fabsl(-1.1) == 1.1 );

        //don't forget to use the float version!

        //#random
        {
            //seed the random number generator with the current time

            //

            srand ( time( NULL ) );

            //integer between 0 and RAND_MAX:

                int i = rand();

            //float between 0 and 1:

                float f = rand()/(float)RAND_MAX;
        }
    }

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
        assert( true and true );
    }

#ifdef PROFILE

    //- turn off optimization if you want results to make evident sense
    //- even without optimization, cache access speed is hard to predict
    //   so what you expect may be false

    loop_only_prof( n_prof_runs );
    while_only_prof( n_prof_runs );

    int_assign_prof( n_prof_runs );
    int_sum_prof( n_prof_runs );
    int_sub_prof( n_prof_runs );
    int_mult_prof( n_prof_runs );
    int_div_prof( n_prof_runs );

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

    //main returns status:

        return EXIT_SUCCESS;
        return EXIT_FAILURE;
}
