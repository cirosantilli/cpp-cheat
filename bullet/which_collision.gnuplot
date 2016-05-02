#!/usr/bin/env gnuplot
set key autotitle columnheader
plot 'which_collision.tmp' \
       using 1:($2 == 1 ? $4 : 1/0), \
    '' using 1:($2 == 1 ? $6 : 1/0), \
    '' using 1:($2 == 2 ? $4 : 1/0), \
    '' using 1:($2 == 2 ? $6 : 1/0)
