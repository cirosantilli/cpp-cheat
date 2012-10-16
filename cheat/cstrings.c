#include <stdio.h>
#include <string.h>

int main()

  //escape chars in string conts
    printf("new\nline");
    printf("\t<<< tab char\n");
    printf("%c<<< null char\n",'\0');
    printf("\"\n");
    printf("\\\n");
    printf("\x61\n");
    printf("\xe4\xb8\xad<<< chinese for \"middle\" in utf8\n"); //chinese utf8 TODO teach

  //string creation
    char s1[8]; //allocates 8 bytes memory
    char s2[8] = "s1"; //8 bytes allocated. 's', '1', '\0' set, and 5 undetermined
    char s3[] = "s2"; //3 bytes allocated: s, 2 and \0
    char * s4 = "s3"; //same as last

    puts("sizeof:")
    printf("%d\n",sizeof(s1));
    printf("%d\n",sizeof(s2));
    printf("%d\n",sizeof(s3));
    printf("%d\n",sizeof(s4));

  //string operations
  
    puts("strlen:")
    printf("%d\n",strlen(s1));
    printf("%d\n",strlen(s2));
    printf("%d\n",strlen(s3));
    printf("%d\n",strlen(s4));
    //size until first '\0'
 
    strcat(s1,s2);
    printf("s1 = %s\n",s1);
    //strcat: concatenate into first string

    strcpy(s1,s2); 
    printf("s1 = %s\n",s1);
    //strcpy: copy into first string
    
    //strchr
      //search for char in string
      //return pointer to that char if found
      //return null if not found
 
      //find all occurences of char in string
      char str[] = "This is a sample string";
      char * pch;
      printf ("Looking for the 's' character in \"%s\"...\n",str);
      pch=strchr(str,'s');
      while (pch!=NULL){
        printf ("found at: %d\n",pch-str+1);
        pch=strchr(pch+1,'s');
      }

  return 0;
}
