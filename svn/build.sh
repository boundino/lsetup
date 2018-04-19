#!/bin/bash

SUBFOLDER="notes"
DOCNO="AN-17-097"
TYPE="an" # an, pas, paper

cd ../../../
eval `./${SUBFOLDER}/tdr runtime -sh`
cd ${SUBFOLDER}/${DOCNO}/trunk
tdr --style=${TYPE} b ${DOCNO}