#!/bin/bash

[[ $0 == *.sh ]] && { echo "usage: source build.sh [cmssw ver]" ; exit 1 ; }

# CMSSW_10_3_3_patch1 CMSSW_9_4_13_patch1 CMSSW_8_0_24

[[ $# -ne 1 ]] && return
cmsver=$1

echo
echo -e "Processing \e[36;4;1m$cmsver\e[0m >>>"
cmsrel ${cmsver} || return
cd ${cmsver}/src/
cmsenv
cd ../../

mkdir -p exec/${cmsver}
for i in `echo *.C` ; do 
    echo "building $i ..."
    g++ $i $(root-config --libs --cflags) -g -o exec/${cmsver}/${i%%.C}
done

rm -rf $cmsver