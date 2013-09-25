/**
Simple exercise tac implementataion: no error checking or nice interfaces.

Takes a single filename from stdin and tacs it.

Reads fixed chunk sizes from file, never the entire file at a time.

If a line is larger than this chunk size, the program may exit with EXIT_FAILURE and give an error message.

Mimics GNU cat 8.2, which require that the file end in a newline to print the last line ``properly''. Ex:

     a b \n c d \n

Gets printed as:

    cd
    ab

But:

     a b \n c d

Gets printed as:

     cdab

The most delicate part of the implementation are the unsigned index manipulations which require great care.
*/

//#define DEBUG_OUTPUT

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
  FILE *fp;
  enum CONSTEXPR { BUF_SIZE = 4 }; // Maximum accepted line length is BUF_SIZE including the newline.
  char buffer[BUF_SIZE], buffer_leftover[BUF_SIZE];
  size_t last_newline_position, leftover_bytes, file_size, seek_end_offset, nbytes_read;

  fp = fopen(argv[1], "r");
  fseek(fp, 0, SEEK_END);
  file_size = ftell(fp);
  nbytes_read = BUF_SIZE;
  leftover_bytes = 0;
#ifdef DEBUG_OUTPUT
    printf("file_size = %zu\n", file_size);
#endif
  // Unsigned type loop: use two variables idiom.
  for (size_t seek_end_offset = BUF_SIZE; seek_end_offset < file_size + BUF_SIZE; seek_end_offset += BUF_SIZE) {
    // Last iteration.
    if (seek_end_offset > file_size) {
        nbytes_read = BUF_SIZE - (seek_end_offset - file_size);
        seek_end_offset = file_size;
    }
    fseek(fp, -seek_end_offset, SEEK_END);
    fread(buffer, sizeof(char), nbytes_read, fp);
    last_newline_position = nbytes_read - 1;
    // Unsigned type loop. Use wrap around idiom.
#ifdef DEBUG_OUTPUT
    printf("seek_end_offset         = %zu\n", seek_end_offset);
    printf("nbytes_read             = %zu\n", nbytes_read);
    printf("buffer                  = ");
    fwrite(buffer, sizeof(char), nbytes_read, stdout);
#endif
    for (size_t i = nbytes_read - 1; i < nbytes_read; --i) {
#ifdef DEBUG_OUTPUT
      printf("i                     = %zu\n", i);
      printf("buffer[i]             = %c\n" , buffer[i]);
      printf("last_newline_position = %zu\n", last_newline_position);
      printf("leftover_bytes        = %zu\n", leftover_bytes);
      printf("\n");
#endif
      if (buffer[i] == '\n') {
        if (i < nbytes_read - 1) {
          fwrite(&buffer[i + 1], sizeof(char), last_newline_position - i, stdout);
        }
        last_newline_position = i;
        if (leftover_bytes > 0) {
          fwrite(buffer_leftover, sizeof(char), leftover_bytes, stdout);
          leftover_bytes = 0;
        }
      }
    }
    if (last_newline_position == BUF_SIZE) {
      fprintf(stderr, "line too long\n");
      exit(EXIT_FAILURE);
    }
    leftover_bytes = last_newline_position + 1;
    memcpy(buffer_leftover, buffer, leftover_bytes);
  }
  fwrite(buffer_leftover, sizeof(char), leftover_bytes, stdout);
}
