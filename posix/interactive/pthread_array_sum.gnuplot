#!/usr/bin/env gnuplot
set terminal png size 600, 600
set style data linespoints
set key autotitle columnhead
set output 'pthread_array_sum.png'
set title font ",16"
set title "Array sum time elapsed / N threads"
set xlabel "threads"
set ylabel "time (s)"
plot 'pthread_array_sum.dat' using 1:2 notitle
