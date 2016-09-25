#ifndef COMMON_TEXTURE_H
#define COMMON_TEXTURE_H

#include <stdlib.h>

/**
 * Return checkered array with colors like:
 *
 *     black | green
 *     -------------
 *     blue  | red
 */
unsigned char * common_texture_get_image(unsigned int width, unsigned int height) {
    unsigned char *cur, *image;
    size_t i, j;
    image = malloc(3 * width * height);
    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            cur = &image[3 * (i * width + j)];
            cur[0] = 0;
            cur[1] = 0;
            cur[2] = 0;
            if (i < width / 2) {
                if (j < height / 2) {
                } else {
                    cur[0] = 255;
                }
            } else {
                if (j < height / 2) {
                    cur[1] = 255;
                } else {
                    cur[2] = 255;
                }
            }
        }
    }
    return image;
}

#endif
