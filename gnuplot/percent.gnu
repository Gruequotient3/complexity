reset
set terminal qt

set key bmargin center horizontal
set key font ",15"

set xlabel "percentage" font ",11"
set ylabel "time" font ",11"
plot "../data/percentavlPoints.dat" using 1:2 lw 2.0 with dot,\
"../data/percentavlPoints.dat" using 1:3 lw 2.0 with lines
