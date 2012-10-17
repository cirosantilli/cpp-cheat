#include <stdlib.h>
#include <cmath>
#include <time.h>

/*
 * this will focus in differences between cpp and c.
 * for the rest, go to c_cheat.c
*/

enum STR2INT_ERROR { SUCCESS, STR2INT_ERROR_OVERFLOW, STR2INT_ERROR_UNDERFLOW, INCONVERTIBLE };
//unlike c, already does typedef
//check this to give values
//  http://msdn.microsoft.com/en-us/library/2dzy4k6e%28v=vs.71%29.aspx

//http://stackoverflow.com/questions/114180/pointer-vs-reference
//by arg not supported in c. convenience only im guessing.
void func1 (int &i, int opt=0)
{

}

void func2(float &i) //function overloading
{

}

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

float rand_range(float a, float b){ //float in a range
    return ((b-a)*((float)rand()/RAND_MAX))+a;
}

int main(int argc, char** argv){

  Object o = Object(1);
  o.i = 2;
  //printf("%d",Object::i);

  //arrays of objects
  Object os[3];
  //static array of objects. requires standard constructor to be declared.
  //(the one that takes no arguments, always declare it by reflex.)

  Object os2[] = {Object(1), Object(2), Object(3)}; //static array of objects with constructor Object(int)

  //math

  //absolute value
  abs(-1.1); //1, abs returs INTEGER!!!!!
  fabs(-1.1); //1.1, fabs returs float

  //random values
  srand ( time(NULL) );
  int r = rand(); //integer between 0 and RAND_MAX
  float f = rand()/(float)RAND_MAX; //float between 0 and 1

  return 0;

}
