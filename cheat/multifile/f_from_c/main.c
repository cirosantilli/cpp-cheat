#include <stdio.h>
#include <assert.h>

#include "f.h"

int main( int argc, char** argv )
{
    int i;
    int j;

    //subroutine call
        i = 1;
        s_( &i );
        assert( i == 2 );

    //function call
        i = 1;
        j = f_( &i );
        assert( i  == 2 );
        assert( j  == 2 );

    return 0;
}
