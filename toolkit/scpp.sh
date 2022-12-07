#!/bin/bash

figdir=/afs/cern.ch/work/w/wangj/RECO2022/CMSSW_12_5_2/src/tracklet/analysis

dir=${1:-"figs/"}

dir=${dir%%"/"} # remove possible last slash
lastdir=${dir##*/} # last directory
subdir="./"${dir%%$lastdir} 

set -x
scp -r wangj@lxplus.cern.ch:$figdir/$dir $subdir
set +x
