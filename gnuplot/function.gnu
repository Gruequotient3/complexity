reset
set terminal qt
set key bmargin center horizontal
set key font ",15"
plot [0:128] [0:128] x, x/8, log(x)/log(2) - 1

