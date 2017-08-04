#!/usr/bin/env bash
# install-update-bash.sh #

# Install brew in case it is not installed #
# https://brew.sh/ #
# /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"

# Update brew #
brew update

# Install bash #
brew install bash

# Add the new shell to the list of allowed shells #
sudo bash -c "echo $(brew --prefix)/bin/bash >> /etc/shells"

# Change to the new shell #
chsh -s $(brew --prefix)/bin/bash 

# Reboot and test #
which bash
echo $SHELL
bash --version
echo $BASH_VERSION
