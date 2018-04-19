#!/bin/bash

FOLDER="DmesonRunII"
PAPERINDEX="HIN-16-001"
SUB="papers" # notes, papers, pasS
STYLE="paper" # note, paper, pas
# PAPERINDEX="AN-15-308"
# SUB="notes" # notes, papers, pasS
# STYLE="note" # note, paper, pas

svn co -N svn+ssh://svn.cern.ch/reps/tdr2 $FOLDER
cd $FOLDER
svn update utils
svn update -N ${SUB}
svn update ${SUB}/${PAPERINDEX}
eval `./${SUB}/tdr runtime -sh` # for tcsh. use -sh for bash
cd ${SUB}/${PAPERINDEX}/trunk
tdr --style=${STYLE} b ${PAPERINDEX}