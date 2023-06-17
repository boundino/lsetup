#!/bin/bash

FOLDER=${1:-"dNdeta2022"}

PAPERINDEX=${2:-"HIN-23-007"}
SUB="papers"  #  notes,  papers,  notes
STYLE="paper" #  an,     paper,   pas

## >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> ##

mkdir -p $FOLDER
cd $FOLDER
git clone --recursive ssh://git@gitlab.cern.ch:7999/tdr/$SUB/$PAPERINDEX.git
cd $PAPERINDEX
eval `utils/tdr runtime -sh` # for tcsh. use -sh for bash
tdr --style=$STYLE --temp_dir=$PWD/tmp b 

##

echo -e '\e[32m
# README.md
git clone --recursive ssh://git@gitlab.cern.ch:7999/tdr/'$SUB/$PAPERINDEX'.git
cd '$PAPERINDEX'
eval `utils/tdr runtime -sh` # for tcsh. use -sh for bash
tdr --style='$STYLE' --temp_dir=$PWD/tmp b
\e[0m'
