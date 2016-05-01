#!/usr/bin/env gnuplot
set key autotitle columnheader
plot 'ground_ball.tmp' using 1:($2 == 1 ? $4 : 1/0)
