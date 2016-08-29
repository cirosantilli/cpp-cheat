#!/usr/bin/env gnuplot
set key autotitle columnheader
plot 'gravity.data' using 1:3, \
     '' using 1:4, \
     '' using 1:5
