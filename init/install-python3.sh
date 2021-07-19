#!/bin/bash

# install python 3
brew install python3

# install pipenv
python3 -m pip install --user pipenv
python3 -m pip install --upgrade pipenv

# install modules
python3 -m pip install requests_html
python3 -m pip install requests

# install math modules
python3 -m pip install numpy
python3 -m pip install scipy
python3 -m pip install matplotlib
python3 -m pip install h5py
python3 -m pip install lmfit

# open another shell
# pipenv shell
# pipenv install requests_html
# pipenv install requests

# jupyter notebook
python3 -m pip install jupyterlab
python3 -m pip install notebook

