/*
How to use blas and lapack with the standard
interfaces provided by their respective projects, repectively through
`cblas.h` and `lapacke.h`
*/

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <cblas.h>
#include <lapacke.h>

/**
 * assert two integers are equal
 * if not, print them to stderr and assert false
 */
void assert_eqi(int i1, int i2) {
    if (i1 != i2) {
        fprintf(stderr, "%d\n%d\n\n\n", i1, i2);
        assert(false);
    }
}

/**
 * assert two doubles are equal within err precision
 * if not, print them to stderr
 */
void assert_eqd(double d1, double d2, double err) {
    if (fabs(d1 - d2) > err) {
        fprintf(stderr, "%f\n%f\n\n\n", d1, d2);
        assert(false);
    }
}

/** print an array of doubles to stderr */
void print_vecd(int n, double * v) {
    int i;
    for (i=0; i<n; i++) {
        fprintf(stderr, "%.2f ", v[i]);
    }
    printf("\n");
}

/*
bool eq_vecd2(int n, double * v1, double * v2, double err)
{
    if(fabs(d1 - d2) > err)
        return false
    return true;
}

void assert_eqvd(int n, double * v1, double * v2, double err){
    if(eq_vecd(n, v1, v2, err) != true){
        print_vecd(n, v1);
        print_vecd(n, v2);
    }
}
*/

int main(void) {
    int info, ipiv2[2];
    float err = 1e-6;
    float x2[2], b2[2], c2[2];
    float a2x2[2][2];

	/* cblas */
	{
        x2[0] =  1.0;
        x2[1] = -2.0;
        assert_eqd(cblas_snrm2(2, x2, 1), sqrt(5.0), err);
    }

	/* lapacke */
	{
		/*
		sgesv

		Matrix vector multiply.
		*/
		{
			a2x2[0][0] = 1.0;
			a2x2[1][0] = 2.0;
			a2x2[0][1] = 3.0;
			a2x2[1][1] = 4.0;
			b2[0] = 5.;
			b2[1] = 11.;

			info = LAPACKE_sgesv(
				LAPACK_COL_MAJOR,
				2,
				1,
				&a2x2[0][0],
				2,
				&ipiv2[0],
				&b2[0],
				2
			);
			c2[0] = 1.0;
			c2[1] = 2.0;
			assert_eqi(info, 0);
			assert_eqd(b2[0], c2[0], err);
			assert_eqd(b2[1], c2[1], err);
		}
    }

    return EXIT_SUCCESS;
}
