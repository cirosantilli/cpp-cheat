#include <stdio.h>
#include <string.h>
#include <ctype.h> //for isspace and family

int main(){

  //escape chars in string conts
    puts("\nescape chars:");
    printf("\"\n");
    printf("\\\n");
    printf(">>>\n<<< new line\n");
    printf(">>>\t<<< tab char\n");
    printf(">>>\f<<< feed char\n");
    printf(">>>\v<<< vertical tab\n");
    printf(">>>\r<<< carriage return\n");
    printf(">>>%c<<< null char\n",'\0');
    printf(">>>\x61<<< a in hexadecimal\n");
    printf(">>>\xe4\xb8\xad<<< chinese for \"middle\" in utf8\n"); //chinese utf8 TODO teach

  //string creation
    char s1[8]; //allocates 8 bytes memory
    s1[0] = 's';
    s1[1] = '1';
    s1[2] = '\0'; //terminates with null

    char s2[8] = "s2"; //8 bytes allocated. 's', '1', '\0' set, and 5 undetermined
    char s3[] = "s3"; //3 bytes allocated: s, 2 and \0
    char * s4 = "s4"; //same as last

    char s5[8];
    strcpy(s5,"s2"); //8 bytes allocated. copied s2 into it

    puts("\nsizeof:");
    printf("sizeof(\"%s\") = %d\n",s1,sizeof(s1));
    printf("sizeof(\"%s\") = %d\n",s2,sizeof(s2));
    printf("sizeof(\"%s\") = %d\n",s3,sizeof(s3));
    printf("sizeof(\"%s\") = %d <<< pointers and arrays are different types!\n",s4,sizeof(s4));

  //isspace
    puts("\nisspace:");
    printf("isspace('a') = %d\n",isspace('a'));
    printf("isspace(' ') = %d\n",isspace(' '));
    printf("isspace('\\n') = %d\n",isspace('\n'));


  //isdigit
    puts("\nisdigit:");
    printf("isdigit('0') = %d\n",isspace('0'));
    printf("isdigit('a') = %d\n",isspace('a'));
    printf("isdigit(' ') = %d\n",isspace(' '));

  //string operations
    puts("\nstrlen:");
    printf("strlen(\"%s\") = %d\n",s1,strlen(s1));
    printf("strlen(\"%s\") = %d\n",s2,strlen(s2));
    printf("strlen(\"%s\") = %d\n",s3,strlen(s3));
    printf("strlen(\"%s\") = %d\n",s4,strlen(s4));
    //size until first '\0', excluding '\0'
 

  //strcpy: copy into first string
    puts("\nstrcpy:");
    strcpy(s1,s2); 
    printf("s1 = %s\n",s1);
 
  //strcat: concatenate into first string
    puts("\nstrcat:");
    strcat(s1,s2);
    printf("s1 = %s\n",s1);
    
  //strchr
    //search for char in string
    //return pointer to that char if found
    //return null if not found
 
    puts("\nstrchr:");

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
