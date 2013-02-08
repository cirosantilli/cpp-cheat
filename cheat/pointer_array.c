#include <stdio.h>
#include <stdlib.h> //for memcpy
#include <string.h> 
#include <assert.h> 
#include <wchar.h> 
#include <locale.h>

int* getArr(int i)
{
    //int is[] = {i};
    //return is;
        //WARN
        //return adress of local var
        //data is destroyed on return!

    int* ip = (int*) malloc (sizeof(int)*1);
    return ip;
}

//cheatsheet on pointers and arrays
void print_array(int **mat, int m, int n)
{

    int i, j;

    for(i=0; i<m; i++ )
    {
        for(j=0; j<n; j++ )
        {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

int main()
{

    enum { mc=2, nc=4 };

    //pointer
    {
        int i;
        int* pi, *pi2;
        //*pi = 7;
            //BAD
            //you are modifying some random piece of memory!!!!
            //must declare like that: multiple stars
        pi = &i;
        *pi = 1;
        assert( i == 1 );
        assert( *pi == 1 );
        i = 2;
        assert( i == 2 );
        assert( *pi == 2 );

        printf("(void*)pi = %p\n",(void*)pi);
        printf("(void*)(pi+1) = %p\n",(void*)(pi+1));
        printf("NULL = %p\n",NULL);

        pi2 = pi+1;
        printf("(void*)(pi2-pi) = %p\n",(void*)(pi2-pi));

        //float* fp = &i;
            //ERROR
            //incompatible pointer type
    }

    //array
    {
        {
            {
                int is[3];
                is[0] = 0;
                is[1] = 1;
                is[2] = 2;
                assert( is[0] == 0 );
                assert( is[1] == 1 );
                assert( is[2] == 2 );
            }

            {
                int is[] = {0,1,2};
                assert( is[0] == 0 );
                assert( is[1] == 1 );
                assert( is[2] == 2 );
                    //allocates exact size
                //is = {3,4,5};
                    //ERROR
            }
            
            {
                int is[4] = {1,2};
                assert( is[0] == 1 );
                assert( is[1] == 2 );
                assert( is[2] == 0 );
                assert( is[3] == 0 );
            }
            
            {
                //int is[2] = {1, 3, 2};
                    //WARN too small
            }

            //variable length
            {
                //enum
                {

                    enum M {M=3};
                    int is[M];
                    is[2] = 1;

                }

                //define
                {
#define DEFINESIZE 3
                    //BAD
                    //*no scope*, so you can't use N anymore.
                    //use enum instead
                    int is[DEFINESIZE];
                    is[2] = 1;
                }

                //VLA
                {
                    //- C99
                    //- implementation:
                        //increase/decrease stack pointer
                        //requires one addition and one multiplication per declaration
                    {
                        int n = 2;
                        //scanf( "%d", &n );
                            //OK
                        int isVla[n];
                    }

                    {
                        //int n = 2;
                        //int isVla[n] = { 1, 2 };
                            //ERROR
                            //cannot be initialized
                    }

                    {
                        //const int n = 2;
                        //int isVla[n] = { 1, 2 };
                            //ERROR
                            //cannot be initialized
                    }
                }

            }

        }
 
        //pointers and arrays are different
        {
            puts("pointers and arrays are different types:");
            printf("sizeof(int) = %d\n",sizeof(int));
            printf("sizeof(int*) = %d\n",sizeof(int*));
            printf("sizeof(int[3]) = %d\n",sizeof(int[3]));
            //printf("sizeof(int[]) = %d\n",sizeof(int[]));
                //ERROR
                //incomplete type!
        }

        //locations in memory of an array
        {
            int is[3];
            puts("locations of array:");
            printf("(void*)is = %p\n",(void*)is);
            printf("(void*)&is[0] = %p\n",(void*)&is[0]);
            printf("(void*)&is[1] = %p\n",(void*)&is[1]);
            printf("(void*)&is[2] = %p\n",(void*)&is[2]);
        }

        //for combo
        {
            int is[] = {0,1,2};
            int i;
            for(i=0; i<3; i++ )
            {
                printf("%d ",is[i]);
            }
        }

        {
        //BAD
            //overflow

            //printf("%d\n",is[3]);
            //is[3]=0;
            //printf("%d\n",is[1000000]);
            //is[1000000]=0;

            //for(i=0; i<=1000000000; i++ ){
            //        printf("%d\n",i);
            //        j=is[i];
            //}
            //    segmentation fault
            
            /*printf("%d\n",is[100000]);*/
            //might run: only get segmentation fault if you hit exactly the last position!
        }

        //compare
        {
            //memcmp is faster than for loop
            //one catch: float NaN

            int is[]  = { 0, 1, 2 };
            int is2[] = { 0, 1, 2 };

            assert( is != is2 );
                //compares addresses, not data!
            
            assert( memcmp( is, is2, 3 * sizeof(int)) == 0 );
            is[1] = 0;
            assert( memcmp( is, is2, 3 * sizeof(int)) < 0 );
            is[1] = 2;
            assert( memcmp( is, is2, 3 * sizeof(int)) > 0 );
        }

        //copy
        {
            int is[] = {0,1,2};
            int is2[3];

            //for(i=0; i<3; i++ ){
            //    is2[i] = is[i];
            //}
                //SLOW
                //use memcpy insted

            memcpy(is2,is,3*sizeof(int));
                //copy 3*4 bytes from one is7 to is
                //more efficient than for: direct memory copyint, no i++ or i<n? check
            assert( memcmp( is, is2, 3 * sizeof(int)) == 0 );
    
            memcpy(&is, &(int [5]){ 0,1,2 }, sizeof(is) );
                //C99
            assert( memcmp( is, &(int [5]){ 0,1,2 }, 3 * sizeof(int)) == 0 );
        }

        //multidim
            //BAD
            //never use this
            //always use single dim
        {
            int *m1[2];
            int m11[] = { 1, 2, 3    };
            int m12[] = { 4, 5, 6, 7 };
            m1[0] = m11;
            m1[1] = m12;

            //error: cannot know    how much memory to allocate!
                //int m31[][3];
    
            //error: = {...} works only at declaration
                //int m111[2][3];
                //m111[0] = &(int*[3]){1,2,3};
        
            int m2[][3] =
            {
                { 1, 2, 3 },
                { 4, 5, 6 }
            };
            //allocates the exact ammount: 2 pointeres to int[3]

            int m3[3][3] =
            {
                { 1, 2, 3 },
                { 4, 5, 6 }
            };
            //allocates 3x3, fills only 2x3. the rest is 0 or m3[0] gets a NULL pointer?

            //error: last must be there
                //int m3[][] =
                //{
                //    { 1, 2, 3    },
                //    { 4, 5, 6, 7 }
                //};
                //
                //reason:
                //    this is array of m[3] arrays!!
                //    the data on an array is sequentially written to RAM
                //    and all of its elements have a fixed size (so they can be indexed!)
                //
                //    if you don't know the sizeof(m[3]), (and you don't know the sizeof(m[]!))
                //    you can't put all those m[3] sequentially on the RAM.
                //
                //    the compiler could look at each element of the initialization
                //    and ensure they all have the *same size*, and then take that size,
                //    but this would take a long time, so it just forces the user to input this

                    {
                        //pass multidimentional arrays to functions
                        puts("\npass multidim to func:");
                        //*never do that*: pass an array, and give m and n
                        //this is just to understand arrays better.
                        int* mat[mc]; //two int pointers
                        int mat1[][3] =
                        {
                            { 1, 2, 3 },
                            { 4, 5, 6 }
                        };
                        int i;
                        for( i = 0; i < mc; i++ )
                        {
                            mat[i] = mat1[i]; //first points to the int at address 0 of the matrix mat1
                        }
                        print_array(mat,2,3);
                    }

            //multidimentional > 2
    
                int m4[][2][3] =
                {
                    { { 1, 2, 3 }, { 4 , 5,  6 } },
                    { { 7, 8, 9 }, { 10, 11, 12} }
                };
                //allocates exact amount for first: 2x2x2
                
                int m41[3][2][3] =
                {
                    { { 1, 2, 3 }, { 4 , 5,  6 } },
                    { { 7, 8, 9 }, { 10, 11, 12} }
                };
                //allocates one extra for first dimension

                //error: only first can be empty
                    //int m4[][][2] = {
                    //    {{1,2},{3,4}},
                    //    {{5,6},{7,8}}
                    //};
    
            int m5[mc][nc];

            //error: TODO ? why
                //int m6[][nc] = {
                //    {1,2,3},
                //    {4,5,6}
                //};

                //int m7[mc][nc] = {
                //    {1,2,3},
                //    {4,5,6}
                //};

            //matrix pattern
            {
                int i, j;
                for( i = 0; i < 2; i++ )
                {
                    printf( "\n" );
                    for( j = 0; j < 3; j++ )
                    {
                        printf( "%d ", m1[i][j] );
                    }
                }
                printf( "\n\n" );
            }
        }

        //string
        {
            //text segment
            {
                char cs[] = "abc";
                //char cs[] = {'a','b','c','\0'}
                    //SAME
                    //BAD
                    //harder to write
                    //you may forget the '\0'
                assert( cs[0] == 'a'  );
                assert( cs[1] == 'b'  );
                assert( cs[2] == 'c'  );
                assert( cs[3] == '\0' );
                    //NOTE
                    //use '\0' always
                    //c std functions use that to see where string ends
                
                cs[0] = 'A';
                assert( strcmp(cs,"Abc") == 0 );

                //cs = "Abc";
                    //ERROR
            }

            //can use across lines.
            //no newline added.
            {
                char cs[] = "ab"
                            "cd";
                assert( strcmp( cs, "abcd" ) == 0 );
            }

            //std string functions
            {
                //use '\0' to see ther string ends


                //printf, sprintf
                {
                    char cs[] = "abc";
                    char cs2[4];
                    sprintf(cs2, "%s", cs );
                    assert( strcmp( cs, cs2 ) == 0 );
                }

                //length
                {
                    char cs[] = "abc";
                    assert( strlen(cs) == 3 );
                }

                //copy
                {
                    char cs[] = "abc";
                    char cs2[4];
                    char cs3[1];

                    strcpy( cs2, cs );
                        //more efficient than for loop
                    strcpy( cs2, "abc" );
                        //OK
                    //strcpy( cs3, "abc" );
                        //BAD
                        //no born checking as always
                }

                //compare
                {
                    char cs[] = "abc";
                    char cs2[] = "abc";
                    assert( strcmp( cs, cs2 ) == 0 );
                    assert( strcmp( cs, "abc" ) == 0 );
                        //equality
                    cs[1] = 'a';
                    assert( strcmp( cs, cs2 ) < 0 );
                        //smaller
                    cs[1] = 'd';
                    assert( strcmp( cs, cs2 ) > 0 );
                        //larget
                }
            }
    
            //text segment
            {
                char* cs = "abc";
                assert( cs[0] == 'a' );
                    //NOTE
                    //points to the text segment
                    //very memory efficient
                
                //cs[0] = 'a';
                    //ERROR
                    //text segment cannot me modified
                
                //int * is = {1, 3, 2};
                    //WARN
                    //can't do this
                    //think:
                    //- chars are exactly as in the text segment
                    //- integer 1 is not represented as a single byte char '1'
                    //    but as 4 bytes
            }

            //unicode
            {
                char cs[] = "汉语";
                printf("%s\n",cs);

                //cs[0] = 'a';
                //printf("%s\n",cs);
                    //BAD
                    //only changes first byte
                    //you get trash all over
                
                //cs[0] = '英';
                    //WARN

                setlocale( LC_CTYPE, "" );
                    //NOTE
                    //need this to print correctly

                wchar_t  wcs[] = L"汉语";

                printf( "%ls\n", wcs );

                wcs[0] = L'英';
                printf( "%ls\n", wcs );

                wcs[0] = L'a';
                printf( "%ls\n", wcs );

                //wchar_t  wideString2[] = "asdf";
                    //ERROR
                    //non wide init
            }
        }
    }

    //dynamic
    {
        //vs VLA
        //- no scope
        //
        //      therefore can be allocated in functions
        //      and returned to caller
        //
        //- heap much larger than stack

        int i = 8;
        size_t bytes = sizeof(char)*i;
        char* cp = (char*) malloc (bytes);
        if (cp == NULL)
        {
            printf("could not allocate %zu bytes", bytes);
        }
        strcpy(cp,"0123456");
        printf("%s\n", cp);
        free(cp);
    }

    return 0;
}
