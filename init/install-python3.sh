#!/bin/bash

# install python 3
brew install python3

# install pipenv
pip3 install --user pipenv
pip3 install --upgrade pipenv

# install modules
pip3 install requests_html
pip3 install requests

# open another shell
pipenv shell
# pipenv install requests_html
# pipenv install requests
