/*
Increase the chance that the compiler will use SIMD instructions.

Basically a more abstract and ISA portable (TODO?) version of intrinsics.

Note however that the GCC and other compiles have an auto-vectorization
optimization, which might use SIMD even if you don't use the vector extensions.

TODO: is explicit alignment attribute necessary, or automatically done?
*/

#include "common.h"

typedef int int4 __attribute__ ((vector_size(4 * sizeof(int))));

/*
TODO: SIMD to scalar operations don't appear possible without intrinsics:
http://stackoverflow.com/questions/31597302/gcc-c-vector-extension-how-to-check-if-result-of-any-element-wise-comparison-is
*/
int int4_eq(int4 i, int4 j) {
	return
		i[0] == j[0] &&
		i[1] == j[1] &&
		i[2] == j[2] &&
		i[3] == j[3]
	;
}

int main(void) {
	/* Hello world. */
	{
		int4 i = {1, 2, 3, 4};
		int4 j = {5, 6, 7, 8};
		int4 k = i + j;
		assert(int4_eq(k, (int4){6, 8, 10, 12}));
	}

	/* From / to array. TODO any better way than going over all indices?
	 * Intrinsic way: _mm_load_pd family.
	 * */
	{
		int is[] = {1, 2, 3, 4};
		int js[] = {5, 6, 7, 8};
		int ks[4];
		int ks2[] = {6, 8, 10, 12};
		int4 i;
		int4 j;
		int4 k;
		i[0] = is[0];
		i[1] = is[1];
		i[2] = is[2];
		i[3] = is[3];
		j[0] = js[0];
		j[1] = js[1];
		j[2] = js[2];
		j[3] = js[3];
		k = i + j;
		ks[0] = k[0];
		ks[1] = k[1];
		ks[2] = k[2];
		ks[3] = k[3];
		assert(memcmp(ks, ks2, sizeof(ks)) == 0);
	}

    return EXIT_SUCCESS;
}
