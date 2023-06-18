#!/bin/bash

## lxplus ##

FOLDER=${1:-"dNdeta2022"}

PAPERINDEX=${2:-"HIN-23-007"}
STYLE=${3:-"paper"} #  an,     paper,   pas

## >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> ##

declare -A SUBF
SUBF[an]=notes
SUBF[paper]=papers
SUBF[pas]=notes

SUB=${SUBF[$STYLE]}  #  notes,  papers,  notes

mkdir -p $FOLDER
cd $FOLDER
git clone --recursive ssh://git@gitlab.cern.ch:7999/tdr/$SUB/$PAPERINDEX.git
cd $PAPERINDEX
eval `utils/tdr runtime -sh` # for tcsh. use -sh for bash
tdr --style=$STYLE --temp_dir=$PWD/tmp b 

##

em=$(phonebook --login $USER --terse email) && em=${em%%;}
[[ x$em != x ]] && {
    echo '
[user]
        name = '$USER'
        email = '$em'
' >> .git/config ; }
cat .git/config

echo 'tdr --style='$STYLE' --temp_dir=$PWD/tmp b' > build.sh
chmod 744 build.sh 

##

echo -e '\e[32m
# README.md
git clone --recursive ssh://git@gitlab.cern.ch:7999/tdr/'$SUB/$PAPERINDEX'.git
cd '$PAPERINDEX'
eval `utils/tdr runtime -sh` # for tcsh. use -sh for bash
tdr --style='$STYLE' --temp_dir=$PWD/tmp b
\e[0m'

