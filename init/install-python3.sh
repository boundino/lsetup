#!/bin/bash

# install python 3
brew install python3

# install pipenv
pip3 install --user pipenv
pip3 install --upgrade pipenv

# open another shell
pipenv shell
