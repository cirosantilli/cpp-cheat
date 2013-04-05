#include <stdlib.h>

#include "heading.h"

// prototype of bison-generated parser function
int yyparse();

int main(int argc, char **argv)
{
  if ( (argc > 1) && (freopen(argv[1], "r", stdin) == NULL) )
  {
    cerr << argv[0] << ": File " << argv[1] << " cannot be opened.\n";
    exit( EXIT_FAILURE );
  }
  
  yyparse();

  return EXIT_SUCCESS;
}
