#!/bin/bash

[[ $0 == *.sh ]] && { echo "usage: source build.sh [cmssw ver]" ; exit 1 ; }

[[ $# -ne 1 ]] && return

cmsver=$1

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