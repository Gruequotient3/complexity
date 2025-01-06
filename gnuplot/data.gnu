reset
set terminal qt
set title "Temps en fonction du nombre d'élément" font ",20"
set key bmargin center horizontal
set key font ",15"
set xlabel "Nb Value" font ",11"
set ylabel "time" font ",11"

plot "../data/binaryTreePoints.dat" lw 2.0 with dot,\
"../data/linkedlistPoints.dat" lw 2.0 with dot,\
"../data/vectorPoints.dat" lw 2.0 with dot
