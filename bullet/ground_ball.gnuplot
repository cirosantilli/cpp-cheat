#!/usr/bin/env gnuplot
set key autotitle columnheader
plot 'ground_ball.tmp' using 1:($2 == 1 ? $4 : 1/0), \
    '' using 1:($2 == 1 ? $6 : 1/0)
