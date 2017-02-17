#include "common.h"

/*
equation:

$Y'(t) = f(Y(t),t)$

where

$Y(t) = (y(t), y'(t), y''(t), ...)$
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

int main(void) {
	double mu = 1.0;
	gsl_odeiv2_system sys = { ode_func, ode_jac, 2, &mu };
	gsl_odeiv2_driver * d = gsl_odeiv2_driver_alloc_y_new(
		&sys,
		gsl_odeiv2_step_rk8pd,
		1e-6,
		1e-6,
		0.0
	);
	int i;
	double t = 0.0;
	double t1 = 100.0;
	double y[2] = {1.0, 0.0};
	const int  nPts = 1000;
	double dt = t1 / nPts;
	FILE* fp = fopen(__FILE__ "out.tmp", "w");
	double datax[nPts];
	double datay[nPts];

	for (i = 0; i < nPts; i++) {
		double ti = i * dt;
		int status = gsl_odeiv2_driver_apply(d, &t, ti, y);
		if (status != GSL_SUCCESS) {
			fprintf(stderr, "error, return value=%d\n", status);
			break;
		}

		/* Get output. */
		fprintf(fp, "%.5e %.5e %.5e\n", t, y[0], y[1]);
		printf("%.5e %.5e %.5e\n", t, y[0], y[1]);
		datax[i] = y[0];
		datay[i] = y[1];
	}

	/* Cleanup. */
	fclose(fp);
	gsl_odeiv2_driver_free(d);

	/* Plot. */
	plsdev("xwin");
	plinit();
	plenv(
		gsl_stats_min(datax, 1, nPts),
		gsl_stats_max(datax, 1, nPts),
		gsl_stats_min(datay, 1, nPts),
		gsl_stats_max(datay, 1, nPts),
		0,
		1
	);
	plstring(nPts, datax, datay, "*");
	plend();

	/* #gnuplot */
	/*system("gnuplot -e 'p \"ode.tmp\" u 2:3 w lines; pause -1'");*/

    return EXIT_SUCCESS;
}
