/*# function

    A function is basically a branch, but in which you have to:

    - know where to jump back to after return
    - pass arguments
    - get back a return value
*/

#include "common.h"

void func_int(int i) {}
void func_float(float f) {}
void func_double(double d) {}

/* Struct arguments and return */

    struct struct_func_struct {
        int i;
        int j;
    };

    struct struct_func_struct struct_func() {
        return (struct struct_func_struct){ 0, 1 };
    }

/*
Declaration vs definition
*/

    /* Two decls on the same line, with same return type: */
    int decl_1(), decl_2();
    int decl_1(){ return 1; }
    int decl_2(){ return 2; }

    void decl_def();
    void decl_def();
    void decl_def() {}
    /* ERROR redefine */
    /*void decl_def() {}*/

    int factorial2funcs1(int);
    int factorial2funcs0(int n){
        if (n != 1) {
            return n*factorial2funcs1(n - 1);
        }
        return 1;
    }
    int factorial2funcs1(int n){
        if (n != 1) {
            return n*factorial2funcs0(n - 1);
        }
        return 1;
    }

#if __STDC_VERSION__ <= 199901L
    /*default_return_type() { return 1; }*/
#endif

    int proto_empty_definition() {
        return 1;
    }

        /* ERROR cannot define on same line */
        /*int decl_3(){return 3;}, decl_4(){return 4;};*/

    /* Can declare a function that returns int and a int var with the same `int`. */
    /* Very confusing! */

        int decl_and_initialize_func(), decl_and_initialize;
        int decl_and_initialize_func(){ return 0; }

    int k_and_r(a, p)
        int a;
        char *p;
    {
        return 0;
    }

/*
# overload

    There is no function overloading in C to avoid name mangling:
    C ABI simplicity is one of it's greatest strengths:
    http://stackoverflow.com/questions/8773992/c11-type-generic-expressions-why-not-just-add-function-overloading

    C11 introduces generics, which allow for a similar, albeit more limited effect.
*/

    void overload(int n) {}

    /* ERRORS: */

        /*void overload(float n) {}*/
        /*void overload(int n, int o) {}*/

void func_int_ptr (int *i) {}
void func_int_arr (int i[]) {}

/*
function struct args

    how to deal with passing structs to/from functions
*/

    struct FuncReturn { int i; };

    struct FuncReturn structReturn(struct FuncReturn sIn) {
        struct FuncReturn s_out;
        s_out.i = sIn.i + 1;
        return s_out;
    }

/* # return const from func */

    /* -Wignored-qualifiers */
    const int const_int_func() {
        return 0;
    }

    const int* const_int_ptr_func_int_ptr(int *ip) {
        (*ip)++;
        return ip;
    }

    const struct struct_func_struct const_struct_func() {
        return (struct struct_func_struct){ 0, 1 };
    }

int main(void) {
    {
        func_int(1.1);
        func_float(1);
    }

    /* Two decls on the same line. */
    {
        assert(decl_1() == 1);
        assert(decl_2() == 2);
    }

    /* # return */
    {
        /* Return value is not an lval, so one cannot get its address */
        {
            int *ip;
            /* ERROR */
            /*ip = &int_func_int(1);*/
        }

        /*
        # return struct from function.

            Behaviour defined by the standards.

            Assembly implementation is not specified by ANSI C,
            but common techiques used in cdecl like conventions:

            -   put struct into several registers

            -   automatically add a hidden argument to functions that return structs,
                allocated data on caller and pass a pointer to the struct,
                and let the callee modify that pointer to return it.

            Sample: definition

                struct struct_func_struct struct_func() {
                    struct struct_func_struct s = { 0, 1 };
                    return s;
                }

            gets converted to:

                void struct_func(struct struct_func_struct* sp) {
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
    }

    /*
    # Declaration vs definition

        http://stackoverflow.com/questions/1410563/what-is-the-difference-between-a-definition-and-a-declaration

        Declaration says some information about type, definition specifies it completely.

        Every definition is also a declaration.
    */
    {
        /*
        # extern

            Variable declaration without definition.

            Needs extern, or else it is a definition.

            But there is one more step left: initialization.
        */
        {
            int i;
            {
                extern int i;

                /* ERROR: redeclaration */
                /* TODO why? In particular, why does it work if outside of a function? */
                /* i = 0; */

                /*
                TODO why? Possible outside function.

                http://stackoverflow.com/questions/17090354/why-does-initializing-of-an-extern-variable-locally-inside-a-function-give-an-er
                */
                {
                    /*extern int i = 0;*/
                }
            }
        }

        /* Declaration and definition. */
        {
            int i;
            /* Separate initialization. */
            i = 0;
            assert(i == 0);
        }

        /*
        Variable declaration, definition and initialization in one statment.
        */
        {
            int i = 0;
            assert(i == 0);
        }

        /* struct declaration */
        {

        }

        /* Function declaration vs definitions. */
        {
            /* Function declaration. extern semantics by default. */
            void f();

            /*
            # Local functions

                Declaration can be done inside other functions.

                Definitions not.

                Functions definition inside functions exist only as extensions
                in certain compilers such as gcc if ANSI is not enforced.
            */
            {
                /* ERROR: no definition inside another function: */
                /*void func(){}*/

                /* The following as defined outside main. */
                decl_def();
            }

            /*
            Like for structs, one major application of forward declarations
            is to break definition dependency loops.
            */
            {
                assert(factorial2funcs0(4) == 24);
                assert(factorial2funcs1(4) == 24);
            }

            /*
            In C89, some functions can be used without any declaration as long as they are defined in another file.

            They are called implicit functions.

            They are not allowed in C89.

            But you can use functions which have a declaration that is not a prototype (i.e. without argument checking).
            */
        }

        /*
        Declarations can be done any number of times.

        Definitions only once per scope (block or static in files).
        */
        {
            {
                extern int i;
                extern int i;
                struct s;
                struct s;
                void f();
                void f();
            }

            {
                int i;
                /* ERROR: redeclaration of i */
                /* TODO why is the message redeclaration instead of redefinition? */
                /*int i;*/

                struct s { int i; };
                /* ERROR: redefinition of s */
                /*struct s { int i; };*/
            }
        }

        /* Cannot redeclare a symbols as one of another type. */
        {
            struct i;
            /* ERROR i redeclared as nother type */
            /*void i();*/
        }

        /*
        # Identifier list

        # Parameter list

            TODO

            - http://stackoverflow.com/questions/18820751/identifier-list-vs-parameter-type-list-in-c

        */
        {
            /*
            # Prototype vs declaration

                http://stackoverflow.com/questions/5481579/whats-the-difference-between-function-prototype-and-declaration

                -   Prototype is a declaration that specifies the arguments.
                    Only a single prototype can exist.

                -   a declaration can not be a prototype if it does not have any arguments.
                    The arguments are left unspecified.

                -   to specify a prototype that takes no arguments, use `f(void)`

                In C++ the insanity is reduced, and every declaration is a prototype,
                so `f()` is the same as `f(void)`.

                Save yourself some headache, and never write declarations that are not prototypes.

                TODO why would someone want to use a declaration that is not a prototype?
            */
            {
                /* Declaration that is not a prototype. */
                void proto_decl();

                /* Prototype. */
                void proto_decl(int);

                /* OK, same prototype as above. */
                void proto_decl(int i);

                /* ERROR: conflicting type for */
                /*void proto_decl(float);*/

                /* A definition without arguments however already implies `(void)`. */
                /* ERROR */
                /*int proto_empty_definition(int);*/
                assert(proto_empty_definition() == 1);

                /*
                # float on a prototype after a declaration

                    You can't use `float`, `char`, etc.: only `int`, `double`
                    on prototypes that follow declarations!

                    http://stackoverflow.com/questions/5481579/whats-the-difference-between-function-prototype-and-declaration
                */
                {
                    void proto_decl_float();
                    /* ERROR: An argument that has default promotion can't match*/
                    /*void proto_decl_float(float);*/

                    void proto_decl_double();
                    void proto_decl_double(double);
                }
            }

            /* But not with different return types. */
            /* ERROR conflicting types for `f` */
            /*int f();*/
        }
    }

    /*
    # Implicit int

    # Default return type

        http://stackoverflow.com/questions/12373538/warning-return-type-defaults-to-int-wreturn-type

        In C89, if not specified, the return type defaulted to `int`.

        Appears to have been made illegal in C99.

        `gnu99` allows it by default but gerenrates warnings, `-Wno-return-type` to turn off.
    */
    {
#if __STDC_VERSION__ <= 199901L
        /* WARN: type default to int in declaration of. */
        /*static s;*/
        /*assert(default_return_type() == 1);*/
#endif
    }

    /*
    # K&R function declaration

        This form of function declaration, while standard,
        is almost completely obsolete and forgotten today.

        It is however still ANSI C.

        There seems to be only one case in which it may allow for something
        that ANSI C declarations don't: <http://locklessinc.com/articles/obscurec/>
    */
    {
        char c = 0;
        assert(k_and_r(1, &c) == 0);
    }

    return EXIT_SUCCESS;
}
