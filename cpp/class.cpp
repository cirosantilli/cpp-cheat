/*
# class

    TODO split this up.
*/

#include "common.hpp"

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
                https://stackoverflow.com/questions/12927169/how-can-i-initialize-c-object-member-variables-in-the-constructor
            2) initializing base classes with non default constructors
            3) initializing const elements
            4) initializing member references &
            5) C++11 delegating constructors: call another constructor of the current class
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
        }

        void constMethod() const;
        void constMethod(int *&) const;

        void methodAmbiguous(){callStack.push_back("Base::methodAmbiguous()");}

        // virtual: decides on runtime based on object type
        // http://stackoverflow.com/questions/2391679/can-someone-explain-c-virtual-methods
        virtual void virtualMethod(){callStack.push_back("Base::virtualMethod()");}

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

        /*
        # member initialization outside of constructor
        */

            const int iConstInit = 0;

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
        http://stackoverflow.com/questions/105014/does-the-mutable-keyword-have-any-purpose-other-than-allowing-the-variable-to
    */
    this->mutableI = 1;

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

// Must come outside
const Member Base::member2 = Member(1);

// ERROR: must be declared inside.
//int Base::k;

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
    // ERROR: duplicate.
    //public Base,
    // WARN: cannot use BasePrivate inside: ambiguous.
    //public Derived,
    protected BaseProtected,
    private BasePrivate
{
    public:

        /*
        Call base constructors first.
        */
        Class() : i(0), z(1) {
            callStack.push_back("Class::Class()");
        }

        Class(int i) : i(i), z(0) {
            callStack.push_back("Class::Class(int)");
        }

        /*
        Calls specific base constructors  instead of default ones
        another application os initialization lists.
        */
        Class(int i, int z) : Base(i,z), BaseProtected(i), BasePrivate(i), i(i), z(z) {
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
            // BAD: m constructor would be called, but this is useless since we have already called it!
            // to construct it before.
            // This is an application of initialization constructors.
            //this->m = m;

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

        int i;
        int z;
        Member m;
        Nested nested;
        //Base nested class visible from here
};

//nested

    // OK: you can see the nested class from derived classes
    class NestedDerived : Class::Nested{};

class Class2 : public Base {
    public:
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

// Design patterns

    // VisibleInnerIterable

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

int main() {
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

            http://en.cppreference.com/w/cpp/language/default_constructor

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

            There are other functions which are also defined by default:
            https://en.wikipedia.org/wiki/Special_member_functions

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
                // Undefined behaviour.
                //assert(o.i == 0);
                assert(o.s == std::string());

                o = DefaultKeyword(1, "a");
                assert(o.i == 1);
                assert(o.s == "a");
            }

            /*
            # delete keyword
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
        Value initialization and zero initialization are both a bit subtle,
        so it is best not to rely on them.

        C++ has 3 types of init

        # Default initialization

        # Value initialization

        # Zero initialization

            - http://en.cppreference.com/w/cpp/language/value_initialization
            - http://en.cppreference.com/w/cpp/language/zero_initialization
            - http://stackoverflow.com/questions/1613341/what-do-the-following-phrases-mean-in-c-zero-default-and-value-initializat

        # Aggregate initialization

            http://en.cppreference.com/w/cpp/language/aggregate_initialization

        # POD

            Plain old data:

            https://stackoverflow.com/questions/146452/what-are-pod-types-in-c
            http://stackoverflow.com/questions/4178175/what-are-aggregates-and-pods-and-how-why-are-they-special
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

            http://stackoverflow.com/questions/5113365/do-built-in-types-have-default-constructors

            C++ adds new ways to initialize base types.

            Those are not however constructors.

            They probably just mimic constructor syntax to help blurr the distinction
            between built-in types and classes and make templates and typedefs work better.
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

    /*
    # Destructor

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
        }
        // Destructor is called now!

        std::vector<std::string> expectedCallStack = {
            "NoBaseNoMember::NoBaseNoMember()",
            "NoBaseNoMember::~NoBaseNoMember()"
        };
        assert(callStack == expectedCallStack);
    }

    // # Array of objects
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

        std::vector<std::string> expectedCallStack{
            "NoBaseNoMember0::NoBaseNoMember0()",
            "NoBaseNoMember1::NoBaseNoMember1()",
            "MemberConstructorTest::MemberConstructorTest()",
            "MemberConstructorTest::~MemberConstructorTest()",
            "NoBaseNoMember1::~NoBaseNoMember1()",
            "NoBaseNoMember0::~NoBaseNoMember0()",
        };
        assert(callStack == expectedCallStack);
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

        Therefore the following may be more effecitive due to copy elision:

            NoBaseNoMember c = NoBaseNoMember();

        in which case only a single constructor is called.
        Copy elision in this case is widely implemented.
        */
        {
            callStack.clear();
            NoBaseNoMember c;       // 1 constructor
            c = NoBaseNoMember();   // 1 constructor of the temporary, 1 assign, 1 destructor of the temporary
            std::vector<std::string> expectedCallStack{
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
            std::vector<std::string> expectedCallStack{
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
    # Copy and assign constructors

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
        // Every class has a default copy operator and assign constructor.
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
                std::vector<std::string> expectedCallStack{
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
                std::vector<std::string> expectedCallStack{
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

        /*
        # as-if rule

            <http://en.cppreference.com/w/cpp/language/as_if>

            Rule that specifies that compilers can optimize any behaviour that is not fixed by the standard.

            The following are specified:

            - Accesses (reads and writes) to the volatile objects occur in the same order as written.

            - At program termination, the data written to all files is exactly as if the program was executed as written.

            - All input and output operations occur in the same order and with the same content
                as if the program was executed as written.

            The only exception to the rule is copy elision.
        */

        /*
        # copy elision

            - http://en.cppreference.com/w/cpp/language/copy_elision
            - http://stackoverflow.com/questions/12953127/what-are-copy-elision-and-return-value-optimization

            Exceptions to the as-if rules, which specifies cases in which compilers
            may reduce the number of copy operations made, which is detectable in C++'
            because of possible side effects constructors and destructors (such as printing to stdout
            or modifying a global std::vector).
        */
        {
            /*
            # temporary copy elision

                If no copy elision is done:

                1. temporary object constructor
                2. copy temporary to c
                3. temporary object destructor

                If copy elision is done:

                1. c is constructed directly.

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
        }
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
