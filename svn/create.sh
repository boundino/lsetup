#!/bin/bash

FOLDER="Djets"

PAPERINDEX="HIN-18-007"
SUB="papers" # notes, papers
STYLE="paper" # an, paper, pas

# PAPERINDEX="AN-17-097"
# SUB="notes" # notes, papers
# STYLE="an" # an, paper, pas

# PAPERINDEX="HIN-18-007"
# SUB="notes" # notes, papers
# STYLE="pas" # an, paper, pas

[[ ! -d $FOLDER ]] && { mkdir $FOLDER ; svn co -N svn+ssh://svn.cern.ch/reps/tdr2 $FOLDER ; }
cd $FOLDER
svn update utils
[[ ! -d $SUB ]] && { svn update -N ${SUB} ; }
svn update ${SUB}/${PAPERINDEX}
eval `./${SUB}/tdr runtime -sh` # for tcsh. use -sh for bash
cd ${SUB}/${PAPERINDEX}/trunk
tdr --style=${STYLE} b ${PAPERINDEX}