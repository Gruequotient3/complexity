reset
set terminal qt

set key bmargin center horizontal

set xlabel "Nb Value" font ",11"
set ylabel "time" font ",11"
plot "data/fixpercentPoints.dat" using 1:2 lw 2.0 with dot, \
"data/fixpercentPoints.dat" using 1:3 lw 2.0 with dot
