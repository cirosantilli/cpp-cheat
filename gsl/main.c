#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>
#include <gsl/gsl_sf_bessel.h>
#include <gsl/gsl_statistics.h>

#include <plplot/plplot.h>

/*
equation:

$Y'(t) = f(Y(t),t)$

where

$Y(t) = ( y(t), y'(t), y''(t), ... )$
*/
int ode_func(double t, const double y[], double f[], void *params) {
    double mu = *((double*)params);
    f[0] = y[1];
    f[1] = -y[0] - mu*y[1]*(y[0]*y[0] - 1);
    return GSL_SUCCESS;
}

/*
Some methods ask for you to give the jacobian of it too
for better performance.

You have to calculate this by hand.
*/
int ode_jac(double t, const double y[], double *dfdy, double dfdt[], void *params) {
    double mu = *((double*)params);
    gsl_matrix_view dfdy_mat = gsl_matrix_view_array (dfdy, 2, 2);
    gsl_matrix* m = &dfdy_mat.matrix;
    gsl_matrix_set(m, 0, 0, 0.0);
    gsl_matrix_set(m, 0, 1, 1.0);
    gsl_matrix_set(m, 1, 0, -2.0*mu*y[0]*y[1] - 1.0);
    gsl_matrix_set(m, 1, 1, -mu*(y[0]*y[0] - 1.0));
    dfdt[0] = 0.0;
    dfdt[1] = 0.0;
    return GSL_SUCCESS;
}

int main (void) {
    double x = 5.0;
    double y = gsl_sf_bessel_J0(x);
    printf("J0(%g) = %.18e\n", x, y);

    /* #eqdifs */
    {
        /* system param */
        double mu = 1.0;

        /* complete system description: */
        gsl_odeiv2_system sys = { ode_func, ode_jac, 2, &mu };

        /* system + solver description: */
        gsl_odeiv2_driver * d = gsl_odeiv2_driver_alloc_y_new(
            &sys,
            gsl_odeiv2_step_rk8pd, //stepping function (given current state and step size, calculate new state)
            1e-6,                  //initial step size
            1e-6,                  //eps_abs      control parmeter
            0.0                    //eps_rel
        );

        int i;

        /* initial time: */
        double t = 0.0;

        /* max desired time: */
        double t1 = 100.0;

        /* initial condition */
        double y[2] = { 1.0, 0.0 };

        /* number of points to print */
        const int  nPts = 1000;

        /* time interval between each print */
        double dt = t1 / nPts;

        /* prepare to get the output */
        FILE* fp = fopen( "ode.tmp", "w" );
        double datax[nPts];
        double datay[nPts];

        for (i = 0; i < nPts; i++) {
            double ti = i * dt;

            /*
            Advance time from t to at leaast is
            will contain new last time value.
            */
            int status = gsl_odeiv2_driver_apply (d, &t, ti, y);

            if (status != GSL_SUCCESS) {
                fprintf( stderr, "error, return value=%d\n", status );
                break;
            }

            /* #get output */

                /* to a file: */
                fprintf( fp, "%.5e %.5e %.5e\n", t, y[0], y[1] );

                /* to stdout: */
                printf( "%.5e %.5e %.5e\n", t, y[0], y[1] );

                /* to array */
                datax[i] = y[0];
                datay[i] = y[1];
        }

        /* finalize */
        fclose(fp);
        gsl_odeiv2_driver_free(d);

        /* plot */

            /* #plplot */
            plsdev("xwin");
            plinit();
            plenv(
                gsl_stats_min( datax, 1, nPts),
                gsl_stats_max( datax, 1, nPts),
                gsl_stats_min( datay, 1, nPts),
                gsl_stats_max( datay, 1, nPts),
                0,
                1
            );
            plstring( nPts, datax, datay, "*" );
            plend();

            /* #gnuplot */
            /*system( "gnuplot -e 'p \"ode.tmp\" u 2:3 w lines; pause -1'" );*/
    }

    return EXIT_SUCCESS;
}
