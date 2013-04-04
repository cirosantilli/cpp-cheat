/*
   this file shows how to use blas and lapack with the standard
   interfaces provided by their respective projects, repectively through
   `cblas.h` and `lapacke.h`
*/

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <plplot/plplot.h>

int main(void)
{ 
    enum NPTS { NPTS = 2047 };
    const double PI = acos(-1.0);

    int   i;
    PLFLT data[NPTS], delta;

    //must always come before other pl calls
    plinit();

    plsdev("xwin");

    //generate data
    delta = 2.0 * PI / (double) NPTS;
    for ( i = 0; i < NPTS; i++ )
        data[i] = sin( i * delta );

    plcol0( 1 );

    //#histogram
    
        plhist(
            NPTS,
            data,
            -1.1,   //xrange left
            1.1,    //       right
            44,
            0
        );

    plcol0( 2 );

    //#labels
        
        pllab(
            "#frValue",     //bottom
            "#frFrequency", //left
            "#frPLplot Example 5 - Probability function of Oscillator"  //title
        );

    plend();
    return EXIT_SUCCESS;
}
