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
brew install ed --with-default-names
brew install findutils --with-default-names
brew install gawk
brew install gnu-indent --with-default-names
brew install gnu-sed --with-default-names
brew install gnu-tar --with-default-names
brew install gnu-which --with-default-names
brew install gnutls
brew install grep --with-default-names
brew install gzip
brew install screen
brew install watch
brew install wdiff --with-gettext
brew install wget
