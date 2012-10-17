#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * fp operations
 * don't forget: your os can give you errors on this operations!
 */

//error reports

void report_cant_open (char * path){
    fprintf(stderr, "could not read from:\n%s\n", path);
}

void report_cant_read (char * path){
    fprintf(stderr, "could not read from:\n%s\n", path);
}

void report_cant_move (char * path){
    fprintf(stderr, "could not move in file:\n%s\n", path);
}

void report_cant_write (char * path){
    fprintf(stderr, "could not write to:\n%s\n", path);
}

void report_cant_close (char * path){
    fprintf(stderr, "could not close from:\n%s\n", path);
}

void report_cant_allocate (size_t bytes){
    fprintf(stderr, "could not allocate %zu bytes", bytes);
}

//opens file at given path, calculates its size, and closes and returns size
long file_size_open(char *path)
{
  FILE *fp = fopen(path, "r");
  if (fp == NULL){
    report_cant_open(path);
    return -1L;
  }
  if ( fseek (fp, 0 , SEEK_END) != 0 ){
    report_cant_move(path);
    return -1L;
  }
  long l = ftell (fp);
  if ( l == -1L ){
    report_cant_move(path);
    return -1L;
  }
  if ( fclose(fp) == EOF ){
    report_cant_close(path);
    return -1L;
  }
  return l;
}

//returns the size of the given open file pointer
long file_size(FILE *fp)
{

  long oldpos = ftell (fp);
  if ( oldpos == -1L ){
    return -1L;
  }

  if ( fseek (fp, 0 , SEEK_END) != 0 ){
    return -1L;
  }

  long l = ftell (fp);
  if ( l == -1L ){
    return -1L;
  }

  //retore old position
  if ( fseek (fp, oldpos , SEEK_SET) != 0 ){
    return -1L;
  }

  return l;

}

//reads the entire file to a char[]
//returns a pointer to the start of that array 
//memory is dynamically allocated, so caller must free it!
//if any problem happens, returns NULL
char * file_read(char *path)
{

  FILE * fp;
  long l;
  char * buffer;
  size_t bytes;

  fp = fopen ( path , "rb" );
  if (fp==NULL) {
    report_cant_open(path);
    return NULL;
  }

  // obtain file size:
  l = file_size(fp);
  if (l < 0){
    fprintf(stderr, "could not determine lenght of:\n%s\n", path);
    return NULL;
  }

  // allocate memory to contain the whole file:
  bytes = sizeof(char)*l;
  buffer = (char*) malloc (bytes);
  if (buffer == NULL) {
    report_cant_allocate(bytes);
    return NULL;
  }

  // copy the file into the buffer:
  if ( fread (buffer,1,l,fp) != l ) {
    report_cant_read(path);
    return NULL;
  }

  /* the whole file is now loaded in the memory buffer. */

  if ( EOF == fclose (fp) ){
    report_cant_close(path);
    return NULL;
  }

  return buffer;
}

//write null terminated string to file
//returns negative integer if fails
int file_write(char *path, char *s)
{

  FILE * fp;
  long l;
  char * buffer;
  size_t bytes;

  fp = fopen ( path , "wb" );
  if (fp==NULL) {
    report_cant_open(path);
    return -1;
  }

  l = strlen(s);

  // copy the file into the buffer:
  if ( fwrite (s,1,l,fp) != l ) {
    report_cant_write(path);
    return -1;
  }

  if ( EOF == fclose (fp) ){
    report_cant_close(path);
    return -1;
  }

  return 1;

}

int main(){

  FILE *fp;
  int err, had_error, fi;
  float ff;
  char c1;
  char *cp1;

  const int buff_size = 16, nelems = 4;

  char path[buff_size], buff[buff_size];
  int elems_write[] = {1,2,3,4};
  int elems_read[nelems];

  //stdin
    //be careful!! stdin won't return EOF
    //
    //the only way to know that a stdin ended is recognizing some specific
    //pattern of the input, such as a newline with fgets, or the end of a
    //number with scanf
    //before this comes, the program just stops waiting for the stdin to
    //produce this, either from user keyboard input, or from the program
    //behind the pipe.

  fputs("fputs to stdout 1\nfputs to stdout 2\n", stdout);
  fputs("fputs to stderr 1\nfputs to stderr 2\n", stderr);
  //*always* put user messages on stderr, even if they are not errors:
  //  stdout is just for program to program output
 

  //fopen
    //don't forget to close after using!
    //r : read. compatible with a,w
    //w : read and write. destroy if exists, create if not.
    //a : append. write to the end. creates if does not exist.
    //+ : can do both input and output. msut use flush or fseek
    //x : don't destroy if exist (c11, not c++!, posix only)
    //b : binary. means nothing in POSIX systems,
    //    on our dear DOS must be used for NL vs NLCR problems
    //    there are two different modes there
    //    Threfore, for portability, make this difference.
    fputs("\n", stderr);
    strcpy(path,"f.tmp");
    fp = fopen(path,"w");
    if (fp==NULL){
      report_cant_open(path);
    } else {
      //fputc
        if (fputc('a',fp) == EOF ){
          fprintf(stderr, "fputc could not write to:\n%s\n", path);
        }
        if ( fputc('\n',fp) == EOF ){
          fprintf(stderr, "fputc could not write to:\n%s\n", path);
        }

      //fputs
        //not automatically newline terminated like puts
        if ( fputs("fputs 1\nfputs 2\n", fp) == EOF ){
          fprintf(stderr, "fputs could not write to:\n%s\n", path);
        }

      //fprintf
        // http://www.cplusplus.com/reference/clibrary/cstdio/fprintf/
        if ( fprintf(fp,"%d\n%.2e\n",123,12.3f) < 0 ){
          fprintf(stderr, "fprintf could not write to:\n%s\n", path);
        }

    }
  
    if ( fclose(fp) == EOF ) {
      fprintf(stderr, "could not close:\n%s\n", path);
    }
    //don't forget to close!
    //* there is a limited ammount of open files at a time by the os
    //* buffered output may not have been saved before closing
    
  //text mode

    //read from a file
      fp = fopen(path,"r");
      if (fp==NULL){
        fprintf(stderr, "could not read from:\n%s\n", path);
      } else {
        //fgetc
          c1 = fgetc(fp);
          if (c1 == EOF){
            if (feof(fp)) {
              fprintf(stderr, "fgetc end of file:\n%s\n", path);
            } else if (ferror(fp)) {
              fprintf(stderr, "fgetc error reading from:\n%s\n", path);
            }
          }
          fprintf(stderr, "c1 = %c\n",c1);
          fgetc(fp);

        //fgets
          //http://www.cplusplus.com/reference/clibrary/cstdio/fgets/
          //reads up to:
          //* newline
          //* buff_size-1 chars
          //* EOF
          //saves result in buff, '\0' terminated
          if ( fgets(buff, buff_size, fp) == NULL ){
            if (feof(fp)) {
              fprintf(stderr, "fgets reached the of file and read nothing:\n%s\n", path);
            } else if (ferror(fp)) {
              fprintf(stderr, "fgets error reading from:\n%s\n", path);
            }
          } else if (feof(fp)) {
              fprintf(stderr, "fgets reached the of file and read some chars before that:\n%s\n", path);
          }
          fprintf(stderr, "buff = %s",buff);

          fgets(buff, buff_size, fp);
          fprintf(stderr, "buff = %s",buff);

        //fscanf
          //complicated like scanf
          if ( fscanf(fp, "%d\n%e\n",&fi,&ff) != 2 ){ //how many values were read
            if (feof(fp)) {
              fprintf(stderr, "fscanf reached the of file and read nothing:\n%s\n", path);
            } else if (ferror(fp)) {
              fprintf(stderr, "fscanf error reading from:\n%s\n", path);
            }
          }
          fprintf(stderr, "%d %.2e\n",fi,ff);
      }

      if ( fclose(fp) == EOF ) {
        fprintf(stderr, "could not close:\n%s\n", path);
      }

    //binary io
      //notice how inneficient this is for ints! 1 occupies 4 bytes and not 1!
      //  mostly useful for data that cannot be interpretred as text (images, executables)
      //better performance only on large chunks
      //good when you know the size of the entire input/output
      //including the 'b' option only makes a difference for DOS. use for compatibility (or maybe don't!)

      strcpy(path,"b.tmp");

      fp = fopen(path,"wb");
      if (fp==NULL){
        fprintf(stderr, "could not open:\n%s\n", path);
      } else {

        //fwrite
          //nelems=sizeof(buff)/sizeof(buff[0]);
          //nelems=strlen(buff)+1

          if ( fwrite(elems_write, sizeof(elems_write[0]), nelems, fp) < nelems ){ //returns number of elements written
            fprintf(stderr, "could not write all the data:\n%s\n", path);
          }

      }

      if ( fclose(fp) == EOF ) {
        fprintf(stderr, "could not close:\n%s\n", path);
      }

    //read
      fp = fopen(path,"rb");
      if (fp==NULL){
        fprintf(stderr, "could not open:\n%s\n", path);
      } else {

          if ( fread(elems_read, sizeof(elems_read[0]), nelems, fp) < nelems ){ //returns number of elements written
            fprintf(stderr, "could not read all the data:\n%s\n", path);
          }
      }

      if ( fclose(fp) == EOF ) {
        fprintf(stderr, "could not close:\n%s\n", path);
      }

      fprintf(stderr, "elems_read[0] = %d\n", elems_read[0]);
      fprintf(stderr, "elems_read[1] = %d\n", elems_read[1]);
      fprintf(stderr, "elems_read[2] = %d\n", elems_read[2]);
      fprintf(stderr, "elems_read[3] = %d\n", elems_read[3]);

  //write entire string to file at once
    strcpy(path,"f.tmp");
    if ( file_write(path,"asdf\nqwer") < 0 ){
      report_cant_write(path);
    }

  //read entire file at once to a string
    char *s = file_read(path);
    if (s == NULL ){
      report_cant_read(path);
    }
    fprintf(stderr, "contents of \"%s\":\n\n%s\n", path, s);
    free(s);

  //reposition read write
  
    //ftell
      //long int curpos = ftell(pf)
      //if ( curpos == -1L ){
      //  report_cant_move();
      //}
  
    //fseek
      //http://www.cplusplus.com/reference/clibrary/cstdio/fseek/
      //
      //SET: beginning
      //CUR: current
      //END: end
      //
      //for binary, n bytes, for read, no necessarily
      //
      //if ( fseek ( pf, 0 , SEEK_SET ) != 0 ) {
      //  report_cant_move();
      //}

    //flush(fp)
      //for output streams only.
      //makes sure all the data is put on the stream.
      //
      // if (flush(fp) == EOF){
      //    //error
      // }

    //TODO fgetpos, fsetpos, rewind

  return 0;
}
