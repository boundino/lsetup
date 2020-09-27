#!/bin/bash

# install python 3
brew install python3

# install pipenv
pip3 install --user pipenv
pip3 install --upgrade pipenv

# install modules
pip3 install requests_html
pip3 install requests

# install math modules
pip3 install numpy
pip3 install scipy
pip3 install matplotlib
pip3 install h5py
pip3 install lmfit

# open another shell
# pipenv shell
# pipenv install requests_html
# pipenv install requests

# jupyter notebook
pip3 install jupyterlab
pip3 install notebook

