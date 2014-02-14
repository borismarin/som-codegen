#/usr/bin/gnuplot
unset key
pl for [c=2:9] "Locke2008_Circadian_Clock.dat" u 1:c w l
pause -1