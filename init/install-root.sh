#!/bin/bash

# https://root.cern.ch/get-root-sources
# https://root.cern.ch/building-root

git clone http://github.com/root-project/root.git
mkdir buildroot
cd buildroot
cmake ../root
cmake --build .
readlink dir/bin/thisroot.sh
# source /path/to/build/dir/bin/thisroot.sh
