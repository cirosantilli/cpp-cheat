#!/usr/bin/env gnuplot
set terminal png size 1024, 1024
set output "ode.png"
set multiplot layout 3,1 title "ODE solution"

set title "Solution: t x g(t) "
set xlabel "t"
set ylabel "g(t)"
plot "ode.dat" using 1:2 notitle

set title "Derivative plot: t x g'(t)"
set xlabel "t"
set ylabel "g'(t)"
plot "ode.dat" using 1:3 notitle

set title "Phase space: g(t) x g(t)"
set xlabel "g'(t)"
set ylabel "g(t)"
plot "ode.dat" using 2:3 notitle
