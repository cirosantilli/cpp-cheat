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

        math vs cmath, XXX vs cXXX

        cXXX puts most things outside the global namespace
        XXX.h puts *all* in the globale namespace

        *always* use <cXXX>

- language versions

    latest: C++11
        previously known as C++0x
        but took too long to come out
    previous: C++03

    http://en.wikipedia.org/wiki/C%2B%2B11

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

#include <vector>  

#include <algorithm>
//sort, reverse, random_shuffle, count, max_element, min_element

//namespaces

    //namespace creation
        //TODO

    //using namespace
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

    //ERROR: can't pass default values for arrays
        //void foo (int bar[] = {0 ,1});

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
            //http://courses.cms.caltech.edu/cs11/material/cpp/donnie/cpp-ops.html

class Member
{
    public:
        Member(){ cout << "Member::Member()"; }
        Member(int i){ cout << "Member::Member(int)"; }
        ~Member(){ cout << "Member::~Member()"; }
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

        void method(){cout << "Base::method()" << endl;;}

        virtual void virtual_method(){ cout << "Base::virtual_method()" << endl; }
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
        //OK: const static integral type
        
        const static Member member;
        //OK default constructor? why
        
        const static Member member2;
        //const static Member member2 = Member();
            //ERROR: non integral type
            //must be init outside
            //
            //why integral types are an exception (complicated):
                //http://stackoverflow.com/questions/13697265/static-const-double-cannot-have-an-in-class-initializer-why-is-it-so

    protected:

        int iProtected;
        void fProtected(){ cout << "Base::fProtected()"; }

    private:

        int iPrivate;
        void fPrivate(){ cout << "Base::fPrivate()"; }

        virtual void private_pure_virtual() = 0;
        //this can/must still be implemented on the base class, even if private!
        
        //how private pure virtual can be usefull
        void useful_private_pure_virtual()
        {
            cout << "common before" << endl;
            private_pure_virtual();
            cout << "common after" << endl;
        }
};

const Member Base::member2 = Member(1);

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
    //must go there because this actually makes many different functions
    //and default value is part of the interface
    class ClassDefault
    {
        ClassDefault(int i=0);
    };

    ClassDefault::ClassDefault(int i){}

    //ERROR
        //ClassDefault::ClassDefault(int i=0){}

//templates class
    //http://www.cplusplus.com/doc/tutorial/templates/
    //
    //ultra reneral! <class T, int N>
    //
    //default values via: <class T=char, int N=10>
    //c = Class<>
    //
    //implementation must be put in .h files and compiled by includers
        //cannot be put inside a .so therfore
        //consider int N, there are int many compilation possibilities!!
//SAME
    //template<typename T=int, int N=10>
template<class T=int, int N=10>
class TemplateClass
{
    public:

        T t;
        T ts[N];

        TemplateClass(){ cout << "TemplateClass::TemplateClass()" << endl; }

        //BAD: what is T = string?
            //TemplateClass() t(0.0){ cout << "TemplateClass::TemplateClass()" << endl; }

        TemplateClass(T t): t(t){ cout << "TemplateClass::TemplateClass(T)" << endl; }

        T method(T){ cout << "TemplateClass::method(T)" << endl; }

        void methodNoT();

        static const int sci = 0;

        //BAD impossible to define?
            //static const TemplateClass<T,N>;
};

//ERROR cannot define template stuff outside
    //TemplateClass::TemplateClass(){}
 
//ERROR cannot define template stuff outside. needs 0x flags
    //template<class T=int, int N=10>
    //void TemplateClass<T,N>::methodNoT(){}


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

int main(int argc, char** argv)
{
    bool b;
    int i = 0;
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

    cout << "variable size array" << endl;

        //cin >> i;
        //int is4[i];
            //BAD; gcc extension
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

        const Class cc;
        //ERROR
            //cc = Class();
        //ERROR
            //cc.i = 1;

    cout << endl;

    cout << "functions" << endl;

        //references
            //basically aliases, similar to int*const poinsters
            //
            //useful only for function parameters/return
            //
            //just link pointers, you have to watch scope. if the original object dies,
            //you get a dangling reference
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
            //SAME
                //therefore no extra memory is used for references
                //whereas pointers use memory
            int& ia2 = ia;
            ia2 = 3;
            cout << "int& ia2 = ia;" << endl;
            cout << i << endl;
            //3

            //ERROR: must be a variable rhs
                //int& ia = 5;

            //ERROR: must be initialized immediatelly
                //int& ia44;
            
            //ERROR: & must get a variable, not pointers!
                //int& ia3 = &i;
                //int& ia3 = new int;

            const int& cia = i;
            //ERROR
                //cia = 2;

            //ERROR: invalid conversion
                //int* ip = &cia;
                //int& ia = cia;

            //ERROR: no array of references forbidden
                //int& is[2] = {i,i};

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

            //copy constructor
                //default calls copy on all memebrs
                c.i = 1;
                cout << "Class c2(c)" << endl;
                Class c3(c);
                cout << c3.i << endl;
                //1
                cout << "Class c2 = c" << endl;
                Class c4 = c;
                //*COPY CONSTRUCTOR CALLED, NOT ASSIGN CONSTRUCTOR*, because object is being created
                //SAME
                    //Class c4(c);
                cout << c4.i << endl;

            //assign operator
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

            TemplateClass<int,10> tci10;
            tci10.ts[9] = 9;

            tci10 = TemplateClass<>(); //default values int 10

            //BAD: wont work, unless you defined an assign operator for this case
            //which is very unlikelly
                //tci10 = TemplateClass<float,20>();

            TemplateClass<string,10> tcs10;
            tcs10.ts[9] = "asdf";

        cout << endl;

        cout << "polymorphism" << endl;

            //behind the scenes a *vtable* is used to implement this

            //ERROR: Base cannot be instantiated because it contains a pure virtual method
            //virtual = 0;. That method must be implemented on derived classes
                //Base b;

            Base* bp = new Class; //even if you can't instantiate base, you can have pointers to it
            //SAME
                //Base* bp = &c;
            cout << "bp->method()" << endl;
            bp->method();
            //base method because non-virtual
            cout << "bp->virtual_method()" << endl;
            bp->virtual_method();
            //class method because virtual
            delete bp;

            c = Class();
            Base& ba = c;
            cout << "ba.method()" << endl;
            ba.method();
            //base
            cout << "ba.virtual_method()" << endl;
            ba.virtual_method();
            //derived
            //you can also have Base&


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

    //from stdlib, learn all containers and algorithms on them

    cout << "vector" << endl;
        //dynamic array based
        //reallocates as necessary

        //creation
            // constructors used in the same order as described above:
            std::vector<int> v1;                                // empty vector of ints
            std::vector<int> v2 (4,100);                       // four ints with value 100
            std::vector<int> v3 (v2.begin(),v2.end());  // iterating through second
            std::vector<int> v4 (v3);                       // a copy of third

            // the iterator constructor can also be used to construct from arrays:
            int myints[] = {16,2,77,29};
            std::vector<int> fifth (myints, myints + sizeof(myints)/sizeof(int) );

            //NEW C++11
            //initializer lists
                //vector<int> v12 { 1, 2 };
                //vector<int> v13 = { 1, 2 };
                //vector<int> v14(2);
                //v14 = { 1, 2 };

        //access
            
            //randomaccess is fast
                v1[0] = 0;
                cout << v1[0] << endl;

                //cout << v1[2] << endl;
                //v1[2] = 2;
                    //ERROR just like array overflow

                cout << v1.back() << endl;
                cout << v1.front() << endl;

        //size, pop and push
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
        v1.insert( v1.begin() + 1, 1 );
        v1.insert( v1.end()   - 1, 1 );
        v1.erase( v1.begin() + 1 );
        v1.erase( v1.begin() + 1, v1.begin() + 2 );

        cout << v1.empty() << endl;

        for (
            vector<int>::iterator i = v1.begin();
            i != v1.end();
            ++i
        )
        {
            cout << *i << endl;
        }

        //algorithms
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

    cout << endl;

    return EXIT_SUCCESS;
}
