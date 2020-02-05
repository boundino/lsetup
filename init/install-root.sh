#!/bin/bash

# https://root.cern.ch/get-root-sources
# https://root.cern.ch/building-root

# Install cmake if not yet done
brew install cmake

# Get root source macros
git clone http://github.com/root-project/root.git

# Build root
mkdir buildroot
cd buildroot
cmake ../root
cmake --build .

# Initialization
readlink dir/bin/thisroot.sh
source $(readlink dir/bin/thisroot.sh)
