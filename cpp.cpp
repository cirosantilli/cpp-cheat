/*
C++ cheatsheat.

Features which are identical to C will not be described.
*/

/*
# Headers

    C++ stdlib headers that are not C stdlib headers don't have the `.h` extension,
    and therefore are not included with the `.h` extension.

    Pre-standardized versions of C++ by Stroustrup used the `.h` extension, for example `iostream.h`,
    but this has been deprecated: <http://stackoverflow.com/questions/214230/iostream-vs-iostream-h-vs-iostream-h>
    It may still exits on certain systems, but never rely on it.

    When writting new libs, you can use either `.h` or `.hpp` as extensions,
    where `.hpp` indicates that the header is C++ specific, and not pure C.

    # C headers

        The standard C++ library provides a `cNAME` version to every `NAME.h` for every C header.
        E.g.: `math.h` vs `cmath`.

        The difference is the following:

        -   cX puts things in std:: namespace. *always* use the CNAME version on new code,
            since this reduces the probability of a name conflicts, and is the standard c++ way of doing things.

            Macro expansion happens *before* namespaces are even compiled,
            so you still refer to macros like `EXIT_SUCCESS` and `assert` as in C,
            and *not* as `std::EXIT_SUCCESS`.

        -  `X.h` puts *all* in the global namespace, it is exactly the same as the c headers.
            *never* use it in new code.

            Those headers exist only for backwards compatibility.

        Avoid using C headers and functionality altogether if that functionality has an equivalent C++ version,
        since the C++ version will play more nicely with new language features and libraries.

# Linux specifics

    The main c++ lib on linux is the GNU Standard C++ Library.

    Shared object name: `libstdc++.so`.

    Website: <http://gcc.gnu.org/libstdc++/>

    Get source code: seems to be on the same tree as gcc?

        git clone git://gcc.gnu.org/git/gcc.git

    -   the so is usually located at

            /usr/lib/i386-linux-gnu/libstdc++.so.X

        If it is not there then

            locate libstdc++

    -   std headers are usually located at

            /usr/include/c++/4.X/`.

        If not, try:

            locate /iostream

    -   the Ubuntu package is called `libstdc++6.X`. `dpkg -l | grep libstd`

    With `g++` the C++ standard library is linked against automatically.
    This does not happen when compiling with `gcc`, and is one of the many reasons why you should use `g++`
    whenever compiling C++ instead of `gcc`.
*/

#include <array>            // array
#include <algorithm>        // copy, erase, lower_bound, remove_if, swap, transform
#include <chrono>           // nanoseconds
#include <exception>        // bad_alloc, bad_cast, bad_exception, bad_typeid, exception, ios_base::failure
#include <fstream>          // fstream, ifstream, ofstream
#include <functional>       // bind2nd
#include <iostream>         // cout, endl
#include <iterator>         // advance, input_iterator_tag, iterator, iterator_traits, next
#include <list>             // forward_list, list
#include <limits>           //
#include <map>              // map, multimap
#include <memory>           // shared_ptr
#include <mutex>            //
#include <new>              //
#include <numeric>          // partial sums, differences on std::vectors of numbers
#include <regex>            //
#include <set>              // multiset, set
#include <string>           // getline, string
#include <sstream>          // stringstream
#include <thread>           //
#include <typeinfo>         // typeid, bad_typeid, bad_typecast
#include <typeindex>        // type_index
#include <tuple>            // tuple
#include <unordered_map>    // unordered_map, unordered_multimap
#include <utility>          // forward, get, pair, size_t, type_info
#include <vector>
#include <valarray>

// C headers.
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cstring>

// Keeps a list of functions that called it for testing purposes.
static std::vector<std::string> callStack;
void printCallStack() {
    std::cout << "callStack:" << std::endl;
    for (auto& s : callStack)
        std::cout << s << std::endl;
    std::cout << "END callStack" << std::endl;
}

// Exception

    void exception_func_int() {
        throw 1;
    }

    class myexception: public std::exception {
        virtual const char* what() const throw() {
            return "myexception::what()";
        }
    };

    // Exception specifications

            // All exceptions are catchable (default):
            void exception_func_all() { throw 0; }

            // Only int exceptions are catchable
            void exception_func_int_only(bool throw_int) throw (int) {
                if (throw_int)
                    throw 1;
                else
                    throw 'c';
            }

            // Only int and exception or derived excpetions are catchable:
            void exception_func_int_exception_only(int which) throw (int, std::exception) {
                switch (which) {
                    case 0: throw 0; break;
                    case 1: throw myexception(); break;
                    default: throw 'c'; break;
                }
            }

            // No exceptions are catchable
            void exception_func_none() throw() {throw 1;}

            void exception_func_none_wrapper() {
                exception_func_none();
            }

    /**
    The destructor of this class throws an exception!!!
    */
    class ExceptionDestructor {
        public:
            ~ExceptionDestructor() { throw std::exception(); }
    };

    void ExceptionDestructorCaller() {
        ExceptionDestructor e;
    }

// #class
//{
    class Empty {};

    /**
    This class has a compiler supplied default constructor.
    */
    class ImplicitDefaultCtor {
        public:
            int i;
            std::string s;
    };

    /**
    This class has no default constructor since another constructor was defined.
    */
    class NoDefaultCtor {
        public:
            NoDefaultCtor(int i) : i(i) {}
            int i;
    };

    /**
    This class defines a default constructor since it will also provide a non default one.
    */
    class ExplicitDefaultCtor {
        public:
            int i;
            ExplicitDefaultCtor(){}
            ExplicitDefaultCtor(int i) : i(i){}
    };

    /**
    This class uses its default copy constructor and assign operator.
    */
    class DefaultCopyAssignCtor {
        public:
            int i;
            DefaultCopyAssignCtor() : i(0) {}
            DefaultCopyAssignCtor(int i) : i(i) {}
    };

    /**
    This politically incorrect clas does not implement the equality == operator.
    */
    class NoEquality {
        public:
            NoEquality() : i(0) {}
            int i;
    };

#if __cplusplus >= 201103L
    class CtorFromCtor {

        public:

            std::vector<int> v;

            /**
            This constructor does the default which is calling the parent's default constrctor before its own.

            An error would be generated if the parent class has no defalt constructor.
            */
            CtorFromCtor(int i) : v(1,i) {}

            /**
            This constructor calls another constructor with arguments before running its own.
            */
            CtorFromCtor(int i, int j) : CtorFromCtor(i) {
                v.push_back(j);
            }
    };
#endif

    /**
    Simple class for tests on constructor destructor order.

    This class has no members which are objects and no base classes.
    */
    class NoBaseNoMember {
        public:

            int i;

            /// Default constructor
            NoBaseNoMember() : i(0) {
                callStack.push_back("NoBaseNoMember::NoBaseNoMember()");
            }

            /// Copy constructor
            NoBaseNoMember(const NoBaseNoMember& other) : i(other.i) {
                callStack.push_back("NoBaseNoMember::NoBaseNoMember(NoBaseNoMember)");
            }

            NoBaseNoMember(int i) : i(i) {callStack.push_back("NoBaseNoMember::NoBaseNoMember(int)");}

            /// Assign
            NoBaseNoMember& operator= (const NoBaseNoMember& rhs) {
                this->i = rhs.i;
                callStack.push_back("NoBaseNoMember::operator=");
                return *this;
            }

            /// Destructor
            ~NoBaseNoMember(){callStack.push_back("NoBaseNoMember::~NoBaseNoMember()");}

            void method(){callStack.push_back("NoBaseNoMember::method()");}

            static NoBaseNoMember create() {
                return NoBaseNoMember();
            }

            static NoBaseNoMember createNrvo() {
                NoBaseNoMember c;
                return c;
            }

            /// It would be hard or impossible to do RVO for this function.
            static NoBaseNoMember createNrvoHard(bool b = false) {
                //2 int constructors
                NoBaseNoMember cf = NoBaseNoMember(0);
                NoBaseNoMember ct = NoBaseNoMember(1);
                return b ? ct : cf;
                //2 int destructors
            }

            static void temporaryReference(NoBaseNoMember& temp) {
                temp.i = 0;
            }

            static void temporaryReferenceConst(const NoBaseNoMember& temp) {}
    };

    class ExplicitCtor {
        public:
            int i;
            explicit ExplicitCtor(int i) : i(i) {}

            explicit ExplicitCtor(int i, int j) : i(i + j) {}
                // TODO this makes no sense right, since it is not a ctor that takes a single arg?
                // why does it compile without warning

            // ERROR: only for constructors.
            //explicit void method(){}
    };

    class NoBaseNoMember0 {
        public:
            NoBaseNoMember0(){callStack.push_back("NoBaseNoMember0::NoBaseNoMember0()");}
            ~NoBaseNoMember0(){callStack.push_back("NoBaseNoMember0::~NoBaseNoMember0()");}
            void method(){callStack.push_back("NoBaseNoMember0::method()");}
    };

    class NoBaseNoMember1 {
        public:
            NoBaseNoMember1(){callStack.push_back("NoBaseNoMember1::NoBaseNoMember1()");}
            ~NoBaseNoMember1(){callStack.push_back("NoBaseNoMember1::~NoBaseNoMember1()");}
            void method(){callStack.push_back("NoBaseNoMember1::method()");}
    };


#if __cplusplus >= 201103L

    /**
    This class exemplifies the `= default` syntax.
    */
    class DefaultKeyword {
        public:

            /**
            This is an explicitly defaulted constructor.
            */
            DefaultKeyword() = default;

            /**
            This is an explicitly defaulted copy constructor.
            */
            DefaultKeyword(const DefaultKeyword&) = default;

            /**
            This is an explicitly defaulted assignment operator.
            */
            DefaultKeyword & operator=(const DefaultKeyword&) = default;

            ~DefaultKeyword() = default;

            // ERROR: Not possible because the default constructor must take no arguments.
            //DefaultKeyword(int i) = default;

            // With the default keyword it is possible to have other
            // constructors besides the Implicitly defined constructor.
            DefaultKeyword(int i, std::string s) : i(i), s(s) {}


            /**
            ERROR: Cannot default anything other than:

            - constructors
            - destructors
            - copy
            - assignment
            */
            //void f() = default;

            int i;
            std::string s;
    };

    /**
    This class exemplifies the `= delete` syntax.
    */
    class DeleteKeyword {
        public:
            DeleteKeyword() = delete;
            DeleteKeyword(int i) : i(i) {}
            DeleteKeyword(const DeleteKeyword&) = delete;
            DeleteKeyword & operator=(const DeleteKeyword&) = delete;

            /**
            With this, the code would compile, but it would not be possible
            to create any instances of this class, since at some point the destructor
            would have to be called!
            */
            //~DeleteKeyword() = delete;

            /* It is possible to delete any function. */
            void f() = delete;
            int i;
    };

#endif

    /**
    This class has an implicit default constructor.
    */
    class UniformInitializationImplicitCtor {
        public:
            int i;
            int j;
    };

    /**
    This class has an explicit default constructor,
    and no constructor that takes 2 ints.
    */
    class UniformInitializationExplicitCtor {
        public:
            int i;
            int j;
            UniformInitializationExplicitCtor() : i(0), j(0) {}
    };

    /**
    This class has a constructor that takes 2 ints.
    */
    class UniformInitializationCtor2 {
        public:
            int i;
            int j;
            UniformInitializationCtor2(int i, int j) : i(i), j(j+1) {}
            bool operator==(const UniformInitializationCtor2& other) {return this->i == other.i && this->j == other.j;}
    };

    int UniformInitializationCtor2Func(UniformInitializationCtor2 o){
        return o.i + o.j;
    }

    class UniformInitializationList {
        public:
            int i;
            int j;
            UniformInitializationList(int i, int j) : i(i), j(j+1) {}
            UniformInitializationList(std::initializer_list<int> list){
                i = *(list.begin());
                j = *(list.begin() + 1);
            }
    };

#if __cplusplus >= 201103L

    /**
    This class has an `Initializer_list` constructor.
    */
    class InitializerListCtor {
        public:

            std::vector<int> v;

            InitializerListCtor(std::initializer_list<int> list) {
                for (auto& i : list)
                    v.push_back(i);
            }

            InitializerListCtor(int before, std::initializer_list<int> list, int after) {
                v.push_back(before + 1);
                for (auto& i : list)
                    v.push_back(i);
                v.push_back(after - 1);
            }
    };

#endif

    class MemberConstructorTest {
        public:
            NoBaseNoMember0 member0;
            NoBaseNoMember1 member1;
            MemberConstructorTest(){callStack.push_back("MemberConstructorTest::MemberConstructorTest()");}
            ~MemberConstructorTest(){callStack.push_back("MemberConstructorTest::~MemberConstructorTest()");}
            void method(){callStack.push_back("MemberConstructorTest::method()");}
    };

    class Member {
        public:
            Member(){callStack.push_back("Member::Member()");}
            Member(int i){callStack.push_back("Member::Member(int)");}
            ~Member(){callStack.push_back("Member::~Member()");}

            void method() {callStack.push_back("Member::method()");}

            int i;
    };

    class Nested {
        public:
            Nested() { callStack.push_back("Nested::Nested()"); }
    };

    /*
    # this

        Magic value that points to the current object.

        It is implemented by the compiler by passing `this` as the first argument
        of every non-static function of the class.

        This is noticeable when doing operator overload:
    */

    class Base {
        public:

            /// Best to put typedefs on top of class so def will go for entire class.
            typedef int NESTED_INT;

            Base() : i(0), j(1) {
                callStack.push_back("Base::Base()");

                // BAD: same as list init, except if i is an object
                // to keep uniform style, always use list init
                //this->i=0;
                //this->j=1;

                // ERROR: ic is const. must be initialized in list initialization.
                //ic=0;

                // BAD: compiles but infinite loop!
                //Base b;
            }
            /*
            # Initialization list

                Initialization lists have 4 main uses:

                1) avoid calling member object constructor and copy separately
                2) initializing base classes with non default constructors
                3) initializing const elements
                4) initializing member references &

            # Delegating constructors

                C++11 also makes it possible to call a different constructor of the current
                class on the initialization list. This feature is called delegating constructors.
            */

            Base(int i, int j) : i(i), j(j) {
                callStack.push_back("Base::Base(int, int)");
            }

            // ERROR: constructor cannot be virtual:

                //virtual Base(float f){}


#if __cplusplus >= 201103L

            /// C++11 initialize array/std containers in list initializtion.
            Base(float f) : i(0), fs4{f,f,f,f}, vi{0,1,2,3} {
                callStack.push_back("Base::Base(float)");
            }
#endif

            virtual ~Base() {
                callStack.push_back("Base::~Base()");
            }

            void method() {
                callStack.push_back("Base::method()");
                int i = iAmbiguous;
                i = iStatic;
                i = iConstStatic;
            }

            void constMethod() const;
            void constMethod(int *&) const;

            //return references

                int& getRefIPublic() {return this->iPublic;}

                /// Value cannot be changed.
                const int& getPrivateConstRef() const {return this->iPrivate;}

                /// Value can be changed
                int& getPrivateRef() {return this->iPrivate;}

                // ERROR: const method cannot return noncosnt reference!
                //int& getPrivateRef() const {return this->iPrivate;}

                // ERROR: const method cannot return noncosnt pointer!
                //int* getPrivateAddress() const {return &this->iPrivate;}

                const int* getPrivateAddressConst() const {return &this->iPrivate;}

            void methodAmbiguous(){callStack.push_back("Base::methodAmbiguous()");}

            // virtual: decides on runtime based on object type
            // http://stackoverflow.com/questions/2391679/can-someone-explain-c-virtual-methods
            virtual void virtualMethod(){callStack.push_back("Base::virtualMethod()");}

            virtual Base* covariantReturn() {
                callStack.push_back("Base:covariantReturn()");
                return new Base;
            }

            virtual void covariantArg(Base* b) {
                callStack.push_back("Base:covariantArg()");
            }

            int i, j;

            // ERROR: cannot initialize here.
            //int initialized_outside_ctor = 0;

            int iPublic;
            int iAmbiguous;

            int* is;

            float fs4[4];
            std::vector<int> vi;

            mutable int mutableI;
            // ERROR: statics can be changed in const functions by default.
            //static mutable int staticMutableI;

            /*
            BAD every class must have an assigment operator.
            But then, assigment does something like this->ic = other->ic
            You could redefine the assigment, but still in your new definition ic cannot be changed.
            <http://stackoverflow.com/questions/634662/non-static-const-member-cant-use-default-assignment-operator>
            */

            // # static

                static void staticMethod();

                // ERROR: static cannot be const.
                //static void staticMethod() const;

                static int iStatic;

                // Concflicts with static int.
                //int iStatic;

                // OK: because const static integral type
                const static int iConstStatic = 0;

            /*
            # member initialization outside of constructor
            */

                const int iConstInit = 0;

                // ERROR: cannot initialize here unless const.
                //static int iStatic = 0;

                // ERROR: non-integral type.
                //const static float fConstStatic = 0.0;

                const static Member member;
                // OK: why ok?

                const static Member member2;
                    //default constructor works

                //const static NoBaseNoMember(1);
                    /*
                    ERROR: non integral type must be init outside.

                    why integral types are an exception:
                    <http://stackoverflow.com/questions/13697265/static-const-double-cannot-have-an-in-class-initializer-why-is-it-so>
                    */

            class Nested {
                public:

                    Nested() {
                        callStack.push_back("Base::Nested::Nested()");
                        int i = privateStaticInt;
                            //you have private access
                    }

                    Member m;
            };

            class Nested2 {
                public:

                    Nested2() {
                        callStack.push_back("Base::Nested2::Nested2()");
                    }

                    Nested innerIn;
                        //inner one

                    ::Nested innerOut;
                        //outter one
            };

        protected:

            int iProtected;
            void fProtected(){callStack.push_back("Base::fProtected()");}

        private:

            int iPrivate;
            void fPrivate(){callStack.push_back("Base::fPrivate()");}
            const static int privateStaticInt = 1;

            typedef int PRIVATE_NESTED_INT;

    };

    /*
    # friend

        Allow external functions and other classes to access private memebers of this class.

        Friendship is not automatically reflexive nor transitive.

        One case in which friendship may be unavoidable is for operator overload of operators which cannot
        be class members and must be implemented as external functions such as `operator<<`.
        This happens because of the nature of operators, which may force them to be implemented outside the class.

        <http://www.cplusplus.com/doc/tutorial/inheritance/>

    # friend and templates

        Things get complicated when friends and template classes interact:

        <http://publib.boulder.ibm.com/infocenter/lnxpcomp/v8v101/index.jsp?topic=%2Fcom.ibm.xlcpp8l.doc%2Flanguage%2Fref%2Ffriends_and_templates.htm>
    */

        class FriendOfFriend;

        class Friend {

            public:

                friend class FriendOfFriend;

                Friend(int i) : i(i) {}
                int getI(){return this->i;}

                //this declaration says that `friendGetIPrivate(Base)` is a friend of this class.
                //It will be defined outside the class.
                friend int friendGetI(Friend f);

                /* The same as friendGetI, but also defined inside the class. */
                friend int friendGetIInnerDefine(Friend f) {

                    // ERROR: it is as if this were a friend external function, so there is no `this`.
                    //return this->i;

                    return f.i;
                }

                int getFriendI(FriendOfFriend f);

            private:

                int i;
                void privateMethod(){};
        };

        /* cannot use the word friend here */
        int friendGetI(Friend f){

            // ERROR: this is a non-member function, so no `this`.
            //return this->i;

            return f.i;
        }

        class FriendOfFriend {

            public:

                FriendOfFriend(int i) : i(i) {}
                int getFriendI(Friend f){return f.i;}
                void callFriendPrivateMethod(Friend f){f.privateMethod();}

            private:

                int i;
        };

        // ERROR: friend used outside class.
        //friend int friendGetI(Friend f){return f.i;}

        // ERROR: not a friend because reflexivity is not automatic.
        //int Friend::getFriendI(FriendOfFriend f) {return f.i;}

    /*
    # const method

        Methods that cannot change the data of their object.

        Inner workings: the hidden *this* pointer is downgraded to `const X*` when passing it to the function:

            void method() const

        becomes:

            void method(const Class* this) const

        instead of:

            void method(Class* this) const
    */
    void Base::constMethod() const {
        // ERROR: cant assign member in const func.
        //this->i = 2;

        // ERROR: cant call non const method inside const method!
        // as that method could change the object
        //this->member.method();

        // ERROR: cant assign member of a member in const method.
        //this->member.i = 1;

        /*
        # mutable

            OK

            Mutable allows you to change it even in a const method.

            Application to multithreading:
            <http://stackoverflow.com/questions/105014/does-the-mutable-keyword-have-any-purpose-other-than-allowing-the-variable-to>
        */
        this->mutableI = 1;

        // Static changes can still be done.
        this->iStatic = 1;

        callStack.push_back("Base::constMethod()");

        {
            // ERROR: conversion from const Base* to Base*.
            //Base* this2 = this;

            const Base* this2const = this;
        }
    }

    // ERROR must not ommit the const here either.
    //void Base::constMethod () {}

    /*
    Cannot return a non const pointer from a const method, since this is const,
    so all members are also const.
    */
    void Base::constMethod(int *& ip) const {
        // ERROR: invalid conversion.
        //ip = &this->iPrivate;
    }

    int Base::iStatic = 0;

    void Base::staticMethod() {
        callStack.push_back("Base::staticMethod()");

        // ERROR: no this!
        //int i = this->i;

        // OK: ok to use static vars
        int i = iStatic;
    }

    // ERROR: static linkage, like in C static.
    // meaning func only visible from current translational unit
    //static void staticMethod()

    // Must come outside
    const Member Base::member2 = Member(1);

    // ERROR: must be declared inside.
    //int Base::k;

    // # virtual

        class BaseAbstract {

            public:

                // Can be called in derived classes init list.
                BaseAbstract(){}

                virtual ~BaseAbstract() {}
                void method() { callStack.push_back("BaseAbstract::method()"); }
                void methodAmbiguous() {callStack.push_back("BaseAbstract::methodAmbiguous()"); }
                virtual void virtualMethod() { callStack.push_back("BaseAbstract::virtualMethod()"); }
                virtual void pureVirtual() = 0;

                // BAD: won't work: must implement on derived class only.
                //virtual void pureVirtualImplementedOtherBase() = 0;

                int i;
                int iAmbiguous;

            private:

                // This can/must still be implemented on the base class, even if private!
                virtual void privatePureVirtual() = 0;

                // How private pure virtual can be useful.
                void usefulPrivatePureVirtual() {
                    callStack.push_back("common before");
                    privatePureVirtual();
                    callStack.push_back("common after");
                }
        };

        class PureVirtualImplementedOtherBase {
            public:
                void pureVirtual() {
                    callStack.push_back("PureVirtualImplementedOtherBase::pureVirtual()");
                }
            private:
                void privatePureVirtual() {
                    callStack.push_back("PureVirtualImplementedOtherBase::privatePureVirtual()");
                }
        };

        class DerivedAbtractAndImplementator : BaseAbstract, PureVirtualImplementedOtherBase {
            //public:
                //void pureVirtual()
                //{
                    //callStack.push_back("PureVirtualImplementedOtherBase::pureVirtual()");
                //}
            //private:
                //void privatePureVirtual()
                //{
                    //callStack.push_back("PureVirtualImplementedOtherBase::privatePureVirtual()");
                //}
        };

        class InheritOverloadBase {
            public:
                void overload(){}
                void not_overload(){}
        };

        class InheritOverloadDerived : public InheritOverloadBase {
            public:
                // `using` is required, or f(int) hides `f()`.
                using InheritOverloadBase::overload;
                void overload(int i) {
                    overload();
                    // This one does not reqire using becase it is not overloaded.
                    not_overload();
                }
        };

#if __cplusplus >= 201103L
        class InheritingCtorBase {
            public:
                int i;
                InheritingCtorBase() : i(0) {}
                InheritingCtorBase(int i) : i(i) {}
        };

        class InheritingCtorDerived : public InheritingCtorBase {
            public:
                // Will define InheritingCtorDerived(int) and the copy constructor.
                using InheritingCtorBase::InheritingCtorBase;
        };
#endif

        class VirtualFromCtorBase {
            public:
                int i;
                int j;
                VirtualFromCtorBase() {
                    // Calls base::a, not derived::a
                    this->i = a();
                    // LINKER ERROR: undefined reference to b().
                    //j = b();
                }
                virtual int a() { return 0; }
                virtual int b() = 0;
        };

        class VirtualFromCtorDerived : public VirtualFromCtorBase {
            public:
                virtual int a() { return 1; }
                virtual int b() { return 10; }
        };

        class VirtualFromCtor2PhaseBase {
            public:
                int i;
                int j;
                VirtualFromCtor2PhaseBase() {}
                void init() {
                    this->i = a();
                    this->j = b();
                }
                virtual int a() { return 0; }
                virtual int b() = 0;
        };

        class VirtualFromCtor2PhaseDerived : public VirtualFromCtor2PhaseBase {
            public:
                VirtualFromCtor2PhaseDerived() { init(); }
                virtual int a() { return 1; }
                virtual int b() { return 10; }
        };

        class MultipleInheritanceConflictBase1 {
            public:
                const static int is = 1;
                int i;
                void f(){}
        };

        class MultipleInheritanceConflictBase2 {
            public:
                const static int is = 2;
                int i;
                void f(){}
        };

        class MultipleInheritanceConflictDerived :
            MultipleInheritanceConflictBase1,
            MultipleInheritanceConflictBase2
            {};

    class BaseProtected {
        public:

            BaseProtected(){callStack.push_back("BaseProtected::BaseProtected()");}
            BaseProtected(int i){callStack.push_back("BaseProtected::BaseProtected(int)");}
            ~BaseProtected(){callStack.push_back("BaseProtected::~BaseProtected()");}
    };

    class BasePrivate {
        public:
            BasePrivate(){callStack.push_back("BasePrivate::BasePrivate()");}
            BasePrivate(int i){callStack.push_back("BasePrivate::BasePrivate(int)");}
            ~BasePrivate(){callStack.push_back("BasePrivate::~BasePrivate()");}
    };

    class Derived : private BasePrivate {};

    class Class :
        public Base,
        //public Base,      // ERROR: duplicate.
        //public Derived,   // WARN: cannot use BasePrivate inside: ambiguous.
        protected BaseProtected,
        private BasePrivate,
        public BaseAbstract
    {
        public:

            /*
            calls base constructors first
            */
            Class() : i(0), z(1) {
                callStack.push_back("Class::Class()");
            }

            Class(int i) : i(i), z(0) {
                callStack.push_back("Class::Class(int)");
            }

            /*
            calls specific base constructors  instead of default ones
            another application os initialization lists

            works even if the BaseAbstract class is abstract!
            this is the only place you can do that: init list of derived classes
            */
            Class(int i, int z) : Base(i,z), BaseProtected(i), BasePrivate(i), BaseAbstract(), i(i), z(z) {
                callStack.push_back("Class::Class(int, int)");
            }

            // WARN: BaseAbstract will be init after TODO ?
            //Class() : BaseAbstract(), Base(i,z), BaseProtected(i), BasePrivate(i), i(i), z(z)

            //try catch in case base constructor can throw exceptions
            Class(int i, int j, int z) try : Base(i,j), i(i), z(z) {
                callStack.push_back("Class::Class(int, int, int)");
            }
            catch(const std::exception &e) {
                throw e;
            }

            Class(Member m) : m(m) {
                //this->m = m;
                    //BAD: m constructor would be called, but this is useless since we have already called it!
                    //to construct it before.
                    //This is an application of initialization constructors.

                callStack.push_back("Class::Class(Member)");
            }

            /*
            Copy constructor.

                Classes already have this by default.

                Useful to customize if class does dynamic allocation!
            */

                Class(const Class& c) : i(c.i), z(c.z), m(c.m) {
                    callStack.push_back("Class::Class(Class)");
                }

                // Classes don't have constructors from base by default.
                Class(const Base& b) : Base(b) {
                    callStack.push_back("Class::Class(Base)");
                }

            /*
            Also calls Base destructor after
            */
            ~Class() { callStack.push_back("Class::~Class()"); }

            // Called method overwriding.
            void method() { callStack.push_back("Class::method()"); }

            // OK.
            template<class C=int>
            void methodTemplate() {
                callStack.push_back("Class::methodTemplate()");
            }

            // Different than overwriding non virtual methods. see polymorphism.
            void virtualMethod() { callStack.push_back("Class::virtualMethod()"); }

            // OK: only difference: if you have a pointer to this class,
            // you can only use virtual if this is declared virtual.
            //virtual void virtualMethod(){callStack.push_back("Class::virtualMethod()");}

            // Definition obligatory if you want to create objects of this class.
            void pureVirtual() { callStack.push_back("Class::pureVirtual()"); }

            // ERROR: unlike function overloading, polyomorphism is decided at runtime
            // and therefore return type must be the same as in declaration
            //int pureVirtual(){return 1;}

                // OK because Class is derived from Base
                // called "covariant return type".
                virtual Class* covariantReturn() {
                    callStack.push_back("Class:covariantReturn()");
                    return new Class;
                }

                    // ERROR: invalid covariant
                    //virtual Class invalidCovariantReturn(){return Class();}

                virtual void covariantArg(Class* c) {
                    callStack.push_back("Class:covariantArg()");
                }

            int i;
            int z;
            Member m;
            Nested nested;
            //Base nested class visible from here


        private:

            virtual void privatePureVirtual(){callStack.push_back("Class:privatePureVirtual()");};
    };

    //nested

        // OK: you can see the nested class from derived classes
        class NestedDerived : Class::Nested{};

    class Class2 : public Base {
        public:

            Class2(){}
            void pureVirtual(){callStack.push_back("Class2::pureVirtual()");}

            // OK: you can override the Nested class from the Base also
            class Nested{};
    };

    class ClassCast {
        ClassCast(Class c){}
    };

    // ERROR:
    //ClassDefault::ClassDefault(int i=0){}

    /*
    Illustrates the copy and swap idiom and related concepts like move contruction.
    */
    class CopyAndSwap {
        public:

            int *is;
            std::size_t n;

            CopyAndSwap(std::size_t n, int val) : n(n) {
                is = new int[n];
                for (std::size_t i = 0; i < n; ++i) {
                    is[i] = val;
                }
            }

            ~CopyAndSwap(){
                delete[] is;
            }

            CopyAndSwap& operator=(const CopyAndSwap& rhs) {
                delete[] is;
                is = new int[rhs.n];
                return *this;
            }

            CopyAndSwap(const CopyAndSwap& other) {
            }
    };

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
            class VisibleInnerIterable {
                public:

                    VisibleInnerIterable();

                    typedef std::vector<int> Iterable;

                    const Iterable& getIterable();

                private:

                    Iterable iterable;
            };

            VisibleInnerIterable::VisibleInnerIterable() : iterable{0,1,2} {}

            const VisibleInnerIterable::Iterable& VisibleInnerIterable::getIterable() {
                return iterable;
            }
        //}
    //}
//}

//struct

    template<class T>
    struct BaseStruct {
        T i;
        BaseStruct(T i) : i(i) {}

        protected:
            int iProtected;

        private:
            int iPrivate;
    };

    struct DerivedStruct : BaseStruct<int> {
        DerivedStruct(int i) : BaseStruct(i) {
            iProtected = i;
        }
    };


// #global scope

    int global = 0;

    // Differently from C, computations can be done to initialize globals.

        int global2 = global+1;
        int ret1() {
            callStack.push_back("before main!");
            return 1;
        }
        int global3 = ret1();

    // ERROR: arbitrary computations cannot be done however, only those that initialize a global

        //global = 1;
        //if (1){}
        //callStack.push_back("global");

//function

    //pass by reference

        //http://stackoverflow.com/questions/114180/pointer-vs-reference

        void byref(int& i) {i++;}
        void bypointer(int *i) {(*i)++;}

        void bypointerConst(const int*& ip, const int*& jp) {
            ip = jp;
        }

    //return reference from function

        int getInt() {return 0;}

        int getIntVar() {
            int i = 0;
            return i;
        }

        /*
        int& getIntRef() {
            int i = 0;
            return i;
        }
        */
        // WARN: reference to local var returned

        /*
        OK the returned i reference is not local
        */
        int& getIntRef(int& i) {
            i++;
            return i;
        }

        /*
        The returned i reference cannot be modified.
        */
        const int& getIntConstRef(int& i) {
            i++;
            return i;
        }

        std::string getString() {return "abc";}

    //default args. C++ only. creates several name mungled functions on the assembly code.

        int DefaultArgs(int i, int j=0)      { return i + j; }

        // ERROR: Cannot use one argument as the default for the other.
        //int DefaultArgs(float f, float f2=f) { return f + f2; }

    // ERROR: no compound literals in c++
    //void foo (int bar[] = (int[2]){0 ,1});

    //function overloading

        void overload(int i){callStack.push_back("overload(int)");}
        void overload(int i, int j){callStack.push_back("overload(int,int)");}
        void overload(float i){callStack.push_back("overload(float)");}
        void overload(float i, float j, float k=0.f){callStack.push_back("overload(float,float,float=)");}

        // OK even if return type is different all is decided at compile time.

            //int overload(int i, int j, int k){return 1;}

        // ERROR: conflict with int.

            //void overload(const int i){}

        // ERROR: cannot differentiate by output since output is used to decide if other parts of code make sense.

            //int overload(){return 0;}
            //float overload(){return 0.f;}

        // ERROR: conflict with int int

            //void overload(int i, int j=0){cout << "int int=";}

        // BAD: compiles, but is useless to give a default,
        // since when calling, caller is *forced* to give a value for j
        // or wil get `call is ambiguous` compile time error
        // because compiler cannot decide between
        // here the default arg can be usefull for a call of type float float.

            //void overload(float i, float j=1){cout << "float float=";}

        // TODO: why does this compile, that is, how not to make an ambiguous call with overload(int).

            void overloadValAddr(const int i){}
            void overloadValAddr(const int& i){}

        void overloadBase(Base b){}
        void overloadBase(BaseProtected b){}

#if __cplusplus >= 201103L

            /* pair of function overload based only on if argument is an rvalue or a lvalue */
            std::string overloadRLvalue(int& i) {
                return "lval";
            }

            std::string overloadRLvalue(int&& i) {
                return "rval";
            }

                /*
                ERROR: ambiguous with both of the above, because in C++:

                    int i = lvalue;

                Leads to copy construction (ambiguous with the `&` overload).

                    int i = rvalue;

                Leads to move construction (ambiguous with the `&&` overload).
                */
            /*
            std::string overloadRLvalue(int i) {
                return "val";
            }
            */
#endif

    //default args

        void defaultArgProto(int i=0);
        void defaultArgProto(int i){}

        // BAD: usually not what you want
        // since includers will not see the default version

            void defaultArgDef(int i);
            void defaultArgDef(int i=0){}

    // ERROR: default cannot go in declaration and definition

            //void defaultArgBoth(int i=0);
            //void defaultArgBoth(int i=0){}

    int def_no_argname(int){return 1;}
    int def_no_argname(int, int){return 2;}

    /*
    # auto arguments
    */

            /*ERROR: no you can't*/
        /*
        int func_auto(auto a){
            ++a;
            return (int)a;
        }
        */

    /*
    # operator overload

            Like regular functions, C++ also allows operators to be overloaded

            This is not only eye candy, but also allows developpers to forget if they are dealing
            with base types or not, thus making code easier to modify: if we ever decide to move
            from base types to classes we just have to implement the operator overload on classes.

            Great tutorial: <http://stackoverflow.com/questions/4421706/operator-overloading?rq=1>

            Good tutorial, specially on how to implement `=`, `+=` and `+` cases:
            <http://courses.cms.caltech.edu/cs11/material/cpp/donnie/cpp-ops.html>

            The following operators can all be overloaded:

                +    -    *    /    =    <    >    +=   -=   *=   /=   << (shift left)   >> (shift right)
                <<=  >>=  ==   !=   <=   >=   ++   --   %    &    ^    !    |
                ~    &=   ^=   |=   &&   ||   %=   []   ()   ,    ->*  ->   new
                delete    new[]     delete[]

            - typecast operator overload `int()`, `float()`, etc.

            Member or not

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
        ERROR: One of the arguments must be a Class or Enum.

        Just imagine the havoc if this were possible! =)
        */

            //int operator+(int i, int j){return i + j + 1;}

        /*
        class that shows the ideal methods of operator overloading.
        */
        class OperatorOverload {

            public:

                int i;

                OperatorOverload() { this->i = 0; }
                OperatorOverload(int i) { this->i = i; }

                /*
                operator=

                    Special care must be taken with `=` when memory is dynamically alocated because
                    of copy and swap idiom questions.

                    This is not the case for this simple class.

                Return non const reference

                    Return a *non* const reference because the following is possible for base types:

                        (a = b) = c

                    which is the same as:

                        a = b
                        a = c

                    so this obscure syntax should also work for classes.
                */
                OperatorOverload& operator=(const OperatorOverload& rhs) {
                    this->i = rhs.i;
                    return *this;
                }

                /*
                operator+=

                    Implement the compound assign, and the non compound in terms of the compound.

                    Must return a non-const reference for the same reason as `=`.
                */
                OperatorOverload& operator+=(const OperatorOverload& rhs) {
                    this->i += rhs.i;
                    return *this;
                }

                /*
                operator++

                    Post and pre increment are both impemented via this operator.

                    <http://stackoverflow.com/questions/6375697/overloading-pre-increment-operator>
                */
                const OperatorOverload& operator++() {
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

                /*
                # typecast overload

                    Automatic conversions will be done using it.

                    Notable example on the stdlib: `ifstream::operator bool()` to be able to do `while(getline)` 
                    becaues getline returns the updated ifstream.
                */

                    operator bool() const { return i % 2 == 1; }
                    operator int() const { return i + 1; }
                    operator float() const { return ((float)i) + 0.5; }
        };

        /*
        operator+

            Implemented in terms of the compound assign.

            Should be const because the following does nothing:

                (a + b) = c

            Should be an external method, since it is just a function of `+=`.
        */

            OperatorOverload operator+ (const OperatorOverload& lhs, const OperatorOverload& rhs) {
                return OperatorOverload(lhs) += rhs;
            }

        /*
        Comparison operators: only tow are needed: `==` and `<`.

        The other are functions of those two.

        It is recommended to implement them as non-member functions to increase incapsulation.
        */

            inline bool operator==(const OperatorOverload& lhs, const OperatorOverload& rhs) {return lhs.i == rhs.i;}
            inline bool operator!=(const OperatorOverload& lhs, const OperatorOverload& rhs) {return !operator==(lhs,rhs);}
            inline bool operator< (const OperatorOverload& lhs, const OperatorOverload& rhs) {return lhs.i < rhs.i;}
            inline bool operator> (const OperatorOverload& lhs, const OperatorOverload& rhs) {return  operator< (rhs,lhs);}
            inline bool operator<=(const OperatorOverload& lhs, const OperatorOverload& rhs) {return !operator> (lhs,rhs);}
            inline bool operator>=(const OperatorOverload& lhs, const OperatorOverload& rhs) {return !operator< (lhs,rhs);}

        /*
        operator<<

            `<<` **cannot** be a member method, because if it were then
            its first argument would be an implicit `Class` for the `this`,
            but the first argument of `<<` must be the `ostream`.

            Therefore it must be a free method outside of a class.

            It is likely that it will need to be a friend of the class in order
            to see its internal fields. This may not be the case in this overly simplified example.
        */

            std::ostream& operator<<(std::ostream& os, const OperatorOverload& c) {
                os << c.i;
                return os;
            }

        /*
        # number of arguments

            One major difference between regular functions and operators is that operators can only
            have  fixed number of arguments, because they have a very peculiar syntax.

            For example, how could a ternary multiplication possibly be called? ` a * b ???? c` ?

            There are some operators which exist for multiple numbers of arguments with different meaning:

            - `-` with one argument:    unary minus
            - `-` with two arguments:   subtraction

            - `*` with one argument:    dereference
            - `*` with two arguments:   multiplication

            For this reason, we must take into account that member operator overloads *already have one extra argument*,
            which is the `this` pointer, which is always passed as a first hidden parameter of member functions.
        */

            /*
            A failed attemtpt to add the middle handside to `operator*`.

            ERROR: operator* must have one or two arguments.
            */
            /*
            const OperatorOverload operator* (const OperatorOverload& lhs, const OperatorOverload& mhs, const OperatorOverload& rhs){
                return OperatorOverload(lhs.i * mhs.i * rhs.i);
            }
            */

        /*
        operator*

            operator* can be two things:

            - multiplication `a * b` if it has  two arguments   (or one    in a member method)
            - dereference `*ptr` if it has      one argument    (or none   in a member method)

            It is only differenced by the number of arguments.
        */

            /*
            This exists because it is the dereference operator.

            This is implemented on classes which represent pointers, such as `shared_ptr`,
            which is not the case for this class.
            */

                /*
                Dereference operator.

                This should not be implemented for this class since it makes no (usual) sense,
                it is just to illustrate that it is possible.
                */
                int operator* (const OperatorOverload& rhs){
                    return rhs.i;
                }

                OperatorOverload operator* (const OperatorOverload& lhs, const OperatorOverload& rhs){
                    return OperatorOverload(lhs.i * rhs.i);
                }

        /*
        operator-

        - `-` with one argument:    unary minus
        - `-` with two arguments:   subtraction

        */

                /* Can be defined in terms of * if you class implements it. */
                const OperatorOverload operator- (const OperatorOverload& rhs){
                    return OperatorOverload(-1) * rhs;
                }

                /* Defined in terms of unary minus and +. */
                const OperatorOverload operator- (const OperatorOverload& lhs, const OperatorOverload& rhs){
                    return lhs + (-rhs);
                }

        /*
        operator overload and templates

            Operator overload and templates do not play very well together
            because operator overload leads to special function calling syntax,
            which does not go well with the template calling syntax.
        */

            template <class T>
            T operator/(const T& i, const T& j) {return i + j;}

/*
#namespaces
*/

    // ERROR: same naming rules as vars
    //namespace 2D{}

    // BAD: by convention, namespaces start with lower case
    namespace D2{}

    int i;

    void f() {
        callStack.push_back("::f");
    }

    void prototype();

    namespace namea {

        int in_namea_only = 0;

        class C {
            public:
                C() {
                    callStack.push_back("namea::C");
                }
        };

        namespace nameaa {
            int i;

            void f() {
                callStack.push_back("nameaa::f");
            }

            class C {
                public:
                    C() {
                        callStack.push_back("nameaa::C");
                    }
            };
        }

        namespace nameab {
            int i;

            void f() {
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
                // ERROR: refers to current incomplete C already
                //not existem namea::C
            {
                C() {
                    callStack.push_back("namea::nameab::C");
                    f();
                    //no ambiguity because using inside f() only afects the function
                }
            };
        }

        int i;

        void f() {
            ::i = 0;
            i = 0;   //namea::i
            namea::i = 0;
            nameaa::i = 0; //namea::nameaa::i
            callStack.push_back("namea::f");
        }
    }

    namespace namea {
        //can add new members
            int j;
            void newFunc(){}
            class B{};

        // ERROR: redefinition
        //int i;

        // Implementation of namea::prototype.
        //void prototype(){}
    }

    // ERROR: must be declared/defined inside.
    //namea::i = 0;
    //void namea::prototype(){}
    //int namea::j;
    //void namea::g(){}
    //class namea::B{};

    // ERROR.
    //template<class T> namespace t {}

    // # ADL

        namespace adl0 {

            struct s {};

            int adl(struct s s){
                return 0;
            }

            int i;

            int adlNoType(int i){
                return 0;
            }

            int adlMultiArg(int i, struct s s, int j){
                return 0;
            }
        }

        namespace adl1 {

            struct s {};

            int adl(struct s s){
                return 1;
            }

            int i;

            int adlNoType(int i){
                return 1;
            }

            int adl0FromAdl1(struct adl0::s s) {
                return 1;
            }

            int adl0And1FromAdl1(struct adl0::s s0, struct s s1) {
                return 1;
            }

            float adl01(struct adl0::s s, struct s s1){
                return 0.5;
            }
        }

        namespace adl0 {
            float adl01(struct s s, struct adl1::s s1){
                return 0.5;
            }
        }

// #preprocessor

    // The C++ preprocessor it Turing complete by mistake.
    //
    // This leads to the concept of Template Metaprogramming,
    // which allows you to write code that is ultra DRY / runs fast but is very large.
    // TODO confirm.

// #template

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

    // # template integer parameter
    template<int N>
    int templateAddInt(int t) {
        return t + N;
    }

    // # template recursion

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
    # template template parameters
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
    # template default parameters
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

    // # template specialization

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

    // # template argument deduction

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
    # template class
    */

        template<class BASE=Base, class T=int, int N=10>
        // OK, can derive from template.
        class TemplateClass : public BASE {
            public:

                T t;
                T ts[N];

                TemplateClass(){callStack.push_back("TemplateClass::TemplateClass()");}

                // BAD: what is T = string?
                //TemplateClass() t(0.0){callStack.push_back("TemplateClass::TemplateClass()");}

                TemplateClass(T t): t(t){callStack.push_back("TemplateClass::TemplateClass(T)");}

                void method() {
                    callStack.push_back("TemplateClass::method()");
                }

                void methodDefinedOutside();

                T method(T){callStack.push_back("TemplateClass::method(T)");}

                // OK:
                template<class C=int>
                void methodTemplate() {
                    callStack.push_back("TemplateClass::methodTemplate()");
                }

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
        class TemplateFixed : TemplateClass<Base,int,10> {};

        // OK:
        class TemplatedNestedOut : TemplateClass<Base,int,10>::Nested {};

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
        void TemplateClass<BASE,T,N>::methodDefinedOutside() {
            callStack.push_back("TemplateClass::methodDefinedOutside()");
        }

#if __cplusplus >= 201103L
        // # template specialization

            // Specialization of function for case 12 only.
            template<>
            void TemplateClass<Base,int,11>::methodDefinedOutside() {
                callStack.push_back("TemplateClass<Base,int,11>::methodDefinedOutside()");
                // ERROR: T undeclared on specialiation
                //T t;
            }

            // ERROR: case 11 was already defined on the spcecialization of methodDefinedOutside 11.
            //template<> class TemplateClass<Base,int,11> {};


            // Specialization of entire class from now on, a completely new class is created in case 12.
            template<> class TemplateClass<Base,int,12> {
                public:

                    void newMethod() {
                        callStack.push_back("TemplateClass<Base,int,12>::newMethod()");
                    }
            };

            // ERROR: case 12 class, created in class template specialization
            // does not contain such a function
            //template<>
            //void TemplateClass<Base,int,12>::methodDefinedOutside(){}
#endif

        //typename keyword qualifier

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

            The only way the compiler can differentiate between both, is knowing beforehand if `HAS_I::i`
            is a type or a value.

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
                HAS_I::i * i;
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

        // Base case.
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

/*
#thread
*/

    int nNsecs = 10;
    int threadGlobal = 0;
    int threadGlobalMutexed = 0;
    std::mutex threadGlobalMutex;
    std::thread::id lastThreadId;
    std::set<std::thread::id> threadIds;

    int threadGlobalEq0 = 0;
    int threadGlobalMutexedEq0 = 0;
    int threadChange = 0;

    void threadFunc(int threadCountToSqrt) {
        std::thread::id id = std::this_thread::get_id();
        for (int i=0; i<threadCountToSqrt; i++)
        for (int j=0; j<threadCountToSqrt; j++) {
            if (lastThreadId != id) {
                ++threadChange;
                //threadIds.insert(id);
                lastThreadId = id;
            }

            // cout is not thread safe order gets mixed up.
            //std::cout << id << " " << i << endl;

            // If happens.

                threadGlobal = 1;
                if (threadGlobal == 0)
                    ++threadGlobalEq0;
                threadGlobal = 0;

            // If never happens!

                threadGlobalMutex.lock();
                // if not available, wait
                //threadGlobalMutex.try_lock();
                // If not available, return!
                threadGlobalMutexed = 1;
                if (threadGlobalMutexed == 0)
                    ++threadGlobalMutexedEq0;
                threadGlobalMutexed = 0;
                threadGlobalMutex.unlock();

        }
        std::this_thread::sleep_for (std::chrono::nanoseconds(nNsecs));
        // Done, pass to another thread.
        std::this_thread::yield();
    }

#ifdef PROFILE
    const static int nProfRuns = 100000000;

    // Only the loop. Discount this from every other profile run.
    void loopOnlyProf(int n) {
        int i;
        for (i=0; i<n; i++);
    }

    void whileOnlyProf(int n) {
        int i = 0;
        while (i < n)
            ++i;
    }

    void intAssignProf(int n) {
        int i,j;
        for (i=0; i<n; i++)
            j=1;
    }

    void doNothing(){}

    void funcCallProf(int n) {
        int i;
        for (i=0; i<n; i++)
            doNothing();
    }

    static inline void inlineDoNothing(){}

    void inlineFuncCallProf(int n) {
        int i;
        for (i=0; i<n; i++)
            inlineDoNothing();
    }

    void intSumProf(int n) {
        int i, j = 0;
        for (i=0; i<n; i++)
            j = j + 0;
    }

    void intSubProf(int n) {
        int i, j = 0;
        for (i=n; i>0; i--);
            j = j - 0;
    }

    void intMultProf(int n) {
        int i, j = 1;
        for (i=0; i<n; i++)
            j = j * 1;
    }

    void intDivProf(int n) {
        int i, j = 1;
        for (i=0; i<n; i++)
            j = j / 1;
    }

    void floatSumProf(int n) {
        float f;
        int i;
        for (i=0; i<n; i++)
            f = f + 0.0;
    }

    void floatSubProf(int n) {
        float f;
        int i;
        for (i=0; i<n; i++)
            f = f - 0.0;
    }

    void floatMultProf(int n) {
        int i;
        float j;
        for (i=0; i<n; i++)
            j = j * 1.0;
    }

    void floatDivProf(int n) {
        int i;
        float j;
        for (i=0; i<n; i++)
            j = j / 1.0;
    }

    void putsProf(int n) {
        int i;
        for (i = 0; i < n; ++i)
            puts("");
    }

    void stack1bProf(int n) {
        int is[1];
        int i;
        for (i = 0; i < n; ++i)
            int is[1];
    }

    void stack1kbProf(int n) {
        int is[1];
        int i;
        for (i = 0; i < n; ++i) {
            int is[0x800];
        }
    }

    void stack1mbProf(int n) {
        int is[1];
        int i;
        for (i = 0; i < n; ++i)
            int is[0xF0000];
    }

    void heapMalloc1bProf(int n) {
        char* cp;
        int i;
        for (i = 0; i < n; ++i) {
            cp = (char*) malloc(sizeof(char) * 1);
            free(cp);
        }
    }

    void heapMalloc1kbProf(int n) {
        char* cp;
        int i;
        for (i = 0; i < n; ++i) {
            cp = (char*) malloc(sizeof(char) * 0x800);
            free(cp);
        }
    }

    void heapMalloc1mbProf(int n) {
        char* cp;
        int i;
        for (i = 0; i < n; ++i) {
            cp = (char*) malloc(sizeof(char) * 0xF0000);
            free(cp);
        }
    }

    void heapNew1bProf(int n) {
        char* cp;
        int i;
        for (i = 0; i < n; ++i) {
            cp = new char[1];
            delete[] cp;
        }
    }

    void heapNew1kbProf(int n) {
        char* cp;
        int i;
        for (i = 0; i < n; ++i) {
            cp = new char[0x800];
            delete[] cp;
        }
    }

    void heapNew1mbProf(int n) {
        char* cp;
        int i;
        for (i = 0; i < n; ++i) {
            cp = new char[0xF0000];
            delete[] cp;
        }
    }

    class BaseProf {
        public:
            virtual void virtualMethod(){}
    };

    class ClassProf {
        public:
            void method(){}
            virtual void virtualMethod(){}
    };

    void methodCallProf(int n) {
        ClassProf c;
        int i;
        for (i = 0; i < n; ++i) {
            c.method();
        }
    }

    void virtualMethodCallProf(int n) {
        ClassProf c;
        int i;
        for (i = 0; i < n; ++i) {
            c.virtualMethod();
        }
    }

#endif

//constexpr

    int not_constexpr_func() {
        return 1;
    }

    constexpr int constexpr_func(int i) {
        return i;
    }

        /*
        C++11 specifies that the body of a constexrp function must contain a single return statement.

        Otherwise, it would be too much work for the compiler to do.

        <http://stackoverflow.com/questions/3226211/why-is-it-ill-formed-to-have-multi-line-constexpr-functions>
        */
    /*
    constexpr int constexpr_func_multi_statement(int i) {
        int j;
        return i;
    }
    */

    constexpr int ConstexprFactorial(int n) {
        return (n == 1) ? 1 : n * ConstexprFactorial(n - 1);
    }


        /**
        ERROR: the compiler ensures that the function is constexpr,
        so this does not compile.
        */
    /*
    int constexpr constexpr_func_bad(){
        return std::time();
    }
    */

//string

    std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
        std::stringstream ss(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            elems.push_back(item);
        }
        return elems;
    }

    std::vector<std::string> split(const std::string &s, char delim) {
        std::vector<std::string> elems;
        split(s, delim, elems);
        return elems;
    }

//File IO

    void ios_write_fail(std::string path) {
        throw std::ios_base::failure("Error: Could not write to file: " + path);
    }

    void ios_read_fail(std::string path) {
        throw std::ios_base::failure("Error: Could not read file: " + path);
    }

    /**
    Read entire file into a string at once.
    */
    void read_file(std::ifstream &ifs, std::string &data_read) {
        ifs.seekg(0, std::ios::end);
        size_t size = ifs.tellg();
        data_read.resize(size);
        ifs.seekg(0);
        ifs.read(&data_read[0], size);
        ifs.close();
    }

//to_str

    template <class K, class V>
    std::string map_to_str(std::map<K,V> map) {
        std::stringstream result;
        for (auto& pair : map) {
            result << pair.first << ":" << pair.second << ", ";
        }
        return result.str();
    }

//attributes

    void noreturn_func [[ noreturn ]] () { throw 1; }

//Misc

    bool odd(int i){ return (i % 2) == 1; }

    int bind2ndTarget(int i, int j) {
        return i + j;
    }

    class ClassWithTypedef {
        public:
            typedef int typedefPublic;
        private:
            typedef int typedefPrivate;
    };

/*
# main

    # main signature

        - http://stackoverflow.com/questions/4207134/what-is-the-proper-declaration-of-main
        - http://stackoverflow.com/questions/1621574/can-the-arguments-of-mains-signature-in-c-have-the-unsiged-and-const-qualifie

        Much like in C, only:

            int main();
            int main(int, char*[]);

        are required to work, but more likely work as well.

    # Call main from the program

        In C++, cannot be called from anywherelse in the program, including recursively:
        http://stackoverflow.com/questions/2128321/can-main-function-call-itself-in-c

        This restriction does not seem to exist in C.
*/
int main(int argc, char **argv) {

    // # Scope
    {
        /*
        # typedef struct

        # typedef class

            # struct keyword omission

            Unlike in C, struct tags and variable names live in the same namespace.

            In C++ you can normally omit `struct`
            `struct s` is called an #elaborated-type-specifier.
            <http://stackoverflow.com/a/14261176/895245>

            But if there is ambiguity, the only way to refer to the struct
            is by appending `struct`.
        */
        {
            int s = 1;
            struct s {int i;};
            assert(s == 1);
            // ERROR
            //s t = {1};
            struct s t = {1};
            assert(t.i == 1);

            int c = 1;
            class c { public: int i; };
            assert(c == 1);
            // ERROR
            //c u = {1};
            class c u = {1};
            assert(u.i == 1);
        }
    }

    /*
    # assign operator

        Unlike in C, C++ assign operator returns lvalues!

        TODO rationale. Related to return refs from functions?
    */
    {
        int i = 0, j = 1, k = 2;

          (i = j) = k;
        /*^^^^^^^^^
          |
          returns a lvalue pointing to `i`

          Therefore is the same as:

          i = j;
          i = k;
        */

        assert(i == 2);
        assert(j == 1);
        assert(k == 2);

        // ERROR: as in C, most other operators do not return lvalues
        //(i + j) = k;
    }

    /*
    # bool

        in C++, unlike in C, bool is part of the language.
    */
    {
        bool b;

        b = true;
        b = 1;

        if (true)
        {
            assert(true);
        }
        if (false)
        {
            assert(false);
        }

        {
            std::stringstream oss;
            oss << true;
            assert(oss.str() == "1");
        }

        {
            std::stringstream oss;
            oss << false;
            assert(oss.str() == "0");
        }

    }

    // # unsigned
    {
        unsigned int ui = -1;
        int i = 1;
        //if (ui<i)
        // WARN: in c, no WARN
    }

    /*
    # constant expressions at compile time

        <http://en.cppreference.com/w/cpp/language/constant_expression>

        Constant expressions at compile time can be used in contexts where non constants cannont:

        - array lengths at array declaration
        - numeric template parameters

        The compiler is able to determine which expressions are constant recursively.

        Note that variables with the keyword `const` may or may not be constant expressions.
        depending on how they are initialized.

        Those defined with the keyword constexpr however are ensured by the compiler to be
        compile time constants.
    */

    /*
    Get array length, find array length: <http://stackoverflow.com/questions/4108313/how-do-i-find-the-length-of-an-array>

    Besides the C sizeof method which does not work for pointers and has lots of duplication, C++ offers:
    */
    {
        // Vector class. Has overhead, but probably the best option given its flexibility.

        // #array class. No overhead. Fixed size. Template based.
        {
            // WARN: double brackets required TODO why
            //std::array<int, 3> a{0, 1, 2};

            std::array<int, 3> a{{0, 1, 2}};
            assert(a.size() == 3);
        }

        // Method which I don't understand.
        {
            //template<class T, size_t N>
            //size_t size(T (&)[N]) { return N; }
        }
    }

    /*
    # array size from variables

        In C++, any constant expression at compile time can be used as an array size.

        This includes in particular intetegers declared as `const` and initialized by a constant expression,
        and in C++11 all `constexpr` variables.
    */
    {
        std::srand(time(NULL));

        {
            int i = 1;
            i = std::rand();
            // ERROR: the size would not be fixed
            //int is[i];
        }

        {
            // Compile time constant since the literal 1 is a constant expression.
            const int ci = 1;
            // Cannot do that, so the size is fixed!
            //ci = 2;
            int is[ci];
        }

        // ERROR: the compiler is able to see that ci is not a compile time constant
        {
            const int ci = std::rand();
            //int is[ci];
        }
    }

    /*
    # const keyword

        There are differences between the `const` keyword in C and C++!

        Also, in C++ const can be used to qualify methods.

        <http://stackoverflow.com/questions/8908071/const-correctness-in-c-vs-c>
    */
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
            const int i = std::time(NULL);
        }

        //consts must be initialized at declaration because they cannot be modified after.
        {
            //const int i;
            // ERROR i not initialized

            // ERROR uninitialized
            //int * const ipc;

            // OK: we can change which object it points to
            {
                int i = 0;
                int j = 0;
                int const * icp;
                icp = &i;
                icp = &j;
                // ERROR
                //*icp = 1;
            }

            // C is initialized by the constructor
            // so it is OK to do this unlike for base types
            const Class c;
        }

        // Const for classes.
        {
            const Class c;

            // Cannot reassign:

                //cc = Class();

            // Cannot assign members:

                //cc.i = 1;

            // Can create const refs to:

                const int& cia = c.i;

            // Cannot create non const refs:

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

#if __cplusplus >= 201103L

    /*
    # constexpr

        C++11 keyword.

        `const` variables can either be compile time constants or not.

        The compiler is able to decide that at compile time, but it may be hard for human
        readers to predict if a given variable is a constexpr of not.

        Using the constexpr keyword however makes the compiler ensure that the variables are constant expressions,
        so that the compile time constantness is more explicit.

        Two uses:

        - variables

            Means that the value of an expression is known at compile time.

        - functions

            The value returned by constexpr functions is known to be a compile time constant.

            The compiler enforces this by inspecting the function.
    */
    {
        // OK: built-in operations that take constexprs return a constexpr
        {
            constexpr int i = 1 + 1;
        }

        // OK: it is a constexpr
        {
            constexpr int i = 0;
            constexpr int i2 = i;
        }

        // OK: the compiler sees that a const initialized by a constexpr is also a constexpr.
        {
            const int i = 0;
            constexpr int i2 = i;
        }

        // ERROR: for non built-in operators, only constexpr functions can be used.
        {
            //constexpr int i = not_constexpr_func();
        }

        // constexpr functions only work if all their arguments are constexprs.
        {
            { constexpr int i = constexpr_func(1); }
            //{ constexpr int i = constexpr_func(std::time(NULL)); }
        }

        // Recursive functions can be constexpr, as long as they fit into one line.
        {
            constexpr int i = ConstexprFactorial(3);
            assert(i == 6);
        }

        // ERROR: the compiler sees that this is not a constexpr.
        // Avoid relying on this execept for legacy code: always initialize a constexpr from constexprs!
        {
            const int i = std::time(NULL);
            //constexpr int i2 = i + 1;
        }

        // ERROR: it is not a constexpr
        {
            int i = 0;
            //i = std::time(NULL);
            // We could change i at any time!
            //constexpr int i2 = i + 1;
        }

        // ERROR: constexprs cannot be modified after initialization
        {
            constexpr int i = 0;
            //i = 1;
        }

        // WARN: unitialized constexpr
        {
            //constexpr int i;
        }

        /*
        cannot have constexpr to complex types

        TODO rationale
        */
        {
            //constexpr std::string s = "abc";
        }
    }

#endif

#if __cplusplus >= 201103L

    /*
    # nullptr

        C++11 keyword.

        Better alternative to `0` and `NULL` ugliness:

        <http://stackoverflow.com/questions/1282295/what-exactly-is-nullptr>

    # nullptr_t

        Type of nullptr.
    */
    {
        // No address can be nullptr
        {
            std::nullptr_t p = nullptr;
            int i;
            //assert(&i != p);
                //gcc 4.7 warning: &i will never be null. Smart.
        }

        // It is possible to convert NULL and 0 to nullptr_t.
        {
            std::nullptr_t p;
            p = NULL;
            p = 0;
        }

        /*
        It is not possible to convert nullptr_t to NULL and 0

        This allows to overload a function for both pointer and integer.

        In that case, passing it a `0` would always select the integer version.
        */
        {
            //int i = nullptr;
        }

        // Unlike in NULL, the size of nullptr_t is fixed.
        {
            assert(sizeof(std::nullptr_t) == sizeof(void*));
        }
    }

#endif

    /*
    # &

    # References.

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
        // Basic usage as function parameters that are return values.
        {
            int i = 0;
            byref(i);
            assert(i == 1);
        }

        /*
        References have the same address of the variables.

        Therefore:

        - if declared inside the same function as the value, no extra memory / dereferencing
            needs to be used for references, the compiler can figure everything out at compile time.

        - if declared as function arguments, references may be implemented as implicit pointers passing,
            sharing therefore the disadvantages of pointers.

            Therefore, if you want to be sure of efficiency, pass built-in types by value and not by reference.
        */
        {
            // They have the same address.
            {
                int i = 0;
                int& ia = i;
                ia = 1;
                assert(i == 1);
                assert(&i == &ia);
            }

            /*
            For the same reason, it is possible to initialize a reference from another reference.
            */
            {
                int i = 0;
                int& ia = i;
                int& ia2 = ia;
                ia2 = 2;
                assert(i == 2);
            }
        }

        /*
        ERROR: Must not initialize non-const ref with a rvalue.

        Can however do that for const references.

        The same goes for function parameters.
        */
        {
            //int& ia = 0;
            //std::string& s = getString();
            const std::string& s = getString();
            //byref(1);
        }

        /*
        ERROR: references must be initialized imediatelly
        otherwise, how can they be initalized in the future?

        For references in constructors, they must be initialized at the initialization list.
        */
        {
            //int& ia;
        }

        /*
        It is possible to get references from pointers.
        */
        {
            int i = 0;
            int* ip = &i;
            int& ia = *ip;
            ia = 1;
            assert(i == 1);

            // ERROR: & must get a variable/dereferenced pointer, not pointers themselves!
            {
                //int& ia = &i;
            }
        }

        /* It is not possible to make an array of references. */
        {
            int i = 1;
            int j = 2;

            // ERROR: array of references forbidden
            //int& is[2] = {i,i};
        }

        /*
        # const references

            References that do not allow one to modify the value of the variable.
        */
        {

            //it is possible to make a const reference from a non-const object
            {
                int i = 1;
                const int& cia = i;

                // ERROR: const references cannot be modified
                //cia = 2;
            }

            //it is possible to make a const reference form a const object
            {
                const int ci = 1;
                const int& cia = ci;

                // ERROR: const references cannot be modified
                //cia = 2;
            }

            /*
            The rules imposed by the compiler make sure that it is hard or impossible to cheat references by mistake.
            */
            {
                int i = 1;
                const int& cia = i;

                // ERROR: invalid conversion
                //int& ia = cia;

                // ERROR: invalid conversion
                //int *ip = &cia;
            }

            /*
            const references can be initialized by rvalues!

            This cannot be wrong since they cannot be modified,
            so it is not possible to modify the non-existent variable.

            In this case what happens is that a simple copy takes place.

            One case in which this rule is very important is parameter passing to functions.

            For exapmle, the following would be bad:

                void f(int& i) {
                    i++;
                }

                ...

                f(1);
                    //does not compile

            and is impossible, but:

                void f(const int& i) {
                    //i++;
                        //impossible
                }

                f(1);

            is ok, since it is impossible to change i in the function if it is const
            */
            {
                //initialization from a literal
                {
                    const int& i = 1;
                    assert(i == 1);
                }

                /*
                Initialization from a non-reference function return.

                Functions that return references return lvalues,
                so an example with such a function would not be meaningful.
                */
                {
                    const int& i = getInt();
                    assert(i == 0);
                }
            }
        }

        /*
        # reference to pointer

            like for other variable, references can be made to pointer variables.
        */
        {
            {
                int i = 0;
                int j = 1;
                int *ip = &i;
                int *jp = &j;
                int*& ipa = ip;
                int*& jpa = jp;

                jpa = ip;
                    //now `jp` is the same as `ip`!

                *jp = 2;
                assert(i == 2);
                    //therefore modifying what `jp` points to modifies `i`!

                // ERROR: makes no sense: cannot have a pointer to `int&`
                //int&* ipaBad = ip;

                // ERROR: `&i` is an rvalue. Cannot initialize a non const reference to it.
                //int&* ipaBad = &i;
            }

            /*
            # reference to pointer and const

                Just like for pointers to pointers in C, the rules prevent `const` variables
                from being modified.
            */
            {
                /*
                Obviously, cannot remove const qualifiers, or it would be easy to modify constants.
                */
                {
                    const int c = 0;
                    const int *ip = &c;
                    //int *&ipa = ip;
                    //int *ipa = ip;
                    //*ipa = 1;
                }

                /*
                `const int*& = int*` initialization fails for the same reason that `const int* = (int*)` fails in C:
                this would allow for constant modification.
                */
                {
                    //If (1) were possible below, then it would be possible to change the value of the constant c.
                    {
                        /*
                            int *ip = NULL;
                            const int*& ipa = ip;   // (1) THIS is not possible
                            const int c = 0;
                            ipa = &c;               // OK because ipa is const. `ip` points to `c`
                            *ip = 1;                // OK because ip  is not const
                        */
                    }

                    /*
                    This is different without the reference, because in this case
                    it would not be possible to change the const variable.

                    Just like in C, the issues only show up in pointer dimensions > 1,
                    and the reference behaves like a pointer.
                    */
                    {
                        int *ip = NULL;
                        const int* ipa = ip;   // (1) THIS is ok without the reference, a new pointer is created
                        const int c = 0;
                        ipa = &c;              // OK because ipa is const. ip still points to NULL
                        //*ip = 1;             // does not change the constant, ip still points to NULL
                    }
                }
            }

            /*
            What to do if:

            - a function modifies what pointers point to but not the object pointed to.

                It therefore takes

            - we want to pass pointers to that function, modify what they point to,
                and then outside of the function modify the object being pointed to?

            Is this a valid use case for `const_cast`?
            */
            {
                //the motivation: functions
                {
                    int i = 0;
                    int j = 1;
                    int *ip = &i;
                    int *jp = &j;

                    //const int *ip = &i;
                    //const int *jp = &j;
                        //if those were const, the function call would work,
                        //but not the `*ip = 2`;

                    //bypointerConst(ip, jp);
                        //cannot initialize `const int*&` with `int*&`.

                    *ip = 2;
                    //assert(j == 2);
                }

                //same problem simplified without functions
                {
                    int i = 0;
                    int *ip = &i;

                    //int*& ipa = ip;
                        //possible

                    //const int*& ipa = ip;
                        //TODO why is this not possible
                }

                //but this is possible?
                {
                    int i = 0;
                    const int& ia = i;
                }
            }
        }

        /*
        Single line initialization syntax.

        Like the pointer symbol `*`, the reference symbol `&` needs to be duplicated for each new reference variable.
        */
        {
            //ok: both ia and ja are references
            {
                int i = 1;
                int j = 2;
                int &ia = i, &ja = j;

                ia = -1;
                ja = -2;

                assert(i == -1);
                assert(j == -2);
            }

            //ko: ja is a new int, not a reference
            {
                int i = 1;
                int j = 2;
                int& ia = i, ja = j;

                ia = -1;
                ja = -2;

                assert(i == -1);
                assert(j ==  2);
            }

            //with references to pointers it looks like this
            {
                int i = 0;
                int j = 1;
                int *ip = &i;
                int *jp = &j;

                int *& ipa = ip, *& jpa = jp;

                jpa = ip;
                *jp = 2;
                assert(i == 2);
            }
        }

        /*
        # return reference from function

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
                assert(b.iPublic == 0);
                ia = 1;
                assert(b.iPublic == 1);
            }

            //you can modify a private if you non const reference to it
            {
                    Base b;
                    int& ia = b.getPrivateRef();
                    ia = 0;
                    assert(b.getPrivateRef() == 0);
                    ia = 1;
                    assert(b.getPrivateRef() == 1);
            }

            //if the reference is const it does not work anymore
            {
                Base b;

                {
                    const int& ia = b.getPrivateConstRef();
                    //ia = 1;
                }

                // ERROR: invalid initialization
                {
                    //int& ia = b.getPrivateConstRef();
                }
            }

            /*
            In C, all functions return rvalues,
            although if a function returns a pointer and that pointer is dereferenced it becomes an lvalue,
            so the following works:

                (*ret_int_ptr()) = 1;

            In C++, there is an exception: all functions that return references return lvalues directly.
            */
            {
                int i = 0;
                (getIntRef(i)) = 2;
                assert(i == 2);
            }
        }
    }

#if __cplusplus >= 201103L

    /*
    # auto

        C++11 keyword

        Completelly differs in meaning with the useless C `auto` keyword.

        Variable type is infered based on return value of initialization.

        Reduces code duplication, since it allows us to not write explicitly types everywhere.

        Major application: create an iterator without speficying container type.
    */
    {
        // Basic usage.
        {
            //the compiler infers the type of i from the initialization.
            auto i = 1;
        }

        // Reference.
        {
            int i = 1;
            auto& ai = i;
            ai = 2;
            assert(i == 2);
        }

        // ERROR: must initialize immediately. How could the compiler deduce type otherwise?
        {
            //auto i;
            //i = 1;
        }

        // If initialized from reference, discards the reference, while decltype keeps it.
        {
            int i = 0;
            int& ir = i;
            auto ir2 = ir;
            ir2 = 1;
            assert(i == 0);
        }

        // Array. Seems not.
        {
            //auto is[]{1, 0};
        }

        {
            typedef int Type;
            std::vector<std::vector<Type>> is{{0}, {1, 2}};
            for (auto& i : is[1]) std::cout << i << std::endl;
        }
    }

#endif

#if __cplusplus >= 201103L

    /*
    # decltype

        C++11 keyword

        Replace decltype with type of an expression at compile time.

        More powerful than `auto`.
    */
    {
        int i = 1;
        float f = 2.0;
        decltype(i + f) f2 = 1.5;
        assert(f2 == 1.5);

        //implies reference while auto does not
        {
            int i = 0;
            int& ir = i;
            decltype(ir) ir2 = ir;
            ir2 = 1;
            assert(i == 1);
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
    # vla

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
            // ERROR: may not be initialized
            //cin >> i;
            //int is4[i] = {1, 2};
        }
    }

    // # enum
    {
        //unlike c, already does typedef
        {
            enum TEXTURE {GRASS, WALL, SKY};
            TEXTURE t = GRASS;
        }
    }

    // # typedef
    {
        // It is possible to call constructors with typedefs
        {
            typedef Base BaseTypedef;
            BaseTypedef b = BaseTypedef(1);
            //              ^^^^^^^^^^^
        }

        // Typdefs inside classes follow public / private scoping.
        {
            ClassWithTypedef::typedefPublic i;
            // ERROR: not accessible from this context
            //ClassWithTypedef::typedefPrivate j;
        }
    }

    // # for
    {

        //you can define i inside the for scope only
        int is[] = {0, 1, 2};
        for (int i=0; i<3; i++)
        {
            assert(i == is[i]);
            // ERROR: already declared in this scope
            //int i;
        }
    }

#if __cplusplus >= 201103L

#endif

    // # function
    {
        // # overload
        {
            overload(1);
            assert(callStack.back() == "overload(int)");
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

            assert(callStack.back() == "overload(float)");
            callStack.clear();

            /*
            ERROR: ambiguous
            should compiler coverts to Base or BaseProtected? Both are possible via the default copy constructors.
            */
            {
                Class cOverload;
                //overloadBase(cOverload);
            }

            // ERROR: ambiguous
            //i=4;
            //overloadValAddr(i);

            // # default arguments
            {
                assert(DefaultArgs(1)    == 1);
                assert(DefaultArgs(1, 1) == 2);
            }

            /*
            # default arguments for references

                There seems to be no standard way of doing that without using extra memory / verbosity.

                <http://stackoverflow.com/questions/2816293/passing-optional-parameter-by-reference-in-c>
            */
        }

        /*
        In C++, unlike in C, definitions can ommit argument names if they don't use those arguments!

        This probably exists for method overridding.
        */
        {
            assert(def_no_argname(0)     == 1);
            assert(def_no_argname(0, 0)  == 2);
        }

        /*
        # operator overload
        */
        {
            //OperatorOverload overload `+`
            {
                //==
                assert(OperatorOverload(3) == OperatorOverload(3));

                //<
                assert(OperatorOverload(1) < OperatorOverload(2));

                //=
                {
                    OperatorOverload i(1);
                    assert(i == OperatorOverload(1));
                }

                //+=
                {
                    OperatorOverload i(1);
                    i += OperatorOverload(2);
                    assert(i == OperatorOverload(3));
                }

                //+
                assert(OperatorOverload(1) + OperatorOverload(2) == OperatorOverload(3));

                //++
                {
                    OperatorOverload i(1);
                    assert(++i == OperatorOverload(2));
                    assert(i == OperatorOverload(2));

                    /* TODO understand and get working */
                    /*
                    i = OperatorOverload(1);
                    assert(i++ == OperatorOverload(1));
                    assert(i == OperatorOverload(2));
                    */
                }

                //-
                {
                    // Unary
                    assert(-OperatorOverload(1) == OperatorOverload(-1));

                    // Subtraction
                    assert(OperatorOverload(2) - OperatorOverload(1) == OperatorOverload(1));
                }

                //*
                {
                    // Dereference
                    assert(*(OperatorOverload(1)) == 1);

                    // Subtraction
                    assert(OperatorOverload(2) - OperatorOverload(1) == OperatorOverload(1));
                }

                //<<
                {
                    OperatorOverload i(123);
                    std::stringstream os;
                    os << i;
                    assert(os.str() == "123");
                }

                //typecast overload
                {
                    OperatorOverload oo(1);

                    // Explicit typecast:
                    assert(((bool)oo) == true);
                    assert(((int)oo) == 2);
                    assert(((float)oo) == 1.5);

                    // Implicit typecast:
                    assert(oo);

                    int i = oo;
                    assert(i == 2);

                    float f = oo;
                    assert(f == 1.5f);
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

                assert(operator+(i, j) == OperatorOverload(3));

                i.operator=(j);
                assert(i == j);
            }

            /*
            operator overload and templates
            */
            {
                // Works because of template ty.
                assert(OperatorOverload(1) / OperatorOverload(2) == OperatorOverload(3));

                // ERROR: Impossible syntax
                //assert(OperatorOverload(1) /<OperatorOverload> OperatorOverload(2) == OperatorOverload(3));

                // If we needed to specify the template parameter to the operator on this case,
                // an explicit `operator/` call would be needed
                assert(operator/<OperatorOverload>(OperatorOverload(1), OperatorOverload(2)) == OperatorOverload(3));
            }
        }


#if __cplusplus >= 201103L

        /*
        # lambda

            C++11

            Function without name.

            Specialy useful in conjunction with function that take functions as arguments such as `std::find_if`,
            when we only want to use the function passed once.

            Good explanation: <http://stackoverflow.com/a/7627218/895245>

            TODO: why square brackets? Why not pass by reference as in a regular function?
        */
        {
            {
                int i = 0;
                int j = 0;
                auto f = [&i,&j](int k) -> int {i = 1; j = 1; return k + 1;};
                assert(f(0) == 1);
                assert(i == 1);
                assert(j == 1);
            }

            // Typical application with find_if.
            {
                std::vector<int> v = {2, 0, 1};
                assert(std::find_if(v.begin(), v.end(),
                    [](int i) {return i % 2 == 1;}) == --v.end());
            }
        }

#endif

    }

    /*
    # template

        Greatly reduces code duplication

        Can be used both in functions and classes.

        For each template that is used, a new name mangled function is compiled.
        This has the following downsides:

        - code bloat.

            Final exectutable gets larger.

        - Implementation must be put in `.h` files and compiled by includers,
            since only used templates generate code for the corresponding definitions.

            Pre-compiling all possibilities on a `.so` is obviously not an option:
            just consider int N, there are int many compilation possibilities!

    # three types of arguments

        There are 3 possible arguments for templates:

        - types
        - integers values
        - other templates (see template teamplate)

    # extends

        No equivalent to Javas "T extends Drawable"... sad.

        But wait, there seems to be something coming on C++14: template restrictions to the rescue?
        <http://stackoverflow.com/questions/15669592/what-are-the-differences-between-concepts-and-template-constraints>

    # disambiguating dependent qualified type names

        Syntax:

            template <class T>
            std::string foo(vector<T> vec, ... other args)
            {
                typename std::vector<T>::iterator it = vec.begin();
            }

        source:

            <http://eli.thegreenplace.net/2011/04/22/c-template-syntax-patterns/>

        TODO0

    # Disambiguating explicitly qualified template member usage

        Syntax:

            template<class U> void func(U arg)
            {
                int obj = arg.template member_func<int>();
            }

        Source: http://eli.thegreenplace.net/2011/04/22/c-template-syntax-patterns/

        TODO0

    # sources

        - <http://www.codeproject.com/Articles/257589/An-Idiots-Guide-to-Cplusplus-Templates-Part-1>

            Very complete and exemplified intro article.

        - <http://eli.thegreenplace.net/2011/04/22/c-template-syntax-patterns/>

            Short intro, covers some quirky points.
    */
    {

        /*
        basic usage
        */
        {
            assert(templateAdd<int>(1, 1) == 2);
            assert(templateAdd<float>(1.0, 1.0) == 2);
        }

        /*
        # template specialization

            Give an specific behaviour for certain types.
        */
        {
            assert((templateSpec<double,double>(1.0, 1.0)) == 3.1);
        }

        /*
        # template argument deduction

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

            /*
            # template keyword qualifier

                Just like the typename qualifier helps the compiler solve another type of parsing ambiguity,
                in this case if `<` is a minus or a template instantiation.

                Only used inside of templates that use templates!

                Very good example of the template qualifier:
                <http://stackoverflow.com/questions/610245/where-and-why-do-i-have-to-put-the-template-and-typename-keywords>
            */
            {
                TemplateQualifier tq;
                TemplateQualifierTest<TemplateQualifier>(tq, tq, &tq);
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
            assert(factorial<3>() == 6);
                //because of this call
                //all factorials from
                //1 to 3 will be compiled

            assert(factorial<6>() == 720);
                //because of this call
                //all factorials from
                //4 to 6 will be compiled
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

        //double less signs: can only be used in C++11.
        //or compiler could get confused with `>>` operator
        {
            {std::vector<std::vector<int> > vv;}
            //                            ^
            //                            THIS space was required before C++11

#if __cplusplus >= 201103L
            {std::vector<std::vector<int>> vv;}
#endif
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
        # template class

            Only points which differ significantly from template functions shall be covered here.
        */
        {
            {
                TemplateClass<Base,int,10> c;
                c.ts[9] = 9;
            }

            {
                TemplateClass<Base,std::string,10> c;
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
                    assert(callStack.back() == "TemplateClass::methodDefinedOutside()");
                    // 12 class does not contain method().
                    //TemplateClass<Base,int,12>().method();
                }

                {
                    TemplateClass<Base,int,11> c;
                    callStack.clear();
                    c.methodDefinedOutside();
                    assert(callStack.back() == "TemplateClass<Base,int,11>::methodDefinedOutside()");
                    //TemplateClass<Base,int,12>().method();
                        //12 class does not contain method()
                }

                {
                    TemplateClass<Base,int,12> c;
                    callStack.clear();
                    c.newMethod();
                    assert(callStack.back() == "TemplateClass<Base,int,12>::newMethod()");
                    //TemplateClass<Base,int,12>().method();
                        //12 class does not contain method()
                }
            }
        }
    }

    /*
    # exception #throw #catch

        Great source: <http://www.cplusplus.com/doc/tutorial/exceptions/>

        Application: centralize error handling in a single place, even if outside executing functions.

        The application is similar to C's longjmp, but the implementation is different.
        TODO how are they implemented in assembly code? <http://stackoverflow.com/questions/490773/how-is-the-c-exception-handling-runtime-implemented>
        It is more magic than C longjmp as it does type checking.

        Anything can be thrown, but the most standard and extensible method is to throw subclasses of exception,
        so just do that always.

        There is no finally block: <http://stackoverflow.com/questions/161177/does-c-support-finally-blocks-and-whats-this-raii-i-keep-hearing-about>
        Deinitializations are left for destructors.

        # Standard exceptions.

            - exception         base class of all stdlib exceptions.
            - bad_alloc         thrown by new on allocation failure
            - bad_cast          thrown by dynamic_cast when fails with a referenced type
            - bad_exception     thrown when an exception type doesn't match any catch
            - bad_typeid        thrown by typeid
            - ios_base::failure thrown by functions in the iostream library

    # exception safety

        Different levels of how much excpetion handlind a function does:

        <http://en.wikipedia.org/wiki/Exception_safety>
    */
    {
        /*
        Exceptions can jump out of functions.

        This is their main reason for existing!
        */
        {
            try {
                exception_func_int();
            } catch (int i) {
                assert(i == 1);
            }
        }

        /*
        # std::exception

            Anything can be thrown, including classes and base types.

            All stdlib exceptions inherit from `exception`, so it is a good idea to only throw
            things inherited from it.

            `std::exception` has limited use since its constructor does not take any arguments,
            so you cannot describe the error. Some stdlib derived class constructors do however.
        */
        {
            try {
                throw std::exception();
            } catch (std::exception e) {
            }
        }

        /*
        Catch blocks work like function overloads and catch by type.
        */
        try {
            throw 'c';
        } catch (int i) {
            assert(false);
        } catch (char c) {
        }

        /*
        `...` is the default case
        */
        try {
            throw 1.0;
        } catch (int i) {
            assert(false);
        } catch (char c) {
            assert(false);
        } catch (...) {
        }

        /*
        Derived classes.

        Just like for function overloading, base classes catch for derived classes.
        */
        {
            try {
                throw myexception();
            } catch (std::exception& ex) {
            }
            /*
            This compiles, but generates a warning, since the first catch will always catch instead of this one.
            */
            //catch (myexception& ex)       {assert(false);}
            catch (...)                     {assert(false);}

            /*
            this is a more common exception ordering, first derived then base.
            */
            {
                try {
                    throw myexception();
                } catch (myexception& ex) {
                } catch (std::exception& ex) {
                    assert(false);
                } catch (...) {
                    assert(false);
                }
            }
        }

        /*
        # what

            Returns a string which contains information about the exception.

            Many stdlib exceptions simply return the error message given on the constructor.
        */
        {
            std::string msg = "custom message";
            std::ios_base::failure e(msg);
            assert(e.what() == msg);
        }

        /*
        # uncaught exceptions.

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
        # exception specifications

            Functions can specify which exceptions are catchable with the following syntax.
        */
        {
            try {
                exception_func_int_only(true);
            } catch (int i) {
            } catch (...) {
                assert(false);
            }

            try {
                //exception_func_int_only(false);
            } catch (...) {
                /* not even ... this can catch non int exceptions thrown by this function */
            }

            try {
                exception_func_int_exception_only(1);
            } catch (int i) {
            } catch (myexception& ex) {
            } catch (...) {
                assert(false);
            }

            try {
                //exception_func_none();
            } catch (...) {
                /* no exception thrown by this function is catchable */
            }

            try {
                //exception_func_none_wrapper();
            } catch (...) {
                /* the same goes if we wrap the function */
            }
        }

        /*
        # exception from destructor

            Never throw an exception from a destructor.

            Destructors are meant to clean up after exceptions, so if you throw exceptions from them,
            things get messy.

            C++ specifies that if this happens during stack unwinding, the program may terminate!

            What to do to avoid that: <http://stackoverflow.com/questions/130117/throwing-exceptions-out-of-a-destructor>

            The following code could lead to that.
        */
        if (0) {
            try {
                ExceptionDestructor e;
            } catch (...) {
            }

            try {
                ExceptionDestructorCaller();
            } catch (...) {
            }
        }

#if __cplusplus >= 201103L
        /*
        # noexcept

            Improved version of `throw` for functions.

            `throw` for functions becomes deprecated in C++11.

            TODO
        */
        {
        }
#endif
    }

    // # class
    {
#if __cplusplus >= 201103L
        /*
        define class inside function
        */
        {
            // As of C++11, classes can be defined inside functions!
            // This matches the behaviour for structs in C.
            {
                class C {};
            }

            // Template classes however cannot be defined in functions.
            // Just think what should the compiler do in this case?
            {
                //template<class T> class C {};
            }
        }
#endif

        /*
        # Constructor

            Called whenever object is created to initialize the object.
        */
        {
            /*
            # Default constructors

                <http://en.cppreference.com/w/cpp/language/default_constructor>

                Constructor that takes no arguments.

                Can be one explicitly created by the programmer:
                all that matters is that it takes no arguments.

                It is a good idea to always implement a default constructor,
                since this is the only way arrays of fixed numbers of objects can be created before C++03

                The concept of default constructor exists because there are
                certain differences in syntax and behaviour when using default constructors,
                for example:

                - the most vexing parse only happens for default constructors.
                - the default constructor can be is implicitly declared and defiend by the compiler.

            # Implicily declared constructors

                If no explicit constructor is declared,
                the compiler automatically declares the following functions:

                - default constructor
                - copy constructor
                - assignment constructor
                - destructor

                If any constructor is explicitly declared, even one taking multiple default args,
                then *none* of the implicitly declared constructors are declared: that must be done manually.

            # Trivial default constructor

            # Implicily defined default constructor

                If the implicitly-declared default constructor is not deleted
                or trivial, it is defined (that is, a function body is generated
                and compiled) by the compiler, and it has exactly the same effect
                as a user-defined constructor with empty body and empty initializer list.
                That is, it calls the default constructors of the bases
                and of the non-static members of this class.

                In particular, the IDDC does not do zero initialization on non-class members
                such as `int`, so those have undefined values.
            */
            {
                // To call the default constructor, use this syntax
                {
                    callStack.clear();
                    NoBaseNoMember c; //default constructor was called!
                    std::vector<std::string> expectedCallStack = {
                        "NoBaseNoMember::NoBaseNoMember()",
                    };
                    assert(callStack == expectedCallStack);
                }

                /*
                The implicitly defined default constructor does not necessarily initialize member built-in types:
                http://stackoverflow.com/questions/2417065/does-the-default-constructor-initialize-built-in-types

                Class member default constructors however are called.
                */
                {
                    ImplicitDefaultCtor o;
                    if (o.i != 0)
                        // undefined behaviour.
                        std::cout << "ImplicitDefaultCtor undefined behaviour: o.i = " << o.i << std::endl;

                    // Defined behaviour because class:
                    assert(o.s == "");

                    // *however*, the following does value initialization,
                    // not the default constructor, and built-in members are indeed 0 initialized!
                    {
                        ImplicitDefaultCtor o = ImplicitDefaultCtor();
                        assert(o.i == 0);
                    }
                }

                {
                    // ERROR:
                    //NoDefaultCtor o;

                    // ERROR cannot be done because this class has not default constructors.
                    //NoDefaultCtor os[2];

                    // Implicit copy and assign are still defined:
                    NoDefaultCtor o(1);
                    NoDefaultCtor o2(o);
                    o = o2;
                }

#if __cplusplus >= 201103L
                /*
                # Default keyword

                    As of C++11, the `= default` statement can be added to a constructor to explicitly
                    say that the default should be used.

                    This allows a class to have multple constructors,
                    plus the implictly defined one.
                */
                {
                    DefaultKeyword o;
                    //assert(o.i == 0); // undefined behaviour
                    assert(o.s == std::string());

                    o = DefaultKeyword(1, "a");
                    assert(o.i == 1);
                    assert(o.s == "a");
                }

                /*
                # Delete keyword
                */
                {
                    // ERROR: Explicitly deleted:
                    //DeleteKeyword o;

                    DeleteKeyword o(1);

                    // ERROR: Explicitly deleted:
                    //DeleteKeyword o2(o);

                    DeleteKeyword o2(2);

                    // ERROR: Explicitly deleted:
                    //o2 = o1;
                }
#endif
            }

            /*
            # Most vexing parse

                Default constructor vs function declaration syntax gotcha!

                <http://stackoverflow.com/questions/180172/default-constructor-with-empty-brackets>
            */
            {
                /*
                BAD

                Declares *FUNCTION* called `c` that returns `Class` inside function main.

                This is the same as in C, where it is possible to declare a function from inside another function,
                but not define it.

                Therefore there would be not way for C++ to distinguish between the two,
                and still be backwards compatible with C.
                */
                {
                    Class c();

                    // ERROR: function definition is not possible inside another function.

                        //Class c() {return Class();}

                    //c.i;
                }

                // If you want to call a default constructor, use:
                {
                    Class c;
                    assert(c.i == 0);
                }

                /*
                For non-default constructors, things work as expected,
                as this syntax could not possibly be a function declaration.
                */
                {
                    Class c(1);
                    assert(c.i == 1);
                }
            }

            /*
            Value initialization and zero initialization are both a bit subtle, so it is best not to rely on them.

            # value initialization

                <http://en.cppreference.com/w/cpp/language/value_initialization>

            # aggregate initialization

                <http://en.cppreference.com/w/cpp/language/aggregate_initialization>

            # POD

                Plain old data:

                <http://stackoverflow.com/questions/4178175/what-are-aggregates-and-pods-and-how-why-are-they-special>

            # zero initialization

                <http://en.cppreference.com/w/cpp/language/zero_initialization>

                <http://stackoverflow.com/questions/1613341/what-do-the-following-phrases-mean-in-c-zero-default-and-value-initializat>
            */
            {
                // Syntax with new.
                {
                    // Base types.
                    {
                        int* is = new int[2]();
                        assert(is[0] == 0);
                        assert(is[1] == 0);
                        delete[] is;
                    }

                    // Works for structs.
                    {
                        struct T {int a;};
                        T *t = new T[1]();
                        assert(t[0].a == 0);
                        delete[] t;
                    }

                    /*
                    Works for objects.

                    Note how the default constructor was called since `z == 1`.
                    */
                    {
                        {
                            Class *cs = new Class[1]();
                            assert(cs[0].i == 0);
                            assert(cs[0].z == 1);
                            delete[] cs;
                        }
                    }

                    // But only works with default constructors.
                    {
                        //Class *cs = new [1](1);
                    }
                }
            }

            /*
            # initialize built-in types

                <http://stackoverflow.com/questions/5113365/do-built-in-types-have-default-constructors>

                C++ adds new ways to initialize base types.

                Those are not however constructors.

                They probably just mimic constructor syntax to help blurr the distinction
                between built-in types and classes.
            */
            {
                // Parenthesis initialization
                {
                    int i(1);
                    assert(i == 1);
                }

                {
                    // Most vexing parse.
                    //int i();
                }

                {
                    int i = int();
                    assert(i == 0);
                }

#if __cplusplus >= 201103L
                /*
                # Brace initialization of scalars

                    See uniform initialization.

                    <http://stackoverflow.com/questions/14232184/initializing-scalars-with-braces>

                # Uniform initialization

                    In c++11 every type can be initialized consistently with `{}`.

                    Advantages:

                    - non verbose initialization of multiple structures
                    - reduces syntax barriers between objects and built-in classes.

                    Disadvantages:

                    - ambiguous with initializer list construction!
                    - implementing the initializer list constructor breaks client code?!
                        because it has priority over other constructors.
                */
                {
                    // Built-int types
                    {
                        int i{1};
                        assert(i == 1);

                        // ERROR: narrowing conversion from double to int not allowed inside `{}`
                        // this is the main difference between `{}` and `()` and `=`.

                            //int iNarrow{1.5};

                        // Widening types is OK:

                            float f{1};

                        // Works for arrays.

                            int is[]{0, 1, 2};
                            assert(is[1] == 1);
                    }

                    // Objects.
                    {
                        // The 2 argument constructor is called.
                        {
                            {
                                UniformInitializationCtor2 o{1, 1};
                                assert(o.i == 1);
                                assert(o.j == 2);
                            }

                            // Conversion gets done for passing args to functions
                            {
                                UniformInitializationCtor2 o = {1, 1};
                                assert(o.i == 1);
                                assert(o.j == 2);

                                assert(UniformInitializationCtor2Func({1, 1}) == 3);

                                assert((o == UniformInitializationCtor2{1,1}));
                                assert((o.operator==({1,1})));
                                // ERROR: TODO why does this fail to compile?
                                //assert((o == {1,1}));
                            }
                        }

                        /*
                        If there is an initializer list ctor, the init list wins.

                        This is one inconvenient of using uniform initialization.

                        If ever an initializer list is created, it may breaks client code
                        that uses the other constructor.
                        */
                        {
                            UniformInitializationList o{1, 1};
                            assert(o.i == 1);
                            assert(o.j == 1);
                        }

                        // Application: initialize complex objects.
                        {
                            // With uniform init.
                            {
                                std::vector<std::pair<int,std::string> > v{
                                    {0, "zero"},
                                    {1, "one"},
                                    {2, "two"},
                                };

                                assert(v[0].second == "zero");
                            }

                            // Without uniform init. Slightly less readable don't you think?
                            {
                                std::vector<std::pair<int,std::string> > v{
                                    std::pair<int,std::string>(0, "zero"),
                                    std::pair<int,std::string>(1, "one"),
                                    std::pair<int,std::string>(2, "two"),
                                };
                            }
                        }

                        // TODO0 why are they different?
                        {
                            // Does this work because it is treated like a struct since it does not have constructors?
                            {
                                UniformInitializationImplicitCtor o{1, 2};
                                assert(o.i == 1);
                                assert(o.j == 2);
                            }

                            // ERROR.
                            {
                                //UniformInitializationExplicitCtor o = {1, 2};
                            }
                        }
                    }
                }
#endif
            }

#if __cplusplus >= 201103L
            // Call one constructor from constructor.
            {
                CtorFromCtor c(0,1);
                assert((c.v == std::vector<int>{0, 1}));
            }
#endif
        }

#if __cplusplus >= 201103L

        /*
        # brace enclosed initializer list

            See inializer list

        # list initialization

            See initializer list constructor.

        # initializer list contructor

            Useful in cases where you don't know beforehand how many arguments
            a constructor should receive.

            For example, the stdlib std::vector class gets an initializer list constructor on C++11,
            which allows one to initialize it to any constant.

            TODO0 could this not be achieved via cstdarg?
        */
        {
            //STL std::vector usage example
            {
                std::vector<int> v{0, 1};
                //std::vector<int> v = std::vector<int>({0, 1});
                    //SAME
                assert(v[0] == 0);
                assert(v[1] == 1);
                assert(v == std::vector<int>({0, 1}));
                assert((v == std::vector<int>{0, 1}));

                // Assignment also works via implicit conversion.
                v = {1, 0};
                assert((v == std::vector<int>{1, 0}));

                // ERROR: TODO why no implicit conversion is made?
                //assert((v == {0, 1}));
            }

            // How to implemente one.
            {
                {
                    InitializerListCtor o{0, 1};
                    assert((o.v == std::vector<int>{0, 1}));
                }

                // Initializer list constructor is called
                {
                    InitializerListCtor o{0, 0, 0, 0};
                    assert((o.v == std::vector<int>{0, 0, 0, 0}));
                }

                // 3 param constructor is called
                {
                    InitializerListCtor o(0, {0, 0,}, 0);
                    assert((o.v == std::vector<int>{1, 0, 0, -1}));
                }
            }

            /*
            auto rule: brace initializer can be bound to auto

            This means that for loop work

            http://en.cppreference.com/w/cpp/utility/initializer_list
            */
            {
                {
                    auto l{0, 1, 2};
                    // SAME:
                    //initializer_list<int> l{0, 1, 2};
                    assert(l.size() == 3);
                    assert(*l.begin() == 0);
                }

                // The rule for auto makes this ranged for work.
                // TODO0 why here? I see an `int`, not an `auto`
                int i = 0;
                for (int x : {0, 1, 2}) {
                    assert(x == i);
                    i++;
                }
            }
        }
#endif

        /*
        # destructor

            Called when:

            1) statically allocated object goes out of scope
            2) dynamically allocated object gets deleted

            Major application:

            - delocate dynamic memory that was allocated on constructor

            Virtual: not necessary *but* almost always what you want a polymorphic class
            to which there will be pointers to base classes.
        */
        {
            callStack.clear();

            {
                NoBaseNoMember b;
            } //destructor is called now!

            std::vector<std::string> expectedCallStack = {
                "NoBaseNoMember::NoBaseNoMember()",
                "NoBaseNoMember::~NoBaseNoMember()"
            };
            assert(callStack == expectedCallStack);
        }

        // # array of objects
        {
            // Default constructor is called when array is created.
            {
                callStack.clear();
                NoBaseNoMember os[2]; //default constructor called
                std::vector<std::string> expectedCallStack = {
                    "NoBaseNoMember::NoBaseNoMember()",
                    "NoBaseNoMember::NoBaseNoMember()",
                };
                assert(callStack == expectedCallStack);
            }

            /*
            To initialize the objects with a non default constructor
            one possibility is to use simply use assignment for each item.

            The downside of this method is that constructors are called twice
            for each array element.
            */
            {
                callStack.clear();

                NoBaseNoMember os[2]; //default constructor called
                os[0] = NoBaseNoMember(0);
                os[1] = NoBaseNoMember(1);

                std::vector<std::string> expectedCallStack{
                    "NoBaseNoMember::NoBaseNoMember()",
                    "NoBaseNoMember::NoBaseNoMember()",
                    "NoBaseNoMember::NoBaseNoMember(int)",
                    "NoBaseNoMember::~NoBaseNoMember()",
                    "NoBaseNoMember::NoBaseNoMember(int)",
                    "NoBaseNoMember::~NoBaseNoMember()",
                };
                //assert(callStack == expectedCallStack);
            }

            /*
            Faster because does not call default constructors and extra destructors.
            */
            {
                callStack.clear();

                NoBaseNoMember os[] = {NoBaseNoMember(0), NoBaseNoMember(1)};

                std::vector<std::string> expectedCallStack = {
                    "NoBaseNoMember::NoBaseNoMember(int)",
                    "NoBaseNoMember::NoBaseNoMember(int)",
                };
                assert(callStack == expectedCallStack);
            }

            /*
            If constructors take a single argument, conversions are made explicitly,
            and we can write even less useless code.
            */
            {
                NoBaseNoMember os[] = {0, 1};
            }

            /*
            In C++11, it is also possible to initialize objects that take more than two arguments
            via uniform initialization.
            */
            {
                Class cs[] = {{0, 1}, {2, 3}};
            }

            /*
            # memset

                Like many C functions, memset does not work with objects, because objects
                may contain extra data such as a VTABLE.
            */
            if (0) {
                Class *var = new Class;
                std::memset(var, 0, sizeof(Class));
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

            std::vector<std::string> expectedCallStack =
            {
                "NoBaseNoMember0::NoBaseNoMember0()",
                "NoBaseNoMember1::NoBaseNoMember1()",
                "MemberConstructorTest::MemberConstructorTest()",
                "MemberConstructorTest::~MemberConstructorTest()",
                "NoBaseNoMember1::~NoBaseNoMember1()",
                "NoBaseNoMember0::~NoBaseNoMember0()",
            };
            assert(callStack == expectedCallStack);
        }

        // # static fields
        {
            {
                Class c, c1;
                int i;
                c.iStatic = 0;
                assert(Class::iStatic == 0);
                c1.iStatic = 1;
                assert(Class::iStatic == 1);
                Class::iStatic = 2;
                assert(Class::iStatic == 2);
            }

            {
                Class c;
                c.staticMethod();
                Class::staticMethod();
            }
        }

        /*
        # temporary objects

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

                std::vector<std::string> expectedCallStack =
                {
                    "NoBaseNoMember::NoBaseNoMember()",
                    "NoBaseNoMember::NoBaseNoMember()",
                    "NoBaseNoMember::operator=",
                    "NoBaseNoMember::~NoBaseNoMember()",
                };
                assert(callStack == expectedCallStack);
            }

            /*
            Methods of temporaries can be called.

            Constructor and destructor are called, so this is not very efficient,
            and a static method would probably be better in this case.
            */
            {
                callStack.clear();
                NoBaseNoMember().method();
                std::vector<std::string> expectedCallStack =
                {
                    "NoBaseNoMember::NoBaseNoMember()",
                    "NoBaseNoMember::method()",
                    "NoBaseNoMember::~NoBaseNoMember()",
                };
                assert(callStack == expectedCallStack);
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
                NoBaseNoMember::temporaryReference(b);
                //NoBaseNoMember::temporaryReference(NoBaseNoMember());
                NoBaseNoMember::temporaryReferenceConst(NoBaseNoMember());
            }
        }

        /*
        # copy and assign constructors

            The difference is that:

            - copy is a way to initialize a new object
            - assign is a way to modify an existing object to ressemble another

            The implicitly defined constructors might not do what you want, specially when you
            allocate memory inside the constructor! See the Rule of Three.

            Implicilty Default copy and assign is probably exist in order to allow class parameter passing to functions.

            - <http://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom>
            - <http://stackoverflow.com/questions/4172722/what-is-the-rule-of-three>
        */
        {
            //every class has a default copy operator and assign constructor
            {
                DefaultCopyAssignCtor c0(0);
                DefaultCopyAssignCtor c1(1);

                //assign operator
                c0 = c1;
                assert(c0.i == c1.i);

                //copy constructor
                DefaultCopyAssignCtor c2(c0);
                assert(c2.i == c0.i);

                //there are still two separate copies of the object
                c0.i = 0;
                c1.i = 1;
                assert(c0.i == 0);
            }

            // # copy constructor
            {
                NoBaseNoMember c(1);

                //explicity copy notation
                {
                    callStack.clear();
                    NoBaseNoMember c1(c);
                    std::vector<std::string> expectedCallStack =
                    {
                        "NoBaseNoMember::NoBaseNoMember(NoBaseNoMember)",
                    };
                    assert(callStack == expectedCallStack);
                    assert(c1.i == 1);
                }

                /*
                Same as above.

                *COPY CONSTRUCTOR CALLED, NOT ASSIGN CONSTRUCTOR*
                because object is being created

                On C++11, move constructor will be called if rhs is a rvalue.
                */
                {
                    callStack.clear();
                    NoBaseNoMember c1 = c;
                    std::vector<std::string> expectedCallStack =
                    {
                        "NoBaseNoMember::NoBaseNoMember(NoBaseNoMember)",
                    };
                    assert(callStack == expectedCallStack);
                    assert(c1.i == 1);
                }
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
                assert(b.i == 1);
            }

            /*
            # equality operator for classes

                There is no default `==` operator for classes.

                You must define your own.
            */
            {
                NoEquality c0;
                NoEquality c1;

                //ERROR no match for operator ==
                    //assert(c0 == c1);
            }

            /*
            # rule of three

                If you need to implement either of (to deal with dynamic allocation):

                - destructor
                - assignment =
                - copy constructor

                It is likely that you need to implement all the three.

                In that case, you should use the copy and swap idiom.
            */

            /*
            # copy and swap idom

                The best way to implement the rule of three:

                - without code duplication
                - with exception type safety

                Great explanation: <http://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom>

                Why swap should be afriend: <http://stackoverflow.com/questions/5695548/public-friend-swap-member-function>
            */
            {
                CopyAndSwap c0(2, 2);
                CopyAndSwap c1(3, 3);

                //assign
                //c0 = c1;
                //assert(c0);

                //assign
                //CopyAndSwap c2(c0);
            }

#if __cplusplus >= 201103L
            /*
            # #rvalue reference

                <http://www.artima.com/cppsource/rvalue.html>

                C++11

                New type of reference.

                Old references are referred to as lvalue references, since they must be initialized by lvaues.

                Denoted by double ampersand `&&`.

                There is one difference between them and lvalue references:
                rvalue references can only be initialized by both rvalues,
                unlike lvalue references which can only be initialized by lvalues
                (except if they are const).

                Main motivation: implement move semantics.
            */
            {

                /*
                Cannot be bound to an lvalue on stack.

                This is the *key* property of rvalue references, since it allows function overload
                to differentiate lvalues from rvalues, and thus implement move contructors.
                */
                {
                    int i = 0;

                    int&& irr = 1;

                    // ERROR: i is not rvalue, it is a lvalue!
                    //int&& irrBad = i;
                }

                // On all other aspects besides initialization, rvalue references
                // are identical to lvalue references.
                {
                    int&& irr = 0;
                    assert(irr == 0);

                    irr = 1;
                    assert(irr == 1);

                    //once assigned, rvalue references are iden
                    std::cout << "&iff = " << &irr << std::endl;
                }

                // Can function overload based on rvalue or lvalue.
                // This is essential for move semantics.
                {
                    int i;
                    assert(overloadRLvalue(i) == "lval");
                    assert(overloadRLvalue(1) == "rval");
                }
            }

            /*
            # xvalue

            # glvalue

            # prvalue

                In addition to the C99 rvalues and lvalues,
                the C++11 standard defines new concepts:

                - xvalue
                - glvalue
                - prvalue

                <http://stackoverflow.com/questions/3601602/what-are-rvalues-lvalues-xvalues-glvalues-and-prvalues>

                This is probably a consequence of move semantincs.

            */

            /*
            # move constructor

                Constructor that takes rvalues instead of lvalues.

                Used to implement move semantics.

            # move semantics

                Useful in situtations where a class manages dynamic data.

                Basic idea: when copying from an rvalue, it is not necessary to make an expensive copy of it:
                it suffices to acquire its data via swap, and leave it on a valid state (via a default constructor for example).

                This is true because the rvalue passed to a copy constructor cannot be seen.

                Value reference allows to overload the copy constructor based not on type,
                but on the fact that a value is an rvalue or an lvalue!

                No change must be done to the copy and swap idiom for move semantics to work for the assigment operator,
                since in C++11 `int i = rvale` calls a move consttuctor on `i` while `int i = lvalue` calls a copy constructor.

                <http://stackoverflow.com/questions/3106110/what-is-move-semantics>
            */
            {
            }
#endif

            /*
            # as-if rule

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
            # copy elision

                <http://en.cppreference.com/w/cpp/language/copy_elision>
                <http://stackoverflow.com/questions/12953127/what-are-copy-elision-and-return-value-optimization>

                Exceptions to the as-if rules, which specifies cases in which compilers
                may reduce the number of copy operations made, which is detectable in C++'
                because of possible side effects constructors and destructors (such as printing to stdout
                or modifying a global std::vector).
            */
            {
                /*
                # temporary copy ellision

                    If no copy elision is done:

                    1) temporary object constructor
                    2) copy temporary to c
                    3) temporary object destructor

                    If copy elision is done:

                    1) c is constructed directly.

                    Therefore both results are possible and the result is unpredictable:

                        std::vector<std::string> expectedCallStack = {
                            "NoBaseNoMember::NoBaseNoMember()",
                        };

                        std::vector<std::string> expectedCallStack = {
                            "NoBaseNoMember::NoBaseNoMember()",
                            "NoBaseNoMember::~NoBaseNoMember()",
                        };

                        assert(callStack == expectedCallStack);
                */
                {
                    {
                        callStack.clear();
                        NoBaseNoMember c = NoBaseNoMember();
                        std::cout << "temporary copy elision" << std::endl;
                        for (auto s : callStack) std::cout << "  " << s << std::endl;
                    }

                    {
                        callStack.clear();
                        NoBaseNoMember c;
                        c = NoBaseNoMember();
                        std::cout << "no temporary copy elision" << std::endl;
                        for (auto s : callStack) std::cout << "  " << s << std::endl;
                    }
                }

                /*
                # RVO

                    Return value optimization.

                    Like in C, when a function returns an object, the compiler adds a hidden pointer
                    to the function.

                    Ex: definition

                        static NoBaseNoMember create()
                        {
                            return NoBaseNoMember();
                        }

                    gets converted to:

                        static create(NoBaseNoMember* hiddenTemp)
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
                    for (auto s : callStack) std::cout << "  " << s << std::endl;
                }

                /*
                # NRVO

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
                        for (auto s : callStack) std::cout << "  " << s << std::endl;
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
                        for (auto s : callStack) std::cout << "  " << s << std::endl;
                    }
                }

                /*
                # exception copy elision
                */
                {
                }
            }
        }

        /*
        # Inheritance
        */
        {
            /*
            # Override

                Means to implement a method on the derived class, replacing the definition on the base class.
            */
            {
                Class c;
                Class* cp = &c;

                c.i = 0;
                c.Class::i = 0;
                cp->Class::i = 0;
                c.Base::i = 1;
                c.BaseAbstract::i = 2;

                assert(c.i          == 0);
                assert(c.Class::i   == 0);
                assert(cp->Class::i == 0);

                assert(c.Base::i   == 1);
                assert(cp->Base::i == 1);

                assert(c.BaseAbstract::i   == 2);
                assert(cp->BaseAbstract::i == 2);

                // ERROR: ambiguous
                //c.iAmbiguous = 0;
                c.Base::iAmbiguous = 0;
                c.BaseAbstract::iAmbiguous = 0;

                callStack.clear();
                c.method();
                assert(callStack.back() == "Class::method()");
                // ERROR: ambiguous
                //c.methodAmbiguous();
                callStack.clear();
                c.Base::methodAmbiguous();
                assert(callStack.back() == "Base::methodAmbiguous()");

                callStack.clear();
                c.BaseAbstract::methodAmbiguous();
                assert(callStack.back() == "BaseAbstract::methodAmbiguous()");
            }

            /*
            Inheritance and overloading.

            You cannot overload an inherited method directly

            http://stackoverflow.com/questions/72010/c-overload-resolution

            TODO why is that using required? What is the advantage?
            */
            {
                InheritOverloadDerived c;
                c.overload();
            }

#if __cplusplus >= 201103L
            /*
            # inheriting constructors

            Reuse base class constructors: <http://stackoverflow.com/questions/8093882/using-c-base-class-constructors>
            is possible "automatically" only in C++11 (using `using`).

            Before C++11, is was necessary to call each constructor explicitly and forward the argments.

            Only implemented in G++ 4.8. -std=c++11 flag available since G++ 4.7.
            */
            {
                InheritingCtorDerived c0;
                assert(c0.i == 0);
                InheritingCtorDerived c1(1);
                InheritingCtorDerived c2(c0);
            }
#endif

            /*
            # virtual

                Virtual: decides on runtime based on object type.

                <http://stackoverflow.com/questions/2391679/can-someone-explain-c-virtual-methods>

            # Pure virtual function

                Cannot instantiate this class

                Can only instantiate derived classes that implement this.

                If a class has a pure virtual method is called as an *abstract class* or *interface*.

                In Java there is a language difference between those two terms,
                and it might be a good idea to differentiate them when speaking about C++:

                - interface: no data
                - abstract: data

            # Polymorphism

                - loop an array of several dereived classes
                - call a single base class method
                - uses the correct derived override

                Implementation: *vtable* is used to implement this.

            # vtable

                <http://en.wikipedia.org/wiki/Virtual_method_table>

                Whenever you create a pointer to a class with a virtual method,
                that pointer points to a pointer that identifies the class type,
                and points to the correct method.

                Consequence: every call to a virtual methods means:

                - an extra pointer dereference
                - an extra pointer stored in memory

                Also virtual functions cannot be inlined.

            # Static interfaces

                It is possible to assert that interfaces are implemented without dynamic vtable overhead via CRTP:

                - <http://stackoverflow.com/questions/2587541/does-c-have-a-static-polymorphism-implementation-of-interface-that-does-not-us>

                - <http://en.wikipedia.org/wiki/Template_metaprogramming#Static_polymorphism>

            # CRTP

                Curiously recurring template pattern.

                <http://en.wikipedia.org/wiki/Curiously_recurring_template_pattern#Static_polymorphism>
            */
            {
                // ERROR: BaseAbstract cannot be instantiated because it contains a pure virtual method
                // virtual = 0;. That method must be implemented on derived classes
                //BaseAbstract b;

                // Even if you can't instantiate base, you can have pointers to it.
                {
                    BaseAbstract* bap = new Class;
                    // SAME:
                    //BaseAbstract* bap = &c;

                    callStack.clear();
                    bap->method();
                    // Base method because non-virtual.
                    assert(callStack.back() == "BaseAbstract::method()");

                    callStack.clear();
                    bap->virtualMethod();
                    // Class method because virtual.
                    assert(callStack.back() == "Class::virtualMethod()");

                    delete bap;
                }

                // You can also have BaseAbstract&.
                {
                    Class c;
                    BaseAbstract& ba = c;

                    callStack.clear();
                    ba.method();
                    assert(callStack.back() == "BaseAbstract::method()");

                    callStack.clear();
                    ba.virtualMethod();
                    assert(callStack.back() == "Class::virtualMethod()");
                }

                {
                    Class c = Class();
                    Base* bp = &c;
                    bp = bp->covariantReturn();

                    callStack.clear();
                    bp->virtualMethod();
                    assert(callStack.back() == "Class::virtualMethod()");

                    // ERROR: conversion from Base to Class
                    //classPtr = basePtr->covariantReturn();
                }

                /*
                It is not possibleto implement pure virtual methods on another base class:
                they must be implemented on the Derived class.
                */
                {
                    //DerivedAbtractAndImplementator d; //ERROR
                }

                // Call virtual method from base constructor: http://stackoverflow.com/questions/496440/c-virtual-function-from-constructor?lq=1
                // Not possible because derived class has not yet been initialized.
                // Workaround? http://www.parashift.com/c%2B%2B-faq-lite/calling-virtuals-from-ctor-idiom.html
                {
                    {
                        VirtualFromCtorDerived c;
                        assert(c.i == 0);
                    }

                    // The simplest thing to do seems to be to define a separate init function.
                    // Downside: requires you to write a new constructor on the derived, and forward all argments.
                    {
                        VirtualFromCtor2PhaseDerived c;
                        assert(c.i == 1);
                        assert(c.j == 10);
                    }
                }
            }

            /*
            # multiple inheritance

                In C++, if a member of an object or static variable of a class
                comes from two base classes, an ambiguity occurs and the program does not
                compile.

                This just makes multiple inheritance very insane, since the addition of
                new fields in a Base class can break existing code on Derived classes.
            */
            {
                //MultipleInheritanceConflictDerived::is;
                //MultipleInheritanceConflictDerived().i;
                //MultipleInheritanceConflictDerived().f();
            }

            /*
            # dreaded diamond

            # virtual inheritance

                Solves the dreaded diamond problem.

                Has nothing to do with the `virtual` keyword for methods:
                everything is done at compile time in this usage.

                <http://stackoverflow.com/questions/21558/in-c-what-is-a-virtual-base-class>
            */
        }

        // # friend
        {
            Friend f(1);
            FriendOfFriend ff(2);

            assert(friendGetI(f)               == f.getI());
            assert(friendGetIInnerDefine(f)    == f.getI());
            assert(ff.getFriendI(f)            == f.getI());
        }

        // # nested classes
        {
            Base::Nested baseNested;
            Base::Nested2 baseNested2;
        }

        // # nested typedefs
        {
            Base::NESTED_INT i = 1;
            // ERROR: is private
            //Base::PRIVATE_NESTED_INT j = 1;
        }
    }

    /*
    # struct

        Structs in C++ are very similar to classes: support access modifiers,
        inheritance, constructors, templates, etc.

        The major difference between them is that the default access modifier for structs
        is public, while for classes it is private.

        This is why structs are used on many simple short language examples:
        no public line is needed.

        The Google C++ style guide recommends using struct only if there is no constructors,
        and classes otherwise.

        <http://stackoverflow.com/questions/2750270/c-c-struct-vs-class>
    */
    {
        struct DerivedStruct s(1);
        assert(s.i == 1);
    }

    /*
    # RTTI

        Run time type information.

        Any function that gets class information explicitly at runtime:

        - `typeid`
        - `dynamic_cast`

        Google style 3.26 discourages this, since if you really need it your design is probably flawed.

        Also using typeid on variables means that extra meta data must be kept about those variables.
    */

    /*
    # typeid

        Get type of variables

        Can be done for both types and variables of the type.

        Returns objects of `type_info`

    # type_info

        Type returned by `typeid`.
    */
    {
        // typeid returns `type_info`.
        //
        // However copy and assign for type_info are private,
        // so the following fails.
        {
            //std::type_info t = typeid(int);
            //std::type_info t(typeid(int));
        }

        // type_info implements `==` and `!=`.
        //
        // typeid's of different types are always different.
        {
            int i, i1;
            int& ia = i;
            Class c;

            assert(typeid(i)  == typeid(int) );
            assert(typeid(ia) == typeid(int&));
            assert(typeid(i)  == typeid(i1)  );
            assert(typeid(i)  != typeid(c)   );
        }

        // name: returns a string representation of the type.
        //
        // The exact string is implementation defined.
        {
            std::cout << "typeid(int).name() = " << typeid(int).name() << std::endl;
        }

        // before: <http://stackoverflow.com/questions/8682582/what-is-type-infobefore-useful-for>
        // hash_code: return a size_t hash of the type
    }

    /*
    # type_index

        Wrapper around type_info that allows copy and assign.
    */
    {
        std::type_index t = typeid(int);
    }

    /*
    # type_traits

        <http://www.cplusplus.com/reference/type_traits/>
    */
    {
    }

    /*
    # typecast

        Sources:

        - <http://www.cplusplus.com/doc/tutorial/typecasting/>
        - <http://stackoverflow.com/questions/28002/regular-cast-vs-static-cast-vs-dynamic-cast>
        - <http://stackoverflow.com/questions/332030/when-should-static-cast-dynamic-cast-and-reinterpret-cast-be-used>
    */
    {
        /*
        Implicit typecast.

        Works if types are convertible, either by the compiler or by a constructor that takes one single argument.
        */
        {
            //convertible basetypes
            //same as in C
            {
                int i = 0.25;
                assert(i == 0);
            }

            //via constructor that takes a single argument and is not explicit
            //works becaues the constructor NoBaseNoMember(int) exists
            {
                NoBaseNoMember c = 1;
                assert(c.i == 1);
            }

            /*
            # explicit

                Keyword specifies that a given constructor can only be used explicitly.
            */
            {
                // ERROR:
                //ExplicitCtor c = 1;
            }
        }

        /*
        # explicit typecast
        */
        {
            /*
            # c style typecast

                TODO what does it do in relation to the others? why should it not be used?
            */

            /*
            # dynamic_cast

                - done at runtime
                - only for pointers or references
                - can only be done from / to base derived

                    - always works for derived to base

                    - baes to derived:

                        - compiles only for polymorphic classes

                        - a runtime check is done to see if the cast is correct or an exception is thrown
            */
            {
            }

            /*
            # static_cast

                - done at compile time
                - only for pointers or references
                - can only be done from / to base derived.

                    Always compiles, but if the conversion is wrong, bad errors may happen at runtime.
            */

            /*
            # reinterpret_cast

                Converts anything to anything by copying bytes.

                Behaviour is not portable in general.
            */

            /*
            # const_cast

                Change (add/remove) constantness and volatility of objects (property called cv-qualification).

                TODO when should it be used?

                <http://stackoverflow.com/questions/357600/is-const-cast-safe/357640#357640>
            */
            {
                //remove const
                {
                    const int i = 0;
                    int const * ip = &i;

                    *const_cast<int*>(ip) = 1;
                    //assert(i == 1);
                        //TODO why fail?

                }

                // ERROR: Returns rvalues. Therefore cannot initialize non-const references.
                {
                    int i = 0;
                    int *ip;
                    //const int*& ipa = const_cast<const int*>(ip);
                        //ipa is a non const reference.
                        //int *const& would be a const reference.
                }

                // ERROR: only has effect for a single statement
                {
                    //const_cast<int*>(ip);
                    //*ip = 1;
                }

                // ERROR: only works for pointers
                {
                    const int i = 0;
                    //const_cast<int>(i) = 1;
                }
            }

            // Function pointer typecast.
            {
                // Required when a function is overloaded, and you want to use a function pointer.
                // TODO understand syntax.
                {
                    std::string s = "a,bc. d";
                    auto end = s.end();
                    s.erase(std::remove_if(s.begin(), end, (int(*)(int))std::ispunct), end);
                    std::cout << s << std::endl;
                    assert(s == "abc d");
                }
            }
        }
    }

    /*
    # dynamic memory

        C++ replaces C's malloc and free with new and delete.

        It is very rare to need explicit dynamic allocation. Always use:

            std::vector<int> is(n)

        instead of:

            int *is = new int[n];

        and `vector<int>(n)` is as efficient and much more flexible than `new int[N]`.

        Dynamic allocation is a dangerous, and it may lead to hard to debug memory leaks.

        Always encapsulate dynamic allocation inside class constructors,
        and free it the destructor, like `std::vector` does.

        Never use C style malloc on C++ code. `new` works better with classes.

    # new

        Allocate dynamic memory.

        Throw `std::bad_alloc` in case of error.

    # realloc

        There is no direct replacement to realloc or calloc as of C++11
        <http://stackoverflow.com/questions/3482941/how-do-you-realloc-in-c>
    */
    {
        /*
        basic usage with proper error checking
        */
        {
            int* ip;
            try {
                ip = new int[5];
            } catch(std::bad_alloc& ba) {
                assert(false);
            }
            ip[0] = 1;
            delete[] ip;
        }

        /*
        # delete

            Free memory allocatedby `new`.

            Just like C `free`:

            - deleting a `NULL` does nothing.
            - deleting any other pointer twice can lead to memory corruption
            - deleting a pointer which was not dynamically allocated can lead to memory curruption

            Destructor of object pointed to is called.

            A common technique is to set a pointer to `NULL` after it is deleted,
            to avoid deleting a pointer twice:
            <stackoverflow.com/questions/4190703/is-it-safe-to-delete-a-null-pointer>

            An even better techinque may be to use smart pointers and containers.
        */
        {
            delete (int*)NULL;
            delete[] (int*)NULL;

            //delete NULL;
            // WARN: cannot delete an integer type

            //delete (void*)NULL;
            // WARN: cannot delete a void pointer
        }

        //allocate single object / base type
        {
            int* ip = new int;
            *ip = 1;
            delete ip;
        }

        //delete calls destructors of deleted objects
        {
            callStack.clear();
            NoBaseNoMember* cp = new NoBaseNoMember;
            //NoBaseNoMember* cp = new NoBaseNoMember();
                //SAME
            assert(callStack.back() == "NoBaseNoMember::NoBaseNoMember()");

            cp->method();

            callStack.clear();
            delete cp;
            assert(callStack.back() == "NoBaseNoMember::~NoBaseNoMember()");
                //calls destructor
        }

        {
            callStack.clear();
            NoBaseNoMember* cp = new NoBaseNoMember[2];
            assert(callStack.back() == "NoBaseNoMember::NoBaseNoMember()"); callStack.pop_back();
            assert(callStack.back() == "NoBaseNoMember::NoBaseNoMember()"); callStack.pop_back();

            cp[0].method();
            cp[1].method();

            callStack.clear();
            delete[] cp;
            assert(callStack.back() == "NoBaseNoMember::~NoBaseNoMember()"); callStack.pop_back();
            assert(callStack.back() == "NoBaseNoMember::~NoBaseNoMember()"); callStack.pop_back();
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
        # calloc

            An analogue effect to calloc can be attained with *value-initialization*.

            <http://stackoverflow.com/questions/808464/c-new-call-that-behaves-like-calloc>
        */
    }

    /*
    # namespace
    */
    {
        //variables
        {
            int i;
            i = 0;          //inner  i
            ::i = 0;        //global i
            namea::i = 0;   //namea  i
            i++;
            assert(i        == 1);
            assert(::i      == 0);
            assert(namea::i == 0);

            f();
            namea::f();
            namea::nameaa::f();
        }

        /*
        # using

            Be very careful with `using`, because there is no way to unuse afterwards.

            In particuar, *never* use `using namespace X` on the toplevel a header file,
            or you shall confuse includers to tears.
        */
        {
            using namespace namea;

            // ERROR ambiguous
            //f();
            //::f
            //namea::f

            ::f();
            namea::f();
            namea::nameaa::f();

        }

        //in_namea_only = 1;
            //brackets limit the using namespace scope
            //It is obligatory to specify unused namespaces.

        // ERROR: no namespace inside funcs
        //namespace main{}

        //namespace chaining
        {
            using namespace namea;
            using namespace nameaa;

            //f();
                // ERROR ambiguous
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
                // ERROR: ambiguous.
                //::f
                //namea::f
        }

        //subimport
        {
            // Imports only name::f.
            using namea::f;

            f();
                // OK: overwrides global f().
                //namea::f

            // ERROR: only f was imported.
            //C c;
        };

        /*
        # ADL

            Argument dependent name lookup.

            <http://en.wikipedia.org/wiki/Argument-dependent_name_lookup>

            Allows for functions without namespace qualification:

            - to be found
            - to haves ambiguities resolved

            based on the namespace in which the types of their arguments are defined.

            Explains why operator `<<` does not need the `std::` qualifier,
            even though *must* be implemented as a non-member function!!
            (see info on operator overload for why)

            ADL for operators is a major use case, because specifying namespaces
            for operators completely destroys their eyecandy appeal.
        */
        {
            // ADL allows both to be found and differentiated!
            {
                {
                    struct adl0::s s;
                    assert(adl(s) == 0);
                }

                {
                    struct adl1::s s;
                    assert(adl(s) == 1);
                }
            }

            // Only works if the type is defined on the same namespace as the function.
            {
                struct adl0::s s;
                // ERROR: not declared on this scope
                //assert(adl0FromAdl1(s) == 1);
            }

            // Works if at least one of the argument types is in the namespace.
            {
                struct adl0::s s;
                assert(adlMultiArg(0, s, 1) == 0);
            }

            // Lookup works even if types from both namespaces are used.
            {
                struct adl0::s s0;
                struct adl1::s s1;
                assert(adl0And1FromAdl1(s0, s1) == 1);
            }

            // Of course, calls can still be ambiguous.
            {
                struct adl0::s s0;
                struct adl1::s s1;
                // ERROR: ambiguous call
                //assert(adl01(s0, s1) == 0.5);
            }

            // Only works for *types* defined in the namespaces, not values.
            {
                //assert(adlNoType(adl0::i) == 0);
                // ERROR: adlNoType not found on this scope
                //assert(adlNoType(adl1::i) == 0);
            }
        }
    }

    // # stdlib
    {
        // # string
        {
            // Initialize from string literal.
            {
                std::string s = "abc";
            }

            // cout works as expected.
            {
                std::string s = "abc";
                std::stringstream oss;
                oss << s;
                assert(oss.str() == "abc");
            }

            /*
            # + for strings

            # cat

            # concatenate.

                Creates a new string.

                The only way to do inline this without creating a new string seems to be by using stringstream.
                http://stackoverflow.com/questions/662918/how-do-i-concatenate-multiple-c-strings-on-one-line
            */
            {
                std::string s = "ab";
                std::string s1 = "cd";
                assert(s + s1   == "abcd");
                assert(s + "cd" == "abcd");
                assert("cd" + s == "cdab");
            }

            // length
            {
                std::string s = "abc";
                assert(s.length() == 3);
            }

            {
                std::string s = "abc";
                s[0] = 'A';
                assert(s == "Abc");

                // BAD: no born check! Compiles.
                //s[3] = 'd';
            }

            /*
            # lowercase

                http://stackoverflow.com/questions/313970/stl-string-to-lower-case
            */
            {
                // Best stdlib way with transform:
                std::string s = "AbCd1_";
                std::transform(s.begin(), s.end(), s.begin(), ::tolower);
                assert(s == "abcd1_");

                //Boost has a single function: boost::algorithm::to_lower(str);
            }

            /*
            # c_str

                Convert std::string to C null terminated char* string.
            */
            {
                std::string s = "abc";
                assert((std::strcmp(s.c_str(), "abc")) == 0);
            }

            // # substring
            {
                std::string s = "abcde";
                assert(s.substr(1, 3) == "bcd");
            }

            // # Split at a character into array of strings.
            {
                // Best stdlib solution for any character: http://stackoverflow.com/questions/236129/how-to-split-a-string-in-c
                // There are shorters sstream solutions that split at whitespace.
                // For Boost it's a one liner.
                {
                    assert((split("01:23::45", ':') == std::vector<std::string>{"01", "23", "", "45"}));

                    std::vector<std::string> v;
                    split("01:23::45", ':', v);
                    assert((v == std::vector<std::string>{"01", "23", "", "45"}));
                }
            }

            /*
            # strip

            # chomp

            # trim

                Exact same techniques as removing elements from vectors but for characters.

                It's just that those operations are so common on strings...

                http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
            */
            {
                // A single character: remove and erase idiom.
                // Single remove_all call in Boost.
                {
                    std::string s = "a bc d";
                    auto end = s.end();
                    s.erase(std::remove(s.begin(), end, ' '), end);
                    assert((s == "abcd"));
                }

                // Any character in a string: remove_if + custom function. std::ispunct is a typical choice.
                // Single liner with boost::remove_if + is_any_of.
                {
                    std::string s = "a,bc. d";
                    auto end = s.end();
                    // stdc ispunct:
                    s.erase(std::remove_if(s.begin(), end, ::ispunct), end);
                    // stdlib ispunct. Fails without the cast.
                    //s.erase(std::remove_if(s.begin(), end, (int(*)(int))std::ispunct), end);
                    assert((s == "abc d"));
                }
            }

            /*
            # getline

                Read istream until a any given character, by default newline, and store chars read into a string.

                The other major method of getting data from streams is `operator<<`,
                which generaly speaking reads until whitespace. getline is generaly saner.

                Returns the stream itself, which allows to:

                - chain calls
                - do while(getline) combos, as streams can be converted to bool via the `void*()`
                    operator which returns a pointer type which is then converted to a boolean.
            */
            {
                // Up to newline.
                {
                    std::stringstream ss;
                    std::string s;
                    ss << "ab\n\nc";

                    // The delim is removed from the string.
                    assert(std::getline(ss, s));
                    assert(s == "ab");

                    // Empty
                    assert(std::getline(ss, s));
                    assert(s == "");

                    // No problem if end of stream.
                    assert(std::getline(ss, s));
                    assert(s == "c");

                    // Stream over.
                    assert(!std::getline(ss, s));
                }

                // The stream itself is returned.
                {
                    std::stringstream ss;
                    std::string s;
                    std::string s2;
                    ss << "ab\n\nc";
                    std::getline(std::getline(ss, s), s2);
                    assert(s == "ab");
                    assert(s2 == "");
                }

                // Up to custom char.
                {
                    std::stringstream ss;
                    std::string s;
                    ss << "ab::f";
                    std::getline(ss, s, ':');
                    assert(s == "ab");
                }

                // Read stream line-wise.
                {
                    std::stringstream ss;
                    std::string line;
                    std::vector<std::string> lines;
                    ss << "ab\n\nc";
                    while (getline(ss, line))
                        lines.push_back(line);
                    assert((lines == std::vector<std::string>{"ab", "", "c"}));
                }
            }

            /*
            # stringstream

            # basic_stringstream

                An iostream String backed implementation.

                The following is defined:

                    typedef basic_stringstream<char> stringstream;

                    typedef basic_stringstream<char>

                Very useful to test streams without creating files / stdin.
            */
            {
                std::stringstream oss("abcd");

                // str does not clear the std::stringstream object
                assert(oss.str() == "abcd");

                // To clear it you could do: http://stackoverflow.com/questions/20731/in-c-how-do-you-clear-a-stringstream-variable
                // Set to empty:
                oss.str("");
                // Clear flags. Very important, not only for error indicators but also for end of stream.
                oss.clear();
                assert(oss.str() == "");

                // ERROR: use of deleted function because the constructor is =delete.
                //oss = std::stringstream();
            }

            // Possible application: build up a huge string step by step.
            // May be more efficient than concatenations which always generates new objects.
            {
                std::stringstream oss;
                oss << "ab";
                oss << "cd";
                assert(oss.str() == "abcd");
            }

            /*
            # int to string

                There are a few standard alternatives.

                <http://stackoverflow.com/questions/5590381/easiest-way-to-convert-int-to-string-in-c>
            */
            {
                /*
                C++11 solves the question once and for all with a robust one-liner for base types.

                It is not intended however for class input.
                */
#if __cplusplus >= 201103L
                assert(std::to_string(123) == "123");
#endif

                /*
                std::stringstream seems to be the best pre C++11 solution.

                It also has the advantage of working for any class that implements `operator<<`.
                */
                {
                    std::stringstream oss;
                    oss << 123;
                    assert(oss.str() == "123");
                }

                /*
                C sprintf

                Works, but uses too many conversion operations.
                */
                {
                    char cs[16];
                    std::sprintf(cs, "%d", 123);
                    std::string s = (cs);
                    assert(s == "123");
                }
            }

            // #int to string
            // http://stackoverflow.com/questions/7663709/convert-string-to-int-c
            {
                // Best C++11 error checking option: stoi
#if __cplusplus >= 201103L
                assert(std::stoi("123") == 123);
#endif
            }
        }

        /*
        # io

            See cppref now: http://en.cppreference.com/w/cpp/io

            Take a good look at the inheritance tree.

            The following are defined:

                extern  istream  cin;   //standard input (stdin)
                extern wistream wcin;
                extern  ostream  cout;  //standard output (stdout)
                extern wostream wcout;
                extern  ostream  cerr;  //standard error (stderr)
                extern wostream wcerr;
                extern  ostream  clog;  //standard log (stdlog)
                extern wostream wclog;

            # istream #ostream

                Istream and ostream are IO interfaces.

                They have many implementations, backed by different types of data:

                - files
                - strings in memory

                The main methods of getting data out of streams are:

                - getline for linewise operations
                - operator << for word wise operations
                - read(char*, size_t). Reads a fixed number of characters into an array.

            # endl

                System dependent newline.

        */
        {
            /*
            # cout

                stdout.

                `ostream` object.

                For tests, std::stringstream shall be used as the results can then be tested,
                and the behaviour is identical to cout.

                `<<` is very magic. You need to understand:

                - operator overload
                - function template argument deduction
                - namespaces adl

                before really understanding why it works.

            # cerr

                Cout for stderr

            # clog

                By default also points to stderr, but can be redirected with TODO.
            */
            {
                std::cout << "cout" << std::endl;
                std::cerr << "cerr" << std::endl;
                std::clog << "clog" << std::endl;
            }

            /*
            # cin #stdin

                `istream` object.

                Avoid using it for similar reasons as scanf:

                - hard to handle invalid inputs
                - difficult to predict behaviour

                getline is the best option.
            */
            {
                //std::cout << "Enter an integer:" << endl;
                //std::cin >> i;
                //std::cout << i << std::endl;
            }

            // This is how a very explicit usage of `<<` would look like
            {
                std::stringstream ss;

                //TODO0 how to get his working?
                //std::operator<<<std::ostream,std::string>(ss, "explicit");

                std::operator<<(std::operator<<(ss, "explicit "), "call");
            }

            // #<< left shift overload
            {
            }

            // #>> right shift overload istream
            // Get input out of streams into string.
            // Overloaded for many different types of inputs: <http://www.cplusplus.com/reference/istream/istream/operator%3E%3E/>
            {
                // char*, std::string
                // - skip whitespace as defined by `isspace`.
                // - read until first whitespace found
                {
                    std::stringstream ss("ab cd\tef  \t\ngh i.;)j");
                    std::string s;
                    ss >> s;
                    assert(s == "ab");
                    ss >> s;
                    assert(s == "cd");
                    ss >> s;
                    assert(s == "ef");
                    ss >> s;
                    assert(s == "gh");
                    ss >> s;
                    assert(s == "i.;)j");
                }

                // Numeric types: int, float.
                // - skip whitespace as defined by `isspace`.
                // - read until cannot be part of the type anymore (TODO what does that mean exactly?)
                {
                    std::stringstream ss("1.0 2 \n \t 3.0f 4a a");
                    float f;
                    std::string s;
                    ss >> f;
                    assert(f == 1.0f);
                    ss >> f;
                    assert(f == 2.0f);
                    ss >> f;
                    assert(f == 3.0f);

                    // f suffix is not part of floats
                    ss >> s;
                    assert(s == "f");

                    ss >> f;
                    // TODO what happens? Error checking.
                }

                // Since `>>` returns the istream, it is possible to chain calls:
                {
                    std::stringstream ss("1 1.5 2");
                    int i, j;
                    float f;
                    ss >> i >> f >> j;
                    assert(i == 1);
                    assert(f == 1.5);
                    assert(j == 2);
                }
            }

            /*
            # printf format strings

                In C++ there is no more printf formatting strings: must use the C libs for that.

                It is possible however to obtain some level of formatting control with manipulators.

            # manipulators

                Allow to control the output format.
            */
            {
                /*
                # boolalpha

                    Control the format of boolean printing.

                    - on: print `true` or `false`
                    - no: print `1`    or `0` (default)

                    Mnemonic: if true use alpha chars. Else, use numeric chars.
                */
                {
                    std::stringstream ss;

                    ss << std::boolalpha << true;
                    assert(ss.str() == "true");
                    ss.str("");

                    ss << std::noboolalpha << true;
                    assert(ss.str() == "1");
                    ss.str("");

                    //default is noboolalpha
                    ss << true;
                    assert(ss.str() == "1");
                    ss.str("");
                }

                /*
                Once an options is eaten by the ostream, it stays as the default option.
                */
                {
                    std::stringstream ss;

                    ss << std::boolalpha;

                    ss << true;
                    assert(ss.str() == "true");
                    ss.str("");
                        //does not clear earlier passed options

                    ss << true;
                    assert(ss.str() == "true");
                    ss.str("");

                    ss << std::noboolalpha;

                    ss << true;
                    assert(ss.str() == "1");
                    ss.str("");
                }

                /*
                # width

                    Minimum number of chars to output.

                    If not enough, complete with fill.

                # fill

                    See width.

                # left right internal
                */
                {
                    std::stringstream ss;
                    int i = 12;

                    ss.width(4);
                    ss.fill(' ');

                    ss << std::left << i;
                    assert(ss.str() == "12  ");
                    ss.str("");

                    ss << std::right << i;
                    //assert(ss.str() == "  12");
                        //why fails?
                    ss.str("");
                }

                /*
                # dec #hex #oct

                    Control how integers are printed.
                */
                {
                    std::stringstream ss;

                    ss << std::hex << 10;
                    assert(ss.str() == "a");
                    ss.str("");

                    ss << std::oct << 10;
                    assert(ss.str() == "12");
                    ss.str("");

                    ss << std::dec << 10;
                    assert(ss.str() == "10");
                    ss.str("");

                    ss << 10;
                    assert(ss.str() == "10");
                    ss.str("");
                }

                /*
                # scientific fixed none

                # precision

                    Controls number of digits to print.
                */
                {
                    std::stringstream ss;
                    ss.precision(3);
                    float f = 1.2345;

                    //none is the default
                    ss << f;
                    assert(ss.str() == "1.23");
                    ss.str("");

                    ss << std::fixed << f;
                    assert(ss.str() == "1.235");
                    ss.str("");

                    ss << std::scientific << f;
                    assert(ss.str() == "1.235e+00");
                    ss.str("");

                    /*
                    None can only be set via `unsetf(ios_base::floatfield)`.
                    */
                    {
                        ss.unsetf(std::ios_base::floatfield);
                        ss << f;
                        assert(ss.str() == "1.23");
                        ss.str("");
                    }
                }
            }

            /*
            # file io

            # ifstream

            # ofstream

            # fstream
            */
            {
                std::string path("fileio.tmp");
                std::string data("ab\n\nc\n");

                // Write to file.
                {
                    std::ofstream ofs(path);
                    if (ofs) {
                        ofs << data;
                        ofs.close();
                    } else {
                        ios_write_fail(path);
                    }
                }

                // #Read entire file at once: stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
                // Best way seems to be to get file size, allocate, and read manually.
                {
                    std::ifstream ifs(path);
                    if (ifs) {
                        std::string data_read;
                        read_file(ifs, data_read);
                        assert(data_read == data);
                    } else {
                        ios_read_fail(path);
                    }
                }

                // #Copy file to another. #cp
                // #rdbuf http://stackoverflow.com/questions/2141749/what-does-ifstreamrdbuf-actually-do
                {
                    std::string data = "abc\ndef\n";
                    std::string src_path = "src.tmp";
                    std::string dst_path = "dst.tmp";
                    // Create input file.
                    {
                        std::ofstream src(src_path, std::ios::binary);
                        src << data;
                        // 2 times 4 Gb.
                        //for (int i = 0; i < 2; i++) {
                            //for (int j = 0; j < 0xFFFFFFFF; j++) {
                                //src << std::hex << j;
                            //}
                        //}
                        src.close();
                    }
                    // Copy.
                    std::ifstream src(src_path, std::ios::binary);
                    std::ofstream dst(dst_path,   std::ios::binary);
                    dst << src.rdbuf();
                    src.close();
                    dst.close();
                    // Check copy.
                    {
                        std::ifstream dst(dst_path, std::ios::binary);
                        std::string data_read;
                        read_file(dst, data_read);
                        assert(data_read == data);
                        src.close();
                    }
                }

                // #Compare two files larger than memory.
                // TODO is there an easier way than reading each?
                {
                }

                // #Append to file.
                {
                    std::ofstream ofs(path);

                    if (ofs) {
                        ofs << data;
                        ofs.close();
                    } else {
                        ios_write_fail(path);
                    }

                    // #open #Reopen
                    // Can be used to reopen ofstream with new properties.
                    // Also consider clearing error flags if there can be any.
                    //ofs.clear()
                    ofs.open(path, std::ios::app);
                    if (ofs) {
                        ofs << data;
                        ofs.close();
                    } else {
                        ios_write_fail(path);
                    }

                    std::ifstream ifs(path);
                    if (ifs) {
                        std::string data_read;
                        read_file(ifs, data_read);
                        assert(data_read == data + data);
                    } else {
                        ios_read_fail(path);
                    }
                }

                /*
                # binary io

                    Use ios::binary, and the binary functions write and read.
                */
                {
                    // TODO
                    //std::string path("binary.tmp");
                    //std::vector<int> data{0x123, 0x456};
                    //std::vector<int>::size_type size = data.size();
                    //std::vector<int> data_read(size);
                    //std::ofstream ofs(path, std::ios::binary);
                    //if (ofs) {
                        //ofs.write(&data[0], size);
                        //ofs.close();
                    //} else {
                        //ios_write_fail(path);
                    //}

                    //std::ifstream ifs(path);
                    //if (ifs) {
                        //std::string data_read;
                        //read_file(ifs, data_read);
                        //assert(data_read == data);
                    //} else {
                        //ios_read_fail(path);
                    //}
                }

                /*
                # error handling

                    # is_open vs bool cast

                        `is_open` false implies `operator bool()` false, but the converse is false: `operator bool()` is more strict.

                        <http://stackoverflow.com/questions/14920457/c-difference-between-casting-ifstream-to-bool-and-using-ifstreamis-open>

                    IO functions do not raise exceptions by default, but may be turned on.

                    The best standard exception to raise is probably `std::ios_base::failure`.

                    Relevant standard exceptions:

                        http://en.cppreference.com/w/cpp/io/ios_base/failure

                    SO thread:

                        http://stackoverflow.com/questions/9670396/exception-handling-and-opening-a-file
                */
                {
                    std::string path("i_dont_exist.tmp");
                    std::ifstream ifs(path);
                    if (ifs) {
                    } else {
                        try {
                            throw std::ios_base::failure("Error: Could not write to file: " + path);
                        } catch (std::ios_base::failure e) {
                            std::clog << e.what() << std::endl;
                        }

                    }
                }

                // # ios::in: flag automatically set for ifstream, but not fstream
                //http://stackoverflow.com/questions/7463410/is-iosin-needed-for-ifstreams-opened-in-binary-mode
            }
        }

        /*
        # path #directory #join

            Like in C, no system independant path or directory operations (for the love of God...)

            Boost does have a system independant path separator.

            Some Boost fs features were proposed on TR2.
        */

#if __cplusplus >= 201103L
        /*
        # static_assert

            Make assertions at compile time.

            In this way you don't waste time compiling large programs,
            or do potentially dangerous runtime operations to test your program.

            Probably became possible on C++11 because of features such as `constexpr`,
            which allow to better manage compile time constantness.

            <http://stackoverflow.com/questions/1647895/what-does-static-assert-do-and-what-would-you-use-it-for>
        */
        {
            static_assert(0 < 1, "msg");

            // ERROR: static assertion failed
            //static_assert(0 > 1, "msg");

            std::srand(time(NULL));
            // ERROR: needs to be a constexpr
            //static_assert(std::rand() >= 0);
        }
#endif

        /*
        # limits

            C++ version of climits.

            Contains information on the built-in types, inclding largest and smallest of each type.

            TODO compare to climits which uses macros. Advantage of templates is the scoping?
        */
        {
            std::cout << "numeric_limits<int>::" << std::endl;
            std::cout << "  max() = "            << std::numeric_limits<int>::max() << std::endl;
            std::cout << "  min() = "            << std::numeric_limits<int>::min() << std::endl;
            std::cout << "  digits = "           << std::numeric_limits<int>::digits << std::endl;
            std::cout << "  is_signed = "        << std::numeric_limits<int>::is_signed << std::endl;
            std::cout << "  is_integer = "       << std::numeric_limits<int>::is_integer << std::endl;
            std::cout << std::endl;
        }

        /*
        # utility

            Lots of miscelaneous utilities.

            <http://en.cppreference.com/w/cpp/utility>
        */
        {

#if __cplusplus >= 201103L
            /*
            # tuple

                Hold a ordered collection of elements.

                Each element can be of a different type.

                The length is always fixed.
            */
            {
                //create
                {
                    //constructor
                    {
                        std::tuple<int,char,std::string> t0(0, 'a', "a");
                    }

                    /*
                    # make_tuple

                        forwards arguments to tuple constructor.

                        The advantage over the constructor is that since it is a function
                        template argument deduction can be done, so we don't need to type in
                        template arguments.

                        Remember that template argument deduction cannot be done for constructors.
                    */
                    {
                        std::tuple<int,char,std::string> t;

                        //without make_tuple
                        t = std::make_tuple(0, 'a', "a");
                        t = std::tuple<int,char,std::string>(0, 'a', "a");

                        //with make_tuple
                    }

                    //tuple from pair
                    {
                        std::tuple<int,char> t2( std::pair<int,char>(0, 'a'));
                    }

                    //uniform initialization
                    {
                        std::tuple<int,char,std::string> t{0, 'a', "a"};
                    }

                    // Fails because the tuple constructor are is `explicit`!
                    // TODO Rationale? <http://stackoverflow.com/questions/14961809/returning-a-tuple-from-a-function-using-uniform-initialization-syntax>
                    {
                        //std::tuple<int, int> t = {0, 1};
                        //std::tuple<int, int> t[]{{0, 1}};
                    }
                }

                /*
                # get

                    Get single element from tuple.

                    Returns references, so it is possible to modify the tuples with them.

                    Copies are made from input elements
                */
                {
                    std::tuple<int,std::string> t0(0, "abc");

                    assert(std::get<0>(t0) == 0);
                    assert(std::get<1>(t0) == "abc");

                    std::get<0>(t0) = 1;
                    assert(std::get<0>(t0) == 1);

                    std::get<1>(t0)[0] = '0';
                    assert(std::get<1>(t0) == "0bc");
                }

                /*
                # tie

                    Unpack a tuple.

                    Unpack by reference seems not to be possible: <http://stackoverflow.com/questions/16571883/unpacking-a-std-tuple-into-pointers>

                # ignore

                    Magic that exists only to ignore one of tie outputs.
                */
                {
                    int i;
                    std::string s;
                    std::tuple<int,float,std::string> t(1, 1.5, "abc");
                    std::tie(i, std::ignore, s) = t;
                    assert(i == 1);
                    assert(s == "abc");

                    // Clearly copies are made.
                    i = 2;
                    assert(std::get<0>(t) == 1);
                }

                /*
                Relational operators operations are implemented

                <http://www.cplusplus.com/reference/tuple/tuple/operators/>

                `<` family is lexicographical.
                */
                {
                    std::tuple<int,char> t0(0, 'a');
                    std::tuple<int,char> t1(0, 'a');
                    std::tuple<int,char> t2(1, 'b');
                    std::tuple<int,char> t3(-1, 'b');
                    std::tuple<int,char> t4(0, 'b');

                    assert(t0 == t1);
                    assert(t0 != t2);
                    assert(t0 < t2);
                    assert(t0 > t3); //-1 counts
                    assert(t0 < t4); //0 ties, 'a' < 'b'
                }

                //swap contents of two tuples of same type
                {
                    std::tuple<int,char> t0(0, 'a');
                    std::tuple<int,char> t1(1, 'b');

                    std::tuple<int,char> old_t0 = t0;
                    std::tuple<int,char> old_t1 = t1;

                    t0.swap(t1);

                    assert(t0 == old_t1);
                    assert(t1 == old_t0);
                }
            }
#endif

            /*
            # pair

                Particular case of tuple for two elements

                Methods which also exist for tuple will not be discussed.

                Specially important because of `map`.
            */
            {
                //access: can also be done via `.first` and `.second` in addition to tuple `get`.
                {
                    std::pair<int,char> p(0, 'a');
                    assert(std::get<0>(p) == p.first);
                    assert(std::get<1>(p) == p.second);
                }
            }

            /*
            # forward

                TODO
            */
            {
            }
        }

        /*
        # containers

            The stdlib furnishes several containers.

            It is a very important part of an algorithm to choose the right container for the task.

            As of C++11, most containers are abstract, that is, only specify which operations it supports.

            For example, a `UnorderedMap` could be implemented both as a hash map or a RB tree concrete data structures,
            but is always supports the same operations: insert, remove, and so on.

            The major data structures which you must know about in order of decreasing usefulness are:

            - std::vector
            - set
            - map
            - list
            - deque
            - heap and priority queue
        */

        /*
        # vector

            Array backed conatiner that grows / shrinks as necessary.

            $O(1)$ random access.

            $O(n)$ element removal from interior

            $O(1)$ element append to end (amortized, $O(n)$ worst case)

            All methods that work for several SLT containers shall only be cheated here once.
        */
        {
            // Create
            {
                // Empty
                {
                    std::vector<int> v;
                    // C++11 initializer lists:
                    std::vector<int> v1{};
                    assert(v == v1);
                }

                /*
                Fill constructor.

                Make a `std::vector` with n copies of a single value.
                */
                {
                    //copies of given object
                    {
                        assert(std::vector<int>(3, 2) == std::vector<int>({2, 2, 2}));
                    }

                    //default constructed objects. int = 0.
                    {
                        assert(std::vector<int>(3) == std::vector<int>({0, 0, 0}));
                    }
                }

                // Range copy.
                {
                    std::vector<int> v{0, 1, 2};
                    std::vector<int> v1(v.begin(), v.end());
                    assert(v == v1);
                }

                // From existing array.
                {
                    int myints[]{0, 1, 2};
                    std::vector<int> v(myints, myints + sizeof(myints) / sizeof(int));
                    std::vector<int> v1 = {0, 1, 2};
                    assert(v == v1);
                }
            }

            // Vectors have order.
            {
                std::vector<int> v{0, 1, 2};
                std::vector<int> v1{2, 1, 0};
                assert(v != v1);
            }

            /*
            # Contigous storage

            # Data

                Storage is required to be contiguous by TR1:
                http://stackoverflow.com/questions/849168/are-stdvector-elements-guaranteed-to-be-contiguous

                C++11 introduces the `data()` method which returns a pointer to the first element.
                It works even if the vector is empty.
                http://stackoverflow.com/questions/6485496/how-to-get-stdvector-pointer-to-the-raw-data

                Before C++11, `&v[0]` works for non-empty vectors.

                `vector<bool>` as usual is an exception.
            */
            {
                std::vector<int> v{0, 1, 2};
                assert(&v[0] == v.data());
                // True because contiguous:
                assert(v.data()[1] == v[1]);
            }

            // size methods
            {
                /*
                # size

                # length of vector

                # size_type

                    Number of elements in std::vector.

                    This has type std::vector<X>::size_type
                */
                {
                    std::vector<int> v;
                    assert(v.size() == 0);
                    v.push_back(0);
                    assert(v.size() == 1);
                }

                /*
                # resize

                    If larger than current size, append given element at end.

                    If smaller than current size, remove elements from end.
                */
                {
                    // Reduce size
                    {
                        std::vector<int> v{0, 1};
                        v.resize(1);
                        assert((v == std::vector<int>{0}));
                    }

                    // Increase size
                    {

                        // Using default constructor objects.
                        {
                            std::vector<int> v{1};
                            v.resize(3);
                            assert((v == std::vector<int>{1, 0, 0}));
                        }

                        // Using copies of given object.
                        {
                            std::vector<int> v{1};
                            v.resize(3, 2);
                            assert((v == std::vector<int>{1, 2, 2}));
                        }
                    }
                }
            }

            // Capacity methods.
            {
                /*
                # capacity

                    Get currently allocated size.

                    Different from size, which is the number of elements in the std::vector!

                    At least as large as size.

                    Likely to be a power of 2 on most implementations.
                */
                {
                    std::vector<int> v;
                    v.push_back(0);
                    v.push_back(1);
                    v.push_back(2);
                    assert(v.capacity() >= 3);
                    std::cout << "capacity = " << v.capacity() << std::endl;
                }

                // # max_size: estimative of what your OS allows you to allocate
                {
                    std::cout << "max_size (MiB) = " << std::vector<int>().max_size() / (1 << 20) << std::endl;
                }

                // # reserve: increase allocated size if larger than current size.
                {
                    std::vector<int> v;
                    v.reserve(3);
                    assert(v.capacity() >= 3);
                    // size() is untouched
                    assert(v.empty());
                }

#if __cplusplus >= 201103L
                // # shrink_to_fit
                {
                    std::vector<int> v{0, 1};
                    v.reserve(4);
                    v.shrink_to_fit();
                    assert(v.capacity() == 2);
                }
#endif
            }

            // `std::vector` stores copies of elements, not references.
            {
                std::string s = "abc";
                std::vector<std::string> v{s};
                v[0][0] = '0';
                assert(v[0] == "0bc");
                assert(s    == "abc");
            }

            // Modify.
            {
                {
                    std::vector<int> v;
                    v = {0};
                    v = {0, 1};
                    assert((v == std::vector<int>{0, 1}));
                }

                /*
                # push_back

                # append

                    Push to the end of the std::vector.

                    Amortized time O(1), but may ocassionaly make the std::vector grow,
                    which may required a full data copy to a new location if the
                    current backing array cannot grow.

                # push_front

                    Does not exist for std::vector, as it would always be too costly (requires to move
                    each element forward.) Use deque if you need that.
                */
                {
                    std::vector<int> v;
                    std::vector<int> v1;

                    v.push_back(0);
                    v1 = {0};
                    assert(v == v1);

                    v.push_back(1);
                    v1 = {0, 1};
                    assert(v == v1);

                    /*
                    push_back makes copies with assign `=`

                    If you want references, use pointers, or even better, auto_ptr.
                    */
                    {
                        std::vector<std::string> v;
                        std::string s = "abc";

                        v.push_back(s);
                        v[0][0] = '0';
                        assert(v[0] == "0bc");

                        //s was not changed
                        assert(s == "abc");
                    }
                }

                /*
                # pop_back

                    Remove last element from std::vector.

                    No return val. Rationale: <http://stackoverflow.com/questions/12600330/pop-back-return-value>
                */
                {
                    std::vector<int> v{0, 1};

                    v.pop_back();
                    assert(v == std::vector<int>{0});

                    v.pop_back();
                    assert(v == std::vector<int>{});
                }

                /*
                # insert

                    This operation is inneficient for `std::vector` if it is not done at the end.

                # concatenate

                    The range form of insert can be used to append one vector to anoter.
                */
                {
                    // Single element form.
                    {
                        std::vector<int> v = {0,1};
                        std::vector<int> v1;

                        v.insert(v.begin(), -1);
                        v1 = {-1, 0, 1};
                        assert(v == v1);

                        v.insert(v.end(), 2);
                        v1 = {-1, 0, 1, 2};
                        assert(v == v1);
                    }

                    // Range form.
                    {
                        std::vector<int> v = {0,1};
                        std::vector<int> v1 = {2,3};

                        v.insert(v.end(), v1.begin(), v1.end());
                        assert((v == std::vector<int>{0, 1, 2, 3}));
                    }
                }

                /*
                # erase

                    Remove given elements from container given iterators to those elements.

                    This operation is inneficient for std::vectors,
                    since it may mean reallocation and therefore up to $O(n)$ operations.

                    Returns a pointer to the new location of the element next to the last removed element.
                */
                {
                    // Single element
                    {
                        std::vector<int> v{0, 1, 2};
                        auto it = v.erase(v.begin() + 1);
                        assert((v == std::vector<int>{0, 2}));
                        assert(*it == 2);
                    }

                    // Range
                    {
                        std::vector<int> v{0, 1, 2, 3};
                        auto it = v.erase(v.begin() + 1, v.end() - 1);
                        assert((v == std::vector<int>{0, 3}));
                        assert(*it == 3);
                    }
                }

                /*
                # remove

                    Helper to remove all elements that compare equal to a value from container.

                    Does not actually remove the elements: only ensures that the beginning of the range
                    does not contain the item to be removed.

                    Ex:

                        0, 1, 0, 2, 0, 1

                    Value to remove: `0`

                    Range to remove from:

                        0, 1, 0, 2, 0, 1
                        ----------

                    After the remove:

                        1, 2, X, Y, 0, 1
                        ----------

                    where `X` and `Y` are trash, and not necessarily 0!

                    To actually remove the items, an `erase` is needed after remove
                    because `remove` is not a class method and thus cannot remove items from a container.

                    This is called the erase and remove idiom.

                    After a remove the container becomes:

                        1, 2, 0, 1

                # erase and remove idiom

                # remove and erase idiom

                    See remove.
                */
                {
                    // Verbose version
                    {
                        std::vector<int> v{0, 1, 0, 2, 0, 1};
                        auto end = std::next(v.end(), -2);
                        auto firstTrashIt = std::remove(v.begin(), end, 0);
                        // Unpredictable result:
                        std::cout << "remove:";
                        for (auto& i : v) std::cout << " " << i;
                        std::cout << std::endl;
                        v.erase(firstTrashIt, end);
                        assert((v == std::vector<int>{1, 2, 0, 1}));
                    }

                    // Compact version
                    {
                        std::vector<int> v{0, 1, 0, 2, 0, 1};
                        auto end = std::next(v.end(), -2);
                        v.erase(std::remove(v.begin(), end, 0), end);
                        assert((v == std::vector<int>{1, 2, 0, 1}));
                    }
                }

                // # remove_if # filter
                // Algorithm. Remove if a given function evaluates to true on an element.
                {
                    std::vector<int> v{0, 1, 2, 3, 4};
                    auto end = v.end();
                    v.erase(std::remove_if(v.begin(), end, odd), end);
                    assert((v == std::vector<int>{0, 2, 4}));

                    // Common combo with lambdas
                    {
                        std::vector<int> v{0, 1, 2, 3, 4};
                        auto end = v.end();
                        v.erase(std::remove_if(v.begin(), end,
                            [](int i) {return i % 2 == 1;}), end);
                        assert((v == std::vector<int>{0, 2, 4}));
                    }
                }

                // # transform
                // Algorithm. Replace elements by output of a function.
                {
                    std::vector<int> v{0, 1, 2};
                    std::transform(v.begin(), v.end(), v.begin(),
                            [](int i) {return i * i;});
                    assert((v == std::vector<int>{0, 1, 4}));
                }

                // # clear
                {
                    std::vector<int> v{0, 1, 2};
                    v.clear();
                    assert(v.size() == 0);
                }

                /*
                # print vector

                # vector to string

                    No built-in way.

                    http://stackoverflow.com/questions/4850473/pretty-print-c-stl-containers
                    190 votes on question, 30 on top answer! Come on C++!

                    http://stackoverflow.com/questions/1430757/c-vector-to-string?lq=1
                */
                // ERROR: no default operator `<<`.
                //cout << v;
            }

            // Random access is O(1) since array backed
            {

                std::vector<int> v{0, 1, 2};

                // First element:

                    assert(v.front() == 0);
                    assert(v.front() == v[0]);

                // Last element:

                    assert(v.back() == 2);

                // Nth element:

                    v[0] = 1;
                    assert(v[0] == 1);

                /*
                BAD: just like array overflow will not change std::vector size,
                and is unlikelly to give an error
                */
                {
                    //v1[2] = 2;
                }

                // #back  Get reference to last  element in vector.
                // #front Get reference to first element in vector.
                // #at    Like `[]`, but does bound checking and throws `out_of_range` in case of overflow.
                {
                    std::vector<int> v{0, 1, 2};
                    assert(v.front() == 0);
                    assert(v.at(1)   == 1);
                    assert(v.back()  == 2);
                    try {
                        assert(v.at(3) == 0);
                    } catch (std::out_of_range& e) {
                    } catch (...) {
                        assert(false);
                    }
                }
            }

            /*
            # bool std::vector

                *bool std::vectors are evil!*

                The standard requires `vector` to have an specialization for bool which packs bits efficiently.

                While efficient, in order to work this specialization breaks common std::vector interfaces
                that require taking addresses only in the case of this specialization, since it does not
                make sense to takes addresses anymore.

                Alternatives to `vector<bool>`: <http://stackoverflow.com/questions/670308/alternative-to-vectorbool>

                A good alternative seem to be deque<bool>, which behaves as intended.
            */
            {
                // Works fine and dandy as expected.
                {
                    std::vector<int> v{1, 0};
                    int& i(v[0]);
                }

                // Does not compile!!!
                {
                    std::vector<bool> v{true, false};
                    //bool& b(v[0]);
                }

                // It was not a problem with bool, the problem really is `vector<bool>`.
                {
                    bool b[]{true, false};
                    bool& b2(b[0]);
                }
            }
        }

        /*
        # deque

            Double ended queue.

            Random access.

            Very similar interface to std::vector, except that:

            - insertion to front is O(1)
            - there is no guarantee of inner storage contiguity

            Discussion on when to use deque or std::vector:
            <http://stackoverflow.com/questions/5345152/why-would-i-prefer-using-vector-to-deque>

            It is controversial if one should use deque or std::vector as the main generic container.
        */

        /*
        # set

            - unique elements: inserting twice does nothing

            - always ordered: $O(log)$ find / insert

            - immutable elements: it is not possible to modify an object,
                one must first remove it and resinsert.

                This is so because modification may mean reordering.
        */
        {
            // C++11 initializer list
            {
                {
                    std::set<int> s{1, 2, 0, 1};
                    std::set<int> s2{0, 1, 2};
                    assert(s == s2);
                }

                {
                    std::set<std::string> s = {"a", "c", "b", "a"};
                    std::set<std::string> s1 = {"a","b", "c"};
                    assert(s == s1);
                }
            }

            // You can modify objects if you store pointers.
            {
                int i = 0;
                std::set<int*> s;
                s.insert(&i);
                std::set<int*>::iterator it = s.find(&i);
                *(*it) = 1;
                assert(i == 1);
            }

            /*
            # insert

                Like for std::vector, insert makes copies.

                Return is a pair conatining:

                - if the item was not present, an iterator to the item inserted and true
                - if the item was     present, an iterator to the existing item inserted and false
            */
            {
                std::pair<std::set<int,std::string>::iterator,bool> ret;
                std::set<int> s;

                ret = s.insert(1);
                assert(ret.first == s.find(1));
                assert(ret.second == true);

                ret = s.insert(2);
                assert(ret.first == s.find(2));
                assert(ret.second == true);

                ret = s.insert(0);
                assert(ret.first == s.find(0));
                assert(ret.second == true);

                //item already present:
                //nothing is done and returns false on the pair
                ret = s.insert(1);
                assert(ret.first == s.find(1));
                assert(ret.second == false);

                std::set<int> s1 = {0, 1, 2};
                assert(s == s1);
            }

            /*
            # erase

                Remove element from set.

                Returns number of elements removed.
            */
            {
                std::set<int> s = {0, 1, 2};

                assert(s.erase(1) == 1);
                std::set<int> s2 = {0, 2};
                assert(s == s2);

                assert(s.erase(1) == 0);
            }

            // ERROR no random access since it uses bidirection iterator.
            {
                //cout << s[0] << endl;
            }

            //size
            {
                std::set<int> s;
                assert(s.size() == 0);
                s.insert(0);
                assert(s.size() == 1);
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
                std::set<int> s = {0, 1, 2};
                std::set<int>::iterator it;

                it = s.find(1);
                assert(*it == 1);

                it = s.find(3);
                assert(it == s.end());
            }

            /*
            count

                Count how many times an item is in the set.

                Can only return 1 or 0.

                Equivalent to doing a find.
            */
            {
                std::set<int> s = {1, 2, 0, 1};
                assert(s.count(1) == 1);
                assert(s.count(3) == 0);
            }
        }

        /*
        # hashmap

            There seems to be no explicit hashmap container, only a generic map interface,

            See map.

            Nonstandard `hash_map` already provided with gcc and msvc++.
            It is placed in the `std::` namespace, but it is *not* ISO.

        # map

            <http://www.cplusplus.com/reference/map/map/>

            Also comes in an unordered version `unordered_map`.

            Ordered.

            Also comes in an multiple value input version `multimap`.

            Does not require a hash function. Usually implemented as a self balancing tree such as a rb tree.

        # unordered_map

            TODO complexity comparison to map.
        */
        {
            /*
            The initializer list constructor makes things very easy.
            */
            {
                std::map<int,std::string> m{
                    {0, "zero"},
                    {1, "one"},
                    {2, "two"},
                };
            }

            /*
            emplace

                put a value pair into the map without creating the pair explicitly

                needs gcc 4.8: <http://stackoverflow.com/questions/15812276/stdset-has-no-member-emplace>
            */
            {
                //std::map<int,std::string> m;
                //m.emplace(0, "zero");
                //m.emplace(1, "one");
                //m.emplace(2, "two");
            }

            /*
            # insert

                Insert pair into map.

                The return value is similar to that of a set insertion with respec to the key.
            */
            {
                std::map<int,std::string> m;
                std::pair<std::map<int,std::string>::iterator,bool> ret;

                ret = m.insert(std::pair<int,std::string>(0, "zero"));
                assert(ret.first == m.find(0));
                assert(ret.second == true);

                ret = m.insert(std::pair<int,std::string>(1, "one"));
                assert(ret.first == m.find(1));
                assert(ret.second == true);

                //key already present
                ret = m.insert(std::pair<int,std::string>(1, "one2"));
                assert(m[1] == "one");
                assert(ret.first == m.find(1));
                assert(ret.second == false);
            }

            /*
            iterate

                Map is ordered.

                It is iterated in key `<` order.

                Iteration returns key value pairs.
            */
            {
                std::map<int,std::string> m{
                    {1, "one"},
                    {0, "zero"},
                };

                int i = 0;
                int is[] = {0, 1};
                for (auto& im : m) {
                    assert(im.first == is[i]);
                    //cout << im->second << endl;
                    ++i;
                }
                assert(i == 2);
                assert(map_to_str(m) == "0:zero, 1:one, ");
            }

            /*
            [] operator

                get value from a given key

                WARNING: if the key does not exist, it is inserted with a value with default constructor.

                This can be avoided by using `find` instead of `[]`.
            */
            {
                std::map<int,std::string> m{
                    {0, "zero"},
                    {1, "one"},
                };

                assert(m[0] == "zero");
                assert(m[1] == "one");

                //inserts `(3,"")` because `""` is the value for the default string constructor
                assert(m[2] == "");
                assert(m.size() == 3);
            }

            /*
            # find #check if in map

                Similar to `std::set` find with respect to the keys:
                returns an iterator pointing to the pair which has given key, not the value.

                If not found, returns `map::end()`

                This is perferrable to `[]` since it does not insert non-existent elements.
            */
            {
                std::map<int,std::string> m{
                    {0, "zero"},
                    {1, "one"},
                };

                assert(m.find(0)->second == "zero");
                assert(m.find(1)->second == "one");

                assert(m.find(2) == m.end());
                assert(m.size() == 2);
            }

            /*
            erase

                Remove element from map.

                Returns number of elements removed.
            */
            {
                int ret;

                std::map<int,std::string> m{
                    {0, "zero"},
                    {1, "one"},
                };

                std::map<int,std::string> m2;
                m2.insert(std::pair<int,std::string>(0, "zero"));

                ret = m.erase(1);
                assert(ret = 1);

                assert(m == m2);

                ret = m.erase(1);
                assert(ret == 0);
            }
        }

        /*
        # list

            Doubly linked list.

            Advantages over std::vector: fast inservion and removal from middle.

            Unless you really need those operations fast, don't use this data structure.

            No random access.

        # forward_list

            Like list, but singly linked, and therefore not backwards interable.
        */
        {
            //initializer list constructor
            {
                std::list<int> l{0, 1};
            }

            // # emplace
            {
                std::list<int> l{0, 1};
                l.emplace(++l.begin(), 2);
                assert(l == std::list<int>({0, 2, 1}));
            }

            // # remove: remove all elements with a given value from list
            {
                std::list<int> l{0, 1, 0, 2};
                l.remove(0);
                assert(l == std::list<int>({1, 2}));
            }

            // # splice: transfer elements from one list to another
            {
                std::list<int> l{0, 1};
                std::list<int> l2{2, 3};
                l.splice(++l.begin(), l2);
                assert(l == std::list<int>({0, 2, 3, 1}));
                assert(l2 == std::list<int>());
            }
        }

        /*
        # iterator

            Iteration could be done with random access in certain data structures with a for i loop.

            Iterators are better becase you can also use them for structures without random access,
            so if you decide to change structures in the future the job will be much easier.

            # iterator categories

                Iterators are categorized depending on the operations they can do:

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

                    typedef random_it std::vector<int>::iterator;

                It is possible to retreive the class of an interator via `std::iterator_traits<ITER>::interator_category`.
        */
        {
            // Before C++11: begin and end were the only way to use iterators.
            // After C++11; the range based syntax is the best way to use them.
            {
                /*
                # forward iteration

                    Can be done on all containers.

                    # begin

                        Returns an iterator to the first element.

                    # end

                        Returns an iterator to the first element *after* the last.
                */
                {
                    std::vector<int> v{1, 2, 0};
                    int i = 0;
                    int is[]{1, 2, 0};

                    for (auto it = v.begin(); it != v.end(); ++it) {
                        assert(*it == is[i]);
                        ++i;
                    }
                }

                /*
                # backwards iteration

                    Can only be done on biderectional containers.

                    # rbegin

                        Reversed begin.

                        Returns a `reverse_iterator` that points to the last emlement.

                        ++ on reversed iterators decreases them.

                    # rend

                        Returns a reversed iterator to the element before the first.
                */
                {
                    std::vector<int> v{1, 2, 0};
                    int i;
                    int is[]{1, 2, 0};

                    i = 2;
                    for (auto it = v.rbegin(); it != v.rend(); ++it) {
                        assert(*it == is[i]);
                        //cout << *it << endl;
                        --i;
                    }
                }
            }

            /*
            # range based for loop #foreach

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
#if __cplusplus >= 201103L
                //forward
                {
                    // If `int&` is used, no useless copies are made.
                    // and the vector can be modified directly.
                    {
                        std::vector<int> v{1, 2, 0};
                        int is[]{1, 2, 0};
                        int i = 0;
                        for (int& iv : v) {
                            assert(iv == is[i]);
                            //cout << iv << endl;
                            iv++;
                            i++;
                        }
                        assert((v == std::vector<int>{2, 3, 1}));
                    }

                    // Without `&`, makes copies of each element.
                    // Usually not what we want.
                    {
                        std::vector<int> v{1, 2, 0};
                        int is[]{1, 2, 0};
                        int i = 0;
                        for (int iv : v) {
                            assert(iv == is[i]);
                            //cout << iv << endl;
                            iv++;
                            i++;
                        }
                        assert((v == std::vector<int>{1, 2, 0}));
                    }

                    // Less code duplication with auto.
                    // This is the best way to do it.
                    {
                        std::vector<int> v{1, 2, 0};
                        int is[]{1, 2, 0};
                        int i = 0;
                        for (auto& iv : v) {
                            assert(iv == is[i]);
                            //cout << *it << endl;
                            i++;
                        }
                    }
                }

                /*
                # range based for loop for arrays

                    Also works for bare arrays for which the size is known at compile time!
                */
                {
                    {
                        int is[]{1, 2};
                        for (int& i : is) {
                            i *= 2;
                        }
                        assert(is[0] == 2);
                        assert(is[1] == 4);
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
                /*
                backwards

                    TODO possible? Seems not out of the C++11 box: <http://stackoverflow.com/questions/8542591/c11-reverse-range-based-for-loop>

                    Auto is a lifesaver here to avoid typing the iterator type.
                */
                {
                    std::vector<int> v = {1, 2, 0};
                    int i;
                    int is[] = {1, 2, 0};

                    //forward
                    {
                        i = 2;
                        for (auto it = v.rbegin(); it != v.rend(); ++it) {
                            assert(*it == is[i]);
                            //cout << *it << endl;
                            i--;
                        }
                    }
                }
            }

            /*
            # generic containers

                There is no standard iterator independent from container.

                This can be done via type erasure techinques.

                But would mean loss of performance because of lots of polymorphic calls
                and stdlib is obssessed with performance.

                The best solution seems to use typedefs:

                    typedef it_t std::vector<int>::iterator;

                And then if ever your container changes all you have to do is modify one single typedef:

                    typedef it_t set<int>::iterator;

                TODO isnt auto and range based for a better solution in c++11?
            */
            {
                std::vector<int> v{1, 2};
                std::set<int> s{1, 2};
                std::vector<int>::iterator itVec(v.begin());
                std::set<int>::iterator itSeti(s.begin());

                // Does not exist:

                    //iterator<int> itVec = v.begin();
                    //iterator<int> itSeti = s.begin();

                // Best workaround is using auto:

                    auto vit(v.begin());
                    auto sit(v.begin());
            }

            // No born checking is done
            {
                std::vector<int> v{1, 2};

                // Last element.
                *(v.end() - 1);

                // After last element no born check.
                *(v.end());

                // No such method.
                //(v.end().hasNext());
            }

            /*
            Base pointers and arrays can be used anywhere iterators can.

            The stdlib functions have specializations for pointers.

            <http://stackoverflow.com/questions/713309/c-stl-can-arrays-be-used-transparently-with-stl-functions>
            */
            {
                int is[]{2, 0, 1};
                int j = 0;
                for (auto& i : is) {
                    assert(i == is[j]);
                    j++;
                }
            }

            /*
            # size_t for slt containers

                See size_type.

            # size_type

                Random access containers such as std::vectors, strings, etc have a `size_type` member typedef
                that represents a type large enough to hold its indexes.

                For arrays, this type is exactly the C `size_t`.

                For a std::vector, it will also probably be `size_t`, since std::vectors are array backed,
                but using `size_type` gives more generality.

                This type is returned by methods such as `size()`.
            */
            {
                std::vector<int> v{2, 0, 1};
                std::vector<int>::size_type i(1);
                v[i] = 1;
            }

            /*
            # iterator_traits

                Contain information about iterators.

                This allows to create template functions that take generic iterators independent of the
                exact container type as is the case for many function sunder `<algorithm>`.
            */
            {
                //value_type
                //pointer
                //reference
                {
                    typedef std::iterator_traits<std::vector<int>::iterator>::value_type ValueType;
                    typedef std::iterator_traits<std::vector<int>::iterator>::pointer    Pointer;
                    typedef std::iterator_traits<std::vector<int>::iterator>::reference  Reference;
                    assert(typeid(ValueType) == typeid(int));
                    assert(typeid(Pointer)   == typeid(int*));
                    assert(typeid(Reference) == typeid(int&));
                }

                /*
                # difference_type

                    The type returned on a difference between two pointers.

                    Unlike size_type, this value is signed, since the difference may well be negative.
                */
                {
                    typedef typename std::iterator_traits<std::vector<int>::iterator>::difference_type DifferenceType;
                    std::vector<int> v{0, 1};
                    assert(typeid(v.end() - v.begin()) == typeid(DifferenceType));
                }

                /*
                # iterator_category

                    iterator_category is a struct *type*, not a value.

                    Therefore, in order to compare it one must use `typeid`.
                */
                {
                    assert(typeid(std::iterator_traits<std::vector<int>::iterator>::iterator_category)
                            == typeid(std::random_access_iterator_tag));
                }
            }
        }

        /*
        # valarray

            Array of values. Wors much like a mathematical vector.

            Container that overloads many mathematical operations in a similar way to what Fortran does,
            which may be more efficient and convenient.

            Very obscure, for several reasons:

            - other techniques achieve what it achieves
            - low compiler support

            Downsides compared to vectors:

            - not resizable, so no push_back

            <http://stackoverflow.com/questions/1602451/c-valarray-vs-vector>
        */
        {
            std::valarray<int> v;
            std::valarray<int> v0{0, 1, 2};
            std::valarray<int> v1{3, 4, 5};

            assert(v0.sum() == 3);
            assert(v0.min() == 0);
            assert(v0.max() == 2);

            /*
            v = v0;
            v.cshift(1);
            assert((v == std::valarray<int>{1, 2, 0}).min());
            */

            // == is elementwise equality.
            //
            // For equality of all elements, do `.min() == true`
            {
                std::valarray<int> v0{0, 1, 2};
                std::valarray<int> v1{0, 2, 2};
                assert(((v0 == v1) == std::valarray<bool>{true, false, true}).min());

            }

            // +, -, *, /, etc are overloaded elementwise.
            //
            // They are also overloaded for contained data type.
            {
                assert((v0 + v1 == std::valarray<int>{3, 5, 7}).min());
                assert((v0 +  1 == std::valarray<int>{1, 2, 3}).min());
            }

            // Basic cmath functions are overloaded for valarray elementwise.
            {
                assert((abs(std::valarray<int>{-1, 0, 1})    == std::valarray<int>{1, 0, 1}).min());
                assert((pow(std::valarray<int>{-2, 0, 2}, 2) == std::valarray<int>{4, 0, 4}).min());
            }
        }

        // # algorithm
        {
            {
                assert(std::min(0.1, 0.2) == 0.1);
                assert(std::max(0.1, 0.2) == 0.2);
            }

            // # sort
            {
                std::vector<int> v{2, 0, 1};
                std::sort(v.begin(), v.end());
                std::vector<int> v1 = {0, 1, 2};
                assert((v == std::vector<int>{0, 1, 2}));
            }

            // # reverse
            {
                std::vector<int> v{2, 0, 1};
                std::reverse(v.begin(), v.end());
                assert((v == std::vector<int>{1, 0, 2}));
            }

            /*
            # swap

                Does things equivalent to:

                    template <class T> void swap (T& a, T& b)
                    {
                        T c(a); a=b; b=c;
                    }

                However stdlib can specialize it to do operations more efficiently.

                Some stdlib classes implement swap as a method.

                Particularly important because of the copy and swap idiom.
            */

            // # randomize
            {
                std::vector<int> v{2, 0, 1};
                std::random_shuffle(v.begin(), v.end());
            }

            // # copy
            {
                std::vector<int> v{2, 0, 1};
                std::vector<int> v2(5, 3);
                std::copy(v.begin(), v.end(), v2.begin() + 1);
                assert(v2 == std::vector<int>({3, 2, 0, 1, 3}));
            }

            /*
            # equal

                Compares ranges of two containers.
            */
            {
                std::vector<int> v {0, 1, 2   };
                std::vector<int> v2{   1, 2, 3};
                assert(std::equal(v.begin() + 1, v.end(), v2.begin()));
            }

            /*
            # accumulate

                Sum over range.

                Also has functional versions <http://www.cplusplus.com/reference/numeric/accumulate/>
            */
            {
                std::vector<int> v{2, 0, 1};
                assert(std::accumulate(v.begin(), v.end(), 0)     == 3);
                assert(std::accumulate(v.begin(), v.end(), 10)    == 13);
            }

            /*
            # find

                Return iterator to first found element.
            */
            {
                std::vector<int> v{2,0,1};
                unsigned int pos;

                pos = std::find(v.begin(), v.end(), 0) - v.begin();
                assert(pos == 1);

                pos = std::find(v.begin(), v.end(), 1) - v.begin();
                assert(pos == 2);

                pos = std::find(v.begin(), v.end(), 2) - v.begin();
                assert(pos == 0);

                pos = std::find(v.begin(), v.end(), 3) - v.begin(); //end() returned
                assert(pos == v.size());
            }

            /*
            # find_if

                Like find, but using an arbitrary condition on each element instead of equality.

                Consider usage with C++11 lambdas and functional.
            */
            {
                std::vector<int> v{2, 0, 1};
                assert(std::find_if (v.begin(), v.end(), odd) == --v.end());
            }

            /*
            # binary_search

                Container must be already sorted.

                Log complexity.

                Only states if the element is present or not, but does not get its position.

                If you want to get the position of those items, use `equal_range`, `lower_bound` or `upper_bound`.
            */
            {

                std::vector<int> v{0, 1, 2};
                assert(std::binary_search(v.begin(), v.end(),     1) == true);
                assert(std::binary_search(v.begin(), v.end(),     3) == false);
                assert(std::binary_search(v.begin(), v.end() - 1, 2) == false);
            }

            /*
            # lower_bound

                Finds first element in container which is not less than val.
            */
            {
                std::vector<int> v{0, 2, 3};
                auto it = std::lower_bound(v.begin(), v.end(), 1);
                assert(it - v.begin() == 1);
            }

            /*
            # upper_bound

                Finds first element in container is greater than val.
            */
            {
                std::vector<int> v{0, 1, 2};
                auto it = std::upper_bound(v.begin(), v.end(), 1);
                assert(it - v.begin() == 2);
            }

            /*
            # equal_range

                Finds first and last location of a value iniside a ranged container.

                Return values are the same as lower_bound and upper_bound.

                log complexity.
            */
            {
                std::vector<int> v{0, 1, 1, 2};
                std::vector<int>::iterator begin, end;
                std::tie(begin, end) = std::equal_range(v.begin(), v.end(), 1);
                assert(begin - v.begin() == 1);
                assert(end   - v.begin() == 3);
            }

            // # count
            {
                std::vector<int> v{2,1,2};
                assert(std::count(v.begin(), v.end(), 0) == 0);
                assert(std::count(v.begin(), v.end(), 1) == 1);
                assert(std::count(v.begin(), v.end(), 2) == 2);
            }


            // # max_element #min_element
            {
                std::vector<int> v{2,0,1};
                assert(*std::max_element(v.begin(), v.end()) == 2);
                assert(*std::min_element(v.begin(), v.end()) == 0);
            }

            /*
            # advance

                Advance iterator by given number.

                If random access, simply adds + N.

                Else, calls `++` N times.

                Advantage over `+`: only random access containers support `+`,
                but this works for any container, allowing one to write more general code.

                Beware however that this operation will be slow for non random access containers.
            */
            {
                std::vector<int> v{0, 1, 2};
                auto it = v.begin();
                std::advance(it, 2);
                assert(*it == 2);
            }

#if __cplusplus >= 201103L
            /*
            # next

                Same as advance, but returns a new iterator instead of modifying the old one.
            */
            {
                std::vector<int> v{0, 1, 2};
                auto it(v.begin());
                auto itNext = std::next(it, 2);
                assert(*it == 0);
                assert(*itNext == 2);
            }
#endif

            /*
            # priority queue

                Offers `O(1)` access to the smalles element.

                Other operatoins vary between `O(n)` and `O(1).

                Most common implementaions are via:

                - binary heap
                - fibonacci heap

                Boost offers explicit heap types: fibonacci, binary and others.

                But no guarantees are made.

                As of C++11, does not support the increase key operation.

                A binary heap without increase key can be implemented via the heap function family under algorithm.
            */

            /*
            # heap

                Binary heap implementation.

                <http://en.wikipedia.org/wiki/Heap_%28data_structure%29>

                In short:

                - getting largest element is O(1)
                - removing the largest element is O(lg) for all implementation
                - other operations (insertion) may be O(1) or O(lg) depending on the implementation.

                this makes for a good priority queue.
                Exact heap type is not guaranteed. As of 2013, it seems that most implementations use binary heaps.

                For specific heaps such as Fibonacci, consider [Boost](http://www.boost.org/doc/libs/1_49_0/doc/html/heap.html).

                <http://stackoverflow.com/questions/14118367/stl-for-fibonacci-heap>

                There is no concrete heap data structure in C++:
                only heap operations over random access data structures.
                This is why this is under algoritms and is not a data structure of its own.

                There is however a `priority_queue` stdlib container.

                Why random access structure is needed: <https://github.com/cirosantilli/comp-sci/blob/1.0/src/heap.md#array-implementation>
            */
            {
                int myints[]{10, 20, 30, 5, 15};
                std::vector<int> v(myints, myints + 5);

                /*
                # make_heap

                    Make random access data structure into a heap.

                    This changes the element order so that the range has heap properties

                    Worst case time: $O(n)$.
                */
                    std::make_heap(v.begin(), v.end());
                    assert(v.front() == 30);

                /*
                # pop_heap

                    Remove the largest element from the heap.

                    That element is moved to the end of the data structure, but since the
                    heap should have its length reduced by one, that element will then be out of the heap.

                    Assumes that the input range is already a heap (made with `make_heap` for example).
                */
                    std::pop_heap(v.begin(), v.end());

                    //the element still exists on the data structure
                    assert(v.back() == 30);

                    //the second largest element hat become the largets
                    assert(v.front() == 20);

                    //remove the element from the data structure definitively
                    v.pop_back();

                /*
                # push_heap

                    Insert element into a heap.

                    Assumes that:

                    - the range 0 - (end - 1) was already a heap
                    - the new element to be inserted into that heap is at end.
                */

                    //add the new element to the data structure
                    v.push_back(99);

                    //reorganize the data so that the last element will be placed in the heap
                    std::push_heap(v.begin(), v.end());

                    assert(v.front() == 99);

                /*
                # sort_heap

                    Assumes that the input range is a heap, and sorts it in increasing order.

                    The assumption that we have a heap allows for $O(ln)$ sorting,
                    much faster than the optimal bound $O(n log n)$.

                    This is exactly what the heapsort alrotithm does: make_heap and then sort_heap.
                */

                    std::sort_heap(v.begin(), v.end());
                    //assert(v)
                    //v == 5 10 15 20 99
            }
        }

#if __cplusplus >= 201103L
        /*
        # functional

            Do magic with functions.

            Useful with stdlib functions that take functions as arguments.
        */
        {
            /*
            # bind2nd

                Tranform a function that takes two arguments into a function that takes only the first.

                Useful with stdlib functions that must take functions that take a single argument,
                but you want to pass an extra parameter to that function.

                TODO0 get working
            */
            {
                /*
                std::vector<int> v = {2, 0, 1};
                assert(std::find_if (
                    v.begin(),
                    v.end(),
                    std::bind2nd([](int i, int param){return i == param + 1;}, 1)
                ) == v.begin());
                */
            }
        }
#endif

        /*
        # hash

            <http://www.cplusplus.com/reference/functional/hash/>

            The stdlib furnishes overloaded hash functions for stdlib containers.

            Those functions are implemented as callable classes that implement `()`.

            For base types, those hashes are found under the `functional`.

            For std::vectors, only `std::vector<bool>` has a template.

            For other types, they are found in the same header that defines those types:
            ex: hash for std::vectors is under `<vector>`.

            Returns a `size_t` result.
        */
        {
            std::cout << "hash" << std::endl;
            std::cout << "  1 = "        << std::hash<int>()(1) << std::endl;
            std::cout << "  string abc = "    << std::hash<std::string>()("abc") << std::endl;
        }

#if __cplusplus >= 201103L
        /*
        # regex

            Finally they are supported!

            Many types are supported: Javascript, grep, awk, ...

            It is probably saner and more powerful to stick to Javascript regexes.
        */
        {
            // Js has `[:d:]` equivalent POSIX `[:digit:]`.
            std::regex r("a.(c|d)");
        }
#endif

        // # memory
        {
#if __cplusplus >= 201103L
            /*
            # shared_ptr

                Introuced in C++11.

                Before that as part of boost.
            */
            {
                {
                    callStack.clear();
                    std::shared_ptr<NoBaseNoMember> spi1(new NoBaseNoMember);
                    std::shared_ptr<NoBaseNoMember> spi2(spi1);
                    spi1->method();
                    spi1 = std::shared_ptr<NoBaseNoMember>(new NoBaseNoMember);
                    spi2 = std::shared_ptr<NoBaseNoMember>(spi1);
                    assert(callStack.back() == "NoBaseNoMember::~NoBaseNoMember()");
                }
            }
#endif
        }

#if __cplusplus >= 201103L
        /*
        # thread #multithreading #parallel #concurrency

            Requires `-pthread` flag on g++ Linux.
        */
        {
            // Start threads.
            std::thread t1(threadFunc, 1000);
            std::thread t2(threadFunc, 1000);

            // Ensure that both threads ended.
            t1.join();
            t2.join();

            assert(threadChange > 0);
            //assert(threadIds.size() == 2);
            //assert(threadGlobalEq0 > 0);
            assert(threadGlobalMutexedEq0 == 0);

            std::thread::id mainId = std::this_thread::get_id();
            std::this_thread::sleep_for(std::chrono::nanoseconds(nNsecs));
            std::this_thread::yield();
        }
    }
#endif

    /*
    # preprocessor

        Almost the same as the C one:
        http://stackoverflow.com/questions/5085533/is-a-c-preprocessor-identical-to-a-c-preprocessor
    */
    {
        /*
        # standard preprocessor defines
        */
        {
            /*
            # __cplusplus

                Defined only if using C++ compiler.

                Its value is the actual C++ version in use in a similar way to __STDC_VERSION__

                Values:

                - C98: 199711L
                - C11: 201103L
            */
            {
#ifdef __cplusplus
            printf("__cplusplus = %li\n", __cplusplus);
#endif
            }
        }
    }

#if __cplusplus >= 201103L
    /*
    # Attributes

        Implemented as extensions for a long time in GCC via `__attribtes__`
        and in Microsoft with `#pragma`. Now some have been standardized!

        Intended only for functions which don't change behaviour: only to help
        compilers optimize or geneate better error messages.

        <http://www.stroustrup.com/C++11FAQ.html#attributes>

        Attributes can be defined for various objects, and there are 2 standard ones:
        noreturn and carries_dependency
    */
    {
        try {
            noreturn_func();
        } catch (int i) {}
    }
#endif

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

        // Allocation.
        {
            stack1bProf(nProfRuns);
            stack1kbProf(nProfRuns);
            stack1mbProf(nProfRuns);

            heapMalloc1bProf(nProfRuns);
            heapMalloc1kbProf(nProfRuns);
            //heapMalloc1mbProf(nProfRuns);

            heapNew1bProf(nProfRuns);
            heapNew1kbProf(nProfRuns);
            // new is faster!
            //heapNew1mbProf(nProfRuns);
        }

        methodCallProf(nProfRuns);
        // 2x as expensive than function call
        virtualMethodCallProf(nProfRuns);

        // BAD: don't do stdout on profiling
        // system time is not counted anyways
        //putsProf(nProfRuns);
#endif

    // # Design patterns
    {
        //VisibleInnerIterable
        {
            VisibleInnerIterable c;
            VisibleInnerIterable::Iterable ita = c.getIterable();
            VisibleInnerIterable::Iterable::iterator it = ita.begin();

            int i;
            int is[]{0,1,2};
            for (
                it = ita.begin(), i=0;
                it != ita.end();
                ++it, ++i
            )
            {
                assert(*it == is[i]);
            }
        }
    }

    /*
    # Idioms

        Basically very small design patterns.
    */
    {
        /*
        # Dynamic multi-dimensional array

            Sources: <http://www.cplusplus.com/forum/articles/7459/>

            In addition to C malloc like techniques, C++ also offers the simpler possibility of using std::vectors
            which will automatically  manage the memory allocation / dellocation for us.

            The tradeoff is that this method will be potentially slower since it:

            -   requires constructor calls at non uniform initialization.

            -   may require function calls for the `[]` operator overload.

                It is however likely that the compiler will inline those.
        */
        {
            // Given width and height.
            {
                int width = 2, height = 3;
                std::vector<std::vector<int>> array_2d(height, std::vector<int>(width));
                array_2d[0][0] = 1;
                array_2d[2][1] = 5;
                assert(array_2d[0][0] == 1);
                assert(array_2d[0][1] == 0);
                assert(array_2d[2][1] == 5);
            }

            // Uniform initialized.
            {
                std::vector<std::vector<int>> array_2d{
                    {0, 1},
                    {2, 3},
                    {4, 5},
                };
                assert(array_2d[0][0] == 0);
                assert(array_2d[2][1] == 5);
            }
        }
    }

    /*
    # main return

        Like in C99, C++ return can omit the return, in which case it returns 0.
    */

        std::cout << "ALL ASSERTS PASSED" << std::endl;
        return EXIT_SUCCESS;

    // global/static destructors happen at exit time.
}
