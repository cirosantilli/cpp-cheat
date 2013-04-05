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
    enum CTES { NPTS = 100 };
    const double PI   = acos(-1.0);
    const double PI_2 = PI/2.0;

    int i;
    int plot_type;
    PLFLT delta;
    PLFLT datax[NPTS];
    PLFLT datay[NPTS];
    PLFLT datay2[NPTS];

    //generate data
    delta = 2.0 * PI / (double) NPTS;
    for ( i = 0; i < NPTS; i++ )
    {
        datax[i] = (PLFLT)i;
        datay[i] = sin( i * delta );
        datay2[i] = sin( i * delta + PI_2 );
    }

    plot_type = -1;

    switch(plot_type)
    {
        //#minimal program
        case -1:
            plsdev("xwin");
            plinit();
            plenv( 0.0, (PLFLT)NPTS, -1.0, 1.0, 0, 1 );
            plstring( NPTS, datax, datay, "*" );
            pllab( "", "", "#frplhist" );
            plend();
        break;

        //#major cheat
        case 0:

            //#plsdev

                //must come before plinit! (constructor args)
                
                //decides where output will go
                
                //if missing, will be asked for user from command line.
                
                //to screen:
                
                    plsdev("xwin");

                //to file:

                    //plsdev("svg");
                    //plsfnam("a.svg");

            //must always come before plotting calls:
            plinit();

            //#plenv
                
                //<http://plplot.sourceforge.net/docbook-manual/plplot-html-5.9.9/scales.html>
            
                //general plotting params

                //customizations can be made with:
                //plvpor, plvasp, plvpas, plwind, plbox
                
                //mandatory, unless you set all other customizations with their respective functions
            
                plenv( 0.0, (PLFLT)NPTS, -1.0, 1.0, 0, 1 );
                //xmin, xmax, ymin, ymax, just, type
                //just:
                //- 0: scale x/y indepedently
                //- 1: same scale for x/y.
                //type:
                //0: box
                //1:     + axes
                //2:            + grids

            //#plcol0 #map0
                
                //color map for axes, labels 
                
                //different from colors for the actual plot
                //where colors may have meanings such as legend
                //or values
                
                //there is the concept of current color

                //0 	black (default background)
                //1 	red (default foreground)
                //2 	yellow
                //3 	green
                //4 	aquamarine
                //5 	pink
                //6 	wheat
                //7 	grey
                //8 	brown
                //9 	blue
                //10 	BlueViolet
                //11 	cyan
                //12 	turquoise
                //13 	magenta
                //14 	salmon
                //15 	white

                plcol0( 1 );

            plstring( NPTS, datax, datay, "*" );
            
            plcol0( 2 );
            plstring( NPTS, datax, datay2, "+" );
                                         //glyph to draw

            //#labels
            
                plcol0( 3 );

                //see <#text formatting> for how to format text
            
                pllab(
                    "#frbottom label $x^2$",
                    "#frleft label",
                    "#frplstring"  //title
                );

            //#plend
                
                //frees memory
            
                plend();

        break;

        //#histogram
        case 1:
            plsdev("xwin");
            plinit();
            //doest not need plenv
            plhist(
                NPTS,
                datay,
                -1.1,   //xrange left
                1.1,    //       right
                44,     //how many bars to plot (it averages points?)
                0       //option flags
            );
            pllab( "", "", "#frplhist" );
            plend();
        break;

        //#multiple windows
        case 2:
            //TODO
            plsdev("xwin");
            plenv( 0.0, (PLFLT)NPTS, -1.0, 1.0, 0, 1 );
            plinit();
            plhist( NPTS, datay, -1.1, 1.1, 44, 0 );
            plend();
        break;

    }


    //#customizing view

            //#plvport
                
                //set viewport
                
                //mandatory for plstring

                /*plvpor( 0.0, (PLFLT)NPTS, -1.0, 1.0 );*/
                //xmin, xmax, ymin, ymax

                /*plbox( "bclnst", 0.0, 0, "bnstv", 0.0, 0 );*/

        //#plwind

            /*plwind( -2.0, 3.0, -100.0, 0.0 );*/

        //#plbox

            /*plbox( "", 0.0, 0, "cmstv", 30.0, 3 );*/

    //#text formatting
    
        //#plsesc

            //change escape char to (default '#'):
        
            //plsesc( '@' );
    
        //#in strings

            //#u: move up to the superscript position (ended with #d)
            //#d: move down to subscript position (ended with #u)
            //#b: backspace (to allow overprinting)
            //##: number symbol
            //#+: toggle overline mode
            //#-: toggle underline mode
            //#gx: Greek letter corresponding to Roman letter x (see below)
            //#fn: switch to normal (sans-serif) font
            //#fr: switch to Roman (serif) font
            //#fi: switch to italic font
            //#fs: switch to script font
            //#(nnn): Hershey character nnn (1 to 4 decimal digits)
            //#[nnn]: unicode character nnn (nnn can be decimal or hexadecimal [e.g., starting with 0x]) (UNICODE ONLY).
            //#<0x8nnnnnnn>: absolute FCI to be used to change fonts in mid-string. (nnnnnnn must be exactly 7 digits). (UNICODE ONLY).
            //#<0xmn>: change just one attribute of the FCI in mid-string where m is the hexdigit and n is the hexpower. If more than two digits are given (so long as the eighth digit does not mark this as an absolute FCI, see above) they are ignored. (UNICODE ONLY).
            //#<FCI COMMAND STRING/>: the FCI COMMAND STRING is currently one of "sans-serif", "serif", "monospace", "script", "symbol", "upright", "italic", "oblique" "medium", or "bold" (without the surrounding quotes). These FCI COMMAND STRINGS change one attribute of the FCI according to their name. (UNICODE ONLY). 

    return EXIT_SUCCESS;
}
