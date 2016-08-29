#!/usr/bin/env gnuplot
set key autotitle columnheader
plot 'gravity_collision.data' using 1:($2 == 1 ? $3 : 1/0), \
    '' using 1:($2 == 1 ? $4 : 1/0), \
    '' using 1:($2 == 1 ? $5 : 1/0), \
    '' using 1:($2 == 1 ? $6 : 1/0)
