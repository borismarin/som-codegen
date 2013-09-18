#/usr/bin/gnuplot
unset key
pl for [c=2:9] "<./circadian" u 1:c w l
pause -1