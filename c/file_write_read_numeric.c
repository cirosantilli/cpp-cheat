/* Helpers to write numbers to files. TODO also implement read and check results. */

#include "common.h"

/* Write an array of ints to a human readable text file.
 *
 * ints are newline separated.
 *
 * Return -1 on failure, 0 on success.
 */
int write_int_array_to_file(
    char *path,
    int *arr,
    size_t len
) {
    size_t i;
    FILE *fp;

    fp = fopen(path, "w");
    if (fp == NULL) {
        return -1;
    }
    for (i = 0; i < len; i++){
        if (fprintf(fp, "%d\n", arr[i]) < 0) {
            return -1;
        }
    }
    if (EOF == fclose(fp)) {
        return -1;
    }
    return 0;
}

/* Same as write_int_array_to_file but for floats.
 *
 * Floats are saved in exp notation
 * with precision (decimal places) precision.
 */
int write_float_array_to_file(
    char *path,
    float *arr,
    size_t len,
    int precision
) {
    size_t i;
    FILE *fp;

    fp = fopen(path, "w");
    if (fp == NULL){
        return -1;
    }
    for (i = 0; i < len; i++) {
        if (fprintf(fp,"%.*e\n", precision, arr[i]) < 0) {
            return -1;
        }
    }
    if (EOF == fclose(fp)) {
        return -1;
    }
    return 0;
}

int main(void) {
    /* ints */
    {
        int array[] = {
            0,
            1,
            -1,
            12873453
        };
        write_int_array_to_file(
            COMMON_TMPFILE_NAMED("int"),
            array,
            COMMON_ARRAY_SIZE(array)
        );
    }

    /* floats */
    {
        float array[] = {
            1.1f,
            1.001f,
            -1.1f,
            1.23456e2
        };
        write_float_array_to_file(
            COMMON_TMPFILE_NAMED("float"),
            array,
            COMMON_ARRAY_SIZE(array),
            2
        );
    }

    return EXIT_SUCCESS;
}
