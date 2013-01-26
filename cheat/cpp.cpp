/*
this will focus in differences between cpp and c.
for the rest, go to c.c

good general resources

- http://www.cplusplus.com
    explains well what most the features of the language do for beginners
    no motivation, many features missing, no stdlib.
- http://yosefk.com/c++fqa/
    comments on the quirks of c++
    fun and informative for those that know the language at intermediate level
- http://geosoft.no/development/cppstyle.html
    coding guidelines, clearly exemplified

#headers

    stdlib headers don't have the .h extension

    when writting new libs, you use the extension ``.h`` or ``.hpp``

    with ``g++`` those get linked to automatically

    #c stdlin can be accessed

        math vs cmath, X vs cX

        cX puts things in std:: namespace. *always* use it.
        X.h puts *all* in the global namespace. *never* use it.

- language versions

    latest: C++11
        previously known as C++0x
        but took too long to come out
        in gcc: add -c++0x flag
    previous: C++03

    http://en.wikipedia.org/wiki/C%2B%2B11

- returning references
        http://stackoverflow.com/questions/795674/which-are-the-implications-of-return-a-value-as-constant-reference-and-constant?rq=1

*/

#include <iostream>
//cout

#include <string>
//string

#include <exception>
//exception base exception class
    //bad_alloc	thrown by new on allocation failure
    //bad_cast	thrown by dynamic_cast when fails with a referenced type
    //bad_exception	thrown when an exception type doesn't match any catch
    //bad_typeid	thrown by typeid
    //ios_base::failure	thrown by functions in the iostream library

#include <vector>  

#include <set>  

#include <algorithm>

#include <memory>

#include <cstdlib>

#include <cassert>

using namespace std;
//namespace for entire source file from now on
 
class Member
{
    public:
        Member(){ cout << "Member::Member()" << endl; }
        Member(int i){ cout << "Member::Member(int)" << endl; }
        ~Member(){ cout << "Member::~Member()" << endl; }

        void method() { cout << "Member::method()" << endl; }

        int i;
};

class Nested
{
    public:

        Nested()
        {
            cout << "Nested::Nested()" << endl;
        }
};
 
class Base
{
    public:

        /*
        default constructor
            if no constructor is declared, a default constructor is created

            if any constructor is declared, even with non default args,
            the default is not created
         */
        Base() : i(0), j(1) //list initialization
        { 
            cout << "Base::Base()" << endl; 
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
            cout << "Base::Base(int, int)" << endl;
        }

        //virtual Base(float f){}
            //ERROR constructor cannot be virtual
  
        Base(float f) : fs4{f,f,f,f}
        {
            cout << "Base::Base(float)" << endl;
        } 
            //C++11
            //must init entire array

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
            cout << "Base::~Base()" << endl;
        }

        void method()
        {
            cout << "Base::method()" << endl;
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

        void methodAmbiguous(){ cout << "Base::methodAmbiguous()" << endl; }

        virtual void virtualMethod(){ cout << "Base::virtualMethod()" << endl; }
        //virtual: decides on runtime based on object type
            //http://stackoverflow.com/questions/2391679/can-someone-explain-c-virtual-methods
 
        virtual Base* covariantReturn()
        {
            cout << "Base:covariantReturn()" << endl;
            return new Base;
        }

        virtual void covariantArg(Base* b)
        {
            cout << "Base:covariantArg()" << endl;
        }
    
        int i,j;
        //ERROR: cannot initialize here
            //int i = 0;

        int iAmbiguous;

        int* is;

        float fs4[4];

        //BAD: every class must have an assigment operator
        //but then, assigment does something like this->ic = other->ic
        //you could redefine the assigment, but still in your new definition
        //ic cannot be changed
        //http://stackoverflow.com/questions/634662/non-static-const-member-cant-use-default-assignment-operator
            //const int ic;
    
        //static
        
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

        class Nested
        {
            public:

                Nested()
                {
                    cout << "Base::Nested::Nested()" << endl;
                    cout << "privateStaticInt: " << privateStaticInt << endl;
                    //yes, you have private access
                }

                Member m;
        };
        
        class Nested2
        {
            public:

                Nested2()
                {
                    cout << "Base::Nested2::Nested2()" << endl;
                }

                Nested innerIn;
                //inner one
                
                ::Nested innerOut;
                //outter one
        };

    protected:

        int iProtected;
        void fProtected(){ cout << "Base::fProtected()" << endl; }

    private:

        int iPrivate;
        void fPrivate(){ cout << "Base::fPrivate()" << endl; }
        const static int privateStaticInt = 1;

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

    cout << "Base::constMethod()" << endl;
}

//void Base::constMethod () {}
    //ERROR
    //must not ommit the const here either

int Base::iStatic = 0;

void Base::staticMethod()
{
    cout << "Base::staticMethod()" << endl;

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

        void method(){ cout << "BaseAbstract::method()" << endl; }

        void methodAmbiguous(){ cout << "BaseAbstract::methodAmbiguous()" << endl; }

        virtual void virtualMethod(){ cout << "BaseAbstract::virtualMethod()" << endl; }
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
            cout << "common before" << endl;
            privatePureVirtual();
            cout << "common after" << endl;
        }
};

class PureVirtualImplementedOtherBase
{
    public:

        void pureVirtualImplementedOtherBase()
        {
            cout << "PureVirtualImplementedOtherBase::pureVirtualOtherBase()" << endl;
        }
};

class BaseProtected
{
    public:

        BaseProtected(){ cout << "BaseProtected::BaseProtected()" << endl; }
        BaseProtected(int i){ cout << "BaseProtected::BaseProtected(int)" << endl; }
        ~BaseProtected(){ cout << "BaseProtected::~BaseProtected()" << endl; }
};

class BasePrivate
{
    public:
        BasePrivate(){ cout << "BasePrivate::BasePrivate()" << endl; }
        BasePrivate(int i){ cout << "BasePrivate::BasePrivate(int)" << endl; }
        ~BasePrivate(){ cout << "BasePrivate::~BasePrivate()" << endl; }
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
            cout << "Class::Class()" << endl;
        }

        Class(int i) : i(i), z(0)
        {
            cout << "Class::Class(int)" << endl;
        }

        Class(int i, int z) : Base(i,z), BaseProtected(i), BasePrivate(i), BaseAbstract(), i(i), z(z)
        {
            cout << "Class::Class(int, int)" << endl;
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
            cout << "Class::Class(int, int, int)" << endl;
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
            cout << "Class::Class(Member)" << endl;
        }

        //copy constructor
            //classes already have this by default
            //useful to customize if class does dynamic allocation!
        Class(const Class& c) : i(c.i), z(c.z), m(c.m)
        {
            cout << "Class::Class(Class)" << endl;
        }

        //assign operator
            //all classes come with a default
            Class& operator=(const Class& rhs)
            {
                cout << "Class::operator=(Class)" << endl;
                i = rhs.i;
                z = rhs.z;
                m = rhs.m;
                return *this; //so shat a = b = c may work
            }
        
        /*
        also calls Base destructor after
        */
        ~Class(){ cout << "Class::~Class()" << endl; }

        void method(){ cout << "Class::method()" << endl; }
        //called method overwriding
        
        template<class C=int>
        void methodTemplate()
        {
            cout << "Class::methodTemplate()" << endl;
        }
            //OK
 
        void virtualMethod(){ cout << "Class::virtualMethod()" << endl; }
            //different than overwriding non virtual methods. see polymorphism.
        
        //virtual void virtualMethod(){ cout << "Class::virtualMethod()" << endl; }
            //OK
            //only difference:
            //if you have a pointer to this class, you can only use virtual if this
            //is declared virtual
        
        void pureVirtual(){ cout << "Class::pureVirtual()" << endl; }
        //definition obligatory if you want to create objects of this class

        //int pureVirtual(){ return 1; }
            //ERROR
            //unlike function overloading, polyomorphism is decided at runtime
            //and therefore return type must be the same as in declaration

            virtual Class* covariantReturn()
            { 
                cout << "Class:covariantReturn()" << endl;
                return new Class;
            }
                //OK
                //because Class is derived from Base
                //callde "covariant return type"
  
                //virtual Class invalidCovariantReturn(){ return Class(); }
                    //ERROR invalid covariant
                    
                    
            virtual void covariantArg(Class* c)
            {
                cout << "Class:covariantArg()" << endl;
            }

        int i;
        int z;
        Member m;
        Nested nested;
        //Base nested class visible from here

    private:

        virtual void privatePureVirtual(){ cout << "Class:privatePureVirtual()" << endl; };
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
        void pureVirtual(){ cout << "Class2::pureVirtual()" << endl; }

        class Nested{};
        //OK
        //you can override the Nested class from the Base also
};

class ClassCast
{
    ClassCast(Class c){}
};

    //ERROR
        //ClassDefault::ClassDefault(int i=0){}

//templates class
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

            TemplateClass(){ cout << "TemplateClass::TemplateClass()" << endl; }

            //BAD: what is T = string?
                //TemplateClass() t(0.0){ cout << "TemplateClass::TemplateClass()" << endl; }

            TemplateClass(T t): t(t){ cout << "TemplateClass::TemplateClass(T)" << endl; }

            void method()
            {
                cout << "TemplateClass::method()" << endl;
            }
            
            void methodDefinedOutside();

            T method(T){ cout << "TemplateClass::method(T)" << endl; }

            template<class C=int>
            void methodTemplate()
            {
                cout << "TemplateClass::methodTemplate()" << endl;
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

    template<class BASE, class T, int N>
    void TemplateClass<BASE,T,N>::methodDefinedOutside()
    {
            cout << "TemplateClass::methodDefinedOutside()" << endl;
    }
        //c++11
        //even if independent on template args, still cannot be pre compiled
 

    //specialization
 
        template<>
        void TemplateClass<Base,int,11>::methodDefinedOutside()
        {
            cout << "TemplateClass<Base,int,11>::methodDefinedOutside()" << endl;
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
                    cout << "TemplateClass<Base,int,12>::newMethod()" << endl;
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


//global scope
    int global = 0;

    //NOTE different from c, where these were errors
        int global2 = global+1;
        int ret1(){
            cout << "before main!" << endl;
            return 1;
        }
        int global3 = ret1();

    //ERROR everything must start with a typename
        //global = 1;
        //if(1){}
        //cout << "global" << endl;

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
        void overload(int i){ cout << "overload(int)"; }
        void overload(int i, int j){ cout << "overload(int,int)"; }
        void overload(float i){ cout << "overload(float)"; }
        void overload(float i, float j, float k=0.f){ cout << "overload(float,float,float=)"; }

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
            //or wil get ``call is ambiguous`` compile time error
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
            //this can be reset with ``-ftemplate-depth``
 

//namespaces
    //- *never* use ``using namespace X`` on a header file

    //namespace 2D{}
        //ERROR
        //same naming rules as vars

    namespace D2{}
        //BAD
        //by convention, start upper case

    int i;

    void f()
    {
        cout << "::f" << endl;
    }

    void prototype();

    namespace namea
    {

        class C
        {
            public:
                C()
                {
                    cout << "namea::C" << endl;
                }
        };

        namespace nameaa
        {
            int i;

            void f()
            {
                cout << "nameaa::f" << endl;
            }

            class C
            {
                public:
                    C()
                    {
                        cout << "nameaa::C" << endl;
                    }
            };
        }

        namespace nameab
        {
            int i;

            void f()
            {
                cout << "namea::nameab::f" << endl;

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
                    cout << "namea::nameab::C" << endl;
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
            cout << "namea::f" << endl;
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

int main(int argc, char** argv)
{
    bool b;
    int i = 0;
    int is2[2];
    unsigned int ui = 1;
    //NOTE no warn
    unsigned int uiNeg = -1;
    int * ip;

    //WARN makes sense, in c, no WARN!
    //if(ui<i)
        //cout << "ui<i" << endl;

    cout << "io" << endl;
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

    cout << "for" << endl;
        //you can define i inside the for scope only
        for(int i=0; i<5; i++)
            cout << i << " ";
    cout << endl;

    cout << "array" << endl;

        //cin >> i;
        //int is4[i];
            //UNPORTABLE: gcc extension
            //
            //C99 supports
            //
            //compiler implementation:
            //must increment/decrement stack pointer at each array
            //meaning, one extra multiplication and sum for every VLA declared

        //cin >> i;
        //int is4[i] = {1,2}
            //ERROR, cannot initialize. what if i<2?

    cout << endl;

    cout << "const" << endl;

        const int ic=2;
        //ERROR: in c this is only a warning, and allows us to change ic.
            //int* ip = ic;
 
        //ERROR: must be initialized, since in c++ consts really are consts
            //const int ic2;

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

    cout << endl;

    cout << "references" << endl;
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
            int i=1;
            cout << i << endl;
            byref(i);
            cout << i << endl;
        }

        {
            cout << "int i = 1;" << endl;
            int i=1;
            cout << "int& ia = i;" << endl;
            int& ia = i;
            cout << "ia = 2;" << endl;
            ia = 2;
            cout << "i = " << endl;
            cout << i << endl;
            //2
            cout << "&ia" << endl;
            cout << &ia << endl;
            cout << "&i" << endl;
            cout << &i << endl;
            //SAME
                //therefore no extra memory is used for references
                //whereas pointers use memory
            cout << "int& ia2 = ia;" << endl;
            int& ia2 = ia;
            cout << "ia2 = 3;" << endl;
            ia2 = 3;
            cout << "i == " << endl;
            cout << i << endl;
            //3

            //ERROR: must be a variable rhs
                //int& ia = 5;

            //ERROR: must be initialized immediatelly
                //int& ia;
        }

        {
            int i = 1;
            int * ip = &i;
            int& ia = *ip;
        
            //ERROR: & must get a variable/dereferenced pointer, not pointers themselves!
                //int& ia = &i;
                //int& ia = new int;
        }

        {
            int i=1;
            const int& cia = i;

            //ERROR
                //cia = 2;

            //ERROR: invalid conversion
                //int* ip = &cia;

            const int& cia2 = cia;

            //ERROR: invalid conversion
                //int& ia = cia;

            //ERROR: no array of references forbidden
                //int& is[2] = {i,i};

            const int ci = 1;
            const int& ciac = ci;

            //int& iac = ci;
                //ERROR
                //must be const int&
        }

        cout << "return" << endl;
            //never from functions (if new, return auto_ptr, if not new, you got an error)
            //only from methods, when data is in the object
            //just like pointers, if object dies, data dies!

            {
                //you can modify a private
                    Base b;
                    int& i = b.getPrivate();
                    i = 1;
                    cout << b.getPrivate() << endl;
                    i = 2;
                    cout << b.getPrivate() << endl;
            }

            {
                //now you can only see, not modify
                    Base b;
                    const int& i = b.getPrivateConst();
                    //i = 1;
                    cout << i << endl;
            }

        cout << endl;

    cout << endl;

    cout << "functions" << endl;

            cout << "overload" << endl;

                overload(1);
                overload(1.0f);

                //overload(1.0);
                    //ERROR: ambiguous overload(int) overload(float)
                    //compiler does not know wether convert double to float or int

                //Class cOverload;
                //overloadBase(cOverload);
                    //ERROR ambiguous
                    //coverts to Base or BaseProtected

                //i=4;
                //overloadValAddr(i);
                    //ERROR: ambiguous

            cout << endl;

            cout << "template" << endl;

                cout << "factorial<9>();" << endl;
                cout << factorial<9>() << endl;
                    //because of this call, all factorials from
                    //1 to 9 will be compiled

                cout << "factorial<20>();" << endl;
                cout << factorial<20>() << endl;
                    //because of this call, all factorials from
                    //1 to 20 will be compiled

            cout << endl;

    cout << endl;

    cout << "data types" << endl;

        //contrary to c, in cpp there is a bool type
        b = true;
        cout << true << endl;
        //1
        cout << false << endl;
        //0
 
    cout << endl;

    cout << "string" << endl;

        //in cpp, strings are classes, much more convenient to manipulate
        
        {
            //create
            string s("s");
            string s1 = "s1";
            string s2;

            cout << s << endl;
            //s

            cout << "concat" << endl;
            cout << "s + s1" << endl;
            s2 = s + s1;
            cout << s2 << endl;
            //s2

            cout << "s == s1" << endl;
            cout << (s == s1) << endl;
            //0
            
            cout << "s == s" << endl;
            cout << (s == s) << endl;

            cout << "s.length()" << endl;
            cout << s.length() << endl;
            //1
        }

        {
            string s("s");
            s[0] = 't';
            s[1] = 't';
            //WARN
            //no born check!
        }
    
    cout << endl;

    cout << "class" << endl;
    
        Class *cp, *classPtr;
        Class c, c1;
        Base *bp, *basePtr;
        Member m;

        //creation
            {
                cout << "Class c;" << endl;
                Class c;
                //Base Class
                    //Base and Class constructor are called!
                    //if no default constructor, error
                //there is a default constructor if you don't define any constructor
                    //but if you define any constructor (even non null), you have to write
                    //the empty one yourself, so just write it always
            }

            {
                cout << "Class c;" << endl;
                Class c;
                cout << "c = Class();" << endl;
                c = Class();
                //total 2 constructor calls
            }

            {
                cout << "Class c = Class();" << endl;
                Class c = Class();
                //single constructor call
            }

            {
                //Class c();
                //c.i = 1;
                    //ERROR
                    //declares *FUNCTION* called ``c()`` that returns ``Class``
                    //functions inside functions like this are a gcc extension

            }

            //static
            {
                Class c, c1;
                int i;
                c.iStatic = 0;
                cout << c1.iStatic << endl;
                //0
                c.iStatic = 1;
                cout << c1.iStatic << endl;
                //1
                Class::iStatic = 2;
                cout << c1.iStatic << endl;

                c.staticMethod();
                Class::staticMethod();

                i = c.iConstStatic;
            }
                
        cout << endl;

        cout << "copy, assigment" << endl;
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
                cout << c1.i << endl;
                //1
                cout << "Class c2 = c" << endl;
                Class c2 = c;
                //SAME
                    //*COPY CONSTRUCTOR CALLED, NOT ASSIGN CONSTRUCTOR*
                    //because object is being created
                cout << c2.i << endl;
            }

            {
                Base b;
                //Class c(b);
                    //ERROR
                    //no constructor
            }

            {
                Class c;
                c.Base::i = 1;
                Base b(c);
                    //OK
                    //copy base fields
                    //can transform derived into base implicitly
                cout << b.i << endl;
                //1
            }

            {
                //assign operator
                //default assign calls assign (=) on all members
                Class c, c1;
                c.i = 1;
                c1.i = 2;
                c1 = c;
                cout << c1.i << endl;
                //1
            }

            //there are default copy/assign funcs from base classes
            //they assign/copy to base object fields inherited from derived only
                c = Class();
                cout << "Base base(c);" << endl;
                Base base(c);
                cout << "base = Class();" << endl;
                base = Class();

                //c = base;
                    //ERROR
                    //not from derived to base

            //pointer conversions
                bp = &c;

                //bp = &m;
                //cp = &base;
                    //ERROR
                    //can only convert from derived to base

        cout << endl;

        cout << "arrays of objects" << endl;

            {
                cout << "Class os[3];" << endl;
                Class cs[3];
                //3x Class() calls!
                    cs[0] = Class(1);
                    cs[1] = Class(2);
                    cs[2] = Class(3);

                //initialized
                    cout << "Class cs2[] = {Class(1), Class(2), Class(3)};" << endl;
                    Class cs2[] = { Class(1), Class(2), Class(3) };
                    //3x Class() calls. more efficient therefore
            }

        cout << endl;

        cout << "temporaries" << endl;

            cout << "Class().method();" << endl; //an instance without name is created and destroyed
            Class().method();
            //Class() Class().method1() ~Class

            cout << "cout << Class();" << endl;
            cout << Class() << endl;
            //i j

        cout << endl;
 
        //ERROR
            //Class* cp = &Class();
                //address of what?
            c = Class();
            cp = &c;

        cout << "operator overload" << endl;

            c.i = 1;
            c.j = 2;
            cout << "cout << c;" << endl;
            cout << c << endl;
            //1 2

        cout << endl;

        cout << "template" << endl;

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
                cout << "TemplateClass<Base,int,10>().methodDefinedOutside<>();" << endl;
                TemplateClass<Base,int,10>().methodDefinedOutside();
                cout << "TemplateClass<Base,int,11>().methodDefinedOutside<>();" << endl;
                TemplateClass<Base,int,11>().methodDefinedOutside();
                cout << "TemplateClass<Base,int,12>().methodDefinedOutside<>();" << endl;
                TemplateClass<Base,int,12>().newMethod();
                //TemplateClass<Base,int,12>().method();
                    //12 class does not contain method()
            }

        cout << endl;

        cout << "overwridding" << endl;

            {
                Class c;
                Class* cp = &c;

                c.i = 0;
                c.Class::i = 0;
                cp->Class::i = 0;
                c.Base::i = 1;
                c.BaseAbstract::i = 2;

                cout << c.i << endl;
                cout << c.Class::i << endl;
                cout << cp->Class::i << endl;
                //0

                cout << c.Base::i << endl;
                cout << cp->Base::i << endl;
                //1

                cout << c.BaseAbstract::i << endl;
                cout << cp->BaseAbstract::i << endl;
                //2

                //c.iAmbiguous = 0;
                    //ERROR ambiguous
                c.Base::iAmbiguous = 0;
                c.BaseAbstract::iAmbiguous = 0;

                c.method();
                //Class
                c.Base::methodAmbiguous();
                c.BaseAbstract::methodAmbiguous();
                //c.methodAmbiguous();
                    //ERROR ambiguous
            }

        cout << endl;

        cout << "polymorphism" << endl;

            //behind the scenes a *vtable* is used to implement this

            //BaseAbstract b;
                //ERROR: BaseAbstract cannot be instantiated because it contains a pure virtual method
                //virtual = 0;. That method must be implemented on derived classes
              
            //even if you can't instantiate base, you can have pointers to it
            {
                cout << "BaseAbstract* bap = new Class;" << endl;
                BaseAbstract* bap = new Class;
                //SAME
                    //bap = &c;
                cout << "bap->method();" << endl;
                bap->method();
                //base method because non-virtual
                cout << "bap->virtualMethod();" << endl;
                bap->virtualMethod();
                //class method because virtual
                delete bap;
            }

            {
                //you can also have BaseAbstract&
                cout << "Class c;" << endl;
                Class c;
                cout << "BaseAbstract& ba = c;" << endl;
                BaseAbstract& ba = c;
                cout << "ba.method()" << endl;
                ba.method();
                //base
                cout << "ba.virtualMethod()" << endl;
                ba.virtualMethod();
                //derived
            }

            {
                cout << "covariantReturn" << endl;
                Class c = Class();
                Base* bp = &c;
                bp = bp->covariantReturn();
                cout << "bp->virtualMethod();" << endl;
                bp->virtualMethod();
                //Class

                //classPtr = basePtr->covariantReturn();
                    //ERROR
                    //conversion from Base to Class
            }

        cout << endl;

        cout << "typecasting" << endl;
            //http://www.cplusplus.com/doc/tutorial/typecasting/

            //implicit via constructor/assigment
                //class A {};
                //class B { public: B (A a) {} };
                //A a;
                //B b=a;

        cout << endl;

        cout << "inner classes" << endl;

            {
                cout <<"Base::Nested baseNested;" << endl;
                Base::Nested baseNested;
                cout << "Base::Nested2 baseNested2;" << endl;
                Base::Nested2 baseNested2;
            }

        cout << endl;

    cout << endl;

    cout << "dynamic memory" << endl;

        ip = new int [5];
        ip[0] = 1;
        delete [] ip;

        //can also alocate single int
            //useless of course
            //but is might be useful to allocate a single object
            ip = new int;
            *ip = 1;
            delete ip;

        cout << "new Class;" << endl;
        cp = new Class;
        //SAME cp = new Class();
        cp->i = 10;
        delete cp;
        //calls destructor
        cout << endl;

        cout << "new Class[2];" << endl;
        cp = new Class[2];
        cp[0].i = 3;
        cp[1].i = 4;
        delete [] cp;
        //calls destructors
        cout << endl;

        ip = new int;
        delete ip;
        //BAD: undefined behavior, maybe crash
            //delete ip;
        
        ip = new int;
        //BAD: memory leak. memory is lost forever.
            //ip = new int;
        delete ip;

        //BAD: undefined behavior, maybe crash. ip was not allocated!
            //delete ip;

    cout << "exceptions" << endl;
        //TODO
        //
    cout << endl;

    cout << "enum" << endl;

        enum TEXTURE { GRASS, WALL, SKY };
        TEXTURE t = GRASS;
        //unlike c, already does typedef
        //check this to give values
            //http://msdn.microsoft.com/en-us/library/2dzy4k6e%28v=vs.71%29.aspx

        //ERROR
            //enum E2 { E2=i };
            //only const expressions allowed
 
    cout << endl;

    cout << "namespace" << endl;

        //variables

            i=0;   //inner i
            ::i=0; //global i
            namea::i=0; //namea i
            i++;
            cout << i << endl;
            cout << ::i << endl;
            cout << namea::i << endl;
            cout << endl;
            //1 0 0

            i=0;
            ::i=0;
            namea::i=0;
            ::i++;
            cout << i << endl;
            cout << ::i << endl;
            cout << namea::i << endl;
            cout << endl;
            //0 1 0

            f();
            namea::f();
            namea::nameaa::f();
            cout << endl;

            i=0;
            ::i=0;
            namea::i=0;
            i++;
            cout << i << endl;
            cout << ::i << endl;
            cout << namea::i << endl;
            cout << endl;
            //1 0 0
        
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
            { using namespace newNamea;
                //f();
                //ERROR ambiuous
                //::f
                //namea::f
            }

        //subimport
            { using namea::f;
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

    cout << endl;

    //from stdlib, learn all containers and algorithms on them

    cout << "vector" << endl;
        //dynamic array based
        //reallocates as necessary

        //creation
            // constructors used in the same order as described above:
            std::vector<int> v1;                                // empty vector of ints
            std::vector<int> v2( 4, 100 );                       // four ints with value 100
            std::vector<int> v3( v2.begin(), v2.end() );  // iterating through second
            std::vector<int> v4( v3 );                       // a copy of third

            // the iterator constructor can also be used to construct from arrays:
            int myints[] = {16,2,77,29};
            std::vector<int> v5 (myints, myints + sizeof(myints)/sizeof(int) );

            //NEW C++11
            //initializer lists
                vector<int> vInitList1 { 1, 2 };
                vector<int> vInitList2(2);
                vInitList2 = { 1, 2 };
 
        //modify
            cout << "vector<int>(1)" << endl;
            cout << "v1.size()" << endl;
            v1 = vector<int>(1);
            cout << v1.size() << endl;
            //1
            cout << "v1.push_back(1)" << endl;
            cout << "v1.size()" << endl;
            v1.push_back(1);
            cout << v1.size() << endl;
            //2
            cout << "v1.pop_back(1)" << endl;
            cout << "v1.size()" << endl;
            v1.pop_back();
            cout << v1.size() << endl;
            //1
            //ERROR
                //cout << "v1[2] = 2" << endl;
                //cout << "v1.size()" << endl;
                //v1[10] = 2;
                //cout << v1.size() << endl;
                //1
            cout << "v1<int>()" << endl;
            v1 = vector<int>();
            cout << "v1.size()" << endl;
            cout << v1.size() << endl;
            //0

            {
                //vectors make copies
                    vector<string> v;
                    std::string s = "abc";
                    v.push_back(s);
                    cout << v[0] << endl;
                    //abc
                    v[0][0] = '0';
                    cout << v[0] << endl;
                    //0bc
                    v[0][0] = '0';
                    cout << s << endl;
                    //abc
            }

            //size            Return size
            //empty           Test whether vector is empty. same as size=0
            //resize          Change size
            //max_size        Return maximum size (what could fit your program ram)

            //allocation related
                //capacity        get how mush is allocated
                //reserve         change how much is allocated
                //shrink_to_fit   Shrink allocated array to fit cur size
                //data            get pointer to allocated array

            //return interators
            v1 = vector<int>(2,0);
            v1.insert( v1.begin() + 1, 1 );
            v1.insert( v1.end()   - 1, 1 );
            v1.erase( v1.begin() + 1 );
            v1.erase( v1.begin() + 1, v1.begin() + 2 );

        //info
 
            cout << "v1 = vector<int>(0,0)" << endl;
            cout << "v1.empty()" << endl;
            v1 = vector<int>(2,0);
            cout << v1.empty() << endl;

            cout << "v1 = vector<int>(1,0)" << endl;
            cout << "v1.empty()" << endl;
            v1 = vector<int>(1,0);
            cout << v1.empty() << endl;

        //random access is fast
            
            v1 = vector<int>(2,0);
            v1[0] = 0;
            cout << v1[0] << endl;

            //cout << v1[2] << endl;
            //v1[2] = 2;
                //ERROR just like array overflow

            cout << v1.back() << endl;
            cout << v1.front() << endl;

        for (
            vector<int>::iterator i = v1.begin();
            i != v1.end();
            ++i
        )
        {
            cout << *i << endl;
        }

    cout << endl;

    cout << "set" << endl;
        //unique elements
            //inserting twice does nothing
        //
        //immutable elements
        //
        //ordered
        //inserted elements are in that order
        //therefore, logarithmic find

        {
            set<int> s;
            s.insert(1);
            s.insert(2);
            s.insert(0);
            s.insert(1);

            //cout << s[0] << endl;
                //ERROR
                //no random access method

            //int is3[3] = {0,1,2};
            //for
            //(
                //set<int>::iterator it = s.begin(), i=0 ;
                //it != s.end();
                //it++, i++
            //)
            //{
                //assert( *it == is3[i] )
            //}
            //0 1 2

            //count
                //can only return 1 or 0
                assert( s.count(1) == 1 );
                assert( s.count(3) == 0 );
        }
        

    cout << endl;

    cout << "algorithms" << endl;

            sort( v1.begin(), v1.end() );

            bool contains = binary_search( v1.begin(), v1.end(), 1 );
            //must be already sorted

            reverse( v1.begin(), v1.end() );
            random_shuffle( v1.begin(), v1.end() );
            int num_zeros = count( v1.begin(), v1.end(), 0 );
            int highest = *max_element (v1.begin(), v1.end());
            int lowest = *min_element (v1.begin(), v1.end());

            unsigned int pos = find( v1.begin(), v1.end(), 1 ) - v1.begin();
            if( pos < v1.size() )
                cout << pos << endl;
            else
                cout << "not found" << endl;

            cout << "min(0.1,0.2)" << endl;
            cout << min(0.1,0.2) << endl;
            cout << "max(0.1,0.2)" << endl;
            cout << max(0.1,0.2) << endl;

    cout << endl;

    cout << "memory" << endl;

        cout << "shared_ptr" << endl;
            //C++11

            shared_ptr<Base> spi1(new Base);
            shared_ptr<Base> spi2(spi1);
            cout << "spi1->method();" << endl;
            spi1->method();
            spi1 = shared_ptr<Base>(new Base);
            cout << "spi2(sp1);" << endl;
            spi2 = shared_ptr<Base>(spi1);
            cout << "^^^^^ first base destroyed!" << endl;

        cout << endl;

    cout << endl;

    return EXIT_SUCCESS;
}
