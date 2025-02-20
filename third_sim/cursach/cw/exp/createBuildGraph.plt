#!/usr/bin/gnuplot
set datafile separator " "
set title "Dependency of Time on Length" font ",14"
set xlabel "Length" font ",12"
set ylabel "Time (microseconds)" font ",12"
set grid

set term png size 800,600
set output "buildExp.png"
plot "dataSuffixBuild.dat" using 1:2 with linespoints title "Time vs Length" lt rgb "blue" pt 7 lw 2