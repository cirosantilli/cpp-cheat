#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

/*
  TODO
    memory segments/layout : text data heap stack command line

    file/stream io

    multifiles/headers, where looks for them
    .a, .so

    struct

    enum
    typedef

    multithreading/ipc
 
    static
    const
    volatile

  assembly language:

    http://www.plantation-productions.com/Webster/www.artofasm.com/Linux/HTML/AoATOC.html
*/

typedef enum { SUCCESS, OVERFLOW, UNDERFLOW, INCONVERTIBLE } STR2INT_ERROR;

//a pow b
int pow2(int a, int b)
{
   int res = 1;
   int i;
   for(i=0; i<b; i++){
     res = res*a;
   }
   return res;
}
 
//TODO does not work
float pow2f(float a, float b)
{
   float res = 1.f;
   float i;
   for(i=0; i<b; i++){
     res = res*a;
   }
   return res;
}

int main(){

  //base types
    puts("\nbase types");
    int i=5,j=7; //31 bit + 1 sign bit integer
    long int li = 8L; //64 bit int
    //int i;
    //i = 5;
    //
    //int i=5;
    //int j=7;
    //
    //allowed chars: _,[a-Z],[0-9], canot start with number
    //TODO teach
    printf("16 = %d\n", 16);
    printf("0x10 = %d\n", 0x10);
    printf("020 = %d\n", 020);
    printf("0b10000 = %d\n", 0b10000);
    
    float f = 1.2345f;    //1 signal 23 number 8 exponent
    float f1 = 1.2345e-10f;    //TODO teach
    float f2 = 1.f;
    //float f = 1f; //there must be a dot
    double d = 6.789;
    char c = 'a';
    char *cp;
    char s[8] = "s";
    int sn = 8;

    size_t size = sizeof(int);

  printf("sizeof(int) = %zu\n",sizeof(int)); //how many bytes per int
  printf("sizeof(long int) = %zu\n",sizeof(long int)); //int and long int may be equal!!!!!! this is plataform dependent

  //write to stdout

    //puts: write to stdout.
      //simpler (and faster?) than printf TODO teach
      //automatically newline terminated!
      //can contain newlines
      puts("puts\nputs\n");

    //printf: write formated to sdtout
      //http://www.cplusplus.com/reference/clibrary/cstdio/printf/

      puts("\nprintf:");
      printf("d = %d\n", 1);
      printf("ld = %ld\n", 1L);
      printf("%d %d\n",1,2);

      printf("f = %f\n", f);
      printf(".2f = %.2f\n", f);
      printf("0.2f = %.0f\n", f);
      printf("7.2f = %7.2f\n", f); //at least 7 chars: add spaces. used to make tables.
      printf(".2e = %.2e\n", f);
      printf(".*e = %.*e", 2, f); //treat precision as a parameter

      printf("%s\n", "Hello World");
      printf("%s\n", "Hello\0World");

      printf("%c\n", 'a');
      printf("%d\n", 'a');

      printf("%x\n", 16);

      printf("(void*)&f = %p\n",(void*)&f);
      //prints the 0x address.
      //%p must get a void pointer
      //void* is a type, different than void. doing type cast to it.

      printf("%%<<< escaping percentage\n");

  //read from stdin
  if(0){ //gets annoying after some time

    //gets: deprecated.
      //dangerous: no size check
 
      //gets is deprecated in c11! http://www.cplusplus.com/reference/clibrary/cstdio/fgets/
      //printf("enter a string terminated by newline: (max %d chars, newline will be included in the string)\n", sn);
      //gets(s);
      //printf("you entered:\n%s\n\n",s);

    //scanf : dangerous
      //input is space separated
      //nothing happens on error
    
      printf("enter an integer in decimal and a newline (max 32 bits signed):\n");
      scanf("%d", &i);
      printf("you entered:\n%d\n\n", i);
      //stuff is space separated
      //try 123 456 789 at once. 456 789 stay in the buffer, and are eaten by the second scanf
      
      printf("enter an integer, a space, an integer and a newline (max 32 bits signed):\n");
      scanf("%d %d", &i, &j);
      printf("you entered:\n%d %d\n\n", i, j);

      printf("enter a float and a newline:\n");
      scanf("%f", &f);
      printf("you entered:\n%.2f\n\n", f);

      printf("enter an integer in hexadecimal and a newline: (max 32 bits signed)\n");
      scanf("%x", &i);
      printf("you entered (in decimal):\n%d\n\n", i);

    //fgets + error checking: best method
 
  }

  //directory operations
    //no standard portable way! http://www.devarticles.com/c/a/Cplusplus/Directories-in-Cplusplus/
    //linux: sys/stat.h, unistd.h
    //windows: direct.h
    //portable heavyweight: booost: #include <boost/filesystem/operations.hpp>
    //portable lightweight: dirent.h
    
    //linux only if you don't care!
    if(0){

      #include <sys/stat.h>  
      if( mkdir("newdir",0777) == -1 ){
        puts("could not create newdir");
      } else {
        puts("newdir created");
      }

      puts("enter to remove newdir:");
      gets(s);
      
      #include <unistd.h>
      if( rmdir("newdir") == -1 ){
        puts("could not remove newdir");
      } else {
        puts("newdir removed");
      }

    }

    puts("");

  //path operations
    //puts(realpath("."));

  //TRY: echo "123" | ./c_cheatsheet.out
  //  this will use stdin from a pipe! no user input
  
  //operators
  
    //math
      printf("2+1 = %d\n", 2+1);
      printf("high+4 = %d\n", i+j);
      printf("4*8 = %d\n", 4*8);

      //TODO teach
      printf("4/2 = %d\n", 4/2);
      printf("2/4 = %d\n", 2/4);
      printf("2/4 = %f\n", 2.f/4.f);
      printf("2/4 = %f\n", 2/4.f);
      printf("2/4 = %f\n", 2/(float)4); //type casting
      printf("2/4 = %f\n", ((float)2)/4);
      printf("2/4 = %f\n", (float)(2/4));

      //printf("4^2 = %d\n", 4^2); It's not exponation! not basic operation
      
      printf("10%%8 = %d\n", 10%8);
      //rest of division (modulo)

  // flow control

    //if
      if(1>2){
        printf("true 1>2\n");
      } 
      if(1<2){ 
        printf("true 1<2\n");
      }
      
      if(1<=2){ 
        printf("true 1<=2\n");
      } else {
        printf("true 1>2\n");
      }
      
      if(1>=2){ 
        printf("true 1=>2\n");
      } else {
        printf("true 1<2\n");
      }
      
      if(1>2){ 
        printf("true 1>2\n");
      } else if(1==2){
        printf("true 1==2\n");	
      }else {
        printf("true 1<2\n");
      }
   
  //booleans are ints! TODO teach
      printf("1==1 = %d\n", 1==1);
      printf("1==0 = %d\n", 1==0);

  //from <stdbool>
    printf("true = %d\n", true);
    printf("false = %d\n", false);

  //goto: don't use, but his is how the processor works!
    goto a;
    printf("no");
    a: printf("yes");
    printf("\n\n");
  
  //while
    i=0;
    while(i<10){
      printf("%d ",i);
      i++;	  
    }
    printf("\n");

  //for
    for(i=0; i<10; i++ ){//only when know how many times
      printf("%d ",i);
    }
    printf("\n");
    
    printf("\n");
    for(i=0; i<3; i++ ){ //only when know how many times
      for(j=0; j<3; j++ ){ //only when know how many times
        printf("%d %d\n",i,j);
      }
    }
    printf("\n");
  
  //functions
    printf("%d\n", pow2(1000,2) );
    printf("%.0f\n", pow2f(1000,2) );

  return 0;
}
