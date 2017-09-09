#!/usr/bin/env bash
# install-homebrew.sh #

# https://brew.sh/ #

# Install Homebrew in case it is not installed #
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"

# Test #
echo $(brew --prefix)

