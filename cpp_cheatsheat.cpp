#include <stdlib.h>



int main(int argc, char** argv)
{

//loops

  //for
  for(int i=0; i<n; i++){

  }

  //multiple for
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      for(int k=0; k<n; k++){

      }
    }
  }

//arrays

int a[3]; //only works if a number (3) is given and not a variable, since this is allocated at startup (a variable could be filled by a user stdin for example)
a[0] = 1;
a[1] = 2;
a[2] = 3;

int a[] = {1, 2, 3}; //equivalent to above

int n = 3;
int a[] = new int[3]; //dynamic allocation. can use variables, space is created at runtime. also can fail if no memory is left.
a[0] = 1;
a[1] = 2;
a[2] = 3;

Object a[3]; //static array of objects. requires standard constructor to be declared. (the one that takes no arguments, always declare it by reflex.)

Object a[] = {Object(1), Object(2), Object(3)}; //static array of objects with constructor Object(int)

//classes

class Base{

  public:

    Object(int k){
      this->k = k;
    }

  protected:

    int k;

  private:

    int k;

};

class Object : public Base{

  public:

    Object(int i){
      this->i = i;
    }

    static int j;
    static const int k = 20; //can only initialise static const like this.

  private:

    int i;
};

Object o = Object(1);
Object::j = 2;

//math

  //absolute value
  #include <math.h>
  abs(-1.1) //1, abs returs INTEGER!!!!!
  fabs(-1.1) //1.1, fabs returs float

  //random values
  srand ( time(NULL) );
  int r = rand(); //integer between 0 and RAND_MAX
  float f = rand()/(float)RAND_MAX; //float between 0 and 1

  float rand_range(float a, float b){ //float in a range
    return ((b-a)*((float)rand()/RAND_MAX))+a;
  }

return 0;

}
