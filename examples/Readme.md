Circadian rhythm model
----------------------

This SOM file was generated from the LEMS transcription of a SBML
file, using pylems import/export features.

C code was generated via the cvode/cvode.vm template, with the command
```
python som2code.py comp_Locke2008_Circadian_Clock_0.json cvode/cvode.vm 'C' 
```

to run it, just ```make``` (sundials library required); then
```gnuplot circadian.plot``` to plot the resulting timeseries. Notice
that plotting information is not extracted from the SOM file (as
plotting is not done in C), and the gnuplot script is just a q&d
utility for checking all dynamical variable timeseries.