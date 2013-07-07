/*
this will focus in differences between cpp and c.
for the rest, go to c.c

#sources

- <http://www.cplusplus.com>

    explains well what most the features of the language do for beginners

    no motivation, many features missing, no stdlib.

- <http://en.cppreference.com/w/>

    wiki

    many behaviour examples

- <http://yosefk.com/c++fqa/>

    comments on the quirks of c++

    fun and informative for those that know the language at intermediate level

- <http://geosoft.no/development/cppstyle.html>

    coding guidelines, clearly exemplified

#standard

    like c, c++ is standardized by ISO under the id: ISO/IEC 14882

    like any standard c++ has several versions noted by year

    the first standard is quite recent dating from 1998.

    #C++11

        previously known as C++0x, but took too long to come out

        in gcc: add -c++0x flag. still experimental.

    #C++03

#headers

    stdlib headers that are not c stdlib headers don't have the .h extension

    with `g++` those get linked to automatically

    when writting new libs, you can use either `.h` or `.hpp` as extensions.

    the main c++ lib on linux is the GNU Standard C++ Library vX

    - std bin is located at: `/usr/lib/i386-linux-gnu/libstdc++.so.X`. Try `locate libstdc++`.
    - std headers are located at: `/usr/include/c++/4.X/`. Try `locate /iostream`.

        Note: c++ std headers have no `.h` extension, just like when included.

    - the ubuntu package is called `libstdc++6.X`. `dpkg -l | grep libstd`

    #c stdlin can be accessed

	c++ is a backwards compatible extension of c, therefore it must provide all the c headers with the exact same semantincs.

        However, it also provides a cNAME version to every NAME.h, ex: `math.h` vs `cmath`.

        The difference is the following:

        - cX puts things in std:: namespace. *always* use it on new code, since this reduces the probability of a name conflicts, and is the standard c++ way of doing things.

        - X.h puts *all* in the global namespace, it is exactly the same as the c headers. *never* use it in the code.

- returning references
        http://stackoverflow.com/questions/795674/which-are-the-implications-of-return-a-value-as-constant-reference-and-constant?rq=1

- ipc

    socket model

*libs

    #linear algebra

        #eigen

            http://eigen.tuxfamily.org/index.php?title=Main_Page

            linear algebra, eqdiffs

        #blitz++

            http://blitz.sourceforge.net/

            linear algebra

        #armadillo

            http://arma.sourceforge.net/

            linear algebra

    #tokamak

        rigid body physical engine

*/

#include <algorithm>
#include <chrono>
    //time operations
#include <exception>
    //exception base exception class
        //bad_alloc	thrown by new on allocation failure
        //bad_cast	thrown by dynamic_cast when fails with a referenced type
        //bad_exception	thrown when an exception type doesn't match any catch
        //bad_typeid	thrown by typeid
        //ios_base::failure	thrown by functions in the iostream library
#include <functional>
    //helper arithmetic/logic functions for algorithms
#include <iostream>
    //cout, endl
#include <iterator>
#include <memory>
#include <mutex>
#include <numeric>
    //partial sums, differences on vectors of numbers
#include <set>
#include <string>
    //string
#include <sstream>
    //stream to a string
#include <thread>
#include <typeinfo>
    //get type of vars
#include <vector>

#include <cassert>
#include <cmath>
#include <cstdlib>

using namespace std;

static vector<string> callStack;
    //keeps a list of functions that called it
    //for testing purposes

void printCallStack()
{
    cout << "callStack:" << endl;
    for( vector<string>::iterator it = callStack.begin(); it != callStack.end(); ++it )
        cout << *it << endl;
    cout << "END callStack" << endl;
}

//class
//{
    /*
    simple class for tests on constructor destructor order
    */
    class NoBaseNoMember
    {
        public:
            NoBaseNoMember(){ callStack.push_back( "NoBaseNoMember::NoBaseNoMember()"); }
            ~NoBaseNoMember(){ callStack.push_back( "NoBaseNoMember::~NoBaseNoMember()"); }

            void method(){ callStack.push_back("NoBaseNoMember::method()"); }
    };

    class Member
    {
        public:
            Member(){ callStack.push_back("Member::Member()"); }
            Member(int i){ callStack.push_back("Member::Member(int)"); }
            ~Member(){ callStack.push_back("Member::~Member()"); }

            void method() { callStack.push_back("Member::method()"); }

            int i;
    };

    class Nested
    {
        public:

            Nested()
            {
                callStack.push_back("Nested::Nested()");
            }
    };

    class Base
    {
        public:

            typedef int NESTED_INT;
                //best to put it on top of class
                //so def will go for entire class

            /*
            default constructor
                if no constructor is declared, a default constructor is created

                if any constructor is declared, even with non default args,
                the default is not created
            */
            Base() : i(0), j(1) //list initialization
            {
                callStack.push_back("Base::Base()");
                //this->i=0;
                //this->j=1;
                    //BAD
                    //same as list init, except if i is an object
                    //to keep uniform style, always use list init

                //ic=0;
                    //ERROR: ic is const. must be initialized in list initialization.

                //Base b;
                    //BAD
                    //compiles but infinite loop!
            }
            /*
            list initialization has 4 main uses:
                1) avoid calling member object constructor
                2) initializing base classes with non default constructors
                3) initializing const elements
                4) initializing member references &
            */

            Base(int i, int j) : i(i), j(j)
            {
                callStack.push_back("Base::Base(int, int)");
            }

            //virtual Base(float f){}
                //ERROR constructor cannot be virtual

            Base(float f) : i(0), fs4{f,f,f,f}, vi{0,1,2,3}
            {
                callStack.push_back("Base::Base(float)");
            }
                //C++11
                //initialize arrray/std containers in list initializtion

            /*
            destructor

            called when:
                1) statically allocated object goes out of scope
                2) dynamically allocated object gets deleted

            major application:
                - delocate dynamic memory that was allocated on constructor

            virtual:
                not necessary
                *but*
                almost always what you want a polymorphic class to which there
                will be pointers to base classes
            */
            virtual ~Base()
            {
                callStack.push_back("Base::~Base()");
            }

            void method()
            {
                callStack.push_back("Base::method()");
                int i = iAmbiguous;
                i = iStatic;
                i = iConstStatic;
            }

            void constMethod () const;

            //return references

                const int& getPrivateConst() const { return this->iPrivate; }
                //value cannot be changed

                int& getPrivate() { return this->iPrivate; }
                //value can be changed

                //int& getPrivate() const { return this->iPrivate; }
                    //ERROR
                    //const method cannot return noncosnt reference!

                //int* getPrivateAddress() const { return &this->iPrivate; }
                    //ERROR
                    //const method cannot return noncosnt pointer!

                const int* getPrivateAddressConst() const { return &this->iPrivate; }

            void methodAmbiguous(){ callStack.push_back("Base::methodAmbiguous()"); }

            virtual void virtualMethod(){ callStack.push_back("Base::virtualMethod()"); }
            //virtual: decides on runtime based on object type
                //http://stackoverflow.com/questions/2391679/can-someone-explain-c-virtual-methods

            virtual Base* covariantReturn()
            {
                callStack.push_back("Base:covariantReturn()");
                return new Base;
            }

            virtual void covariantArg(Base* b)
            {
                callStack.push_back("Base:covariantArg()");
            }

            int i,j;
            //ERROR: cannot initialize here
                //int i = 0;

            int iAmbiguous;

            int* is;

            float fs4[4];
            std::vector<int> vi;

            mutable int mutableI;
            //static mutable int staticMutableI;
                //ERROR
                //statics can be changed in const functions by default

            //BAD
                //every class must have an assigment operator
                //but then, assigment does something like this->ic = other->ic
                //you could redefine the assigment, but still in your new definition
                //ic cannot be changed
                //<http://stackoverflow.com/questions/634662/non-static-const-member-cant-use-default-assignment-operator>

            //static
            //{

                static void staticMethod();

                //static void staticMethod() const;
                    //ERROR
                    //static cannot be const

                static int iStatic;
                //ERROR
                    //static int iStatic = 0;
                        //cannot initialize here unless const
                    //int iStatic;
                        //conclicts with static int

                const static int iConstStatic = 0;
                //OK: const static integral type

                //const static float fConstStatic = 0.0;
                    //ERROR
                    //non integral type

                const static Member member;
                //OK default constructor? why

                const static Member member2;
                //const static Member member2 = Member();
                    //ERROR: non integral type
                    //must be init outside
                    //
                    //why integral types are an exception (complicated):
                        //http://stackoverflow.com/questions/13697265/static-const-double-cannot-have-an-in-class-initializer-why-is-it-so
            //}

            class Nested
            {
                public:

                    Nested()
                    {
                        callStack.push_back("Base::Nested::Nested()");
                        int i = privateStaticInt;
                            //you have private access
                    }

                    Member m;
            };

            class Nested2
            {
                public:

                    Nested2()
                    {
                        callStack.push_back("Base::Nested2::Nested2()");
                    }

                    Nested innerIn;
                    //inner one

                    ::Nested innerOut;
                    //outter one
            };

        protected:

            int iProtected;
            void fProtected(){ callStack.push_back("Base::fProtected()"); }

        private:

            int iPrivate;
            void fPrivate(){ callStack.push_back("Base::fPrivate()"); }
            const static int privateStaticInt = 1;

            typedef int PRIVATE_NESTED_INT;

    };

    void Base::constMethod () const
    {
        //this->i = 2;
            //ERROR
            //cant assign member in const func

        //this->member.method();
            //ERROR
            //cant call non const method inside const method!

        //this->member.i = 1;
            //ERROR
            //cant assign member member in const method

        this->mutableI = 1;
            //OK
            //mutable allows you to do that!
            //application (multithreading):
            //<http://stackoverflow.com/questions/105014/does-the-mutable-keyword-have-any-purpose-other-than-allowing-the-variable-to>

        this->iStatic = 1;
            //does not prevent static changes

        callStack.push_back("Base::constMethod()");
    }

    //void Base::constMethod () {}
        //ERROR
        //must not ommit the const here either

    int Base::iStatic = 0;

    void Base::staticMethod()
    {
        callStack.push_back("Base::staticMethod()");

        //int i = this->i;
            //ERROR
            //no this!

        int i = iStatic;
            //OK
            //ok to use static vars
    }
    //static void staticMethod()
        //ERROR
        //static linkage, like in c static
        //meaning func only visible from current translational unit

    const Member Base::member2 = Member(1);
    //must come outside

    //int Base::k;
        //ERROR
        //must be declared inside

    class BaseAbstract
    {

        public:

            BaseAbstract(){}
            //can be called in derived classes init list
            //can be called in derived classes init list

            virtual ~BaseAbstract(){}

            void method(){ callStack.push_back("BaseAbstract::method()"); }

            void methodAmbiguous(){ callStack.push_back("BaseAbstract::methodAmbiguous()"); }

            virtual void virtualMethod(){ callStack.push_back("BaseAbstract::virtualMethod()"); }
            //virtual: decides on runtime based on object type
                //http://stackoverflow.com/questions/2391679/can-someone-explain-c-virtual-methods

            virtual void pureVirtual() = 0;
                //pure virtual function
                //cannot instantiate this class
                //can only instantiate derived classes that implement this
                //if a class has a pure virtual func is called as an *abstract class* or *interface*

            //virtual void pureVirtualImplementedOtherBase() = 0;
                //BAD
                //won't work: must implement on derived class only

            int i;
            int iAmbiguous;

        private:

            virtual void privatePureVirtual() = 0;
            //this can/must still be implemented on the base class, even if private!

            //how private pure virtual can be usefull
            void usefulPrivatePureVirtual()
            {
                callStack.push_back("common before");
                privatePureVirtual();
                callStack.push_back("common after");
            }
    };

    class PureVirtualImplementedOtherBase
    {
        public:

            void pureVirtualImplementedOtherBase()
            {
                callStack.push_back("PureVirtualImplementedOtherBase::pureVirtualOtherBase()");
            }
    };

    class BaseProtected
    {
        public:

            BaseProtected(){ callStack.push_back("BaseProtected::BaseProtected()"); }
            BaseProtected(int i){ callStack.push_back("BaseProtected::BaseProtected(int)"); }
            ~BaseProtected(){ callStack.push_back("BaseProtected::~BaseProtected()"); }
    };

    class BasePrivate
    {
        public:
            BasePrivate(){ callStack.push_back("BasePrivate::BasePrivate()"); }
            BasePrivate(int i){ callStack.push_back("BasePrivate::BasePrivate(int)"); }
            ~BasePrivate(){ callStack.push_back("BasePrivate::~BasePrivate()"); }
    };

    class Derived : private BasePrivate
    {
    };

    class Class :
        public Base,
        //public Base,      //ERROR duplicate
        //public Derived,   //WARN cannot use BasePrivate inside: ambiguous
        protected BaseProtected,
        private BasePrivate,
        public BaseAbstract,
        public PureVirtualImplementedOtherBase
    {
        public:

            /*
            calls base constructors first
            */
            Class() : i(0), z(0)
            {
                callStack.push_back("Class::Class()");
            }

            Class(int i) : i(i), z(0)
            {
                callStack.push_back("Class::Class(int)");
            }

            Class(int i, int z) : Base(i,z), BaseProtected(i), BasePrivate(i), BaseAbstract(), i(i), z(z)
            {
                callStack.push_back("Class::Class(int, int)");
            }
            //calls specific base constructors  instead of default ones
                //another application os initialization lists
            //works even if the BaseAbstract class is abstract!
                //this is the only place you can do that: init list of derived classes
            //Class() : BaseAbstract(), Base(i,z), BaseProtected(i), BasePrivate(i), i(i), z(z)
                //warning BaseAbstract will be init after TODO ?

            //try catch in case base constructor can throw exceptions
            Class(int i, int j, int z) try : Base(i,j), i(i), z(z)
            {
                callStack.push_back("Class::Class(int, int, int)");
            }
            catch(const exception &e)
            {
                throw e;
            }

            Class(Member m) : m(m)
            {
                //BAD: m constructor would be called, but this is useless since we have already called it!
                //to construct it before.
                //This is an application of initialization constructors.
                    //this->m = m;
                callStack.push_back("Class::Class(Member)");
            }

            //copy constructor
                //classes already have this by default
                //useful to customize if class does dynamic allocation!
                Class(const Class& c) : i(c.i), z(c.z), m(c.m)
                {
                    callStack.push_back("Class::Class(Class)");
                }

                //classes don't have constructors from base by default
                Class(const Base& b) : Base(b)
                {
                    callStack.push_back("Class::Class(Base)");
                }

            //assign operator
                //all classes come with a default
                Class& operator=(const Class& rhs)
                {
                    callStack.push_back("Class::operator=(Class)");
                    i = rhs.i;
                    z = rhs.z;
                    m = rhs.m;
                    return *this; //so shat a = b = c may work
                }

            /*
            also calls Base destructor after
            */
            ~Class(){ callStack.push_back("Class::~Class()"); }

            void method(){ callStack.push_back("Class::method()"); }
            //called method overwriding

            template<class C=int>
            void methodTemplate()
            {
                callStack.push_back("Class::methodTemplate()");
            }
                //OK

            void virtualMethod(){ callStack.push_back("Class::virtualMethod()"); }
                //different than overwriding non virtual methods. see polymorphism.

            //virtual void virtualMethod(){ callStack.push_back("Class::virtualMethod()"); }
                //OK
                //only difference:
                //if you have a pointer to this class, you can only use virtual if this
                //is declared virtual

            void pureVirtual(){ callStack.push_back("Class::pureVirtual()"); }
            //definition obligatory if you want to create objects of this class

            //int pureVirtual(){ return 1; }
                //ERROR
                //unlike function overloading, polyomorphism is decided at runtime
                //and therefore return type must be the same as in declaration

                virtual Class* covariantReturn()
                {
                    callStack.push_back("Class:covariantReturn()");
                    return new Class;
                }
                    //OK
                    //because Class is derived from Base
                    //callde "covariant return type"

                    //virtual Class invalidCovariantReturn(){ return Class(); }
                        //ERROR invalid covariant


                virtual void covariantArg(Class* c)
                {
                    callStack.push_back("Class:covariantArg()");
                }

            int i;
            int z;
            Member m;
            Nested nested;
            //Base nested class visible from here

        private:

            virtual void privatePureVirtual(){ callStack.push_back("Class:privatePureVirtual()"); };
    };

    //overload <<
        ostream& operator<<(ostream& os, const Class& c)
        {
            os << c.i << " " << c.j;
            return os;
        }

    //nested
        class NestedDerived : Class::Nested{};
        //OK
        //you can see the nested class from derived classes

    class Class2 : public Base
    {
        public:

            Class2(){}
            void pureVirtual(){ callStack.push_back("Class2::pureVirtual()"); }

            class Nested{};
            //OK
            //you can override the Nested class from the Base also
    };

    class ClassCast
    {
        ClassCast(Class c){}
    };

    //ClassDefault::ClassDefault(int i=0){}
        //ERROR

    //templates class
    //{
        //- ultra reneral! <class T, int N>
        //-default values via: <class T=char, int N=10>
            //c = Class<>
        //- implementation must be put in .h files and compiled by includers
            //cannot be put inside a .so therfore
            //consider int N, there are int many compilation possibilities!!
        //- no equivalent to Javas "T extends Drawable"... sad.

        //SAME
        //template<typename T=int, int N=10>
        template<class BASE=Base, class T=int, int N=10>
        class TemplateClass : public BASE //OK
        {
            public:

                T t;
                T ts[N];

                TemplateClass(){ callStack.push_back("TemplateClass::TemplateClass()"); }

                //BAD: what is T = string?
                    //TemplateClass() t(0.0){ callStack.push_back("TemplateClass::TemplateClass()"); }

                TemplateClass(T t): t(t){ callStack.push_back("TemplateClass::TemplateClass(T)"); }

                void method()
                {
                    callStack.push_back("TemplateClass::method()");
                }

                void methodDefinedOutside();

                T method(T){ callStack.push_back("TemplateClass::method(T)"); }

                template<class C=int>
                void methodTemplate()
                {
                    callStack.push_back("TemplateClass::methodTemplate()");
                }
                    //OK

                static const int sci = 0;

                //BAD impossible to define?
                    //static const TemplateClass<T,N>;

                class Nested
                {
                    public:
                        T t;
                        //NOTE
                        //works
                };
        };

        class TemplateFixed : TemplateClass<Base,int,10> {};
            //NOTE
            //this is exactly the same the TemplateClass with fixed T and N

        class TemplatedNestedOut : TemplateClass<Base,int,10>::Nested {};
            //OK

        //template virtual
        //{
            template<class T=int>
            class TemplateAbstract
            {
                virtual T virtualMethod(){ return 1; }
                virtual T pureVirtualMethod() = 0;
            };

            class TemplateAbstractDerived : public TemplateAbstract<int>
            {
                virtual int virtualMethod(){ return 1; }
                virtual int pureVirtualMethod(){ return 1; }
            };
        //}

        template<class BASE, class T, int N>
        void TemplateClass<BASE,T,N>::methodDefinedOutside()
        {
            callStack.push_back("TemplateClass::methodDefinedOutside()");
        }
            //c++11
            //even if independent on template args
            //still cannot be pre compiled


        //specialization
        //{
            template<>
            void TemplateClass<Base,int,11>::methodDefinedOutside()
            {
                callStack.push_back("TemplateClass<Base,int,11>::methodDefinedOutside()");
                //T t;
                    //ERROR
                    //T undeclared on specialiation
            }
                //c++11
                //specialization of function for case 12 only

            //template<> class TemplateClass<Base,int,11> {};
                //ERROR
                //case 11 was already defined on the spcecialization of methodDefinedOutside 11


            template<> class TemplateClass<Base,int,12>
            {
                public:

                    void newMethod()
                    {
                        callStack.push_back("TemplateClass<Base,int,12>::newMethod()");
                    }
            };
                //NOTE
                //specialization of entire class
                //from now on, a completely new class is created in case 12

            //template<>
            //void TemplateClass<Base,int,12>::methodDefinedOutside(){}
                //ERROR
                //case 12 class, created in class template specialization
                //does not contain such a function
        //}
    //}

    //design patterns
    //{


        //VisibleInnerIterable
        //{
            /*
            this is the best way I could find to make a member
            iterable object such as a container available outside

            design goal:

            - to change container type, you only change a single typedef

            difficulty:

            - there is no `Iterator` interface that iterates over anything in the stdlib
                for performance reasons.

                By iterable understand somtehing that has an `::iterator`,
                a `begin()` and an `end()` methods, like stl containers
            */
            class VisibleInnerIterable
            {
                public:

                    VisibleInnerIterable();

                    typedef vector<int> Iterable;

                    const Iterable& getIterable();

                private:

                    Iterable iterable;
            };

            VisibleInnerIterable::VisibleInnerIterable() : iterable{0,1,2} {}

            const VisibleInnerIterable::Iterable& VisibleInnerIterable::getIterable()
            {
                return iterable;
            }
        //}
    //}
//}

//global scope
//{
    int global = 0;

    //NOTE
    //different from c, where these were errors
    //{
        int global2 = global+1;
        int ret1()
        {
            callStack.push_back("before main!");
            return 1;
        }
        int global3 = ret1();
    //}

    //ERROR
    //everything must start with a typename
    //{
        //global = 1;
        //if(1){}
        //callStack.push_back("global");
    //}
//}

//functions

    //passing by argument
        //c++ only. convenience only?
        //http://stackoverflow.com/questions/114180/pointer-vs-reference
        void byref (int& i){i++;}
        void bypointer (int *i){(*i)++;}

    //default args. c++ only. creates several functions!
        void defaultArgs (int i, int j=0)
        {
            cout << i;
            cout << j;
        }

    //ERROR: can't pass default values for arrays
        //void foo (int bar[] = {0 ,1});

    //function overloading
        void overload(int i){ callStack.push_back("overload(int)"); }
        void overload(int i, int j){ callStack.push_back("overload(int,int)"); }
        void overload(float i){ callStack.push_back("overload(float)"); }
        void overload(float i, float j, float k=0.f){ callStack.push_back("overload(float,float,float=)"); }

        //int overload(int i, int j, int k){return 1;}
            //OK even if return type is different
            //all is decided at compile time

        //ERROR: conflict with int
            //void overload(const int i){ }
        //ERROR: cannot differentiate by output since output is used to decide if other parts of code make sense
            //int overload(){ return 0; }
            //float overload(){ return 0.f; }
        //ERROR: conflict with int int
            //void overload(int i, int j=0){ cout << "int int="; }

        //void overload(float i, float j=1){ cout << "float float="; }
            //BAD
            //compiles, but is useless to give a default,
            //since when calling, caller is *forced* to give a value for j
            //or wil get `call is ambiguous` compile time error
            //because compiler cannot decide between
                //here the default arg can be usefull for a call of type float float

        //TODO why does this compile, that is, how not to make an ambiguous call with overload(int)
            void overloadValAddr(const int i){}
            void overloadValAddr(const int& i){}

        void overloadBase(Base b){}
        void overloadBase(BaseProtected b){}

    //default args
        void defaultArgProto( int i=0 );
        void defaultArgProto( int i ){}

        void defaultArgDef( int i );
        void defaultArgDef( int i=0 ){}
            //NOTE
            //usually not what you want
            //since includers will not see the default version

        //void defaultArgBoth(int i=0);
        //void defaultArgBoth(int i=0){}
            //ERROR
            //cannot go in both places

    //int outter()
    //{
        //int inner(){ return 1; }
        //return inner();
    //}

    //templates
        template<class T=int>
        void fTemplate(T t)
        {
            T t2 = t;
            cout << "fTemplate(T) " << t << endl;
        }

        template<>
        void fTemplate<float>(float t)
        {
            cout << "fTemplate(float) " << t << endl;
            //T t = t;
            //ERROR
                //T not declared
        }

        //variadic
            //c++11

            //base case
            template <typename T>
            T variadicSum(T t) { return(t); }

            template <typename T, typename ...P>
            T variadicSum(T t, P ...p)
            {
                if (sizeof...(p))
                {
                    t += variadicSum(p...);
                }
                return(t);
            }

            //loop
            //template <typename T, typename ...P>
            //T variadicSum2(T t, P ...p)
            //{
                //std::vector list = {p...};

                //if (sizeof...(p))
                //{
                    //t += variadicSum(p...);
                //}
                //return(t);
            //}

    //recursion example
        template<int N>
        int factorial()
        {
            return N*factorial<N-1>();
        }

        template<>
        int factorial<0>()
        {
            return 1;
        }
            //NOTE
            //without this, compilation error
            //for me, blows max template recursion depth of 1024
            //this can be reset with `-ftemplate-depth`


//namespaces
    //- *never* use `using namespace X` on a header file

    //namespace 2D{}
        //ERROR
        //same naming rules as vars

    namespace D2{}
        //BAD
        //by convention, start upper case

    int i;

    void f()
    {
        callStack.push_back("::f");
    }

    void prototype();

    namespace namea
    {

        class C
        {
            public:
                C()
                {
                    callStack.push_back("namea::C");
                }
        };

        namespace nameaa
        {
            int i;

            void f()
            {
                callStack.push_back("nameaa::f");
            }

            class C
            {
                public:
                    C()
                    {
                        callStack.push_back("nameaa::C");
                    }
            };
        }

        namespace nameab
        {
            int i;

            void f()
            {
                callStack.push_back("namea::nameab::f");

                ::i = 0;
                i = 0;   //namea::nameab::i
                nameaa::i = 0; //namea::nameaa::i

                using namespace nameaa;
                    //only affects this function. see C::C() at the f() call
            }

            class C :
                public namea::C
                //public C
                    //ERROR
                    //refers to current incomplete C already
                    //not existem namea::C
            {
                C()
                {
                    callStack.push_back("namea::nameab::C");
                    f();
                    //no ambiguity because using inside f() only afects the function
                }
            };
        }

        int i;

        void f()
        {
            ::i = 0;
            i = 0;   //namea::i
            namea::i = 0;
            nameaa::i = 0; //namea::nameaa::i
            callStack.push_back("namea::f");
        }
    }

    namespace namea
    {
        //can add new members
            int j;
            void newFunc(){}
            class B{};

        //int i;
            //ERROR
            //redefinition

        //void prototype(){}
            //implementation of namea::prototype
    }

    //namea::i = 0;
    //void namea::prototype(){}
    //int namea::j;
    //void namea::g(){}
    //class namea::B{};
        //ERROR
        //must be declared/defined inside

    //template<class T> namespace t {}
        //ERROR
        //nope

//thread
//{
    //TODO
    //- recursive mutex

    int nNsecs = 10;
    int threadGlobal = 0;
    int threadGlobalMutexed = 0;
    std::mutex threadGlobalMutex;
    std::thread::id lastThreadId;
    std::set<std::thread::id> threadIds;

    int threadGlobalEq0 = 0;
    int threadGlobalMutexedEq0 = 0;
    int threadChange = 0;

    void threadFunc(int threadCountToSqrt)
    {
        std::thread::id id = std::this_thread::get_id();
        for( int i=0; i<threadCountToSqrt; i++ )
        for( int j=0; j<threadCountToSqrt; j++ )
        {
            if( lastThreadId != id )
            {
                ++threadChange;
                //threadIds.insert(id);
                lastThreadId = id;
            }

            //cout << id << " " << i << endl;
                //NOTE
                //cout is not thread safe
                //order gets mixed up

            //if happens
                threadGlobal = 1;
                if(threadGlobal == 0)
                    ++threadGlobalEq0;
                threadGlobal = 0;

            //if never happens!
                threadGlobalMutex.lock();
                    //if not available, wait
                //threadGlobalMutex.try_lock();
                    //if not available, return!
                    threadGlobalMutexed = 1;
                    if(threadGlobalMutexed == 0)
                        ++threadGlobalMutexedEq0;
                    threadGlobalMutexed = 0;
                threadGlobalMutex.unlock();

        }
        std::this_thread::sleep_for(std::chrono::nanoseconds(nNsecs));
        std::this_thread::yield();
            //done, pass to another thread
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

    void heapMalloc1bProf(int n)
    {
        char* cp;
        int i;
        for( i = 0; i < n; ++i )
        {
            cp = (char*) malloc( sizeof( char ) * 1 );
            free(cp);
        }
    }

    void heapMalloc1kbProf(int n)
    {
        char* cp;
        int i;
        for( i = 0; i < n; ++i )
        {
            cp = (char*) malloc( sizeof( char ) * 0x800 );
            free(cp);
        }
    }

    void heapMalloc1mbProf(int n)
    {
        char* cp;
        int i;
        for( i = 0; i < n; ++i )
        {
            cp = (char*) malloc( sizeof( char ) * 0xF0000 );
            free(cp);
        }
    }

    void heapNew1bProf(int n)
    {
        char* cp;
        int i;
        for( i = 0; i < n; ++i )
        {
            cp = new char[1];
            delete[] cp;
        }
    }

    void heapNew1kbProf(int n)
    {
        char* cp;
        int i;
        for( i = 0; i < n; ++i )
        {
            cp = new char[0x800];
            delete[] cp;
        }
    }

    void heapNew1mbProf(int n)
    {
        char* cp;
        int i;
        for( i = 0; i < n; ++i )
        {
            cp = new char[0xF0000];
            delete[] cp;
        }
    }

    class BaseProf
    {
        public:
            virtual void virtualMethod(){}
    };

    class ClassProf
    {
        public:
            void method(){}
            virtual void virtualMethod(){}
    };

    void methodCallProf(int n)
    {
        ClassProf c;
        int i;
        for( i = 0; i < n; ++i )
        {
            c.method();
        }
    }

    void virtualMethodCallProf(int n)
    {
        ClassProf c;
        int i;
        for( i = 0; i < n; ++i )
        {
            c.virtualMethod();
        }
    }

#endif

int main(int argc, char** argv)
{

    //bool
    {
        bool b;

        b = true;
        b = 1;

        if(true)
        {
            assert(true);
        }
        if(false)
        {
            assert(false);
        }

        {
            stringstream oss;
            oss << true;
            assert( oss.str() == "1" );
        }

        {
            stringstream oss;
            oss << false;
            assert( oss.str() == "0" );
        }

    }

    //unsigned
    {
        unsigned int ui = -1;
        int i = 1;
        //if(ui<i)
            //WARN
            //in c, no WARN
    }

    cout << "const" << endl;
    {
        {
            const int i = 2;
            //int* ip = i;
                //ERROR
                //in c this is only a warning, and allows us to change ic.
        }

        {
            //const int ic2;
                //ERROR
                //must be initialized, since in c++ consts really are consts
        }

        {
            const Class c;

            //ERROR
                //cc = Class();

            //ERROR
                //cc.i = 1;

            const int& cia = c.i;

            //int& ia = cc.i;
                //ERROR

            //c.method();
                //ERROR
                //method might change c
                //to call it, must tell compiler it doesnt
                //see constMethod
                //therefore, *BE CONST OBSESSIVE!* mark as const every const method!

            c.constMethod();
        }
    }

    cout << "references" << endl;
    {
        //basically aliases, similar to int*const poinsters
        //
        //useful only for function parameters/return
        //
        //just link pointers, you have to watch scope. if the original object dies,
        //you get a dangling reference
        //
        //http://stackoverflow.com/questions/752658/is-the-practice-of-returning-a-c-reference-variable-evil
        //http://stackoverflow.com/questions/7058339/c-when-to-use-references-vs-pointers}

        {
            int i = 0;
            byref(i);
            assert( i == 1 );
        }

        {
            int i = 0;
            int& ia = i;
            ia = 1;
            assert( i == 1 );
            assert( &i == &ia );
                //therefore no extra memory is used for references
                //whereas pointers use memory
            int& ia2 = ia;
            ia2 = 2;
            assert( i == 2 );

            //int& ia = 0;
                //ERROR
                //must be a variable rhs

            //int& ia;
                //ERROR
                //must be initialized immediatelly
        }

        {
            int i = 0;
            int* ip = &i;
            int& ia = *ip;
            ia = 1;
            assert( i == 1 );

            //ERROR: & must get a variable/dereferenced pointer, not pointers themselves!
                //int& ia = &i;
                //int& ia = new int;
        }

        //const
        {
            int i = 1;
            const int& cia = i;
            const int& cia2 = cia;

            const int ci = 1;
            const int& ciac = ci;

            //cia = 2;
                //ERROR

            //int* ip = &cia;
                //ERROR
                //invalid conversion

            //ERROR: invalid conversion
                //int& ia = cia;

            //ERROR: no array of references forbidden
                //int& is[2] = {i,i};

            //int& iac = ci;
                //ERROR
                //must be const int&
        }

        cout << "return" << endl;
        {
            //never from functions (if new, return auto_ptr, if not new, you got an error)
            //only from methods, when data is in the object
            //just like pointers, if object dies, data dies!

            {
                //you can modify a private
                    Base b;
                    int& ia = b.getPrivate();
                    ia = 0;
                    assert( b.getPrivate() == 0 );
                    ia = 1;
                    assert( b.getPrivate() == 1 );
            }

            {
                //now you can only see, not modify
                    Base b;
                    const int& ia = b.getPrivateConst();
                    //ia = 1;
                        //ERROR
            }
        }
    }

    //vla
    //gcc
    {
        //called variable length array VLS

        //C99 supports this

        //compiler implementation:
        //must increment/decrement stack pointer at each array
        //meaning, one extra multiplication and sum for every VLA declared

        {
            //cin >> i;
            //int is4[i];
        }

        {
            //cin >> i;
            //int is4[i] = { 1, 2 };
                //ERROR
                //may not be initialized
        }
    }

    cout << "for" << endl;
    {

        //you can define i inside the for scope only
        int is[] = { 0, 1, 2 };
        for(int i=0; i<3; i++)
        {
            assert( i == is[i] );
            //int i;
                //ERROR
                //already declared in this scope
        }

    }

    cout << "functions" << endl;
    {
        cout << "overload" << endl;
        {
            overload( 1 );
            assert( callStack.back() == "overload(int)" );
            callStack.clear();

            overload(1.0f);
            //overload(1.0);
                //ERROR
                //ambiguous overload(int) overload(float)
                //compiler does not know wether convert double to float or int
            assert( callStack.back() == "overload(float)" );
            callStack.clear();

            //Class cOverload;
            //overloadBase(cOverload);
                //ERROR
                //ambiguous
                //coverts to Base or BaseProtected

            //i=4;
            //overloadValAddr(i);
                //ERROR
                //ambiguous

        }

        cout << "template" << endl;
        {
            assert( factorial<3>() == 6 );
                //because of this call
                //all factorials from
                //1 to 2 will be compiled
            assert( factorial<6>() == 720 );
                //4 to 6 will be compiled

            //variadic template
            {
                assert( variadicSum( 1 )       == 1 );
                assert( variadicSum( 1, 2 )    == 3 );
                assert( variadicSum( 1, 2, 3 ) == 6 );

                assert( fabs( variadicSum( 0.1 )           - 0.1 ) < 1e-6 );
                assert( fabs( variadicSum( 0.1, 0.2 )      - 0.3 ) < 1e-6 );
                assert( fabs( variadicSum( 0.1, 0.2, 0.3 ) - 0.6 ) < 1e-6 );

                assert( variadicSum( 1, 1.0 ) == 2.0 );
            }
        }

    }

    cout << "class" << endl;
    {
        //creation
        {
            {
                {
                    //Base Class
                        //Base and Class constructor are called!
                        //if no default constructor, error
                    //there is a default constructor if you don't define any constructor
                        //but if you define any constructor (even non null), you have to write
                        //the empty one yourself, so just write it always
                    callStack.clear();
                    Class c;
                    vector<string> expectedCallStack =
                    {
                        "Base::Base()",
                        "BaseProtected::BaseProtected()",
                        "BasePrivate::BasePrivate()",
                        "Member::Member()",
                        "Member::Member()",
                        "Base::Nested::Nested()",
                        "Class::Class()",
                    };
                    //assert( callStack == expectedCallStack );

                    callStack.clear();
                }

                vector<string> expectedCallStack =
                {
                    "Base::Base()",
                    "BaseProtected::BaseProtected()",
                    "BasePrivate::BasePrivate()",
                    "Member::Member()",
                    "Member::Member()",
                    "Base::Nested::Nested()",
                    "Class::Class()",
                };
                //assert( callStack == expectedCallStack );
            }

            {
                callStack.clear();

                NoBaseNoMember c;
                c = NoBaseNoMember();

                vector<string> expectedCallStack =
                {
                    "NoBaseNoMember::NoBaseNoMember()",
                    "NoBaseNoMember::NoBaseNoMember()",
                    "NoBaseNoMember::~NoBaseNoMember()"
                };
                assert( callStack == expectedCallStack );
            }

            {
                callStack.clear();
                NoBaseNoMember c = NoBaseNoMember();
                vector<string> expectedCallStack =
                {
                    "NoBaseNoMember::NoBaseNoMember()",
                };
                assert( callStack == expectedCallStack );
            }

            {
                //Class c();
                //c.i = 1;
                    //ERROR
                    //declares *FUNCTION* called `c()` that returns `Class`
                    //functions inside functions like this are a gcc extension
            }
        }

        //static
        {
            {
                Class c, c1;
                int i;
                c.iStatic = 0;
                assert( Class::iStatic == 0 );
                c1.iStatic = 1;
                assert( Class::iStatic == 1 );
                Class::iStatic = 2;
                assert( Class::iStatic == 2 );
            }

            {
                Class c;
                c.staticMethod();
                Class::staticMethod();
            }
        }

        cout << "copy, assigment" << endl;
        {
            //every class gets a default assign operator (=) and copy constructor
            //called shallow copy/assign
            //might not be what you want, specially when you allocate memory inside the constructor!
                //http://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
                //http://stackoverflow.com/questions/4172722/what-is-the-rule-of-three
            {
                //copy constructor
                //default exists always, calls copy on all memebrs

                Class c;
                c.i = 1;
                cout << "Class c2(c)" << endl;
                Class c1(c);
                    //copy constructor
                assert( c1.i == 1 );
                cout << "Class c2 = c" << endl;
                Class c2 = c;
                    //SAME
                    //*COPY CONSTRUCTOR CALLED, NOT ASSIGN CONSTRUCTOR*
                    //because object is being created
                cout << c2.i << endl;
            }

            {
                Base b;
                Class c(b);
                    //NOTE
                    //no default copy from base
                    //you must write one yourself
            }

            {
                Class c;
                c.Base::i = 1;
                Base b(c);
                    //OK
                    //copy base fields
                    //can transform derived into base implicitly
                assert( b.i == 1 );
            }

            {
                //assign operator
                //default assign calls assign (=) on all members
                Class c, c1;
                c.i = 1;
                c1.i = 2;
                c1 = c;
                assert( c1.i == 1 );
            }

            {
                //there are default copy/assign funcs from base classes
                //they assign/copy to base object fields inherited from derived only
                Class c = Class();
                cout << "Base base(c);" << endl;
                Base base(c);
                cout << "base = Class();" << endl;
                base = Class();

                //c = base;
                    //ERROR
                    //not from derived to base

                Base* bp = &c;
                    //OK
                    //pointer conversions

                //bp = &m;
                //cp = &base;
                    //ERROR
                    //can only convert from derived to base
            }
        }

        cout << "arrays of objects" << endl;
        {
            {
                cout << "Class os[3];" << endl;
                Class cs[3];
                    //3x Class() calls!
                cs[0] = Class(1);
                cs[1] = Class(2);
                cs[2] = Class(3);
                    //more 3x Class()

                //initialized
                    cout << "Class cs2[] = {Class(1), Class(2), Class(3)};" << endl;
                    Class cs2[] = { Class(1), Class(2), Class(3) };
                    //3x Class() calls. more efficient therefore
            }
        }

        cout << "temporaries" << endl;
        {
            cout << "Class().method();" << endl; //an instance without name is created and destroyed
            {
                Class().method();
                    //Class() Class().method1() ~Class

                Class( Class() );
                    //i j
                    //temporaries can be passed to functions directly
            }

            {
                Class c = Class();
                Class* cp = &c;

                //Class* cp = &Class();
                    //ERROR
                    //address of what?
            }
        }

        cout << "operator overload" << endl;
        {
            {
                Class c;
                c.i = 1;
                c.j = 2;
                cout << "cout << c;" << endl;
                cout << c << endl;
                    //1 2
            }
        }

        cout << "template" << endl;
        {
            {
                TemplateClass<Base,int,10> c;
                c.ts[9] = 9;
            }

            {
                TemplateClass<> c; //default values int 10
            }

            {
                TemplateClass<Base,string,10> c;
                c.ts[9] = "asdf";
            }

            {
                TemplateClass<> c;
                cout << "c.method();" << endl;
                c.method();
                cout << "c.Base::method();" << endl;
                c.Base::method();
            }


            //tci10 = TemplateClass<float,20>();
                //BAD: wont work, unless you defined an assign operator for this case
                //which is very unlikelly

            {
                Class c;
                c.methodTemplate<int>();
            }

            {
                TemplateClass<>().methodTemplate<>();
            }

            {
                {
                    TemplateClass<Base,int,10> c;
                    callStack.clear();
                    c.methodDefinedOutside();
                    assert( callStack.back() == "TemplateClass::methodDefinedOutside()" );
                    //TemplateClass<Base,int,12>().method();
                        //12 class does not contain method()
                }

                {
                    TemplateClass<Base,int,11> c;
                    callStack.clear();
                    c.methodDefinedOutside();
                    assert( callStack.back() == "TemplateClass<Base,int,11>::methodDefinedOutside()" );
                    //TemplateClass<Base,int,12>().method();
                        //12 class does not contain method()
                }

                {
                    TemplateClass<Base,int,12> c;
                    callStack.clear();
                    c.newMethod();
                    assert( callStack.back() == "TemplateClass<Base,int,12>::newMethod()" );
                    //TemplateClass<Base,int,12>().method();
                        //12 class does not contain method()
                }
            }

        }

        cout << "overridding" << endl;
        {
            {
                Class c;
                Class* cp = &c;

                c.i = 0;
                c.Class::i = 0;
                cp->Class::i = 0;
                c.Base::i = 1;
                c.BaseAbstract::i = 2;

                assert( c.i          == 0 );
                assert( c.Class::i   == 0 );
                assert( cp->Class::i == 0 );

                assert( c.Base::i   == 1 );
                assert( cp->Base::i == 1 );

                assert( c.BaseAbstract::i   == 2 );
                assert( cp->BaseAbstract::i == 2 );

                //c.iAmbiguous = 0;
                    //ERROR ambiguous
                c.Base::iAmbiguous = 0;
                c.BaseAbstract::iAmbiguous = 0;

                callStack.clear();
                c.method();
                assert( callStack.back() == "Class::method()" );
                //c.methodAmbiguous();
                    //ERROR ambiguous
                callStack.clear();
                c.Base::methodAmbiguous();
                assert( callStack.back() == "Base::methodAmbiguous()" );

                callStack.clear();
                c.BaseAbstract::methodAmbiguous();
                assert( callStack.back() == "BaseAbstract::methodAmbiguous()" );
            }
        }

        cout << "polymorphism" << endl;
        {
            //behind the scenes a *vtable* is used to implement this

            //BaseAbstract b;
                //ERROR: BaseAbstract cannot be instantiated because it contains a pure virtual method
                //virtual = 0;. That method must be implemented on derived classes

            //even if you can't instantiate base, you can have pointers to it
            {
                BaseAbstract* bap = new Class;
                //BaseAbstract* bap = &c;
                    //SAME

                callStack.clear();
                bap->method();
                assert( callStack.back() == "BaseAbstract::method()" );
                    //base method because non-virtual

                callStack.clear();
                bap->virtualMethod();
                assert( callStack.back() == "Class::virtualMethod()" );
                    //class method because virtual

                delete bap;
            }

            {
                //you can also have BaseAbstract&
                Class c;
                BaseAbstract& ba = c;

                callStack.clear();
                ba.method();
                assert( callStack.back() == "BaseAbstract::method()" );

                callStack.clear();
                ba.virtualMethod();
                assert( callStack.back() == "Class::virtualMethod()" );
            }

            {
                Class c = Class();
                Base* bp = &c;
                bp = bp->covariantReturn();

                callStack.clear();
                bp->virtualMethod();
                assert( callStack.back() == "Class::virtualMethod()" );

                //classPtr = basePtr->covariantReturn();
                    //ERROR
                    //conversion from Base to Class
            }
        }

        cout << "typecasting" << endl;
        {
            //http://www.cplusplus.com/doc/tutorial/typecasting/

            //implicit via constructor/assigment
                //class A {};
                //class B { public: B (A a) {} };
                //A a;
                //B b=a;

        }

        cout << "nested classes" << endl;
        {
            {
                cout <<"Base::Nested baseNested;" << endl;
                Base::Nested baseNested;
                cout << "Base::Nested2 baseNested2;" << endl;
                Base::Nested2 baseNested2;
            }
        }

        cout << "nested typedefs" << endl;
        {
            Base::NESTED_INT i = 1;
            //Base::PRIVATE_NESTED_INT j = 1;
                //ERROR
                //is private
        }

        //design patterns
        {
            //VisibleInnerIterable
            {
                VisibleInnerIterable c;
                VisibleInnerIterable::Iterable ita = c.getIterable();
                VisibleInnerIterable::Iterable::iterator it = ita.begin();

                int i;
                int is[] = {0,1,2};
                for(
                    it = ita.begin(), i=0;
                    it != ita.end();
                    ++it, ++i
                )
                {
                    assert( *it == is[i] );
                }
            }
        }
    }

    //dynamic memory
    {
        {
            int* ip;
            ip = new int [5];
            ip[0] = 1;
            delete[] ip;
        }

        {
        //can also alocate single int
            //useless of course
            //but is might be useful to allocate a single object
            int* ip = new int;
            *ip = 1;
            delete ip;
        }

        {
            callStack.clear();
            NoBaseNoMember* cp = new NoBaseNoMember;
            //NoBaseNoMember* cp = new NoBaseNoMember();
                //SAME
            assert( callStack.back() == "NoBaseNoMember::NoBaseNoMember()" );

            cp->method();

            callStack.clear();
            delete cp;
            assert( callStack.back() == "NoBaseNoMember::~NoBaseNoMember()" );
                //calls destructor
        }

        {
            callStack.clear();
            NoBaseNoMember* cp = new NoBaseNoMember[2];
            assert( callStack.back() == "NoBaseNoMember::NoBaseNoMember()" ); callStack.pop_back();
            assert( callStack.back() == "NoBaseNoMember::NoBaseNoMember()" ); callStack.pop_back();

            cp[0].method();
            cp[1].method();

            callStack.clear();
            delete[] cp;
            assert( callStack.back() == "NoBaseNoMember::~NoBaseNoMember()" ); callStack.pop_back();
            assert( callStack.back() == "NoBaseNoMember::~NoBaseNoMember()" ); callStack.pop_back();
        }

        {
            //int* ip = new int;
            //delete ip;
                //BAD
                //undefined behavior, maybe crash
                //delete ip;
        }

        {
            //int* ip = new int;
            //ip = new int;
            //delete ip;
                //BAD
                //memory leak. memory is lost forever.
        }

        {
            //int* ip;
            //delete ip;
                //BAD
                //undefined behavior, maybe crash
                //ip was not allocated after delete!
        }
    }

    //exception
    {
        //TODO
        //
    }

    //enum
    {
            //delete ip;
                //BAD
                //undefined behavior, maybe crash
                //ip was not allocated after delete!
        enum TEXTURE { GRASS, WALL, SKY };
        TEXTURE t = GRASS;
        //unlike c, already does typedef
        //check this to give values
            //http://msdn.microsoft.com/en-us/library/2dzy4k6e%28v=vs.71%29.aspx

        //ERROR
            //enum E2 { E2=i };
            //only const expressions allowed
    }

    //namespace
    {
        //variables
        {
            int i;
            i = 0;          //inner  i
            ::i = 0;        //global i
            namea::i = 0;   //namea  i
            i++;
            assert( i        == 1 );
            assert( ::i      == 0 );
            assert( namea::i == 0 );

            f();
            namea::f();
            namea::nameaa::f();
        }

        { int i; }

        {
            using namespace namea;
            //brackets limit the using namespace

            //f();
                //ERROR ambiguous
                //::f
                //namea::f
            ::f();
            namea::f();
            namea::nameaa::f();

            //namespace main{}
                //ERROR
                //no namespace inside funcs
        }

        //namespace chaining
        {
            using namespace namea;
            using namespace nameaa;

            //f();
                //ERROR ambiguous
                //::f
                //namea::f
                //namea::nameaa:f
            ::f();
            namea::f();
            namea::nameaa::f();
        }

        //namespace alias
        namespace newNamea = namea;
        {
            using namespace newNamea;
            //f();
            //ERROR ambiuous
            //::f
            //namea::f
        }

        //subimport
        {
            using namea::f;
            //imports only name::f

            f();
                //OK
                //namea::f
                //overwrides global f()

            //C c;
                //ERROR
                //only f was imported
        };

        using namespace namea;
            //BAD
            //namespace for the rest of this function
            //you can't unuse later

    }

    //stdlib
    {
        //string
        {
            {
                string s = "abc";
            }

            //cout works as expected
            {
                string s = "abc";

                stringstream oss;
                oss << s;
                assert( oss.str() == "abc" );
            }

            {
                string s = "ab";
                string s1 = "cd";
                string s2 = s + s1;
                assert( s2 == "abcd" );
            }

            {
                std::string s = "abc";
                assert( s.length() == 3 );
            }

            {
                string s = "abc";
                s[0] = 'A';
                assert( s == "Abc" );

                //s[3] = 'd';
                    //NOTE
                    //no born check!
                    //compiles
            }

            {
                stringstream oss;
                oss << "ab";
                oss << "cd";
                assert( oss.str() == "abcd" );
            }
        }

        //io
        {
            //in c++ there is no more printf formatting strings
            //must use the c libs for that

            cout << "cout";
            cout << "cout2" << "cout3" << endl;
            cout << 1;

            cerr << "cerr";
            cout << endl;

            //cin
                //cin >> i;
                //cout << i
        }

        //vector
        {
            //dynamic array based
            //reallocates as necessary

            //create

                //empty
                {
                    vector<int> v;
                    vector<int> v1 = {};
                        //NEW C++11
                        //initializer lists
                    assert( v == v1 );
                }

                //single value
                {
                    {
                        vector<int> v(3,2);
                        vector<int> v1 = {2,2,2};
                        assert( v == v1 );
                    }

                    {
                        vector<int> v(3);
                        vector<int> v1 = {0,0,0};
                        assert( v == v1 );
                    }
                }

                //range copy
                {
                    vector<int> v = {0,1,2};
                    vector<int> v1( v.begin(), v.end() );
                    assert( v == v1 );
                }

                //from existing array
                {
                    int myints[] = {0,1,2};
                    vector<int> v (myints, myints + sizeof(myints)/sizeof(int) );
                    vector<int> v1 = {0,1,2};
                    assert( v == v1 );
                }

                //vectors have order
                {
                    vector<int> v = {0,1,2};
                    vector<int> v1 = {2,1,0};
                    assert( v != v1 );
                }

                //size
                {
                    vector<int> v;
                    assert( v.size() == 0 );
                    v.push_back(0);
                    assert( v.size() == 1 );
                }

                //pushed back
                    //size            no of elements pushed back
                    //empty           same as size() == 0
                    //resize          change size. fill with 0
                    //max_size        maximum size (estimtion of what could fit your computer ram)

                //allocation related
                    //capacity        get how much is allocated
                    //reserve         change how much is allocated
                    //shrink_to_fit   shrink allocated array to size
                    //data            get pointer to allocated array

            //modify
            {
                //can modify with initializers
                {
                    vector<int> v;
                    v = {0};
                    v = {0,1};
                    //assert( v = {0,1} );
                        //ERROR
                        //not possible
                }

                //push_back
                {
                    vector<int> v;
                    vector<int> v1;

                    v.push_back(0);
                    v1 = {0};
                    assert( v == v1 );

                    v.push_back(1);
                    v1 = {0,1};
                    assert( v == v1 );
                }

                //push_back makes copies
                {
                    vector<string> v;
                    string s = "abc";
                    v.push_back(s);
                    v[0][0] = '0';
                    assert( v[0] == "0bc" );
                    assert( s == "abc" );
                        //s was not changed
                }

                //pop_back
                {
                    //no return val
                    //reason:
                        //<http://stackoverflow.com/questions/12600330/pop-back-return-value>
                    vector<int> v = {0,1};
                    vector<int> v1;

                    v.pop_back();
                    v1 = {0};
                    assert( v == v1 );

                    v.pop_back();
                    v1 = {};
                    assert( v == v1 );
                }

                //insert
                {
                    vector<int> v = {0,1};
                    vector<int> v1;

                    v.insert( v.begin(), -1 );
                    v1 = {-1,0,1};
                    assert( v == v1 );

                    v.insert( v.end(), 2 );
                    v1 = {-1,0,1,2};
                    assert( v == v1 );
                }

                //erase
                {
                    vector<int> v;
                    vector<int> v1;

                    v = {0,1,2,3};
                    v.erase( v.begin() + 1, v.end() - 1 );
                    v1 = {0,3};
                    assert( v == v1 );

                    v = {0,1,2};
                    v.erase( v.begin() + 1 );
                    v1 = {0,2};
                    assert( v == v1 );
                }

                //clear
                {
                    vector<int> v= {0,1,2};
                    v.clear();
                    assert( v.size() == 0 );
                }

                //cout v;
                    //no default operator <<
            }

            //random access
            {
                //fast

                vector<int> v = {0,1,2};

                assert( v.front() == 0 );
                assert( v.back() == 2 );

                v[0] = 1;
                assert( v[0] == 1 );
                //cout << v1[2] << endl;
                //v1[2] = 2;
                    //ERROR
                    //just like array overflow
                    //will not change vector size
            }

            //iterate
            {
                vector<int>::iterator it;
                vector<int> v = {2,1,0};
                int i;
                int is[] = {2,1,0};
                for(
                    it = v.begin(), i=0;
                    it != v.end();
                    ++it, ++i
                )
                {
                    assert( *it == is[i] );
                }
            }
        }

        //set
        {
            //- unique elements
            //    inserting twice does nothing
            //- immutable elements
            //- always ordered
            //    inserted elements are in that order
            //    therefore, logarithmic find

            {
                set<int> s;
                s.insert(1);
                s.insert(2);
                s.insert(0);
                s.insert(1);
                set<int> s1 = {0,1,2};
                assert( s == s1 );
            }

            {
                set<int> s = {1,2,0,1};
                set<int> s1 = {0,1,2};
                assert( s == s1 );
            }

            {
                std::set<std::string> s = {"a","c","b","a"};
                std::set<std::string> s1 = {"a","b","c"};
                assert( s == s1 );
            }

            {
                //cout << s[0] << endl;
                    //ERROR
                    //no random access method
            }

            //iterate
            {
                //always sorted
                int i;
                int is[] = {0,1,2};
                set<int>::iterator it;
                set<int> s = {1,2,0,1};
                for(
                    it = s.begin(), i=0;
                    it != s.end();
                    it++, i++
                )
                {
                    assert( *it == is[i] );
                    //*it = 3;
                        //ERROR
                        //read only
                }
            }

            {
                int i;
                string is[] = {"a","b","c"};
                std::set<std::string> s = {"a","c","b","a"};
                std::set<std::string>::iterator it;
                for(
                    it = s.begin(), i=0;
                    it != s.end();
                    it++, i++
                )
                {
                    assert( *it == is[i] );
                    char c = (*it)[0];
                    //(*it)[0] = 'a';
                        //ERROR
                        //read only
                }
            }

            //find
            {
                //since always sorted, find has logarithmic complexity
                set<int> s = {0,1,2};
                set<int>::iterator it = s.find(1);
                assert( *it == 1 );
            }

            //you can modify objects if store pointers
            {
                int i = 0;
                set<int*> s;
                s.insert(&i);
                set<int*>::iterator it = s.find(&i);
                *(*it) = 1;
                assert( i == 1 );
            }

            //count
            {
                //can only return 1 or 0
                set<int> s = {1,2,0,1};
                assert( s.count(1) == 1 );
                assert( s.count(3) == 0 );
            }
        }

        //#hashmap
        {
            //C++0x introduces `std::unordered_map`

            //nonstandard `hash_map` already provided with gcc and msvc++

            //it is even placed in the std:: namespace, but it is *not* standard
        }

        //iterator
        {
            //iteration could be done with random access
            //but still use iterators:
            //- if you ever want to change to a container that
                //has slow random access it will be a breeze
            //- with iterators you don't need to know total container size
            //- iterators may allow you not to keep the whole sequence in
            //   memory, but calculate it on the fly
            //

            vector<int> v = { 1, 2 };
            set<int> s = { 1, 2 };

            //no generic iterator for all containers
            {
                vector<int>::iterator itVec = v.begin();
                set<int>::iterator itSeti = s.begin();
                //iterator it
                //it = v.begin();
                //it = s.begin();
                    //DOES NOT EXIST
                    //there is no standard iterator independent from container
                    //this can be done via type erasure techinques
                    //but would mean loss of performance because of lots of polymorphic calls
                    //and stl is obssessed with performance
            }

            //no born check
            {
                *( v.end() - 1 );
                    //last element
                *( v.end() );
                    //after last element
                    //no born check
                //( v.end().hasNext() );
                    //no such method
            }
        }

        //algorithm
        {
            assert( min(0.1,0.2) == 0.1 );
            assert( max(0.1,0.2) == 0.2 );

            //change order
            {
                //sort
                {
                    vector<int> v = {2,0,1};
                    sort( v.begin(), v.end() );
                    vector<int> v1 = {0,1,2};
                    assert( v == v1 );
                }

                //reverse
                {
                    vector<int> v = {2,0,1};
                    reverse( v.begin(), v.end() );
                    vector<int> v1 = {1,0,2};
                    assert( v == v1 );
                }

                //randomize
                {
                    vector<int> v = {2,0,1};
                    random_shuffle( v.begin(), v.end() );
                }
            }

            //find
            {
                {
                    vector<int> v = {2,0,1};
                    unsigned int pos;

                    pos = find( v.begin(), v.end(), 0 ) - v.begin();
                    assert( pos == 1 );

                    pos = find( v.begin(), v.end(), 1 ) - v.begin();
                    assert( pos == 2 );

                    pos = find( v.begin(), v.end(), 2 ) - v.begin();
                    assert( pos == 0 );

                    pos = find( v.begin(), v.end(), 3 ) - v.begin();
                    assert( pos >= v.size()  );
                }

                //binary_search
                {
                    //container must be already sorted
                    //log time

                    vector<int> v = {2,0,1};
                    sort( v.begin(), v.end() );
                    assert( binary_search( v.begin(), v.end(), 1 ) == true );
                    assert( binary_search( v.begin(), v.end(), 3 ) == false );
                    assert( binary_search( v.begin(), v.end() - 1, 2 ) == false );
                }

                {
                    vector<int> v = {2,1,2};
                    assert( count( v.begin(), v.end(), 0 ) == 0 );
                    assert( count( v.begin(), v.end(), 1 ) == 1 );
                    assert( count( v.begin(), v.end(), 2 ) == 2 );
                }

                {
                    vector<int> v = {2,0,1};
                    assert( *max_element( v.begin(), v.end() ) == 2 );
                    assert( *min_element( v.begin(), v.end() ) == 0 );
                }
            }
        }

        //memory
        {
            //shared_ptr
            {
                //C++11
                //before boost
                {
                    callStack.clear();
                    shared_ptr<NoBaseNoMember> spi1(new NoBaseNoMember);
                    shared_ptr<NoBaseNoMember> spi2(spi1);
                    spi1->method();
                    spi1 = shared_ptr<NoBaseNoMember>(new NoBaseNoMember);
                    spi2 = shared_ptr<NoBaseNoMember>(spi1);
                    assert( callStack.back() == "NoBaseNoMember::~NoBaseNoMember()" );
                }
            }
        }

        //typeinfo
        {
            //get type of variables

            int i, i1;
            Class c;

            assert( typeid(i) == typeid(int) );
            assert( typeid(i) == typeid(i1)  );
            assert( typeid(i) != typeid(c)   );

            std::string s( typeid(i).name() );
                //returns string

            //assert( typeid(i).name() == "int" );
                //WARN
                //undefined because value not specified on the standard
        }

        //thread
        {
            //c++11
            //needs -pthread flag on gcc linux

            std::thread t1( threadFunc, 1000 );
            std::thread t2( threadFunc, 1000 );
                //starts them

            t1.join();
            t2.join();
                //both must end

            assert( threadChange > 0 );
            //assert( threadIds.size() == 2 );
            //assert( threadGlobalEq0 > 0 );
            assert( threadGlobalMutexedEq0 == 0 );

            std::thread::id mainId = std::this_thread::get_id();
            std::this_thread::sleep_for( std::chrono::nanoseconds( nNsecs ) );
            std::this_thread::yield();
        }
    }

#ifdef PROFILE

        loopOnlyProf(nProfRuns);
        whileOnlyProf(nProfRuns);

        intAssignProf(nProfRuns);
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

        //allocation
        {
            stack1bProf(nProfRuns);
            stack1kbProf(nProfRuns);
            stack1mbProf(nProfRuns);

            heapMalloc1bProf(nProfRuns);
            heapMalloc1kbProf(nProfRuns);
            //heapMalloc1mbProf(nProfRuns);

            heapNew1bProf(nProfRuns);
            heapNew1kbProf(nProfRuns);
            //heapNew1mbProf(nProfRuns);
                //new is faster!
        }

        methodCallProf(nProfRuns);
        virtualMethodCallProf(nProfRuns);
            //2x as expensive than function call

        //putsProf(nProfRuns);
            //BAD
            //don't do stdout on profiling
            //system time is not counted anyways
#endif

    return EXIT_SUCCESS;

    //global/static destructors happen at exit time
}
