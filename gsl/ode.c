#include "common.h"

int ode_func(double t, const double y[], double f[], void *params) {
    double k = *((double*)params);
    (void)t;
    f[0] = y[1];
    f[1] = k * y[1] * (1.0 - y[0] * y[0]) - y[0];
    return GSL_SUCCESS;
}

/* Some methods ask for you to give the Jacobian of it too
 * for better performance. You have to calculate this by hand.
 */
int ode_jac(double t, const double y[], double *dfdy, double dfdt[], void *params) {
    double k = *((double*)params);
    (void)t;
    gsl_matrix_view dfdy_mat = gsl_matrix_view_array(dfdy, 2, 2);
    gsl_matrix *m = &dfdy_mat.matrix;
    gsl_matrix_set(m, 0, 0, 0.0);
    gsl_matrix_set(m, 0, 1, 1.0);
    gsl_matrix_set(m, 1, 0, -(1.0 + 2.0 * k * y[0] * y[1]));
    gsl_matrix_set(m, 1, 1, k * (1.0 * y[0] * y[0]));
    /* Autonomous. */
    dfdt[0] = 0.0;
    dfdt[1] = 0.0;
    return GSL_SUCCESS;
}

int main(int argc, char **argv) {
    enum Constexpr {n_points = 1000};
    double mu = 1.0;
    gsl_odeiv2_system sys = {ode_func, ode_jac, 2, &mu};
    gsl_odeiv2_driver * d= gsl_odeiv2_driver_alloc_y_new(
        &sys,
        gsl_odeiv2_step_rk8pd,
        1e-6,
        1e-6,
        0.0
    );
    int i;
    double t = 0.0;
    double t1 = 100.0;
    /* Initial condition: f = 0 with speed 0. */
    double y[2] = {1.0, 0.0};
    double dt = t1 / n_points;
    double datax[n_points];
    double datay[n_points];

    for (i = 0; i < n_points; i++) {
        double ti = i * dt;
        int status = gsl_odeiv2_driver_apply(d, &t, ti, y);
        if (status != GSL_SUCCESS) {
            fprintf(stderr, "error, return value=%d\n", status);
            break;
        }

        /* Get output. */
        printf("%.5e %.5e %.5e\n", t, y[0], y[1]);
        datax[i] = y[0];
        datay[i] = y[1];
    }

    /* Cleanup. */
    gsl_odeiv2_driver_free(d);

    /* Plot. */
    if (argc > 1 && argv[1][0] == '1') {
        plsdev("xwin");
        plinit();
        plenv(
            gsl_stats_min(datax, 1, n_points),
            gsl_stats_max(datax, 1, n_points),
            gsl_stats_min(datay, 1, n_points),
            gsl_stats_max(datay, 1, n_points),
            0,
            1
        );
        plstring(n_points, datax, datay, "*");
        plend();
    }

    return EXIT_SUCCESS;
}
