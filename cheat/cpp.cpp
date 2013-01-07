/*
this will focus in differences between cpp and c.
for the rest, go to c_cheat.c

#headers

    stdlib headers don't have the .h extension

    when writting new libs, you use the extension ``.h`` or ``.hpp``

    with ``g++`` those get linked to automatically

    #c stdlin can be accessed

        math vs cmath, XXX vs cXXX

        cXXX puts most things outside the global namespace
        XXX.h puts *all* in the globale namespace

        *always* use <cXXX>

*/

#include <iostream>
//cout

#include <cstdlib>
//EXIT_SUCCESS

#include <string>
//string

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
        void byarg (int &i){i++;}
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
        void overload(float i, int j){ cout << "float int"; }
        //ERROR: how could g++ decide betweetn olverload(int) and this?
            //void overload(int i){}
            //overload(int i, int j=0){}

//classes
    //TODO
        //initialization lists
        //operator overloading
        //multiple inheritance
        //virtual examples
 
class Base
{
    public:

        Base() : 
            i(0),
            j(1)
        {
            cout << "Base::Base()";
            this->i = 0;
            this->j = 1;
        }

        Base(int i) : i(i)
        {
            cout << "Base::Base(int)";
        }

        ~Base()
        {
            cout << "Base::~Base()";
        }

        void method(){cout << "Base::method()";}

        virtual void virtual_method(){cout << "Base::virtual_method()";}
        //virtual: decides on runtime based on object type
            //http://stackoverflow.com/questions/2391679/can-someone-explain-c-virtual-methods
    
        virtual void pure_virtual() = 0;
        //pure virtual function
            //cannot instantiate this class
            //can only instantiate derived classes that implement this
            //if a class has a func like this is is known as an "abstract class"

        int i,j;
        //ERROR: cannot initialize here
            //int i = 0;
    
        static int iStatic;
        //ERROR
            //static int iStatic = 0;
                //cannot initialize here unless const
            //int iStatic;
                //conclicts with static int
        
        const static int iConstStatic = 0;
        //OK because const static

    protected:

        int iProtected;

    private:

        int iPrivate;
};

class Class : public Base
{
    public:

        Class() : i(0) { cout << "Class::Class()" << endl; }
        Class(int i) : i(i) { cout << "Class::Class(int)" << endl; }
        //BAD
            //Class(int i) { this->i = i; }
        ~Class(){ cout << "Class::~Class()"; }

        void method(){ cout << "Class::method()" << endl; }
        //called method overwriding
 
        void virtual_method(){ cout << "Class::virtual_method()" << endl; }
        //different than overwriding non virtual methods
        
        void pure_virtual(){ cout << "Class::pure_virtual()" << endl; }
        //obligatory if you want to create objects of this class

        int i; //TODO compiles but does nothing?
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
    cout << "stdout" << endl;
        //in c++ there is no more printf formatting strings
        //use the c libs for that

        cout << "cout";
        cout << "cout2" << "cout3" << endl;
        cout << 1;

        cerr << "cerr";

    cout << "for" << endl;
        //you can define i inside the for scope only
        for(int i=0; i<5; i++)
        cout << i << " ";

    cout << "functions" << endl;

    cout << "\ndata types" << endl;

        //contrary to c, in cpp there is a bool type
        bool b = true;
        cout << b;
        //1
        bool b2 = false;
        cout << b2;
        //0

    cout << "strings" << endl;

        //in cpp, strings are classes, much more convenient to manipulate
        
        //create
        string s("s");
        string s1 = "s1";
        string s2;

        cout << "to stdout\n";
        cout << s << endl;
        //s

        cout << "concat\n";
        cout << "s + s1\n";
        s2 = s + s1;
        cout << s2 << endl;
        //s2

        cout << "compare\n";

        cout << "s == s1\n";
        cout << (s == s1) << endl;
        //0
        
        cout << "s == s\n";
        cout << (s == s) << endl;

        cout << "s.length()\n";
        cout << s.length() << endl;
        //1

    cout << "class" << endl;
    
        cout << "Class o;" << endl;
        Class o;
        //Class()
            //Class() constructor is called!
        cout << "Class o = Class();" << endl;
        Class o1 = Class();
        cout << "o = Class(1);" << endl;
        o = Class(1);

        o.i = 1;
        o.j = 2;
        cout << "cout << o;" << endl;
        cout << o << endl;
        //1 2

    //arrays of objects
        cout << "Class os[3];" << endl;
        Class os[3];
        //3x Class() calls!
            os[0] = Class(1);
            os[1] = Class(1);
            os[2] = Class(1);

        //initialized
            cout << "Class os2[] = {Class(1), Class(2), Class(3)};" << endl;
            Class os2[] = {Class(1), Class(2), Class(3)};
            //3x Class() calls. more efficient therefore

    //temporaries
        cout << "Class().method1();" << endl;
        Class().method();
        //Class().method1()
 
        //ERROR
            //Class* cp = &Class();
                //address of what?
            Class c = Class();
            Class* cp = &c;

    cout << "dynamic memory" << endl;

        int * ip;
        ip = new int [5];
        ip[0] = 1;
        delete [] ip;

        //can also alocate single int
            //useless of course
            ip = new int;
            *ip = 1;
            cout << *ip << endl;
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
        //calls destructor
        cout << endl;

    cout << "enum" << endl;

        enum TEXTURE { GRASS, WALL, SKY };
        TEXTURE t = GRASS;
        //unlike c, already does typedef
        //check this to give values
            //http://msdn.microsoft.com/en-us/library/2dzy4k6e%28v=vs.71%29.aspx

    return EXIT_SUCCESS;

}
