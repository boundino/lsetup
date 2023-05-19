#!/usr/bin/env bash
# install-gnu-tools.sh #

# https://www.topbug.net/blog/2013/04/14/install-and-use-gnu-command-line-tools-in-mac-os-x/ #

# Install Homebrew in case it is not installed #
# https://brew.sh/ #
# /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Add in .bashrc #
# export PATH="$(brew --prefix coreutils)/libexec/gnubin:/usr/local/bin:$PATH"
# export MANPATH="$(brew --prefix coreutils)/libexec/gnuman:$MANPATH"

# Install coreutils #
brew install coreutils

# Optional #
brew install binutils
brew install diffutils
brew install ed
brew install findutils
brew install gawk
brew install gnu-indent
brew install gnu-sed
brew install gnu-tar
brew install gnu-which
brew install gnutls
brew install grep
brew install gzip
brew install screen
brew install watch
brew install wdiff
brew install wget
