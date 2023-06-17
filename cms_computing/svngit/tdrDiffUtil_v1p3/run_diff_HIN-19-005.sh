#!/bin/bash

CPATH=/afs/cern.ch/user/w/wangj/myDir/X3872/HIN-19-005

#######################
#     --> OLD <--     #
#######################
VER=5353ac0af4de6a75fcaacd4697191370ef236dec ; TAG=submission ;
# VER=bb0f0ea7a7e0b5182dbba152ccfbaed1aeb0d88c ; TAG=v29 ;

## --- ##
OLDVER=$VER ; OLDTAG=$TAG

#######################
#     --> NEW <--     #
#######################
VER=b51d1c82a224b96e13ed01e079a47e9ba1e0981a ; TAG=v30 ;

## --- ##
NEWVER=$VER ; NEWTAG=$TAG

#############################
#   --> Do not change <--   #
#############################

OUTPUT="${OLDTAG}_${NEWTAG}"

REGULAR=${1:-1}
MANUALFIX=${2:-0}

CADI=${CPATH##*/}

[[ -f ${CADI}_temp.pdf ]] && { rm ${CADI}_temp.pdf ; }
[[ $REGULAR -eq 1 ]] && {
    ./gtdr_diff $CPATH/ $OLDVER $NEWVER ; } || {
    [[ $MANUALFIX -eq 1 ]] && {
        ./gtdr_diff_manualfix $CPATH/ ; } ; }

mv output/${CADI}_temp.pdf output/${CADI}_diff_${OUTPUT}.pdf
echo $(readlink -f output/${CADI}_diff_${OUTPUT}.pdf)
