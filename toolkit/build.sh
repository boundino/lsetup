#!/bin/bash

[[ $0 == *.sh ]] && { echo "usage: source build.sh ([cmssw ver])" ; exit 1 ; }

# CMSSW_12_5_4 CMSSW_11_2_1_patch2 CMSSW_10_3_3_patch1 CMSSW_9_4_13_patch1 CMSSW_8_0_24

folder=root
cmsver=
if [[ $# -eq 1 ]]
then
    cmsver=$1
    echo
    echo -e "Processing \e[36;4;1m$cmsver\e[0m >>>"
    cmsrel ${cmsver} || return
    cd ${cmsver}/src/
    cmsenv
    cd ../../
    folder=$cmsver
fi

mkdir -p exec/$folder
for i in `echo *.cc *.C` ; do 
    extension="."${i##*.}
    e=${i%%$extension}
    echo -e "building $i ... \e[33m=> $e\e[0m"
    g++ $i $(root-config --libs --cflags) -g -o exec/${folder}/$e
done

[[ x$cmsver == x ]] || rm -rf $cmsver

