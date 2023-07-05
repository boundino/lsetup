#!/bin/bash

REPO=${1:-"cms-hin-coordination/analysis"}
FOLDER=${REPO%%/*}

## >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> ##

echo $FOLDER ${REPO##*/}

mkdir -p $FOLDER
cd $FOLDER
git clone --recursive ssh://git@gitlab.cern.ch:7999/$REPO.git
cd ${REPO##*/}

em=$(phonebook --login $USER --terse email) && em=${em%%;}
[[ x$em != x ]] && {
    echo '
[user]
        name = '$USER'
        email = '$em'
' >> .git/config ; } || {
    echo '
[user]
        name = wangj
        email = jing.wang@cern.ch
' >> .git/config ; }
cat .git/config

