#!/bin/bash

## lxplus ##

PAPERINDEX="HIN-23-007"
STYLE="paper" #  an,     paper,   pas
FOLDER="$PWD"
DRYRUN=0

GETNECESSARY=2
while getopts "i:s:d:x" opt; do
    case $opt in
        i)
            PAPERINDEX=$OPTARG
            [[ x$OPTARG != x ]] && GETNECESSARY=$((GETNECESSARY-1))
            ;;
        s)
            STYLE=$OPTARG
            [[ x$OPTARG != x ]] && GETNECESSARY=$((GETNECESSARY-1))
            ;;
        d)
            FOLDER=$OPTARG
            ;;
        x)
            DRYRUN=1
            ;;
        \?)
            echo "./create.sh -i [HIN-XX-YYY] -s [an/paper/pas] (-d [subdir]) (-x)"
            exit 1
            ;;
    esac
done

[[ $GETNECESSARY -ne 0 ]] && DRYRUN=1

## >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> ##

declare -A SUBF
SUBF[an]=notes
SUBF[paper]=papers
SUBF[pas]=notes

SUB=${SUBF[$STYLE]}  #  notes,  papers,  notes

[[ $DRYRUN -eq 0 ]] && {

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

} || {
    echo "./create.sh -i [HIN-XX-YYY] -s [an/paper/pas] (-d [subdir]) (-x)"
}

##

echo -e '\e[32;2m
# README.md
git clone --recursive ssh://git@gitlab.cern.ch:7999/tdr/\e[0m\e[32;4m'$SUB'\e[0m\e[32;2m'/'\e[0m\e[32;4m'$PAPERINDEX'\e[0m\e[32;2m.git
cd \e[0m\e[32;4m'$PAPERINDEX'\e[0m\e[32;2m
eval `utils/tdr runtime -sh` # for tcsh. use -sh for bash
tdr --style=\e[0m\e[32;4m'$STYLE'\e[0m\e[32;2m --temp_dir=$PWD/tmp b
\e[0m'

