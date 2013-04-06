#include <stdlib.h>
#include <stdio.h>

#include "heading.h"

// prototype of bison-generated parser function
int yyparse();

int main(int argc, char **argv)
{
  if ( (argc > 1) && (freopen(argv[1], "r", stdin) == NULL) )
  {
    fprintf( stderr, "file:\n%s\ncannot be opened\n", argv[1] );
    exit( EXIT_FAILURE );
  }
  
  yyparse();

  return EXIT_SUCCESS;
}
