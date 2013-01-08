/*
this will focus in differences between cpp and c.
for the rest, go to c.c

good general resources

- http://www.cplusplus.com/doc/tutorial/typecasting/

#headers

    stdlib headers don't have the .h extension

    when writting new libs, you use the extension ``.h`` or ``.hpp``

    with ``g++`` those get linked to automatically

    #c stdlin can be accessed

        math vs cmath, XXX vs cXXX

        cXXX puts most things outside the global namespace
        XXX.h puts *all* in the globale namespace

        *always* use <cXXX>

TODO
- returning references
        http://stackoverflow.com/questions/795674/which-are-the-implications-of-return-a-value-as-constant-reference-and-constant?rq=1

*/

#include <iostream>
//cout

#include <cstdlib>
//EXIT_SUCCESS

#include <string>
//string

#include <exception>
//exception base exception class
    //bad_alloc	thrown by new on allocation failure
    //bad_cast	thrown by dynamic_cast when fails with a referenced type
    //bad_exception	thrown when an exception type doesn't match any catch
    //bad_typeid	thrown by typeid
    //ios_base::failure	thrown by functions in the iostream library

//namespaces

    using namespace std;
    //will try std::XXX whenever XXX is found undefined
        //if there are two possibilities or more, gives an error

    //ERROR
        //using namespace asdf;
            //namespaces must be defined somewhere
            //namespaces compose automatically
            //from now on will also try asdf::, std::asdf::, and asdf::std::

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

    //function overloading
        void overload(int i){ cout << "int"; }
        void overload(int i, int j){ cout << "int int"; }
        void overload(float i){ cout << "float"; }
        void overload(float i, float j, float k=0.f){ cout << "float float float="; }

        //ERROR: conflict with int
            //void overload(const int i){ }
        //ERROR: cannot differentiate by output since output is used to decide if other parts of code make sense
            //int overload(){ return 0; }
            //float overload(){ return 0.f; }
        //ERROR: conflict with int int
            //void overload(int i, int j=0){ cout << "int int="; }
        //WARN
            //compiles, but is useless to give a default,
            //since when calling, caller is *forced* to give a value for j
            //or wil get ``call is ambiguous`` compile time error
            //because compiler cannot decide between
            void overload(float i, float j=1){ cout << "float float="; }
                //here the default arg can be usefull for a call of type float float
         
        //TODO why does this compile, that is, how not to make an ambiguous call with overload(int)
            void overloadValAddr(const int i){}
            void overloadValAddr(const int& i){}

//classes
    //TODO
        //operator overloading
        //multiple inheritance
        //virtual examples
 
class Base
{
    public:

        Base() : i(0), j(1) //list initialization
        { 
            cout << "Base::Base()"; 
            //BAD
                //this->i=0;
                //this->j=1;
                    //same as list init, except if i is an object
                    //to keep uniform style, always use list init
            //ERROR: ic is const. must be initialized in list initialization.
                //ic=0;
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
            cout << "Base::Base(int, int)";
        }

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
            almost always what you want in an interface
        */
        virtual ~Base()
        {
            cout << "Base::~Base()";
        }

        void method(){cout << "Base::method()";}

        virtual void virtual_method(){ cout << "Base::virtual_method()"; }
        //virtual: decides on runtime based on object type
            //http://stackoverflow.com/questions/2391679/can-someone-explain-c-virtual-methods
    
        virtual void pure_virtual() = 0;
        //pure virtual function
            //cannot instantiate this class
            //can only instantiate derived classes that implement this
            //if a class has a pure virtual func is called as an *abstract class* or *interface*

        int i,j;
        //ERROR: cannot initialize here
            //int i = 0;

        int* is;

        //BAD: every class must have an assigment operator
        //but then, assigment does something like this->ic = other->ic
        //you could redefine the assigment, but still in your new definition
        //ic cannot be changed
        //http://stackoverflow.com/questions/634662/non-static-const-member-cant-use-default-assignment-operator
            //const int ic;
    
        static int iStatic;
        //ERROR
            //static int iStatic = 0;
                //cannot initialize here unless const
            //int iStatic;
                //conclicts with static int
        
        const static int iConstStatic = 0;
        //OK: const static

    protected:

        int iProtected;
        void fProtected(){ cout << "Base::fProtected()"; }

    private:

        int iPrivate;
        void fPrivate(){ cout << "Base::fPrivate()"; }

        virtual void private_pure_virtual() = 0;
        //this can still be implemented on the base class
        
        //how private pure virtual can be usefull
        void useful_private_pure_virtual()
        {
            cout << "common before" << endl;
            private_pure_virtual();
            cout << "common after" << endl;
        }
};

class BaseProtected
{
    public:
        BaseProtected(){ cout << "BaseProtected::BaseProtected()"; }
        BaseProtected(int i){ cout << "BaseProtected::BaseProtected(int)"; }
        ~BaseProtected(){ cout << "BaseProtected::~BaseProtected()"; }
};

class BasePrivate
{
    public:
        BasePrivate(){ cout << "BasePrivate::BasePrivate()"; }
        BasePrivate(int i){ cout << "BasePrivate::BasePrivate(int)"; }
        ~BasePrivate(){ cout << "BasePrivate::~BasePrivate()"; }
};

class Member
{
    public:
        Member(){ cout << "Member::Member()"; }
        ~Member(){ cout << "Member::~Member()"; }
};

class Class : public Base, protected BaseProtected, private BasePrivate //inheritance
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

        Class(int i, int z) : Base(i,z), BaseProtected(i), BasePrivate(i), i(i), z(z)
        {
            cout << "Class::Class(int, int)" << endl;
        }
        //calls specific base constructors  instead of default ones
            //another application os initialization lists
        
        //try catch in case base constructor can throw exceptions
        Class(int i, int j, int z) try : Base(i,j), i(i), z(z)
        {
            cout << "Class::Class(int, int, int)" << endl;
        } catch(const exception &e) {
            throw e;
        } 
        
        Class(Member m) : m(m) {
            //BAD: m constructor would be called, but this is useless since we have already called it!
            //to construct it before.
            //This is an application of initialization constructors.
                //this->m = m;
            cout << "Class::Class(Member)" << endl;
        }

        /*
        also calls Base destructor after
        */
        ~Class(){ cout << "Class::~Class()"; }

        void method(){ cout << "Class::method()" << endl; }
        //called method overwriding
 
        void virtual_method(){ cout << "Class::virtual_method()" << endl; }
        //different than overwriding non virtual methods. see polymorphism.
        
        void pure_virtual(){ cout << "Class::pure_virtual()" << endl; }
        //definition obligatory if you want to create objects of this class

        int i; //TODO compiles but does nothing?
        int z;
        Member m;

    private:

        virtual void private_pure_virtual(){ cout << "Class:private_pure_virtual()" << endl; };
};

//overload <<
    ostream& operator<<(ostream& os, const Class& c)
    {
        os << c.i << " " << c.j;
        return os;
    }

class Class2 : public Base
{
    public:
        Class2(){}
        void pure_virtual(){ cout << "Class2::pure_virtual()" << endl; }
};

class ClassCast
{
    ClassCast(Class c){}
};

//default args go in def only!
    //must go there because this actually makes many different function
    class ClassDefault
    {
        ClassDefault(int i=0);
    };

    ClassDefault::ClassDefault(int i){}

    //ERROR
        //ClassDefault::ClassDefault(int i=0){}

int main(int argc, char** argv)
{

    bool b;
    int i;
    int * ip;

    cout << "stdout" << endl;
        //in c++ there is no more printf formatting strings
        //must use the c libs for that

        cout << "cout";
        cout << "cout2" << "cout3" << endl;
        cout << 1;

        cerr << "cerr";
        cout << endl;

    cout << "for" << endl;
        //you can define i inside the for scope only
        for(int i=0; i<5; i++)
            cout << i << " ";
    cout << endl;

    cout << "const" << endl;
        const int ic=2;
        //ERROR: in c this is only a warning, and allows us to change ic.
            //int* ip = ic;
        int is34[ic];
            //WORKS! not like c, since constants really can't be changed
    cout << endl;

    cout << "functions" << endl;

        //references
            //are basically aliases
            //http://stackoverflow.com/questions/752658/is-the-practice-of-returning-a-c-reference-variable-evil
            
            i=1;
            cout << i << endl;
            byref(i);
            cout << i << endl;

            i=i;
            int& ia = i;
            ia = 2;
            cout << "int& ia = i;" << endl;
            cout << i << endl;
            //2
            cout << "&ia" << endl;
            cout << &ia << endl;
            cout << "&i" << endl;
            cout << &i << endl;
            //same
                //therefore no extra memory is used for references
                //whereas pointers use memory
            int& ia2 = ia;
            ia2 = 3;
            cout << "int& ia2 = ia;" << endl;
            cout << i << endl;
            //3
            
            //ERROR: & must get a variable, not pointers!
                //int& ia3 = &i;
                //int& ia3 = new int;

            const int& cia = i;
            //ERROR
                //cia = 2;
            //ERROR: invalid conversion
                //int* ip = &cia;
                //int& ia = cia;



        i=4;
        //ERROR: ambiguous
            //overloadValAddr(i);

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
        
        //create
        string s("s");
        string s1 = "s1";
        string s2;

        cout << "to stdout" << endl;
        cout << s << endl;
        //s

        cout << "concat" << endl;
        cout << "s + s1" << endl;
        s2 = s + s1;
        cout << s2 << endl;
        //s2

        cout << "compare" << endl;

        cout << "s == s1" << endl;
        cout << (s == s1) << endl;
        //0
        
        cout << "s == s" << endl;
        cout << (s == s) << endl;

        cout << "s.length()" << endl;
        cout << s.length() << endl;
        //1
    
    cout << endl;

    cout << "class" << endl;
    
        Class* cp;

        //creation
        
            cout << "Class c;" << endl;
            Class c;
            cout << "Class c1;" << endl;
            Class c1;
            //Base Class
                //Base and Class constructor are called!
                //if no default constructor, error
                c.i = 1;
                c1.i = 2;
                c1 = c;
                cout << c1.i << endl;
                //1

            cout << "c1 = Class();" << endl;
            c1 = Class();
            //another constructor call
            
            cout << "Class c = Class();" << endl;
            Class c2 = Class();
            //Base and class
                //single calls

        cout << endl;
            
        cout << "copy, assigment" << endl;
            //every class gets a default assign operator (=) and copy constructor
            //called shallow copy/assign
            //might not be what you want, specially when you allocate memory inside the constructor!
                //http://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
                //http://stackoverflow.com/questions/4172722/what-is-the-rule-of-three

            //default copy constructor
                //calls copy on all memebrs
                c.i = 1;
                Class c3(c);
                cout << c3.i;

            //default assign calls assign (=) on all members
                c.i = 1;
                c1.i = 2;
                c1 = c;
                cout << c1.i << endl;
                //1

        cout << endl;

        //default assigment

        cout << "arrays of objects" << endl;

            cout << "Class os[3];" << endl;
            Class cs[3];
            //3x Class() calls!
                cs[0] = Class(1);
                cs[1] = Class(2);
                cs[2] = Class(3);

            //initialized
                cout << "Class cs2[] = {Class(1), Class(2), Class(3)};" << endl;
                Class cs2[] = {Class(1), Class(2), Class(3)};
                //3x Class() calls. more efficient therefore

        cout << endl;

        cout << "temporaries" << endl;

            cout << "Class().method();" << endl;
            Class().method();
            //Class().method1()

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

        cout << "polymorphism" << endl;

            //behind the scenes a *vtable* is used to implement this

            //ERROR: Base cannot be instantiated because it contains a pure virtual method
            //virtual = 0;. That method must be implemented on derived classes
                //Base b;

            c = Class();
            Base* bp = new Class;
            //SAME
                //Base* bp = &c;
            bp->method();
            //base method because non-virtual
            bp->virtual_method();
            //class method because virtual
            delete bp;

        cout << endl;

        cout << "typecasting" << endl;
            //http://www.cplusplus.com/doc/tutorial/typecasting/

            //implicit via constructor/assigment
                //class A {};
                //class B { public: B (A a) {} };
                //A a;
                //B b=a;
            

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

    cout << "exceptions" << endl;
        //TODO

    cout << "enum" << endl;

        enum TEXTURE { GRASS, WALL, SKY };
        TEXTURE t = GRASS;
        //unlike c, already does typedef
        //check this to give values
            //http://msdn.microsoft.com/en-us/library/2dzy4k6e%28v=vs.71%29.aspx

    return EXIT_SUCCESS;

}
