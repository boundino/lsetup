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
cmake --build . -j6
# 2022-06-30: -jX to solve the *.pcm out of date issue: https://root-forum.cern.ch/t/wsl-build-from-source-error-rint-pcm-is-out-of-date-cannot-read-module-signature/47564/9

# Initialization
readlink -f bin/thisroot.sh
source $(readlink -f bin/thisroot.sh)
