#!/usr/bin/env gnuplot
set terminal png size 1024, 1024
set style data linespoints
set output 'pthread_work.png'
set multiplot layout 2,1
set xlabel "cores"
set ylabel "time (s)"

set title "wall, user and sys"
set yrange [-20:]
set key right center
plot 'pthread_work.dat' using 2 title 'wall', \
     'pthread_work.dat' using 3 title 'user', \
     'pthread_work.dat' using 4 title 'sys'

set title 'user / wall ratio'
set yrange [0:*]
plot 'pthread_work.dat' using 1:($3/$2) notitle
