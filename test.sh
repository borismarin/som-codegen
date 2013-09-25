#!/bin/bash

set -e


generateFiles()
{
    generateFile $1 'matlab/matlab_ode.vm' 'matlab' 'examples/'$2'.m'
    generateFile $1 'xpp/xpp.vm'           'xpp'    'examples/'$2'.ode'
    generateFile $1 'cvode/cvode.vm'       'C'      'examples/'$2'.c'
}

generateFile()
{
    echo "Converting $1 using template $2 (format $3) and saving to file $4"
    python som2code.py $1 $2 $3 > $4
}

generateFiles 'izhikevich.json'  'izhikevich'
generateFiles 'comp_Locke2008_Circadian_Clock_0.json'  'circadian'
generateFiles 'LEMS_NML2_Ex9_FN.json' 'fn'
generateFiles 'LEMS_NML2_Ex0_IaF.json' 'iaf'
generateFiles 'LEMS_NML2_Ex2_Izh.json' 'izh_lems'






