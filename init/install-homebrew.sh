#!/usr/bin/env bash
# install-homebrew.sh #

# https://brew.sh/ #

# Install Homebrew in case it is not installed #
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Test #
echo $(brew --prefix)

