#include <assert.h>
#include <math.h>
#include <stdio.h>

#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>
#include <gsl/gsl_sf_bessel.h>

/*
solves:

$Y'(t) = f(Y(t),t)$

where

$Y(t) = ( y(t), y'(t), y''(t), ... )$
*/
int ode_func( double t, const double y[], double f[], void *params )
{
    double mu = *((double*)params);
    f[0] = y[1];
    f[1] = -y[0] - mu*y[1]*(y[0]*y[0] - 1);
    return GSL_SUCCESS;
}

/*
some methods ask for you to give the jacobian of f too
for better performance.

you have to calculate this by hand.
*/
int ode_jac( double t, const double y[], double *dfdy, double dfdt[], void *params )
{
    double mu = *((double*)params);
    gsl_matrix_view dfdy_mat = gsl_matrix_view_array (dfdy, 2, 2);
    gsl_matrix* m = &dfdy_mat.matrix; 
    gsl_matrix_set (m, 0, 0, 0.0);
    gsl_matrix_set (m, 0, 1, 1.0);
    gsl_matrix_set (m, 1, 0, -2.0*mu*y[0]*y[1] - 1.0);
    gsl_matrix_set (m, 1, 1, -mu*(y[0]*y[0] - 1.0));
    dfdt[0] = 0.0;
    dfdt[1] = 0.0;
    return GSL_SUCCESS;
}

int main (void)
{
    double x = 5.0;
    double y = gsl_sf_bessel_J0( x );
    printf( "J0(%g) = %.18e\n", x, y );

    //#eqdifs
    {
        //system param
        double mu = 1.0;

        //complete system description:
        gsl_odeiv2_system sys = { ode_func, ode_jac, 2, &mu };

        //system + solver description:
        gsl_odeiv2_driver * d = gsl_odeiv2_driver_alloc_y_new(
            &sys,
            gsl_odeiv2_step_rk8pd, //stepping function (given current state and step size, calculate new state)
            1e-6,                  //initial step size
            1e-6,                  //eps_abs      control parmeter
            0.0                    //eps_rel
        );

        int i;

        //initial time:
        double t = 0.0;

        //max desired time:
        double t1 = 100.0;

        //initial condition
        double y[2] = { 1.0, 0.0 };

        //number of points to print
        int nPts = 1000;

        //time interval between each print
        double dt = t1 / nPts;
        
        FILE* fp = fopen( "ode.tmp", "w" );
        for (i = 1; i <= nPts; i++)
        {
            double ti = i * dt;

            //advance time from t to at leaast ti.
            //t will contain new last time value.
            int status = gsl_odeiv2_driver_apply (d, &t, ti, y);

            if (status != GSL_SUCCESS)
            {
                fprintf( stderr, "error, return value=%d\n", status );
                break;
            }

            //get output:
            fprintf( fp, "%.5e %.5e %.5e\n", t, y[0], y[1] );
            printf(      "%.5e %.5e %.5e\n", t, y[0], y[1] );
        }
        fclose(fp);
        gsl_odeiv2_driver_free(d);

        //if you want to see the points with gnuplot (you do =)):
            //system( "gnuplot -e 'p \"ode.tmp\" u 2:3 w lines; pause -1'" );
    }
        
    return 0;
}
