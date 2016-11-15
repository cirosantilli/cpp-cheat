/* Minimization of take_pictures_docs.c */

#include <stdio.h>
#include <stdlib.h>

#include "common_v4l2.h"

static void save_ppm(
    unsigned int i,
    unsigned int x_res,
    unsigned int y_res,
    size_t data_lenght,
    char *data
) {
    FILE *fout;
    char out_name[256];

    sprintf(out_name, "out%03d.ppm", i);
    fout = fopen(out_name, "w");
    if (!fout) {
        perror("error: fopen");
        exit(EXIT_FAILURE);
    }
    fprintf(fout, "P6\n%d %d 255\n", x_res, y_res);
    fwrite(data, data_lenght, 1, fout);
    fclose(fout);
}

int main(void) {
    CommonV4l2 common_v4l2;
    char *dev_name = "/dev/video0";
    struct buffer *buffers;
    unsigned int
        i,
        x_res = 640,
        y_res = 480
    ;

    CommonV4l2_init(&common_v4l2, dev_name, x_res, y_res);
    for (i = 0; i < 20; i++) {
        CommonV4l2_updateImage(&common_v4l2);
        save_ppm(
            i,
            x_res,
            y_res,
            CommonV4l2_getImageSize(&common_v4l2),
            CommonV4l2_getImage(&common_v4l2)
        );
    }
    CommonV4l2_deinit(&common_v4l2);
    return EXIT_SUCCESS;
}
