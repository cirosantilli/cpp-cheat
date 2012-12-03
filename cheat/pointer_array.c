#include <stdio.h>
#include <stdlib.h> //for memcpy
#include <string.h> 

//cheatsheet on pointers and arrays
void print_22_array(int **mat, int m, int n)
{

  int i, j;

  for(i=0; i<m; i++ ){
    for(j=0; j<n; j++ ){
      printf("%d ", mat[i][j]);
    }
    printf("\n");
  }
}

int main(){

  int i=33, j;
  enum { mc=2, nc=4 };

  puts("\npointers\n");

    int *pi, *pi2;
    //must have serveral stars

    //*pi = 7; //bad! pi points to random address. segmentation fault coming.
    //segmentation fault: target memory not allocated! only pointer memory

    pi = &i;

    printf("i = %d\n",i);
    *pi = 55;
    printf("i = %d\n",i);
    printf("*pi = %d\n",*pi);

    printf("(void*)pi = %p\n",(void*)pi);
    printf("(void*)(pi+1) = %p\n",(void*)(pi+1));

    pi2 = pi+1;
    printf("(void*)(pi2-pi) = %p\n",(void*)(pi2-pi));

    printf("NULL = %p\n",NULL);

  puts("arrays");

    puts("creation");
      int is[3];
      is[0] = 1;
      is[1] = 3;
      is[2] = 2;

      int is2[] = {1, 3, 2}; //allocates exact size
      int is3[5] = {1, 3, 2}; //allocates 5, non-specified = 0: is3[0] = 1, ... , is3[3] == is3[4] == 0
      //int * is4 = {1, 3, 2}; //TODO ? why not like string. is it because 1,3,2 are just text, and are represented as such on the text part, and not as ints?

      //ERROR
        //isn must be constant!
        //might compile in c99, but don't do this: either use enum or a macro.
 
        //puts("enter an % integer:");
        //scanf("%d",&isn);
        //printf("%d\n",isn);
        //int is5[isn];

      puts("enum");
        enum M {M=3};
        int is5[M];
        is5[2] = 1;
        printf("%d\n",is5[2]);

      //DON'T DO THIS! *no scope*, so you can't use N anymore.
        //use enum instead
      puts("define");
#define N 3
        int is4[N];
        is4[2] = 1;
        printf("%d\n",is4[2]);

      char str2[] = "Hi world!"; //allocates on stack
      str2[0] = 'a';

      char* str3 = "Hi world!"; //points to the text segment (program itself): not modifiable TODO confirm
      //ERROR
      //str3[0] = 'a';
        //data segment cant me modified!!
 
    puts("\naccess");
      printf("is[0] = %d\n",is[0]);
      printf("is[1] = %d\n",is[1]);
      printf("is[2] = %d\n",is[2]);
      puts("");

    //pointers and arrays are different
      puts("pointers and arrays are different types:");
      printf("sizeof(int) = %d\n",sizeof(int));
      printf("sizeof(int*) = %d\n",sizeof(int*));
      printf("sizeof(int[3]) = %d\n",sizeof(int[3]));
      //printf("sizeof(int[]) = %d\n",sizeof(int[])); //error: incomplete type!

    //TODO teach
      //locations in memory of an array
      puts("locations of array:");
      printf("(void*)is = %p\n",(void*)is); //prints the 0x address. %p must get a void pointer
      printf("(void*)&is[0] = %p\n",(void*)&is[0]);
      printf("(void*)&is[1] = %p\n",(void*)&is[1]);
      printf("(void*)&is[2] = %p\n",(void*)&is[2]);


    //overflowing
      //printf("%d\n",is[3]);
      //is[3]=0;
      //printf("%d\n",is[1000000]);
      //is[1000000]=0;

      //for(i=0; i<=1000000000; i++ ){
      //    printf("%d\n",i);
      //    j=is[i];
      //}
      //  segmentation fault
      
      /*printf("%d\n",is[100000]);*/
      //might run: only get segmentation fault if you hit exactly the last position!

    //for combo
      for(i=0; i<3; i++ ){
        printf("%d ",is[i]);
      }
      puts("");

      //don't use this to copy: use memcpy instead
      for(i=0; i<=3; i++ ){
        printf("%d ",is[i]);
      }
      printf("\n");

      memcpy(is,is2,3*sizeof(int));
      //copy 3*4 bytes from one is7 to is
      //more efficient than for: direct memory copyint, no i++ or i<n? check
  
      //C99 allows you to do this
      memcpy(&is, &(int [5]){ 1,3,2 }, sizeof(is) );

    //can be of any type
      float fs[] =  {1,2,3,-2};
      printf("%f\n",fs[0]);
    
    //null terminated char array is a string!
      char cs[] = "Hello World";
      printf("%s\n",cs);
    
    //matrix pattern TODO teach
      int *m1[2];
      int m11[] = {1,2,3};
      int m12[] = {4,5,6,7};
      m1[0] = m11;
      m1[1] = m12;

      //error: cannot know  how much memory to allocate!
        //int m31[][3];
  
      //error: = {...} works only at declaration
        //int m111[2][3];
        //m111[0] = &(int*[3]){1,2,3};
    
      int m2[][3] = {
        {1,2,3},
        {4,5,6}
      };
      //allocates the exact ammount: 2 pointeres to int[3]

      int m3[3][3] = {
        {1,2,3},
        {4,5,6}
      };
      //allocates 3x3, fills only 2x3. the rest is 0 or m3[0] gets a NULL pointer?

      //error: last must be there
        //int m3[][] = {
        //  {1,2,3},
        //  {4,5,6,7}
        //};
        //
        //reason:
        //  this is array of m[3] arrays!!
        //  the data on an array is sequentially written to RAM
        //  and all of its elements have a fixed size (so they can be indexed!)
        //
        //  if you don't know the sizeof(m[3]), (and you don't know the sizeof(m[]!))
        //  you can't put all those m[3] sequentially on the RAM.
        //
        //  the compiler could look at each element of the initialization
        //  and ensure they all have the *same size*, and then take that size,
        //  but this would take a long time, so it just forces the user to input this

          //pass multidimentional arrays to functions
            puts("\npass multidim to func:");
            //*never do that*: pass an array, and give m and n
            //this is just to understand arrays better.
            int * mat[mc]; //two int pointers
            int mat1[][3] = {
              {1,2,3},
              {4,5,6}
            };
            for (i=0; i<mc; i++){
              mat[i] = mat1[i]; //first points to the int at address 0 of the matrix mat1
            }
            print_22_array(mat,2,3);

      //multidimentional > 2
  
        int m4[][2][3] = {
          { {1,2,3}, {4,5,6} },
          { {7,8,9}, {10,11,12} }
        };
        //allocates exact amount for first: 2x2x2
        
        int m41[3][2][3] = {
          { {1,2,3}, {4,5,6} },
          { {7,8,9}, {10,11,12} }
        };
        //allocates one extra for first dimension

        //error: only first can be empty
          //int m4[][][2] = {
          //  {{1,2},{3,4}},
          //  {{5,6},{7,8}}
          //};
  
      int m5[mc][nc];

      //error: TODO ? why
        //int m6[][nc] = {
        //  {1,2,3},
        //  {4,5,6}
        //};

        //int m7[mc][nc] = {
        //  {1,2,3},
        //  {4,5,6}
        //};

      //matrix pattern
        printf("\n");
        for(i=0; i<2; i++ ){
          printf("\n");
          for(j=0; j<3; j++ ){
            printf("%d ",m1[i][j]);
          }
        }
        printf("\n\n");

  //malloc: dynamic allocation
    i = 8;
    size_t bytes = sizeof(char)*i;
    char * cp = (char*) malloc (bytes);
    if (cp == NULL) {
      printf("could not allocate %zu bytes", bytes);
    }
    strcpy(cp,"0123456");
    printf("%s\n", cp);
    free(cp);

  return 0;
}
