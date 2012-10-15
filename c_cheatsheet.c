/* Hello World program */

#include<stdio.h>

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

main(){

  int i=5,j=7;
  //int i;
  //i = 5;
  //
  //int i=5;
  //int j=7;
  //
  //allowed chars: _,[a-Z],[0-9], canot start with number

  float f = 1.23;    //1 signal 23 number 8 exponent
  double d = 4.56;
  char c = 'a';
  
  //string
  //escape chars
  printf("Hello World\n");
  printf("Hello\tWorld\n");
  printf("\"\n");
  printf("\x61\n");
  //printf("\u1456\n"); //unicode TODO
  printf("\\\n");
  printf("%c<<< null char\n",'\0');

  //printf
  printf("i = %d\n", i);
  printf("f = %f\n", f);
  printf("f .2 = %.2f\n", f);
  printf("f 0.2 = %.0f\n", f);
  printf("f 7.2 = %7.2f\n", f); // make tables
  printf("highd = %lf\n", d);
  printf("%%\n");
  printf("%d %d\n",i,j);
  printf("%s\n", "Hello World");
  printf("%s\n", "Hello\0World");
  printf("%c\n", 'a');
  
  //scanf
  //scanf("%s", s); 
  scanf("%d", &i);
  printf("%d\n", i);
  
  //math
  printf("2+1 = %d\n", 2+1);
  printf("high+4 = %d\n", i+j);
  printf("4*8 = %d\n", 4*8);

  //TODO teach
  printf("4/2 = %d\n", 4/2);
  printf("2/4 = %d\n", 2/4);
  printf("2/4 = %f\n", 2.f/4.f);
  printf("2/4 = %f\n", 2/4.f);
  printf("2/4 = %f\n", 2/(float)4);
  printf("2/4 = %f\n", ((float)2)/4);
  printf("2/4 = %f\n", (float)(2/4));

  //printf("4^2 = %d\n", 4^2); It's not exponation! not basic operation
  printf("10%%8 = %d\n", 10%8);
   
  //arrays
  printf("\n");

  //creation
  int is[3];
  is[0] = 1;
  is[1] = 3;
  is[2] = 2;
  
  int is2[] =  {1,3,2};

  //access
  printf("%d\n",is[0]);
  printf("%d\n",is[1]);
  printf("%d\n",is[2]);

  printf("%d\n",is[3]);
  is[3]=0;
  //printf("%d\n",is); TODO: how to see?
  //printf("%d\n",&is[0]);
  //how array memory is organized

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
  printf("\n");

  //dynamic allocation
  //TODO
  
  // flow control
  printf("\n");
  printf("\n");
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
   
  goto a;
  printf("id");
  a: printf("di");//don't use
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
  
  //while
  i=0;
  while(i<10){
    printf("%d ",i);
    i++;	  
  }
  printf("\n");
  
  //functions
  printf("%d\n", pow2(1000,2) );
  printf("%.0f\n", pow2f(1000,2) );
}
