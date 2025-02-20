#!/usr/bin/gnuplot
set terminal pngcairo size 800,600 enhanced font 'Arial,12'
set output './findExp.png'

set title "Find Experiment" font ",14"
set xlabel "Length" font ",12"
set ylabel "Time" font ",12"

set grid

set key inside top left box

set xrange [0:*]    # Ось X начинается с 0
set yrange [0:*]    # Ось Y начинается с 0

plot "dataSuffixFind.dat" using 1:2 with linespoints title "suffix find()", \
     "dataSuffixFind.dat" using 1:3 with linespoints title "string find()"