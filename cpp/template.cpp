/*
# template

    Greatly reduces code duplication

    Can be used both in functions and classes.

    For each template that is used, a new name mangled function is compiled.
    This has the following downsides:

    - code bloat.

        Final executable gets larger.

    - Implementation must be put in `.h` files and compiled by includers,
        since only used templates generate code for the corresponding definitions.

        Pre-compiling all possibilities on a `.so` is obviously not an option:
        just consider int N, there are int many compilation possibilities!

# three types of arguments

    There are 3 possible arguments for templates:

    - types
    - integers values
    - other templates (see template template)

# extends

    No equivalent to Javas "T extends Drawable"... sad.

    But wait, there seems to be something coming on C++14: template restrictions to the rescue?
    http://stackoverflow.com/questions/15669592/what-are-the-differences-between-concepts-and-template-constraints

# Disambiguating dependent qualified type names

    Syntax:

        template <class T>
        std::string foo(vector<T> vec, ... other args) {
            typename std::vector<T>::iterator it = vec.begin();
        }

    Source:

        http://eli.thegreenplace.net/2011/04/22/c-template-syntax-patterns/

    TODO

# Disambiguating explicitly qualified template member usage

    Syntax:

        template<class U> void func(U arg)
        {
            int obj = arg.template member_func<int>();
        }

    Source: http://eli.thegreenplace.net/2011/04/22/c-template-syntax-patterns/

    TODO0

# Bibliography

    -   <http://www.codeproject.com/Articles/257589/An-Idiots-Guide-to-Cplusplus-Templates-Part-1>

        Very complete and exemplified intro article.

    -   <http://eli.thegreenplace.net/2011/04/22/c-template-syntax-patterns/>

        Short intro, covers some quirky points.
*/

#include "common.hpp"

class Empty {};

/*
TODO what is this?? why does it compile? how to call this func?
*/

    template <class T>
    int templateTODO(T /*no param name!*/){
        //return i + 1;
        return 1;
    }

template<class T>
T templateAdd(T t0, T t1) {
    return t0 + t1;
}

// Template integer parameter.
template<int N>
int templateAddInt(int t) {
    return t + N;
}

// Template recursion.

    template<int N>
    int factorial() {
        return N*factorial<N-1>();
    }

    //without this template specialization, compilation error
    //for me, blows max template recursion depth of 1024
    //this can be reset with `-ftemplate-depth`
    template<>
    int factorial<0>() {
        return 1;
    }

/*
Template template parameters.
*/

    template<typename T>
    class TemplateTemplateParam {
        public:
            TemplateTemplateParam(){}
            TemplateTemplateParam(T t) : t(t) {}
            T t;
    };

    template<template<typename T> class U>
    class TemplateTemplateInt {
        public:
            U<int> t;
    };

    /*
    template<class T>
    class TemplateTemplateIntNotATemplate {
        public:
            T<int> t;
    };
    */
        /*
        ERROR T is not a template.

        Must use a template template parameter.
        */

    /*
    A case in which using a template template would be a better choice.
    */
    template<class T, class V>
    class TemplateTemplateWouldBeBetter {
        public:
            T t;
            V v;

            bool equal(){return t == v.t;}
    };

    /*
    Illustrates a case in which template template is a good design choice.
    */
    template<typename T, template<typename U> class V>
    class TemplateTemplate {
        public:

            /* the template template enforces that T be used twice,
            once for each memeber type, if that is what this class intends to happen */
            T t;
            V<T> v;

            bool equal(){return t == v.t;}
    };

/*
Template default parameters.
*/

    template<typename T=int, template <typename U> class TT = TemplateTemplateParam, int N=1 >
    T templateDefault(T t, TT<T> tt) {
        return t + tt.t + N;
    }

    // TODO is this possible? g++ 4.8 compiles, clang++ 3.2 says that the first T overshadows the T in `template <typename T>`
    //template<typename T, template <typename T> class TT = TemplateTemplateParam > return t + tt.t + N; }

    template<typename T, T t>
    T TemplateReuseType() {
        return t;
    }

// Template specialization.

    template<typename T, typename U>
    double templateSpec(T t, U u) {
        return t + u;
    }

    template<>
    double templateSpec<double,double>(double t, double u) {
        // ERROR: T cannot be used anymore in this specialization.
        //T res;

        return t + u + 1.1;
    }

    // ERROR: template specialization of a single template parameter not allowed
    /*
        template<typename U>
        double templateSpec<double,U>(double t, U u) {
            return t + u + 1.0;
        }

        template<typename T>
        double templateSpec<T,double>(T t, double u) {
            return t + u + 0.1;
        }
    */

// Template argument deduction.

    template<typename U>
    U templateArgDeduct(U u) {
        return u;
    }

    template<>
    double templateArgDeduct(double u) {
        return u + 1.0;
    }

    template<typename T>
    T templateArgDeductReturn() {
        return 0;
    }

    template<typename T>
    T templateArgDeductLocal() {
        return 0;
    }

    template<typename T, typename U>
    double templateArgDeductNotLast(T t) {
        U u = 0;
        return t + u;
    }

    template<typename T>
    T templateArgTemplateArg(TemplateTemplateParam<T> t) {
        return t.t;
    }

/*
Template class.
*/

    template<class BASE=Empty, class T=int, int N=10>
    // OK, can derive from template.
    class TemplateClass : public BASE {
        public:

            T t;
            T ts[N];

            TemplateClass(){}

            // BAD: what is T = string?
            //TemplateClass() t(0.0){}

            TemplateClass(T t): t(t){}

            void method() {}

            void methodDefinedOutside();

            T method(T){}

            // OK:
            template<class C=int>
            void methodTemplate() {}

            static const int sci = 0;

            // BAD: impossible to define?
            //static const TemplateClass<T,N>;

            class Nested {
                public:
                    T t;
            };

            int getIPrivate(){return iPrivate;}

        private:

            int iPrivate;
    };

    // This is exactly the same the TemplateClass with fixed T and N.
    class TemplateFixed : TemplateClass<Empty,int,10> {};

    // OK:
    class TemplatedNestedOut : TemplateClass<Empty,int,10>::Nested {};

    //template virtual

        template<class T=int>
        class TemplateAbstract {
            virtual T virtualMethod(){return 1;}
            virtual T pureVirtualMethod() = 0;
        };

        class TemplateAbstractDerived : public TemplateAbstract<int> {
            virtual int virtualMethod(){return 1;}
            virtual int pureVirtualMethod(){return 1;}
        };

    // C++11
    template<class BASE, class T, int N>
    void TemplateClass<BASE,T,N>::methodDefinedOutside() {}

#if __cplusplus >= 201103L
    // # template specialization

        // Specialization of function for case 12 only.
        template<>
        void TemplateClass<Empty,int,11>::methodDefinedOutside() {
            // ERROR: T undeclared on specialiation
            //T t;
        }

        // ERROR: case 11 was already defined on the spcecialization of methodDefinedOutside 11.
        //template<> class TemplateClass<Empty,int,11> {};


        // Specialization of entire class from now on, a completely new class is created in case 12.
        template<> class TemplateClass<Empty,int,12> {
            public:

                void newMethod() {}
        };

        // ERROR: case 12 class, created in class template specialization
        // does not contain such a function
        //template<>
        //void TemplateClass<Empty,int,12>::methodDefinedOutside(){}
#endif

    // typename keyword qualifier

        struct HasIMember {
            static int i;
        };

        struct HasIType {
            typedef int i;
        };

        struct HasIFunction {
            int i() { return 1; }
        };

        struct HasITemplate {
            template<int N> int i() { return N; }
        };

        /*
        This function could do two things:

        - multiplication of two values: `HAS_I::i` and `i`
        - declartion of a `i` pointer of type `HAS_I::i`

        The only way the compiler can differentiate between both,
        is knowing beforehand if `HAS_I::i` is a type or a value.

        But with templates, how can the compiler possibly know what `HAS_I::i` is going to be??
        It could be both:

        - a class that has a member `t` such as `HasIMember`.

        - or another class that defines a type such as `HasIType`.

        We must therefore help the compiler decide via the typename keyword!
        */
        template<typename HAS_I>
        void NoTypenameFunc() {
            // Multiplication, or pointer declaration??
            // `HAS_I::i` is both qualified (`::`) and dependant on `HAS_I`.
            // TODO check.
            //HAS_I::i * i;
        }

        template<typename HAS_I>
        void TypenameFunc() {
            typename HAS_I::i * i;
        }

        template<typename HAS_I>
        void NoTypenameInTemplateFunc() {
            // Even if here it clearly cannot be a value, only a type,
            // we must still help the compiler parse it with `typename`.
            //
            // ERROR: this could never work, since it does not have the typename specifier
            // and therefore always means a value for the compiler.
            //std::vector<HAS_I::i> v;
        }

        template<typename HAS_I>
        void TypenameInTemplateFunc() {
            std::vector<typename HAS_I::i> v;
        }

    // Template keyword qualifier.

        class TemplateQualifier {
            public:
                template<int N>
                class Nested {
                    public:
                        int method() { return N; }
                };

                template<int N>
                static int TemplateMethod() { return N; }
        };

        template<typename T>
        void TemplateQualifierTest(TemplateQualifier tq, T t, T* tp) {

            assert(tq.TemplateMethod<1>() == 1);
            assert(tq.template TemplateMethod<1>() == 1);

            // Template keyword is only needed for arguments with dependent type.
            assert(tq.TemplateMethod<1>() == 1);
            assert(tq.template TemplateMethod<1>() == 1);

            //assert( t.TemplateMethod<1>());
            assert(t.template TemplateMethod<1>() == 1);

            //assert( tp TemplateMethod<1>() == 1)
            assert(tp->template TemplateMethod<1>() == 1);

            //assert( T::TemplateMethod<1>() == 1);
            assert(T::template TemplateMethod<1>() == 1);

            //typename T::Nested<1> n;
            typename T::template Nested<1> n;
            assert(n.method() == 1);
        }

#if __cplusplus >= 201103L
// # variadic template

    // Empty case.
    template <typename T>
    T variadicSum(T t) { return(t); }

    template <typename T, typename... P>
    T variadicSum(T t, P... p) {
        if (sizeof...(p)) {
            t += variadicSum(p...);
        }
        return(t);
    }

    template <typename... Args>
    std::size_t VariadicSizeof() {
        return sizeof...(Args);
    }
#endif


int main() {
    /*
    Basic usage.
    */
    {
        assert(templateAdd<int>(1, 1) == 2);
        assert(templateAdd<float>(1.0, 1.0) == 2);
    }

    /*
    Template specialization.

        Give an specific behaviour for certain types.
    */
    {
        assert((templateSpec<double,double>(1.0, 1.0)) == 3.1);
    }

    /*
    Template argument deduction.

        Deduce the template parameters based on the type of the arguments passed to the function,
        when those arguments are typenames used in the template.

        Only works for function templates, not for class templates.
        Why not do it for class templates via constructor:
        <http://stackoverflow.com/questions/984394/why-not-infer-template-parameter-from-constructor?rq=1>

        Complex rules dictate how this happens: <http://accu.org/index.php/journals/409>

        The advantages are:

        - write less
        - don't repeat yourself: if

        However it does make the code harder to understand,
        since readers have to deduce types in their heads to decide which functions will be called.

        In the casse of operators, templates enourmously help with syntatic sugar as:

            cout << "a";

        would have to be written something like:

            operator<<<ostream,string>(cout, "a");

        if there was no template argument deduction, and that would be ugly.
    */
    {
        /*
        The compiler calls the int or double version depending on the function argument!

        If no template parameters need to be passed, the template notation can be ommited completely.

        TODO check
        */
        {
            assert(templateArgDeduct<int>   (1)   == 1);
            assert(templateArgDeduct        (1)   == 1);
            assert(templateArgDeduct<double>(1.0) == 2.0);
            assert(templateArgDeduct        (1.0) == 2.0);
        }

        /*
        Can only deduct parameters which are function arguments,
        not those used only on return types or other places.
        */
        {
            assert((templateArgDeductReturn<int>()) == 0);
            assert((templateArgDeductLocal<int>()) == 0);

            // ERROR.
            //assert((templateArgDeductReturn<>()) == 0);
            //assert((templateArgDeductLocal<>()) == 0);
        }

        /*
        Can only deduct parmeters if the parameter is the last non deducted one.

        Here `U` cannot be deducted because it is not a function parameter,
        so `T` which could be deducted cannot because it is never the last undeduced one.
        */
        {
            assert((templateArgDeductNotLast<int,int>(1)) == 1);

            // ERROR.
            //assert((templateArgDeductNotLast<int>(1)) == 1);
        }

        /*
        argument deduction works!! even if the `int` is not a direct function argument,
        but a template argument to a function argument `TemplateTemplateParam<int>`.
        */
        {
            assert(templateArgTemplateArg     (TemplateTemplateParam<int>(1)) == 1);
            assert(templateArgTemplateArg<int>(TemplateTemplateParam<int>(1)) == 1);
        }

        /*
        # typename keyword qualifier

            Besides the basic usage of typename for defining templates,
            it must also be used under certain conditions to allow the compiler to parse the program
            when templates are used.

            Simple intro to typename: <http://pages.cs.wisc.edu/~driscoll/typename.html>

            Explains well the denominations in the standard: <http://stackoverflow.com/questions/610245/where-and-why-do-i-have-to-put-the-template-and-typename-keywords>

            Can only be used inside of template classes or functions.

            Typename rule: qualified dependent names are always parsed
            as values and not types umless they have the typename keyword.

            If they are put on a place which only accepts types and not values,
            this must generate a compile time error!
        */
        {
            // WARNING: statement `HasIMember::i` has no effect

                //NoTypenameFunc<HasIMember>();

            // ERROR: dependant name is parsed as non type

                //NoTypenameFunc<HasIType>();

            // ERROR: no type named i in HasIMember

                //TypenameFunc<HasIMember>();

            TypenameFunc<HasIType>();

            // ERROR.

                //NoTypenameInTemplateFunc<HasIType>();

            //ERROR.

                //NoTypenameInTemplateFunc<HasIMember>();

            // ERROR.

                TypenameInTemplateFunc<HasIType>();

            // ERROR.

                //TypenameInTemplateFunc<HasIMember>();
        }
    }

    /*
    # Template integer parameter

        Templates can receive integer parameters

        Those parameters must be constexpr.
    */
    {
        assert(templateAddInt<1>(1) == 2);
    }

    // Not a constexpr.
    {
        //std::cout << templateAddInt<std::time(NULL) >(1) << std::endl;
    }

    /*
    # Template recursion

        May lead to huge code bloat, but also great speads and non repetition.
    */
    {
        // because of this call
        // all factorials from
        // 1 to 3 will be compiled
        assert(factorial<3>() == 6);

        // because of this call
        // all factorials from
        // 4 to 6 will be compiled
        assert(factorial<6>() == 720);
    }

    /*
    # template template parameters

        Passing a template as a template argument.
    */
    {
        /*
        This does not compile: template template arguments are required.
        */
        {
            //TemplateTemplateIntNotATemplate<int,TemplateTemplateParam>
        }

        //useless working example
        {
            TemplateTemplateInt<TemplateTemplateParam> t;
            t.t.t = 1;
        }

        /*
        This is an example illustrates a case in which a template teamplate would be useful:

        - to enforce that a single template argument will be used on many places
        - to allow users to write a type only once
        */
        {
            /* bad: types don't match */
            TemplateTemplateWouldBeBetter<int,TemplateTemplateParam<double>> t;

            /* bad: types match, but there is code duplication as `int` must be written twice */
            TemplateTemplateWouldBeBetter<int,TemplateTemplateParam<int>> t2;
        }

        /*
        This solves the above issues
        */
        {
            TemplateTemplate<int,TemplateTemplateParam> t;
            t.v.t = 0;
            t.t = 0;

            /**/
            assert(t.equal());
        }
    }

    /*
    # Lexing pitfalls

    # Syntax problems with templates

        The use of `<` and `>` generated lots of ugly lexing conflicts.

        http://stackoverflow.com/questions/7304699/what-are-all-the-syntax-problems-introduced-by-the-usage-of-angle-brackets-in-c
    */
    {
        /*
        Double less signs: can only be used in C++11,
        or lexer + longest munching rule would get it confused with `>>` operator
        http://stackoverflow.com/questions/5341202/why-doesnt-ab-work-in-c/24947922#24947922
        */
        {
            {std::vector<std::vector<int> > vv;}
            //                            ^
            //                            THIS space was required before C++11

#if __cplusplus >= 201103L
            {std::vector<std::vector<int>> vv;}
#endif
        }

        /*
        > inside template

            typename std::enable_if<sizeof(T) > 1, void>::type

        http://stackoverflow.com/questions/33423702/how-to-use-greater-than-inside-a-template-parameter-and-not-get-a-parsing-er
        */

        /*
        >=

        http://stackoverflow.com/questions/28354108/operators-and-template-ids/28354898#28354898
        */
        {
        }

        /*
        # template keyword qualifier

            Just like the typename qualifier helps the compiler solve another type of parsing ambiguity,
            in this case if `<` is a minus or a template instantiation.

            Only used inside of templates that use templates!

            Very good example of the template qualifier:
            http://stackoverflow.com/questions/610245/where-and-why-do-i-have-to-put-the-template-and-typename-keywords
        */
        {
            TemplateQualifier tq;
            TemplateQualifierTest<TemplateQualifier>(tq, tq, &tq);
        }
    }

/*
# template multiple parameters

    Templates can have multiple parameters of any kind of type.
*/
{
    /*
    # Comma protection gotcha

        The C++ preprocessor does not protect commas inside `<`, so the protecting parenthesis (1)
        and (2) are necessary.
    */
    {
        assert((templateDefault<int,TemplateTemplateParam,1>(1, TemplateTemplateParam<int>(1))) == 3);
        //      ^                                                                                  ^
        //      1                                                                                  2

        // ERROR: assert macro gets too many arguments, because `<>` does not protect its inner commas.
        //assert(templateDefault<int,TemplateTemplateParam,1>(1, TemplateTemplateParam<int>(1)) == 3);
        //                       ^                           ^
        //                       1                           2
    }

    // Reuse a type.
    {
        assert((TemplateReuseType<int,1>()) == 1);
    }
}

/*
# template default parameters

    Each of the 3 parameters types that can be passed to templates can have defaults.
*/
{
    assert((templateDefault<int,TemplateTemplateParam,1>(1, TemplateTemplateParam<int>(1))) == 3);
    assert((templateDefault<int,TemplateTemplateParam  >(1, TemplateTemplateParam<int>(1))) == 3);
    assert((templateDefault<int                        >(1, TemplateTemplateParam<int>(1))) == 3);
    assert((templateDefault<                           >(1, TemplateTemplateParam<int>(1))) == 3);
        //if there are no parameters left, the `<>` can be ommited:
    assert((templateDefault                             (1, TemplateTemplateParam<int>(1))) == 3);
}

#if __cplusplus >= 201103L
    /*
    # variadic template
    */
    {
        assert(variadicSum(1)       == 1);
        assert(variadicSum(1, 2)    == 3);
        assert(variadicSum(1, 2, 3) == 6);

        assert(fabs(variadicSum(0.1)           - 0.1) < 1e-6);
        assert(fabs(variadicSum(0.1, 0.2)      - 0.3) < 1e-6);
        assert(fabs(variadicSum(0.1, 0.2, 0.3) - 0.6) < 1e-6);

        assert(variadicSum(1, 1.0) == 2.0);

        /*
        # sizeof...

            Return number of template arguments passed to tempalte.
        */
        {
            assert( VariadicSizeof<>()        == 0 );
            assert( VariadicSizeof<int>()     == 1 );
            assert((VariadicSizeof<int,int>() == 2));
        }
    }
#endif

    /*
    # SFINAE

        <http://en.wikipedia.org/wiki/Substitution_failure_is_not_an_error>

        TODO0
    */

    /*
    # Template class

        Only points which differ significantly from template functions shall be covered here.
    */
    {
        {
            TemplateClass<Empty,int,10> c;
            c.ts[9] = 9;
        }

        {
            TemplateClass<Empty,std::string,10> c;
            c.ts[9] = "asdf";
        }

        {
            TemplateClass<> c; //default values int 10

            // ERROR: canot ommit `<>` for template classes
            //TemplateClass c2;
        }

        // BAD: wont work, unless you defined an assign operator for this case
        // which is very unlikelly
        //tci10 = TemplateClass<float,20>();

        {
            TemplateClass<>().methodTemplate<>();
        }

        {
            {
                TemplateClass<Empty,int,10> c;
                c.methodDefinedOutside();
                // 12 class does not contain method().
                //TemplateClass<Empty,int,12>().method();
            }

            {
                TemplateClass<Empty,int,11> c;
                c.methodDefinedOutside();
                //TemplateClass<Empty,int,12>().method();
                    //12 class does not contain method()
            }

            {
                TemplateClass<Empty,int,12> c;
                c.newMethod();
                // 12 class does not contain method()
                //TemplateClass<Empty,int,12>().method();
            }
        }
    }
}
