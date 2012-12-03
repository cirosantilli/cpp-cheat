/*
this will focus in differences between cpp and c.
for the rest, go to c_cheat.c

#headers

  stdlib headers don't have the .h extension

  when writting new libs, you use the extension ``.h`` or ``.hpp``

  with ``g++`` those get linked to automatically

  #math vs cmath, XXX vs cXXX

    cXXX puts most things outside the global namespace
    XXX.h puts *all* in the globale namespace

*/

#include <iostream>
//cout

#include <string>
//string

using namespace std;
//will try std::XXX whenever XXX is found undefined

//functions
  //http://stackoverflow.com/questions/114180/pointer-vs-reference
  //passing by argument syntax not supported in c. convenience only im guessing in c++
  void func1 (int &i, int opt=0)
  {

  }

  void func2(float &i) //function overloading
  {

  }
  //ERROR:
    //but not func2(int &i, float opt=0)

//classes
class Base{

  public:

    Base(){
      this->i = 0;
      this->j = 1;
    }

    Base(int i){
      this->i = i;
      this->j = i+1;
    }

  protected:

    int i;

  private:

    int j;

};

class Object : public Base{

  public:

    static int j;
    static const int k = 20; //can only initialise static const like this in body

    Object(){
      this->i = 0;
    }

    Object(int i){
      this->i = i;
    }

    int i;
};

int main(int argc, char** argv){

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

  cout << "\ndata types" << endl;

    //contrary to c, in cpp there is a bool type
    bool b = true;
    cout << b;
    //1
    bool b2 = false;
    cout << b2;
    //0

  cout << "strings";

    //in cpp, strings are classes, much more convenient to manipulate
    
    //create
      string s("s");
      string s1 = "s1";
      string s2;

    cout << "to stdou\n";
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

  cout << "objects";
  
    Object o = Object(1);
    o.i = 2;
    //printf("%d",Object::i);

    //arrays of objects
    Object os[3];
    //static array of objects. requires standard constructor to be declared.
    //(the one that takes no arguments, always declare it by reflex.)

    Object os2[] = {Object(1), Object(2), Object(3)}; //static array of objects with constructor Object(int)

  //enums
    enum TEXTURE { GRASS, WALL, SKY };
    TEXTURE t = GRASS;
    //unlike c, already does typedef
    //check this to give values
    //  http://msdn.microsoft.com/en-us/library/2dzy4k6e%28v=vs.71%29.aspx

  return 0;

}
