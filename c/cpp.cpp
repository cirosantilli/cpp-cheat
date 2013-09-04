/*
this will focus in differences between cpp and c.
for the rest, look for a c cheat.

#C++ vs C

    C and C++ are two completelly different standards.

    C++ attempts to be as much as possible extension of C.

    As such, when new C versions such as C99 come out, it is impossible that C++ will immediately
    follow, but it is very likely that the new C features will be incorporated into C++ if possible
    in the following versions.

    Major differences include:

    - classes. Adds enourmous complexity and capabilities to the language.
    - templates
    - stdlib containers
    - function overloading
    - namespaces

    All of those features allow to drastically reduce code duplicationa and improve code structure,
    at the cost of adding huge complexity to the language (probably at least doubles the complexity).

#sources

    #free

        - <http://www.cplusplus.com>

            Explains well what most the features of the language do for beginners.

            Not official in any way, despite the amazing url and google rank.

        - <http://en.cppreference.com/w/>

            Similar to cplusplus.com, but seems to have more info.

            Wiki driven.

            Attempts to document all the language and stdlibs.

            Many behaviour examples.

        - <http://geosoft.no/development/cppstyle.html>

            coding guidelines, clearly exemplified

        - <http://herbsutter.com/gotw/>

            Herb Sutter Guru of the week.

            Hard topics with simple examples.

        - <http://yosefk.com/c++fqa/>

            Comments on the quirks of c++.

            Fun and informative for those that know the language at intermediate level.

    #non free

        - <http://stackoverflow.com/questions/388242/the-definitive-c-book-guide-and-list>

            List of books.

#standards

    like C, C++ is standardized by ISO under the id: ISO/IEC 14882.

    The latest standard costs 30 dollars as of 2013, but free drafts are also available.

    Links to several versions: <http://stackoverflow.com/questions/81656/where-do-i-find-the-current-c-or-c-standard-documents>

    Drafts are freely available at: <http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2012/>.
    N3337 seems to be very close to C++11.

    Like any standard c++ has several versions noted by year.
    There are also minor revisions knows as technical reports.

    #C++89

        First version.

    #C++03

        Bug fix release, not many new features.

    #C++11

        <https://en.wikipedia.org/wiki/C%2B%2B11>

        Previously known as C++0x, but took too long to come out.

        Unlike C++03, *lots* of new features.

        In gcc: add `-std=c++0x` flag. Still marked experimental,
        but good support for the basic features.

    #C++14

        The future as of 2013. The language seems to be accelerating speed of changes
        since this is expected only 3 years after the last standard. Cool.

#POD

        <http://stackoverflow.com/questions/146452/what-are-pod-types-in-c>

#ipc

    socket model

    TODO0

#libs

    C++ has many major interesting libs.

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

#funny

- <http://stackoverflow.com/questions/1642028/what-is-the-name-of-this-operator>

    How can this have so many upvotes??

- <http://stackoverflow.com/questions/6163683/cycles-in-family-tree-software>

    Funny...

- <https://groups.google.com/forum/#!msg/comp.lang.c++.moderated/VRhp2vEaheU/IN1YDXhz8TMJ>

    Obscure language features.
*/

/*
#headers

    C++ stdlib headers that are not C stdlib headers don't have the .h extension.

    With `g++` the C++ standard library is linked against automatically. 

    When writting new libs, you can use either `.h` or `.hpp` as extensions.

    The main c++ lib on linux is the GNU Standard C++ Library vX.

    - std bin is located at: `/usr/lib/i386-linux-gnu/libstdc++.so.X`. Try `locate libstdc++`.
    - std headers are located at: `/usr/include/c++/4.X/`. Try `locate /iostream`.

        Note: c++ std headers have no `.h` extension, just like when included.

    - the ubuntu package is called `libstdc++6.X`. `dpkg -l | grep libstd`

    #c headers

        However, it also provides a cNAME version to every NAME.h, ex: `math.h` vs `cmath`.

        The difference is the following:

        - cX puts things in std:: namespace. *always* use the CNAME version on new code,
            since this reduces the probability of a name conflicts, and is the standard c++ way of doing things.

            Note however that macro expansion happens *before* namespaces are even compiled,
            so you still refer to macros like EXIT_SUCCESS as EXIT_SUCCESS and not `std::EXIT_SUCCESS`.

        - X.h puts *all* in the global namespace, it is exactly the same as the c headers.
            *never* use it in new code.
*/

#include <algorithm>
#include <chrono>           //time operations
#include <exception>        //bad_alloc, bad_cast, bad_exception, bad_typeid, ios_base::failure
#include <functional>       //helper arithmetic/logic functions for algorithms
#include <iostream>         //cout, endl
#include <iterator>
#include <map>              //map, multimap
#include <memory>           //shared_ptr
#include <mutex>
#include <numeric>          //partial sums, differences on vectors of numbers
#include <set>              //set, multiset
#include <string>           //string
#include <sstream>          //stringstream
#include <thread>
#include <typeinfo>         //get type of vars
#include <unordered_map>    //unordered_map, unordered_multimap
#include <utility>          //pair
#include <vector>

//c headers:

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <cstring>

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

/*exception*/

    void exception_func_int()
    {
        throw 1;
    }

    class myexception: public exception
    {
        virtual const char* what() const throw()
        {
            return "myexception::what()";
        }
    };

    //exception specifications

            //All exceptions are catchable (default):
            void exception_func_all() { throw 0; }

            //only int exceptions are catchable
            void exception_func_int_only( bool throw_int ) throw (int)
            {
                if ( throw_int )
                    throw 1;
                else
                    throw 'c';
            }

            //only int and exception or derived excpetions are catchable:
            void exception_func_int_exception_only( int which ) throw ( int, exception )
            {
                switch (which)
                {
                    case 0: throw 0; break;
                    case 1: throw myexception(); break;
                    default: throw 'c'; break;
                }
            }

            //no exceptions are catchable
            void exception_func_none() throw() { throw 1; }

            void exception_func_none_wrapper()
            {
                exception_func_none();
            }


//#class
//{
    class Empty {};

    /*
    This class has no default constructor since another constructor was defined.
    */
    class NoDefaultCtor
    {
        public:
            NoDefaultCtor( int i ){}
    };

    /*
    This class defines a default constructor since it will also provide a non default one.
    */
    class ExplicitDefaultCtor
    {
        public:
            int i;
            ExplicitDefaultCtor(){}
            ExplicitDefaultCtor( int i ) : i(i){}
    };

    /*
    Simple class for tests on constructor destructor order.

    This class has no members which are objects and no base classes.
    */
    class NoBaseNoMember
    {
        public:

            int i;

            //default constructor
            NoBaseNoMember(){ callStack.push_back( "NoBaseNoMember::NoBaseNoMember()"); }

            //copy constructor
            NoBaseNoMember( const NoBaseNoMember& other ) : i(other.i) {
                callStack.push_back( "NoBaseNoMember::NoBaseNoMember(NoBaseNoMember)");
            }

            //copy
            NoBaseNoMember( int i ) : i(i) { callStack.push_back( "NoBaseNoMember::NoBaseNoMember(int)"); }

            //destructor
            ~NoBaseNoMember(){ callStack.push_back( "NoBaseNoMember::~NoBaseNoMember()"); }

            void method(){ callStack.push_back("NoBaseNoMember::method()"); }

            static NoBaseNoMember create()
            {
                return NoBaseNoMember();
            }

            static NoBaseNoMember createNrvo()
            {
                NoBaseNoMember c;
                return c;
            }

            /* it would be hard or impossible to do RVO for this function */
            static NoBaseNoMember createNrvoHard(bool b = false)
            {
                //2 int constructors
                NoBaseNoMember cf = NoBaseNoMember(0);
                NoBaseNoMember ct = NoBaseNoMember(1);
                return b ? ct : cf;
                //2 int destructors
            }

            static void temporaryReference( NoBaseNoMember& temp )
            {
                temp.i = 0;
            }

            static void temporaryReferenceConst( const NoBaseNoMember& temp )
            {
            }
    };

    class NoBaseNoMember0
    {
        public:
            NoBaseNoMember0(){ callStack.push_back( "NoBaseNoMember0::NoBaseNoMember0()"); }
            ~NoBaseNoMember0(){ callStack.push_back( "NoBaseNoMember0::~NoBaseNoMember0()"); }
            void method(){ callStack.push_back("NoBaseNoMember0::method()"); }
    };

    class NoBaseNoMember1
    {
        public:
            NoBaseNoMember1(){ callStack.push_back( "NoBaseNoMember1::NoBaseNoMember1()"); }
            ~NoBaseNoMember1(){ callStack.push_back( "NoBaseNoMember1::~NoBaseNoMember1()"); }
            void method(){ callStack.push_back("NoBaseNoMember1::method()"); }
    };

    class InitializerList
    {
        public:
            int i;
            float f;
    };

#if __cplusplus >= 201103L

    class InitializerListCtor
    {
        public:

            std::vector<int> v;

            InitializerListCtor(std::initializer_list<int> list) {
                for ( auto& i : list )
                    v.push_back( i );
            }
    };

#endif

    class MemberConstructorTest
    {
        public:
            NoBaseNoMember0 member0;
            NoBaseNoMember1 member1;
            MemberConstructorTest(){ callStack.push_back( "MemberConstructorTest::MemberConstructorTest()"); }
            ~MemberConstructorTest(){ callStack.push_back( "MemberConstructorTest::~MemberConstructorTest()"); }
            void method(){ callStack.push_back("MemberConstructorTest::method()"); }
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

    /*
    #this

        Magic value that points to the current object.

        It is implemented by the compiler by passing `this` as the first argument
        of every non-static function of the class.

        This is noticeable when doing operator overload:
    */

    class Base
    {
        public:

            typedef int NESTED_INT;
                //best to put it on top of class
                //so def will go for entire class

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
                //initialize array/std containers in list initializtion

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

                int& getRefIPublic() { return this->iPublic; }

                const int& getPrivateConstRef() const { return this->iPrivate; }
                //value cannot be changed

                int& getPrivateRef() { return this->iPrivate; }
                //value can be changed

                //int& getPrivateRef() const { return this->iPrivate; }
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

            int i, j;

            //ERROR: cannot initialize here
                //int i = 0;

            int iPublic;
            int iAmbiguous;

            int* is;

            float fs4[4];
            std::vector<int> vi;

            mutable int mutableI;
            //static mutable int staticMutableI;
                //ERROR
                //statics can be changed in const functions by default

            /*
            BAD

            every class must have an assigment operator

            but then, assigment does something like this->ic = other->ic

            you could redefine the assigment, but still in your new definition
            ic cannot be changed

            <http://stackoverflow.com/questions/634662/non-static-const-member-cant-use-default-assignment-operator>
            */

            //#static

                static void staticMethod();

                //static void staticMethod() const;
                    //ERROR
                    //static cannot be const

                static int iStatic;
                //ERROR
                    //static int iStatic = 0;
                        //cannot initialize here unless const
                    //int iStatic;
                        //concflicts with static int

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

        /*
        #multable

            OK

            Mutable allows you to change it even in a const method.

            Application to multithreading:
            <http://stackoverflow.com/questions/105014/does-the-mutable-keyword-have-any-purpose-other-than-allowing-the-variable-to>
        */

        this->mutableI = 1;

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
            Class() : i(0), z(1)
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

    /*
    #templates class

    - ultra general! <class T, int N>

    - default values via: <class T=char, int N=10>
        c = Class<>

    - implementation must be put in .h files and compiled by includers
        cannot be put inside a .so therfore
        consider int N, there are int many compilation possibilities!!

    - no equivalent to Javas "T extends Drawable"... sad.
    */

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

//#global scope

    int global = 0;

    //differently from C, computations can be done to initialize globals

        int global2 = global+1;
        int ret1()
        {
            callStack.push_back("before main!");
            return 1;
        }
        int global3 = ret1();

    //ERROR arbitrary computations cannot be done however, only those that initialize a global

        //global = 1;
        //if(1){}
        //callStack.push_back("global");

//#function

    //pass by reference

        //http://stackoverflow.com/questions/114180/pointer-vs-reference

        void byref (int& i){i++;}
        void bypointer (int *i){(*i)++;}

    //return reference to temporary

        std::string getString() { return "abc"; }
        int getInt() { return 0; }
        int getIntVar() { int i = 0; return i; }

    //default args. C++ only. creates several name mungled functions on the assembly code.

        void defaultArgs (int i, int j=0)
        {
            cout << i;
            cout << j;
        }

    //ERROR: no compound literals in c++

        //void foo (int bar[] = (int[2]){0 ,1});

    //function overloading

        void overload(int i){ callStack.push_back("overload(int)"); }
        void overload(int i, int j){ callStack.push_back("overload(int,int)"); }
        void overload(float i){ callStack.push_back("overload(float)"); }
        void overload(float i, float j, float k=0.f){ callStack.push_back("overload(float,float,float=)"); }

        //OK even if return type is different
        //all is decided at compile time

            //int overload(int i, int j, int k){return 1;}

        //ERROR: conflict with int

            //void overload(const int i){ }

        //ERROR: cannot differentiate by output since output is used to decide if other parts of code make sense

            //int overload(){ return 0; }
            //float overload(){ return 0.f; }

        //ERROR: conflict with int int

            //void overload(int i, int j=0){ cout << "int int="; }

        //BAD
        //compiles, but is useless to give a default,
        //since when calling, caller is *forced* to give a value for j
        //or wil get `call is ambiguous` compile time error
        //because compiler cannot decide between
        //here the default arg can be usefull for a call of type float float

            //void overload(float i, float j=1){ cout << "float float="; }

        //TODO why does this compile, that is, how not to make an ambiguous call with overload(int)

            void overloadValAddr(const int i){}
            void overloadValAddr(const int& i){}

        void overloadBase(Base b){}
        void overloadBase(BaseProtected b){}

    //default args

        void defaultArgProto( int i=0 );
        void defaultArgProto( int i ){}

        //BAD
        //usually not what you want
        //since includers will not see the default version

            void defaultArgDef( int i );
            void defaultArgDef( int i=0 ){}

        //ERROR
        //default cannot go in declaration and definition

            //void defaultArgBoth(int i=0);
            //void defaultArgBoth(int i=0){}

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

        //variadic template

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

        //template recursion example

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

    /*
    #auto
    */

        /*no you can't*/
            /*
            int func_auto(auto a){
                ++a;
                return (int)a;
            }
            */

    /*
    #operator overload

            Great tutorial: <http://stackoverflow.com/questions/4421706/operator-overloading?rq=1>

            Good tutorial, specially on how to implement `=`, `+=` and `+` cases:
            <http://courses.cms.caltech.edu/cs11/material/cpp/donnie/cpp-ops.html>

            Like regular functions, C++ also allows operators to be overloaded

            The following operators can all be overloaded:

                +    -    *    /    =    <    >    +=   -=   *=   /=   <<   >>
                <<=  >>=  ==   !=   <=   >=   ++   --   %    &    ^    !    |
                ~    &=   ^=   |=   &&   ||   %=   []   ()   ,    ->*  ->   new
                delete    new[]     delete[]

            Certain operators can be both member functions and free functions.
            This includes most operators such as `+`, `=`, `+=` and others.
            See: <http://stackoverflow.com/a/4421729/895245> for a discussion on how to decide
            between them.

            One question is that being non member improves the incapsulation, since then those
            functions do not have access to private members, and thus do not reflect changes that are
            otherwise invisible.

            Certain operators *cannot* be member functions, such as `<<`.

            Other *must* be members. Those include:

            - `=`  (assignment)
            - `[]` (array subscription),
            - `->` (member access)
            - `()` (function call)
    */

        /*
        ERROR.

        One of the arguments must be a Class or Enum.

        Just imagine the havoc if this were possible! =)
        */

            //int operator+(int i, int j){ return i + j + 1; }

        /*
        class that shows the ideal methods of operator overloading.
        */
        class OperatorOverload {

            public:

                int i;

                OperatorOverload() {
                    this->i = 0;
                }

                OperatorOverload( int i ) {
                    this->i = i;
                }

                /*
                #operator=

                    Special care must be taken with `=` when memory is dynamically alocated because
                    of copy and swap idiom questions.

                    This is not the case for this simple class.

                #return non const reference

                    Return a *non* const reference because the following is possible for base types:

                        (a = b) = c

                    which is the same as:

                        a = b
                        a = c

                    so this obscure syntax should also work for classes.
                */
                OperatorOverload& operator=(const OperatorOverload& rhs){
                    this->i = rhs.i;
                    return *this;
                }

                /*
                #operator+=

                    Implement the compound assign, and the non compound in terms of the compound.

                    Must return a non-const reference for the same reason as `=`.
                */
                OperatorOverload& operator+=(const OperatorOverload& rhs){
                    this->i += rhs.i;
                    return *this;
                }

                /*
                #operator++

                    Post and pre increment are both impemented via this operator.

                    <http://stackoverflow.com/questions/6375697/overloading-pre-increment-operator>
                */
                const OperatorOverload& operator++(){
                    this->i++;
                    return *this;
                }

                /*
                Ambiguous call.

                    This cannot be distinguished from the member method,
                    since the member method gets am implicit `this` first argument.

                    Therefore any call to this operator would give an ambiguous message
                    if this were defined.

                    The effect is the same as the non member function, but the non member is preferred
                    because it improves encapsulation.
                */

                    /*
                        OperatorOverload operator+(OperatorOverload i, OperatorOverload j){
                            OperatorOverload ret;
                            ret.i = i.i + j.i + 1;
                            return ret;
                        }
                    */
        };

        /*
        #operator+

            Implemented in terms of the compound assign.

            Should be const because the following does nothing:

                ( a + b ) = c

            Should be an external method, since it is just a function of `+=`.
        */

            const OperatorOverload operator+ (const OperatorOverload& lhs, const OperatorOverload& rhs){
                return OperatorOverload(lhs) += rhs;
            }

        /*
        Comparison operators: only tow are needed: `==` and `<`.

        The other are functions of those two.

        It is recommended to implement them as non-member functions to increase incapsulation.
        */

            inline bool operator==(const OperatorOverload& lhs, const OperatorOverload& rhs){return lhs.i == rhs.i;}
            inline bool operator!=(const OperatorOverload& lhs, const OperatorOverload& rhs){return !operator==(lhs,rhs);}
            inline bool operator< (const OperatorOverload& lhs, const OperatorOverload& rhs){return lhs.i < rhs.i;}
            inline bool operator> (const OperatorOverload& lhs, const OperatorOverload& rhs){return  operator< (rhs,lhs);}
            inline bool operator<=(const OperatorOverload& lhs, const OperatorOverload& rhs){return !operator> (lhs,rhs);}
            inline bool operator>=(const OperatorOverload& lhs, const OperatorOverload& rhs){return !operator< (lhs,rhs);}

        /*
        overload <<

            `<<` **cannot** be a member method, because if it were then
            its first argument would be an implicit `Class` for the `this`,
            but the first argument of `<<` must be the `ostream`.

            Therefor it must be a free method outside of a class.
        */

            ostream& operator<<(ostream& os, const OperatorOverload& c)
            {
                os << c.i;
                return os;
            }

        /*
        #operator overload and templates

            Operator overload and templates do not play very well together
            because operator overload leads to special function calling syntax,
            which does not go well with template specifications.
        */

            template <class T> T operator-( const T& i, const T& j) { return i + j;}

/*
#namespaces
*/

    //ERROR: same naming rules as vars
        //namespace 2D{}

    //BAD: by convention, namespaces starts with lower case
        namespace D2{}

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
    /*
    #bool

        in C++, unlike in C, bool is part of the language.
    */
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

    //#unsigned
    {
        unsigned int ui = -1;
        int i = 1;
        //if(ui<i)
            //WARN
            //in c, no WARN
    }

    //#const
    {
        /*
        In C++, consts cannot be changed not even through pointers.

        C this is only a warning, and allows us to change ic.
        */
        {
            const int i = 2;
            //int* ip = i;
        }

        //unlike for constexpr, const does not need to have value define at compile time
        {
            std::srand( time( NULL ) );
            const int i = std::rand();
        }

        //consts must be initialized at declaration because they cannot be modified after.
        {
            //const int ic2;
        }

        //const for classes
        {
            const Class c;

            //cannot reassign

                //cc = Class();

            //cannot assign members

                //cc.i = 1;

            //can create const refs to

                const int& cia = c.i;

            //cannot create non const refs

                //int& ia = cc.i;

            /*
            Can only call const methods,
            because a non const method could change the object.

            Therefore, *BE CONST OBSESSIVE!* mark as const every method that does not change the object!
            */
            {
                //c.method();
                c.constMethod();
            }
        }
    }

    /*
    #&

        See references.

    #references

        Basically aliases, similar to `int* const` poinsters or java objects.

        Useful only for function arguments or / return values. In that case the pros are:

        - callers that have an object don't need to dereference it with `&`

        - it is self documenting on the code that the given reference always points to the same thing
            either to modify it or to pass it efficiently without copy.

        The cons are:

        - callers don't know without looking at the signature if they are passing references or copies,
            and wether they should expect that it is possible that the functio modifies their object.

        Just like for pointers, you have to watch scope. If the original object dies,
        you get a dangling reference

        - <http://stackoverflow.com/questions/752658/is-the-practice-of-returning-a-c-reference-variable-evil>
        - <http://stackoverflow.com/questions/7058339/c-when-to-use-references-vs-pointers>
    */
    {
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
                //must be initialized imediatelly

            //int& ia;
                //ERROR
                //must be initialized imediatelly
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

        //#const ereferences
        {
            int i = 1;
            const int& cia = i;
            const int& cia2 = cia;

            const int ci = 1;
            const int& ciac = ci;

            //cia = 2;
                //ERROR

            //ERROR
            //invalid conversion
                //int* ip = &cia;

            //int& ia = cia;
                //ERROR: invalid conversion

            //int& is[2] = {i,i};
                //ERROR: no array of references forbidden

            //int& iac = ci;
                //ERROR
                //must be const int&
        }

        /*
        #return references from functions

            Just like when returning pointers from functions,
            one must take care not to return dangling references.
        */
        {
            /*
            One simple case in which lifetime is simple to guarantee is
            returning members from objects which the callee owns. For example:
            */
            {
                Base b;
                int& ia = b.getRefIPublic();
                ia = 0;
                assert( b.iPublic == 0 );
                ia = 1;
                assert( b.iPublic == 1 );
            }

            /*
            #return

                C++ adds a special rule: binding a const reference to a on stack
                makes it live to the end of the reference's lifetime

                TODO0 why must it be const? rationale
                TODO0 why the special no base destructor rule mentioned in the gotw article? rationale

                <http://herbsutter.com/2008/01/01/gotw-88-a-candidate-for-the-most-important-const/>
                <http://stackoverflow.com/questions/2784262/does-a-const-reference-prolong-the-life-of-a-temporary>
            */
            {
                //objects
                {
                    //OK
                    {
                        const std::string& s = getString();
                        assert( s == "abc" );
                    }

                    //ERRROR invilid initialization of non const reference
                    {
                        //std::string& s = getString();
                        //assert( s == "abc" );
                    }
                }

                //same for ints
                {
                    {
                        //int& ia = getInt();
                        //int& ia = getIntVar();
                    }

                    {
                        const int& ia = getInt();
                    }
                }
            }

            //you can modify a private if you non const reference to it
            {
                    Base b;
                    int& ia = b.getPrivateRef();
                    ia = 0;
                    assert( b.getPrivateRef() == 0 );
                    ia = 1;
                    assert( b.getPrivateRef() == 1 );
            }

            //if the reference is const it does not work anymore
            {
                Base b;

                {
                    const int& ia = b.getPrivateConstRef();
                    //ia = 1;
                }

                //ERROR invalid initialization
                {
                    //int& ia = b.getPrivateConstRef();
                }
            }
        }
    }

#if __cplusplus >= 201103L

    /*
    #constexpr

        c++11 keyword

        Compile time ensures that an expression is a compile time constant.

    #constexpr function

        TODO
    */
    {
        constexpr int i = 0;
        constexpr int i2 = i + 1;

        //ERROR constexprs are read only

            //i = 1;

        //WARN unitialized constexpr

            //constexpr int i3;

        //unlike for const, this fails, because it is not calculable at compile time
        {
            std::srand( time( NULL ) );
            //constexpr int i = std::rand();
        }

        /*
        cannot have constexpr to complex types

        TODO0 rationale
        */
        {
            //constexpr std::string s = "abc";
        }
    }

#endif

#if __cplusplus >= 201103L

    /*
    #auto

        C++11 keyword

        Completelly differs in meaning with the useless C `auto` keyword.

        Variable type is infered based on return value of initialization.

        Major application: create an iterator without speficying container type.

        More succint than auto when possible to use, but less general.
    */
    {
        //basic usage
        {
            //the compiler infers the type of i from the initialization.
            auto i = 1;
        }

        //reference
        {
            int i = 1;
            auto& ai = i;
            ai = 2;
            assert( i == 2 );
        }

        //ERROR must initialize immediately.
        {
            //auto i;
            //i = 1;
        }

        //does not imply reference while decltype does
        {
            int i = 0;
            int& ir = i;
            auto ir2 = ir;
            ir2 = 1;
            assert( i == 0 );
        }
    }

#endif

#if __cplusplus >= 201103L

    /*
    #decltype

        C++11 keyword

        Replace decltype with type of an expression at compile time.

        More powerful than `auto`.
    */
    {
        int i = 1;
        float f = 2.0;
        decltype( i + f ) f2 = 1.5;
        assert( f2 == 1.5 );

        //implies reference while auto does not
        {
            int i = 0;
            int& ir = i;
            decltype(ir) ir2 = ir;
            ir2 = 1;
            assert( i == 1 );
        }

        //can be used basically anywhere
        {
            int i = 0;
            std::vector<decltype(i)> v;
            v.push_back(0);
        }
    }

#endif

    /*
    #vla

        called variable length array VLS

        C99 supports this

        compiler implementation:
        must increment/decrement stack pointer at each array
        meaning, one extra multiplication and sum for every VLA declared

    */
    {
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

    //#enum
    {
        //unlike c, already does typedef
        {
            enum TEXTURE { GRASS, WALL, SKY };
            TEXTURE t = GRASS;
        }

        //ERROR: only const expressions allowed
        {
            //int i = 0;
            //enum E2 { E2=i };
        }
    }

    //#for
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

#if __cplusplus >= 201103L

    /*
    #range based for for arrays

        Stop writing for loops!

        Also has a version for iterators.

        It seems that the array length is deduced at compile time!
    */
    {
        {
            int is[] = { 1, 2 };
            for (int &i : is) {
                i *= 2;
            }
            assert( is[0] == 2 );
            assert( is[1] == 4 );
        }

        /*
        does not work for dynamic memory since
        there would be no way to know the array size at compile time
        */
        {
            //int *is = new int[2];
            //is[0] = 1;
            //is[0] = 2;
            //for (int &i : is) {
            //    i *= 2;
            //}
            //delete[] is;
        }
    }

#endif

    //#function
    {
        //#overload
        {
            overload( 1 );
            assert( callStack.back() == "overload(int)" );
            callStack.clear();

            //base type conversions
            {
                overload(1.0f);

                /*
                ERROR
                ambiguous overload(int) overload(float)
                compiler does not know wether convert double to float or int
                */
                //overload(1.0);
            }

            assert( callStack.back() == "overload(float)" );
            callStack.clear();

            /*
            ERROR: ambiguous
            should compiler coverts to Base or BaseProtected? Both are possible via the default copy constructors.
            */
            {
                Class cOverload;
                //overloadBase(cOverload);
            }

            //i=4;
            //overloadValAddr(i);
                //ERROR
                //ambiguous
        }

        /*
        #operator overload
        */
        {
            //OperatorOverload overload `+`
            {
                OperatorOverload i;

                //==
                assert( OperatorOverload(3) == OperatorOverload(3) );

                //<
                assert( OperatorOverload(1) < OperatorOverload(2) );

                //=
                i = OperatorOverload(1);
                assert( i == OperatorOverload(1) );

                //+=
                i = OperatorOverload(1);
                i += OperatorOverload(2);
                assert( i == OperatorOverload(3) );

                //+
                assert( OperatorOverload(1) + OperatorOverload(2) == OperatorOverload(3) );

                //++
                {
                    i = OperatorOverload(1);
                    assert( ++i == OperatorOverload(2) );
                    assert( i == OperatorOverload(2) );

                    /* TODO understand and get working */
                    /*
                    i = OperatorOverload(1);
                    assert( i++ == OperatorOverload(1) );
                    assert( i == OperatorOverload(2) );
                    */
                }

                //<<
                {
                    i = OperatorOverload(123);
                    std::stringstream os;
                    os << i;
                    assert( os.str() == "123" );
                }
            }

            /*
            Explicit call syntax.

            Does the same as the implicit call syntax, but is uglier.

            May be required when the function is also a template function.
            */
            {
                OperatorOverload i, j;
                i = OperatorOverload(1);
                j = OperatorOverload(2);

                assert( operator+( i, j ) == OperatorOverload(3) );

                i.operator=( j );
                assert( i == j );
            }

            /*
            #operator overload and templates

                TODO possible to call `operator-`?
            */
            {
                OperatorOverload i, j;
                i = OperatorOverload(1);
                j = OperatorOverload(2);

                //Impossible
                {
                    //assert( (i -<OperatorOverload> j).i == 4 );
                }

                //assert( operator-<OperatorOverload>( i, j ) == OperatorOverload(3) );
            }
        }

        //#template
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

    /*
    #exception

        Great source: <http://www.cplusplus.com/doc/tutorial/exceptions/>

        Application: centralize error handling in a single place, even if outside executing functions.

        The application is similar to C's longjmp, but the implementation is different.
        TODO how are they implemented in assembly code? <http://stackoverflow.com/questions/490773/how-is-the-c-exception-handling-runtime-implemented>
        It is more magic than C longjmp as it does type checking.

        Anything can be thrown, but the most standard and extensible method is to throw subclasses of exception,
        so just do that always.

        There is no finally block: <http://stackoverflow.com/questions/161177/does-c-support-finally-blocks-and-whats-this-raii-i-keep-hearing-about>
        Deinitializations are left for destructors.

        #standard exceptions

            - bad_alloc         thrown by new on allocation failure
            - bad_cast          thrown by dynamic_cast when fails with a referenced type
            - bad_exception     thrown when an exception type doesn't match any catch
            - bad_typeid        thrown by typeid
            - ios_base::failure thrown by functions in the iostream library
    */
    {
        /*
        Exceptions can jump out of functions.

        This is their main reason for existing!
        */
        {
            try
            {
                exception_func_int();
            }
            catch ( int i ) {
                assert( i == 1 );
            }
        }

        /*
        Catch blocks work like function overloads and catch by type.
        */
        try
        {
            throw 'c';
        }
        catch (int i)   { assert(false); }
        catch (char c)  {  }

        /*
        `...` is the default case
        */
        try
        {
            throw 1.0;
        }
        catch (int i)   { assert(false); }
        catch (char c)  { assert(false); }
        catch (...)     { }

        /*
        Derived classes.

        Just like for function overloading, base classes catch for derived classes.
        */
        {
            try
            {
                throw myexception();
            }
            catch ( std::exception& ex )    { }
            /*
            This compiles, but generates a warning, since the first catch will always catch instead of this one.
            */
            //catch ( myexception& ex )       { assert(false); }
            catch (...)                     { assert(false); }

            /*
            this is a more common exception ordering, first derived then base.
            */
            {
                try
                {
                    throw myexception();
                }
                catch ( myexception& ex )       { }
                catch ( std::exception& ex )    { assert(false); }
                catch (...)                     { assert(false); }
            }
        }

        /*
        #uncaught exceptions.

            Uncaught exceptions explose at top level and terminate the program.

            Check out the error messages generated by each exception.

            Classes that derive from exception and implement `what()` can print custom messages,
            which may contain useful debug info. This is a major point in favor of using exception
            classes instead of base types.
        */
        {
            //throw 1;
            //throw 'c';
            //throw 1.0;
            //throw myexception();
        }

        /*
        Exception specifications

            Functions can specify which exceptions are catchable with the following syntax:
        */
        {
            try
            {
                exception_func_int_only( true );
            }
            catch ( int i )  { }
            catch (...)      { assert(false); }

            try
            {
                //exception_func_int_only( false );
            }
            catch (...) { /* not even ... this can catch non int exceptions thrown by this function */ }

            try
            {
                exception_func_int_exception_only( 1 );
            }
            catch ( int i )             { }
            catch ( myexception& ex )   { }
            catch (...)                 { assert(false); }

            try
            {
                //exception_func_none();
            }
            catch (...) { /* no exception thrown by this function is catchable */ }

            try
            {
                //exception_func_none_wrapper();
            }
            catch (...) { /* the same goes if we wrap the function */ }
        }
    }

    //#class
    {
        /*
        #constructor

            Called whenever object is created to initialize the object.
        */
        {
            {
                callStack.clear();
                NoBaseNoMember c; //default constructor was called!
                vector<string> expectedCallStack = {
                    "NoBaseNoMember::NoBaseNoMember()",
                };
                assert( callStack == expectedCallStack );
            }

            /*
            This is how non default constructors should be called.

            The call stack is not predictable becuase of copy ellision,
            but will be a single constructor in most compilers.
            */
            {
                NoBaseNoMember c = NoBaseNoMember(1);
                assert( c.i == 1 );
            }

            /*
            #default constructor

                Constructor that takes no arguments.

                This constructor is special in the sense that it is implicitly called in certain cases.

                If no constructor is declared, a default constructor is created.

                If any case constructor is declared, even with non default args,
                the default is not created.

                It is a good idea to always implement a default constructor,
                since this is the only way arrays of fiexed numbers o fobjects can be created before C++03.
            */
            {
                //the default constructor exists
                {
                    Empty e = Empty();
                }

                //this class does not have a default constructor
                {
                    //NoDefaultCtor o = NoDefaultCtor();
                    //NoDefaultCtor os[2]; //ERROR cannot be done because this class has not default constructors.
                }
            }

            /*
            The default constructor does not necessarily initialize built-in types:

                <http://stackoverflow.com/questions/2417065/does-the-default-constructor-initialize-built-in-types>
            */
            {
                NoBaseNoMember o;
                //assert( o.i == 0 ) //undefined behaviour
            }

            /*
            declaration syntax gotcha
            */
            {
                /*
                BAD

                Declares *FUNCTION* called `c` that returns `Class` inside function main.

                This is the same as in C, where it is possible to declare a function from inside another function,
                but not define it.
                */
                {
                    Class c();

                    //ERROR: definition is not possible inside another function

                        //Class c(){ return Class(); }

                    //c.i;
                }

                //If you want to call a default constructor, use:
                {
                    Class c;
                    assert( c.i == 0 );
                }

                /*
                For non-default constructors, things work as expected,
                as this could not possibe be a function declaration.
                */
                {
                    Class c(1);
                    assert( c.i == 1 );
                }
            }
        }

        /*
        #initializer list
        */
        {
            //works like in C structs
            {
                InitializerList o = { 1, 1.1f };
                assert( o.i == 1 );
                assert( o.f == 1.1f );
                //assert( o.f == 1.1 ); //TODO0 why does this fail even if `assert( 1.0 == 1.0f )`?
            }

#if __cplusplus >= 201103L

            /*
            #initializer list constructor

                c++11 allows for an explicit usage of the initializer list

                This is useful in cases where you don't know beforehand how many arguments
                a constructor should receive.

                For example, the STL Vector class gets an initializer list constructor on C++11,
                which allows one to initialize it to any constant.

                TODO0 could this not be achieved via cstdarg?
            */
            {
                //STL vector usage example
                {
                    std::vector<int> v = { 0, 1 };
                    //std::vector<int> v = std::vector<int>( { 0, 1 } ); //SAME
                    assert( v[0] == 0 );
                    assert( v[1] == 1 );
                    assert( v == std::vector<int>( { 0, 1 } ) );
                    //assert( v == { 0, 1 } );  //ERROR
                }

                //how to use it in a class
                {
                    InitializerListCtor o = { 0, 1 };
                    assert( o.v == std::vector<int>( { 0, 1 } ) );
                }
            }

#endif
        }

        /*
        #destructor

            Called when:

            1) statically allocated object goes out of scope
            2) dynamically allocated object gets deleted

            Major application:

            - delocate dynamic memory that was allocated on constructor

            virtual:

            not necessary
            *but*
            almost always what you want a polymorphic class to which there
            will be pointers to base classes
        */
        {
            callStack.clear();

            {
                NoBaseNoMember b;
            } //destructor is called now!

            vector<string> expectedCallStack = {
                "NoBaseNoMember::NoBaseNoMember()",
                "NoBaseNoMember::~NoBaseNoMember()"
            };
            assert( callStack == expectedCallStack );
        }

        //array of objects
        {
            //default constructor is called when array is created.
            {
                callStack.clear();
                NoBaseNoMember os[2]; //default constructor called
                vector<string> expectedCallStack = {
                    "NoBaseNoMember::NoBaseNoMember()",
                    "NoBaseNoMember::NoBaseNoMember()",
                };
                assert( callStack == expectedCallStack );
            }

            /*
            to initialize the objects with a non default constructor
            one flexible possibility is to use simply use assignment.

            The downside of this method is that constructors are called twice
            for each array element. To overcome this if you know the size of the array
            beforehand you can use initialized arrays.
            */
            {
                callStack.clear();

                NoBaseNoMember os[2]; //default constructor called
                os[0] = NoBaseNoMember(0);
                os[1] = NoBaseNoMember(1);

                vector<string> expectedCallStack = {
                    "NoBaseNoMember::NoBaseNoMember()",
                    "NoBaseNoMember::NoBaseNoMember()",
                    "NoBaseNoMember::NoBaseNoMember(int)",
                    "NoBaseNoMember::~NoBaseNoMember()",
                    "NoBaseNoMember::NoBaseNoMember(int)",
                    "NoBaseNoMember::~NoBaseNoMember()",
                };
                //assert( callStack == expectedCallStack );
            }

            /*
            Faster because does not call default constructors and extra destructors.
            */
            {
                callStack.clear();

                NoBaseNoMember os[] = { NoBaseNoMember(0), NoBaseNoMember(1) };

                vector<string> expectedCallStack = {
                    "NoBaseNoMember::NoBaseNoMember(int)",
                    "NoBaseNoMember::NoBaseNoMember(int)",
                };
                assert( callStack == expectedCallStack );
            }

            /*
            #memset

                Like many C functions, memset does not work with objects, because objects
                may contain extra data such as a VTABLE.
            */
            if ( 0 )
            {
                Class *var = new Class;
                std::memset( var, 0, sizeof(Class) );
            }
        }

        /*
        Member class constructors are called before outter class in declaration order.

        Member class destructors are called after outter class in reverse declaration order.
        */
        {
            callStack.clear();

            {
                MemberConstructorTest o;
            }

            vector<string> expectedCallStack =
            {
                "NoBaseNoMember0::NoBaseNoMember0()",
                "NoBaseNoMember1::NoBaseNoMember1()",
                "MemberConstructorTest::MemberConstructorTest()",
                "MemberConstructorTest::~MemberConstructorTest()",
                "NoBaseNoMember1::~NoBaseNoMember1()",
                "NoBaseNoMember0::~NoBaseNoMember0()",
            };
            assert( callStack == expectedCallStack );
        }

        //#static fields
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

        /*
        #temporary objects

            Temporary objects are objects without a name that exist for short time on the stack.

            May exist in C as an implmentation method for structs,
            but their effect is not noticeable because there are no constructors or destructors in C.
        */
        {
            /*
            Two constructors and *one destructor* called!

            Operation order:

            - `NoBaseNoMember c;` calls a constructor
            - `NoBaseNoMember();` calls a constructor of a temporary object
            - assignment is made
            - the object created by `NoBaseNoMember();` goes out of scope and is destroyed

            Therefore the following may be more effecitive due to copy ellision:

                NoBaseNoMember c = NoBaseNoMember();

            in which case only a single constructor is called.
            Copy ellision in this case is widely implemented.
            */
            {
                callStack.clear();

                NoBaseNoMember c;       //1 constructor
                c = NoBaseNoMember();   //1 constructor of the temporary, 1 assign, 1 destructor of the temporary

                vector<string> expectedCallStack =
                {
                    "NoBaseNoMember::NoBaseNoMember()",
                    "NoBaseNoMember::NoBaseNoMember()",
                    "NoBaseNoMember::~NoBaseNoMember()",
                };
                assert( callStack == expectedCallStack );
            }

            /*
            Methods of temporaries can be called.

            Constructor and destructor are called, so this is not very efficient,
            and a static method would probably be better in this case.
            */
            {
                callStack.clear();
                NoBaseNoMember().method();
                vector<string> expectedCallStack =
                {
                    "NoBaseNoMember::NoBaseNoMember()",
                    "NoBaseNoMember::method()",
                    "NoBaseNoMember::~NoBaseNoMember()",
                };
                assert( callStack == expectedCallStack );
            }

            /*
            Cannot get address of a temporary on current scope
            as it will certainly go out of scope and leave a dangling reference.
            */
            {
                Class c = Class();
                Class* cp = &c;
                //cp = &Class();
            }

            /*
            Temporaries can be passed to functions.

            This is essentially the same as passing them to copy constructors or assigns.

            This is valid because the temporary object is valid until the end of the full expression
            in which it is created; that is, until after the function call returns.

            Temporaries can be passed by address only as const parameters of functions.
            TODO why? Modifying it for return makes no sense, but why not usint it as a buffer?
            isn't its lifetime longer than the function call? Is this related to const lifetime lenghening?
            */
            {
                NoBaseNoMember b;
                NoBaseNoMember::temporaryReference( b );
                //NoBaseNoMember::temporaryReference( NoBaseNoMember() );
                NoBaseNoMember::temporaryReferenceConst( NoBaseNoMember() );
            }
        }

        /*
        #copy vs assign

            every class gets a default assign operator (=) and copy constructor (`Classname(Classname other)`).

            the defaults might not be what you want, specially when you allocate memory inside the constructor!

            <http://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom>

            <http://stackoverflow.com/questions/4172722/what-is-the-rule-of-three>
        */
        {
            //#copy constructor
            {
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

            /*
            #assign operator for classes.

                There is a default assign operator which calls assign (=) on all members.
            */
            {
                Class c, c1;
                c.i = 1;
                c1.i = 2;
                c1 = c;
                assert( c1.i == 1 );

                //there are still two separate copies of the object
                c1.i = 2;
                assert( c.i == 1 );
            }

            /*
            There is no default copy constructor/assign operator inherited from base clases,
            you must write one yourself.
            */
            {
                Base b;
                Class c(b);
            }

            /*
            It is possible to assing / copy from derived to base class.
            */
            {
                Class c;
                c.Base::i = 1;
                Base b(c);
                assert( b.i == 1 );
            }

            /*
            #equality operator for classes

                There is no default `==` operator for classes.

                You must define your own.
            */
            {
                Class c0 = Class();
                Class c1 = Class();
                //assert( c0 == c1 );
            }

            /*
            #copy and swap idom

                TODO <http://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom>
            */
            {
            }

            /*
            #move semantics

                TODO <http://stackoverflow.com/questions/3106110/what-is-move-semantics>
            */
            {
            }

            /*
            #as-if rule

                <http://en.cppreference.com/w/cpp/language/as_if>

                Rule that specifies that compilers can optimize any behaviour that is not fixed by the standard.

                The following are specified:

                - Accesses (reads and writes) to the volatile objects occur in the same order as written.

                - At program termination, the data written to all files is exactly as if the program was executed as written.

                - All input and output operations occur in the same order and with the same content
                    as if the program was executed as written.

                The only exception to the ruls is copy ellision.
            */

            /*
            #copy elision

                <http://en.cppreference.com/w/cpp/language/copy_elision>
                <http://stackoverflow.com/questions/12953127/what-are-copy-elision-and-return-value-optimization>

                Exceptions to the as-if rules, which specifies cases in which compilers
                may reduce the number of copy operations made, which is detectable in C++'
                because of possible side effects constructors and destructors (such as printing to stdout
                or modifying a global vector).
            */
            {
                /*
                #temporary copy ellision

                    If no copy elision is done:

                    1) temporary object constructor
                    2) copy temporary to c
                    3) temporary object destructor

                    If copy elision is done:

                    1) c is constructed directly.

                    Therefore both results are possible and the result is unpredictable:

                        vector<string> expectedCallStack = {
                            "NoBaseNoMember::NoBaseNoMember()",
                        };

                        vector<string> expectedCallStack = {
                            "NoBaseNoMember::NoBaseNoMember()",
                            "NoBaseNoMember::~NoBaseNoMember()",
                        };

                        assert( callStack == expectedCallStack );
                */
                {
                    {
                        callStack.clear();
                        NoBaseNoMember c = NoBaseNoMember();
                        std::cout << "temporary copy elision" << std::endl;
                        for ( auto s : callStack ) std::cout << "  " << s << std::endl;
                    }

                    {
                        callStack.clear();
                        NoBaseNoMember c;
                        c = NoBaseNoMember();
                        std::cout << "no temporary copy elision" << std::endl;
                        for ( auto s : callStack ) std::cout << "  " << s << std::endl;
                    }
                }

                /*
                #RVO

                    Return value optimization.

                    Like in C, when a function returns an object, the compiler adds a hidden pointer
                    to the function.

                    Ex: definition

                        static NoBaseNoMember create()
                        {
                            return NoBaseNoMember();
                        }

                    gets converted to:

                        static create( NoBaseNoMember* hiddenTemp)
                        {
                            //1 constructor, 1 copy, 1 destructor if no temporary copy elision
                            //1 constructor                       if    temporary copy elision
                            *hiddenPtr = NoBaseNoMember();
                        }

                    And calls:

                        c = NoBaseNoMember::create();

                    Get converted to either:

                        NoBaseNoMember hiddenTemp;      //1 constructor call
                        NoBaseNoMember::create(&hiddenTemp);
                        s = temp;                       //1 copy
                                                        //1 destructor for the temporary object

                    If no RVO was made, giving:

                    - 2 constructors
                    - 1 or 2 copies
                    - 1 or 2 destructors

                    or simply:

                        getNoBaseNoMember(&s);

                    if RVO is made which adds up to:

                    - 1 constructor
                    - 0 or 1 copies
                    - 1 destructor
                */
                {
                    NoBaseNoMember c;
                    callStack.clear();

                    c = NoBaseNoMember::create();
                    std::cout << "RVO" << std::endl;
                    for ( auto s : callStack ) std::cout << "  " << s << std::endl;
                }

                /*
                #NRVO

                    Named RVO.

                    Like RVO, but harder to make since takes a named object instead of a temporary return value,
                    that is:

                        NoBaseNoMember c;
                        return c

                    instead of:

                        return NoBaseNoMember();

                    In many cases this cannot be done, and it is hard or impossible for the compiler to optimize this.
                */
                {
                    /* should be possible if the compiler is smart enough */
                    {
                        NoBaseNoMember c;
                        callStack.clear();
                        c = NoBaseNoMember::createNrvo();
                        std::cout << "NRVO" << std::endl;
                        for ( auto s : callStack ) std::cout << "  " << s << std::endl;
                    }

                    /*
                    TODO0 why do I get:

                        NoBaseNoMember::NoBaseNoMember(int)
                        NoBaseNoMember::NoBaseNoMember(int)
                        NoBaseNoMember::NoBaseNoMember(NoBaseNoMember)  //copy from temporary to C
                        NoBaseNoMember::~NoBaseNoMember()               //destructor for the temporary
                        NoBaseNoMember::~NoBaseNoMember()               //destructor for 0
                        NoBaseNoMember::~NoBaseNoMember()               //destructor for 1

                    - where is the constructor of the temporary object?
                    */
                    {
                        NoBaseNoMember c;
                        callStack.clear();
                        c = NoBaseNoMember::createNrvoHard();
                        std::cout << "NRVO hard" << std::endl;
                        for ( auto s : callStack ) std::cout << "  " << s << std::endl;
                    }
                }

                /*
                #exception copy elision
                */
                {
                }
            }
        }

        //#template
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

        //#method overridding
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

        /*
        #polymorphism

            - loop an array of several dereived classes
            - call a single base class method
            - uses the correct derived override

            Implementation: *vtable* is used to implement this.

        #vtable

            <http://en.wikipedia.org/wiki/Virtual_method_table>

            Whenever you create a pointer to a class with a virtual method,
            that pointer points to a pointer that identifies the class type,
            and points to the correct method.

            Consequence: every call to a virtual methods means:

            - an extra pointer dereference
            - an extra pointer stored in memory

            Also virtual functions cannot be inlined.

        */
        {
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

        //#nested classes
        {
            {
                cout <<"Base::Nested baseNested;" << endl;
                Base::Nested baseNested;
                cout << "Base::Nested2 baseNested2;" << endl;
                Base::Nested2 baseNested2;
            }
        }

        //#nested typedefs
        {
            Base::NESTED_INT i = 1;
            //Base::PRIVATE_NESTED_INT j = 1;
                //ERROR
                //is private
        }

        //#design patterns
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

    //#typeid
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

    /*
    #typecast

        Sources:

        - <http://www.cplusplus.com/doc/tutorial/typecasting/>
        - <http://stackoverflow.com/questions/28002/regular-cast-vs-static-cast-vs-dynamic-cast>
        - <http://stackoverflow.com/questions/332030/when-should-static-cast-dynamic-cast-and-reinterpret-cast-be-used>
    */
    {
        //TODO

        //implicit via constructor/assigment
            //class A {};
            //class B { public: B (A a) {} };
            //A a;
            //B b=a;

        /*
        #explicit
        */
        {
            //TODO

            //<http://stackoverflow.com/questions/121162/what-does-the-explicit-keyword-in-c-mean>
        }
    }

    /*
    #dynamic memory

        C++ replaces C's malloc and free with new and delete.

        Use it always instead of malloc on new code.

    #new

        Allocate dynamic memory.

        Throw `std::bad_alloc` in case of error.

    #realloc

        There is no direct replacement to realloc or calloc as of C++11
        <http://stackoverflow.com/questions/3482941/how-do-you-realloc-in-c>
    */
    {
        /*
            basic usage with proper error checking
        */
        {
            int* ip;
            try
            {
                ip = new int[5];
            }
            catch( std::bad_alloc& ba )
            {
                assert( false );
            }
            ip[0] = 1;
            delete[] ip;
        }

        //allocate single object / base type
        {
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

        /*
        #calloc

            There is an analogue to calloc in the language called *value-initialization*.

            <http://stackoverflow.com/questions/808464/c-new-call-that-behaves-like-calloc>
        */
        {
            //base types
            {
                int* is = new int[2]();
                assert( is[0] == 0 );
                assert( is[1] == 0 );
                delete[] is;
            }

            //works for structs
            {
                struct T { int a; };
                T *t = new T[1]();
                assert( t[0].a == 0 );
                delete[] t;
            }

            /*
            Works for objects.

            Note how the default constructor was called since `z == 1`.
            */
            {
                Class *cs = new Class[1]();
                assert( cs[0].i == 0 );
                assert( cs[0].z == 1 );
                delete[] cs;
            }

            //but only works with default constructors
            {
                //Class *cs = new [1](1);
            }
        }
    }

    /*
    #namespace

    - *never* use `using namespace X` on a header file
    */
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

    //#stdlib
    {
        //#string
        {
            //initialize from string literal
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

            //cat. Creates a new string.
            {
                string s = "ab";
                string s1 = "cd";
                string s2 = s + s1;
                assert( s2 == "abcd" );
            }

            //length
            {
                std::string s = "abc";
                assert( s.length() == 3 );
            }

            //
            {
                string s = "abc";
                s[0] = 'A';
                assert( s == "Abc" );

                //s[3] = 'd';
                    //NOTE
                    //no born check!
                    //compiles
            }

            /*
            #stringstream

                Like cout, but output does not get put to stdout, but stored.

                It can be retreived via `str()`.

                Possible application: build up a huge string step by step.
                May be more efficient than concatenations which always generates new objects.
            */
            {
                stringstream oss;
                oss << "ab";
                oss << "cd";
                assert( oss.str() == "abcd" );

                //str does not clear the stringstream object
                assert( oss.str() == "abcd" );

                //to clear it you could do
                oss.str("");
                assert( oss.str() == "" );
            }

            /*
            #int to string

                There are a few standard alternatives.

                <http://stackoverflow.com/questions/5590381/easiest-way-to-convert-int-to-string-in-c>
            */
            {
                /*
                stringstream seems to be the best pre C++11 solution.

                It also has the advantage of working for any class that implements `operator<<`.
                */
                {
                    stringstream oss;
                    oss << 123;
                    assert( oss.str() == "123" );
                }

                /*
                C sprintf

                Works, but uses too many conversion operations.
                */
                {
                    char cs[16];
                    std::sprintf( cs, "%d", 123 );
                    std::string s = (cs);
                    assert( s == "123" );
                }

                /*
                C++11 solves the question once and for all with a robust one-liner for base types.

                It is not intended however for operation with classes.
                */
#if __cplusplus >= 201103L
                assert( std::to_string(123) == "123" );
#endif
            }
        }

        /*
        #file io

        #printf

            In c++ there is no more printf formatting strings
            must use the c libs for that.

        #endl

            System dependent newline.
        */
        {
            cout << "cout" << endl;
            cout << "cout2" << "cout3" << endl;
            cout << 1 << endl;

            cerr << "cerr";
            cout << endl;

            //cin

                //cout << "Enter an integer:" << endl
                //cin >> i;
                //cout << i
        }

        /*
        #vector

            Dynamic array that grows / shrinks as necessary.

            $O(1)$ random access.
        */
        {
            //create
            {
                //empty
                {
                    vector<int> v;

                    //NEW way in C++11
                    //initializer lists
                    vector<int> v1 = {};

                    assert( v == v1 );
                }

                //single value
                {
                    {
                        vector<int> v( 3, 2 );
                        vector<int> v1 = { 2, 2, 2 };
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
                    vector<int> v = { 0, 1, 2 };
                    vector<int> v1( v.begin(), v.end() );
                    assert( v == v1 );
                }

                //from existing array
                {
                    int myints[] = { 0, 1, 2 };
                    vector<int> v( myints, myints + sizeof( myints ) / sizeof( int ) );
                    vector<int> v1 = { 0, 1, 2 };
                    assert( v == v1 );
                }

                //vectors have order
                {
                    vector<int> v =  { 0, 1, 2};
                    vector<int> v1 = { 2, 1, 0};
                    assert( v != v1 );
                }

                //size
                {
                    vector<int> v;
                    assert( v.size() == 0 );
                    v.push_back( 0 );
                    assert( v.size() == 1 );
                }

                /*
                size related:

                - size            no of elements pushed back
                - empty           same as size() == 0
                - resize          change size. fill with 0
                - max_size        maximum size (estimtion of what could fit your computer ram)

                allocation related:

                - capacity        get how much is allocated
                - reserve         change how much is allocated
                - shrink_to_fit   shrink allocated array to size
                - data            get pointer to allocated array
                */
            }

            //the vector stores copies of elements, not references
            {
                std::string s = "abc";
                vector<std::string> v = { s };
                v[0][0] = '0';
                assert( v[0]    == "0bc" );
                assert( s       == "abc" );
            }

            //modify
            {
                //can modify with initializers
                {
                    vector<int> v;
                    v = { 0 };
                    v = { 0, 1 };
                    assert( v == std::vector<int>( { 0, 1 } ) );
                }

                //#push_back
                {
                    vector<int> v;
                    vector<int> v1;

                    v.push_back( 0 );
                    v1 = { 0 };
                    assert( v == v1 );

                    v.push_back(1);
                    v1 = { 0, 1 };
                    assert( v == v1 );

                    /*
                    push_back makes copies with assign `=`

                    If you want references, use pointers, or even better, auto_ptr.
                    */
                    {
                        vector<string> v;
                        string s = "abc";

                        v.push_back( s );
                        v[0][0] = '0';
                        assert( v[0] == "0bc" );

                        //s was not changed
                        assert( s == "abc" );
                    }
                }

                /*
                #pop_back

                    Remove last element from vector.

                    No return val. Rationale: <http://stackoverflow.com/questions/12600330/pop-back-return-value>
                */
                {
                    vector<int> v = { 0, 1 };
                    vector<int> v1;

                    v.pop_back();
                    v1 = { 0 };
                    assert( v == v1 );

                    v.pop_back();
                    v1 = {};
                    assert( v == v1 );
                }

                //#insert
                {
                    vector<int> v = {0,1};
                    vector<int> v1;

                    v.insert( v.begin(), -1 );
                    v1 = { -1, 0, 1 };
                    assert( v == v1 );

                    v.insert( v.end(), 2 );
                    v1 = { -1, 0, 1, 2 };
                    assert( v == v1 );
                }

                //#erase
                {
                    vector<int> v;
                    vector<int> v1;

                    v = { 0, 1, 2, 3 };
                    v.erase( v.begin() + 1, v.end() - 1 );
                    v1 = { 0, 3 };
                    assert( v == v1 );

                    v = { 0, 1, 2 };
                    v.erase( v.begin() + 1 );
                    v1 = { 0, 2 };
                    assert( v == v1 );
                }

                //#clear
                {
                    vector<int> v= { 0, 1, 2 };
                    v.clear();
                    assert( v.size() == 0 );
                }

                //ERROR no default operator `<<`
                    //cout v;
            }

            //random access is O(1) since array backed
            {

                vector<int> v = { 0, 1, 2 };

                //first element

                    assert( v.front() == 0 );
                    assert( v.front() == v[0] );

                //last element

                    assert( v.back() == 2 );

                //nth element:

                    v[0] = 1;
                    assert( v[0] == 1 );

                //BAD:
                //just like array overflow
                //will not change vector size,
                //and is unlikelly to give an error

                    //v1[2] = 2;
            }

            //iterate: vector has random access iterators
        }

        /*
        #set

            - unique elements: inserting twice does nothing

            - always ordered: $O(log)$ find / insert

            - immutable elements: it is not possible to modify an object,
                one must first remove it and resinsert.

                This is so because modification may mean reordering.
        */
        {
            //C++11 initializer list
            {
                {
                    set<int> s = { 1, 2, 0, 1 };
                    set<int> s1 = { 0, 1, 2 };
                    assert( s == s1 );
                }

                {
                    std::set<std::string> s = { "a", "c", "b", "a" };
                    std::set<std::string> s1 = { "a","b", "c" };
                    assert( s == s1 );
                }
            }

            //you can modify objects if you store pointers
            {
                int i = 0;
                set<int*> s;
                s.insert( &i );
                set<int*>::iterator it = s.find(&i);
                *(*it) = 1;
                assert( i == 1 );
            }

            /*
            insert

                Like for vector, insert makes copies.

                Return is a pair conatining:

                - if the item was not present, an iterator to the item inserted and true
                - if the item was     present, an iterator to the existing item inserted and false
            */
            {
                std::pair<set<int,std::string>::iterator,bool> ret;
                set<int> s;

                ret = s.insert(1);
                assert( ret.first == s.find(1) );
                assert( ret.second == true );

                ret = s.insert(2);
                assert( ret.first == s.find(2) );
                assert( ret.second == true );

                ret = s.insert(0);
                assert( ret.first == s.find(0) );
                assert( ret.second == true );

                //item already present:
                //nothing is done and returns false on the pair
                ret = s.insert(1);
                assert( ret.first == s.find(1) );
                assert( ret.second == false );

                set<int> s1 = { 0, 1, 2 };
                assert( s == s1 );
            }

            /*
            erase

                Remove element from set.

                Returns number of elements removed.
            */
            {
                set<int> s = { 0, 1, 2 };

                assert( s.erase(1) == 1 );
                set<int> s2 = { 0, 2 };
                assert( s == s2 );

                assert( s.erase(1) == 0 );
            }

            //ERROR no random access since it uses bidirection iterator
            {
                //cout << s[0] << endl;
            }

            //size
            {
                set<int> s;
                assert( s.size() == 0 );
                s.insert( 0 );
                assert( s.size() == 1 );
            }

            /*
            iterate

                Biderectional iterator.

                Always sorted.
            */

            /*
            find

                If found, returns an iterator pointing to the element.
                Else, returns `map::end()`

                find is `log n` time since the container is ordered.

                log n time complexity since always sorted
            */
            {
                set<int> s = { 0, 1, 2 };
                set<int>::iterator it;

                it = s.find( 1 );
                assert( *it == 1 );

                it = s.find( 3 );
                assert( it == s.end() );
            }

            /*
            count

                Count how many times an item is in the set.

                Can only return 1 or 0.

                Equivalent to doing a find.
            */
            {
                set<int> s = { 1, 2, 0, 1 };
                assert( s.count(1) == 1 );
                assert( s.count(3) == 0 );
            }
        }

        /*
        #tuple

            Hold a ordered collection of elements.

            Each element can be of a different type.

            The length is always fixed.
        */
        {
            //create
            {
                std::tuple<int,char,std::string> t0( 0, 'a', "a" );
                std::tuple<int,char,std::string> t1 = std::make_tuple( 0, 'a', "a" );
                std::tuple<int,char> t2 = std::pair<int,char>( 0, 'a' );
            }

            //get: read write access. Copies are made from input elements
            {
                std::string s = "abc";
                std::tuple<int,std::string> t0( 0, s );

                assert( std::get<0>(t0) == 0 );
                assert( std::get<1>(t0) == "abc" );

                std::get<0>(t0) = 1;
                assert( std::get<0>(t0) == 1 );

                std::get<1>(t0)[0] = '0';
                assert( std::get<1>(t0) == "0bc" );
                //s did not change
                assert( s == "abc" );
            }

            //relational
            {
                std::tuple<int,char> t0( 0, 'a' );
                std::tuple<int,char> t1( 0, 'a' );
                std::tuple<int,char> t2( 1, 'b' );

                assert( t0 == t1 );
                assert( t0 != t2 );
                assert( t0 < t2 );
            }

            //swap contents of two tuples of same type
            {
                std::tuple<int,char> t0( 0, 'a' );
                std::tuple<int,char> t1( 1, 'b' );

                std::tuple<int,char> old_t0 = t0;
                std::tuple<int,char> old_t1 = t1;

                t0.swap( t1 );

                assert( t0 == old_t1 );
                assert( t1 == old_t0 );
            }
        }

        /*
        #pair

            Two elements. Particular case of tuple.
            Methods which exist for tuple will not be discussed.

            Specially important because of unordered_map.

            Also consider the more general tuple.
        */
        {
            //access: can also be done via `.first` and `.second` in addition to `get`.
            {
                std::pair<int,char> p( 0, 'a' );
                assert( std::get<0>(p) == p.first );
                assert( std::get<1>(p) == p.second );
            }
        }

        /*
        #hashmap

            See map.

            Nonstandard `hash_map` already provided with gcc and msvc++.
            It is placed in the `std::` namespace, but it is *not* ISO.

        #map

            <http://www.cplusplus.com/reference/map/map/>

            Also comes in an unordered version `unordered_map`.

            Ordered.

            Also comes in an multiple value input version `multimap`.

            Keys must implement

        #unordered_map

            TODO complexity comparison to map.
        */
        {
            /*
            emplace

                put a value pair into the map without creating the pair explicitly

                needs gcc 4.8: <http://stackoverflow.com/questions/15812276/stdset-has-no-member-emplace>
            */
            {
                //std::map<int,std::string> m;
                //m.emplace( 0, "zero" );
                //m.emplace( 1, "one" );
                //m.emplace( 2, "two" );
            }

            /*
            insert

                Insert pair into map.

                The return value is similar to that of a set insertion with respec to the key.
            */
            {
                std::map<int,std::string> m;
                std::pair<map<int,std::string>::iterator,bool> ret;

                ret = m.insert( std::pair<int,std::string>( 0, "zero" ) );
                assert( ret.first == m.find(0) );
                assert( ret.second == true );

                ret = m.insert( std::pair<int,std::string>( 1, "one" ) );
                assert( ret.first == m.find(1) );
                assert( ret.second == true );

                //key already present
                ret = m.insert( std::pair<int,std::string>( 1, "one2" ) );
                assert( m[1] == "one" );
                assert( ret.first == m.find(1) );
                assert( ret.second == false );
            }

            /*
            iterate

                maps are iterated in key order

                iteration returns key value pairs
            */
            {
                std::map<int,std::string> m;
                m.insert( std::pair<int,std::string>( 1, "one" ) );
                m.insert( std::pair<int,std::string>( 0, "zero" ) );

                int i = 0;
                int is[] = { 0, 1 };
                for ( auto& im : m )
                {
                    assert( im.first == is[i] );
                    //cout << im->second << endl;
                    ++i;
                }
            }

            /*
            [] operator

                get value from a given key

                WARNING: if the key does not exist, it is inserted with a value with default constructor.

                This can be avoided by using `find` instead of `[]`.
            */
            {
                std::map<int,std::string> m;
                m.insert( std::pair<int,std::string>( 0, "zero" ) );
                m.insert( std::pair<int,std::string>( 1, "one" ) );

                assert( m[0] == "zero" );
                assert( m[1] == "one" );

                //inserts `(3,"")` because `""` is the value for the default string constructor
                assert( m[2] == "" );
                assert( m.size() == 3 );
            }

            /*
            find

                Similar to `std::set` find with respect to the keys:
                returns an iterator pointing to the pair which has given key, not the value.

                If not found, returns `map::end()`

                This is perferrable to `[]` since it does not insert non existing elements.
            */
            {
                std::map<int,std::string> m;
                m.insert( std::pair<int,std::string>( 0, "zero" ) );
                m.insert( std::pair<int,std::string>( 1, "one" ) );

                assert( m.find(0)->second == "zero" );
                assert( m.find(1)->second == "one" );

                assert( m.find(2) == m.end() );
                assert( m.size() == 2 );
            }

            /*
            erase

                Remove element from map.

                Returns number of elements removed.
            */
            {
                int ret;

                std::map<int,std::string> m;
                m.insert( std::pair<int,std::string>( 0, "zero" ) );
                m.insert( std::pair<int,std::string>( 1, "one" ) );

                std::map<int,std::string> m2;
                m2.insert( std::pair<int,std::string>( 0, "zero" ) );

                ret = m.erase( 1 );
                assert( ret = 1 );

                assert( m == m2 );

                ret = m.erase( 1 );
                assert( ret == 0 );
            }
        }

        /*
        #iterator

            Iteration could be done with random access in certain data structures with a for i loop.

            But still use iterators:

            - if you ever want to change to a container that
                has slow random access it will be a breeze

            - with iterators you don't need to know total container size

            - iterators may allow you not to keep the whole sequence in
               memory, but calculate it on the fly

            #iterator classes

                Iterators are categorized into classes depending on the operations they can do:

                    <http://www.cplusplus.com/reference/iterator/>

                The clases are (from least to most versatile):

                - Input Output
                - Forward
                - Bidirectional
                - Random Access

                The most versatile iterators (random access) behave much like pointers,
                and overload most pointer operations such as integer increment `it + 1` and
                pointer dereference `*it` in a similar way to pointers.

                Those classes are not language enforced via inheritance like in Java,
                but could be used by programmers to implement typedefs that explain
                the types of operations permitted. So if you are going to use a typedef
                solution not to tie yourself to a given container, consider naming the
                typdefed as one of the classes to indicate the operationt can do:

                    typedef random_it vector<int>::iterator;
        */
        {

            /*
            #foreach

                See range based for.

            #range based for for iterators

                C++11

                Like python foreach or Java improved-for loop.

                This is the best way to iterate a container with C++11.

                Much easier to write or read.

                Also have the advantage that you don't need to specify iterator type!

                Behind the scenes, this method is still based on iterators,
                and the class to be iterated needs to implement:

                - begin()
                - end()

                And the iterator returned must implement:

                - operator++()
                - operator!=()
                - operator*()
            */
            {
                vector<int> v = { 1, 2, 0 };
                int i;
                int is[] = { 1, 2, 0 };

#if __cplusplus >= 201103L
                //forward
                {
                    i = 0;
                    for ( auto& iv : v )
                    {
                        assert( iv == is[i] );
                        //cout << *it << endl;
                        i++;
                    }
                }
#endif

                /*
                backwards

                    TODO possible? Seems not out of the C++11 box: <http://stackoverflow.com/questions/8542591/c11-reverse-range-based-for-loop>

                    Best workaround with auto.
                */
                {
                    vector<int> v = { 1, 2, 0 };
                    int i;
                    int is[] = { 1, 2, 0 };

                    //forward
                    {
                        i = 2;
                        for ( auto it = v.rbegin(); it != v.rend(); it++ )
                        {
                            assert( *it == is[i] );
                            //cout << *it << endl;
                            i--;
                        }
                    }
                }
            }
            /*
            basic usage before C++11
            */
            {
                /*
                #forward iteration

                    Can be done on all containers.

                    #begin

                        Returns an iterator to the first element.

                    #end

                        Returns an iterator to the first element *after* the last.
                */
                {
                    vector<int>::iterator it;
                    vector<int> v = { 1, 2, 0 };
                    int i;
                    int is[] = { 1, 2, 0 };

                    i = 0;
                    for (
                        it = v.begin();
                        it != v.end();
                        ++it
                    )
                    {
                        assert( *it == is[i] );
                        //cout << *it << endl;
                        ++i;
                    }
                }

                /*
                #backwards iteration

                    Can only be done on biderectional containers.

                    #rbegin

                        Reversed begin.

                        Returns a `reverse_iterator` that points to the last emlement.

                        ++ on reversed iterators decreases them.

                    #rend

                        Returns a reversed iterator to the element before the first.
                */
                {
                    vector<int>::reverse_iterator it;
                    vector<int> v = { 1, 2, 0 };
                    int i;
                    int is[] = { 1, 2, 0 };

                    i = 2;
                    for (
                        it = v.rbegin();
                        it != v.rend();
                        ++it
                    )
                    {
                        assert( *it == is[i] );
                        //cout << *it << endl;
                        --i;
                    }
                }
            }

            /*
            #generic containers

                There is no standard iterator independent from container.

                This can be done via type erasure techinques.

                But would mean loss of performance because of lots of polymorphic calls
                and STL is obssessed with performance.

                The best solution seems to use typedefs:

                    typedef it_t vector<int>::iterator;

                And then if ever your container changes all you have to do is modify one single typedef:

                    typedef it_t set<int>::iterator;

                TODO isnt auto and range based for a better solution in c++11?
            */
            {
                vector<int> v = { 1, 2 };
                set<int> s = { 1, 2 };
                vector<int>::iterator itVec = v.begin();
                set<int>::iterator itSeti = s.begin();

                //DOES NOT EXIST:
                    //iterator<int> itVec = v.begin();
                    //iterator<int> itSeti = s.begin();

                //best workaround with auto:

                    auto vit = v.begin();
                    auto sit = v.begin();
            }

            //no born checking is not done
            {
                vector<int> v = { 1, 2 };

                *( v.end() - 1 );
                    //last element

                *( v.end() );
                    //after last element
                    //no born check

                //( v.end().hasNext() );
                    //no such method
            }
        }

        //#algorithm
        {
            {
                assert( min( 0.1, 0.2 ) == 0.1 );
                assert( max( 0.1, 0.2 ) == 0.2 );
            }

            //change order
            {
                //#sort
                {
                    vector<int> v = {2,0,1};
                    sort( v.begin(), v.end() );
                    vector<int> v1 = {0,1,2};
                    assert( v == v1 );
                }

                //#reverse
                {
                    vector<int> v = {2,0,1};
                    reverse( v.begin(), v.end() );
                    vector<int> v1 = {1,0,2};
                    assert( v == v1 );
                }

                //#randomize
                {
                    vector<int> v = {2,0,1};
                    random_shuffle( v.begin(), v.end() );
                }
            }

            /*
            #find

                return iterator to found element
            */
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

            /*
            #binary_search

                Container must be already sorted.

                log complexity
            */
            {

                vector<int> v = {2,0,1};
                sort( v.begin(), v.end() );
                assert( binary_search( v.begin(), v.end(), 1 ) == true );
                assert( binary_search( v.begin(), v.end(), 3 ) == false );
                assert( binary_search( v.begin(), v.end() - 1, 2 ) == false );
            }

            //#count
            {
                vector<int> v = {2,1,2};
                assert( count( v.begin(), v.end(), 0 ) == 0 );
                assert( count( v.begin(), v.end(), 1 ) == 1 );
                assert( count( v.begin(), v.end(), 2 ) == 2 );
            }


            //#max_element #min_element
            {
                vector<int> v = {2,0,1};
                assert( *max_element( v.begin(), v.end() ) == 2 );
                assert( *min_element( v.begin(), v.end() ) == 0 );
            }

            /*
            #heap

                <http://en.wikipedia.org/wiki/Heap_%28data_structure%29>

                In short:

                - getting largest element is O(1)
                - removing the largest element is O(lg) for all implementation
                - other operations (insertion) may be O(1) or O(lg) depending on the implementation

                this makes for a good priority queue.

                There is no heap data structure in C++: only heap operations over random access data structures.
                This is why this is under algoritms.

                Why random access structure works: <https://github.com/cirosantilli/comp-sci/blob/1.0/src/heap.md#array-implementation>

                Type not guaranteed: it seems that most implementations use binary heaps.

                For specific heaps such as Fibonacci, consider [Boost](http://www.boost.org/doc/libs/1_49_0/doc/html/heap.html).

                <http://stackoverflow.com/questions/14118367/stl-for-fibonacci-heap>
            */
            {
                int myints[] = { 10, 20, 30, 5, 15 };
                std::vector<int> v( myints, myints + 5 );

                /*
                #make_heap

                    Make random access data structure into a heap.

                    This changes the element order so that the range has heap properties

                    Worst case time: $O(n)$.
                */
                    std::make_heap( v.begin(), v.end() );
                    assert( v.front() == 30 );

                /*
                #pop_heap

                    Remove the largest element from the heap.

                    That element is moved to the end of the data structure, but since the
                    heap should have its length reduced by one, that element will then be out of the heap.

                    Assumes that the input range is already a heap (made with `make_heap` for example).
                */
                    std::pop_heap( v.begin(), v.end() );

                    //the element still exists on the data structure
                    assert( v.back() == 30 );

                    //the second largest element hat become the largets
                    assert( v.front() == 20 );

                    //remove the element from the data structure definitively
                    v.pop_back();

                /*
                #push_heap

                    Insert element into a heap.

                    Assumes that:

                    - the range 0 - ( end - 1 ) was already a heap
                    - the new element to be inserted into that heap is at end.
                */

                    //add the new element to the data structure
                    v.push_back( 99 );

                    //reorganize the data so that the last element will be placed in the heap
                    std::push_heap( v.begin(), v.end() );

                    assert( v.front() == 99 );

                /*
                #sort_heap

                    Assumes that the input range is a heap, and sorts it in increasing order.

                    The assumption that we have a heap allows for $O(ln)$ sorting,
                    much faster than the optimal bound $O(n log n)$.

                    This is exactly what the heapsort alrotithm does: make_heap and then sort_heap.
                */

                    std::sort_heap( v.begin(), v.end() );
                    //assert( v )
                    //v == 5 10 15 20 99
            }
        }

        //#memory
        {

#if __cplusplus >= 201103L

            /*
            #shared_ptr

                Introuced in C++11.

                Before that as part of boost.
            */
            {
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

#endif
        }

#if __cplusplus >= 201103L

        /*
        #thread

            c++11

            needs `-pthread` flag on g++ linux
        */
        {

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

#endif

    /*
    #standard preprocessor defines
    */
    {
        /*
        #__cplusplus

            Defined only if using C++ compiler.

            Its value is the actual C++ version in use in a similar way to __STDC_VERSION__

            Values:

            - C98: 199711L
            - C11: 201103L
        */
        {
#ifdef __cplusplus
        printf( "__cplusplus = %li\n", __cplusplus );
#endif
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
