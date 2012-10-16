#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/*
  TODO typedef, enum, multithreading
 
  assembly language:

    http://www.plantation-productions.com/Webster/www.artofasm.com/Linux/HTML/AoATOC.html
*/

typedef enum { SUCCESS, OVERFLOW, UNDERFLOW, INCONVERTIBLE } STR2INT_ERROR;

//a^b
int pow2(int a, int b){
   int res = 1;
   int i;
   for(i=0; i<b; i++){
     res = res*a;
   }
   return res;
 }
 
 //a^b
float pow2f(float a, float b){
   float res = 1;
   float i;
   for(i=0; i<b; i++){
     res = res*a;
   }
   return res;
 }

int main(){

  int i=5,j=7; //31 bit + 1 sign bit integer
  long int li = 8L; //64 bit int
  //int i;
  //i = 5;
  //
  //int i=5;
  //int j=7;
  //
  //allowed chars: _,[a-Z],[0-9], canot start with number
  
  float f = 1.23;    //1 signal 23 number 8 exponent
  float f1 = 1.23e-10;    //TODO teach
  double d = 4.56;
  char c = 'a';
  char s[8] = "s";
  int sn = 8;

  //TODO teach
  printf("16 = %d\n", 16);
  printf("0x10 = %d\n", 0x10);
  printf("020 = %d\n", 020);
  printf("0b10000 = %d\n", 0b10000);

  //write to stdout

    //puts: write to stdout.
      //simpler (and faster?) than printf TODO teach
      //automatically newline terminated!
      //can contain newlines
      puts("puts\nputs\n");
  
    //printf: write formated to sdtout
      printf("i = %d\n", i);
      printf("i = %ld\n", 10L);
      printf("f = %f\n", f);
      printf("f .2 = %.2f\n", f);
      printf("f 0.2 = %.0f\n", f);
      printf("f 7.2 = %7.2f\n", f); //7 add spaces to make tables
      printf("highd = %lf\n", d);
      printf("%%\n");
      printf("%d %d\n",i,j);

      printf("%s\n", "Hello World");
      printf("%s\n", "Hello\0World");

      printf("%c\n", 'a');
      printf("%d\n", 'a');

      printf("%x\n", 16);
      printf("(void*)&i = %p\n",(void*)&i);
      //prints the 0x address.
      //%p must get a void pointer
      //void* is a type, different than void. doing type cast to it.

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

  //file io input output (or to stdout/err)
    //don't forget: your os can give you errors!
 
    FILE *file;
    char path[] = "test.txt";
    file = fopen(path,"a");
    //don't forget to close!
    //r : read. compatible with a,w
    //w : read and write. destroy if exists, create if not.
    //a : append. write to the end. creates if does not exist.
    //+ : can do both input and output. msut use flush or fseek
    //x : don't destroy if exist (c11, not c++!, posix only)
    //b : binary. means nothing in POSIX systems.
    
    if (file==NULL){
      fprintf(stderr, "could not write to %s\n", path);
    } else {
    //fputs : puts for files.
      //not automatically newline terminated.
      //can contain newlines.
      fputs("fputs to stdout 1\nfputs to stdout 2\n", stdout);
      fputs("fputs to stderr 1\nfputs to stderr 2\n", stderr);
      fputs("fputs to file 1\nfputs to file 2\n", file);
    }
  
    //fprintf : same as puts vs printf

  //reposition read write

    //TODO flush, fseek, fsetpos, rewind
    
    fclose(file);
    //don't forget to close! there is a limited ammount of open files at a time by the os

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


  //pointers TODO teach
    int *pi,*pi2;
    //must have serveral stars
    //memory is not yet allocated!
 
    //*pi = 7; //bad! pi points to random address. segmentation fault coming.
    pi = &i;

    printf("*pi = %d\n",*pi);
    printf("i = %d\n",i);
    *pi = 55;
    printf("*pi = %d\n",*pi);
    printf("i = %d\n",i);

    printf("(void*)pi = %p\n",(void*)pi);
    printf("(void*)(pi+1) = %p\n",(void*)(pi+1));

    pi2 = pi+1;
    printf("(void*)(pi2-pi) = %p\n",(void*)(pi2-pi));

  //arrays
  printf("\n");

  //creation
    int is[3];
    is[0] = 1;
    is[1] = 3;
    is[2] = 2;

    int is2[3] = {1, 3, 2};
    int is3[4] = {1, 3, 2};
    int is4[] = {1, 3, 2};

    int isn = 8;
    const int isnc = 8;

    int is5[isn];
    is[0] = 1;
    is[1] = 3;
    is[2] = 2;

    //scanf("%d",%isn)
    //int is6[isn]; //error: variable size! could come from scanf for example
    //isnc = 3; error you tried to change isnc.
    int is6[isnc]; //ok. iscnc is constant

  //access
    printf("is[0] = %d\n",is[0]);
    printf("is[1] = %d\n",is[1]);
    printf("is[2] = %d\n",is[2]);
    puts("");

  //TODO teach
    //locations in memory of an array
    printf("sizeof(int) = %d\n",sizeof(int)); //how many bytes per int
    printf("sizeof(long int) = %d\n",sizeof(long int)); //int and long int may be equal!!!!!! this is plataform dependent
    printf("sizeof(*int) = %d\n",sizeof(int*)); //how many bytes per int*
    printf("(void*)is = %p\n",(void*)is); //prints the 0x address. %p must get a void pointer
    printf("(void*)&is[0] = %p\n",(void*)&is[0]);
    printf("(void*)&is[1] = %p\n",(void*)&is[1]);
    printf("(void*)&is[2] = %p\n",(void*)&is[2]);
    puts("");

    printf("sizeof(is) = %d\n",sizeof(is)); //int[] is different from int *!!!

  //naughty things
    printf("%d\n",is[3]);
    is[3]=0;

    //for(i=0; i<=1000000000; i++ ){
    //    printf("%d\n",i);
    //    j=is[i];
    //}
    //  segmentation fault
    
    /*printf("%d\n",is[100000]);*/
    //might run: only get segmentation fault if you hit exactly the last position!

  //for combo
  for(i=0; i<=3; i++ ){
    printf("%d ",is[i]);
  }
  printf("\n");

  //can be of any type
  float fs[] =  {1,2,3,-2};
  printf("%f\n",fs[0]);
  
  //nul terminated char array is a string!
  char cs[] = "Hello World";
  printf("%s\n",cs);
  
  //matrix
  int m[2][3] = {
    {1,2,3},
    {4,5,6}
  };
  
  //matrix pattern
    printf("\n");
    for(i=0; i<2; i++ ){
      printf("\n");
      for(j=0; j<3; j++ ){
        printf("%d ",m[i][j]);
      }
    }
    printf("\n\n");

  //dynamic allocation
  //memory segments/layout : text data heap stack command line
  //size a.out
  //http://www.geeksforgeeks.org/archives/14268
  //TODO
  
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
