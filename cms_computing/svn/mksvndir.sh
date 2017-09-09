FOLDER="BsubsRAA"
PAPERINDEX="AN-17-210"

#
svn co -N svn+ssh://svn.cern.ch/reps/tdr2 $FOLDER
cd $FOLDER
svn update utils
svn update -N notes
svn update notes/${PAPERINDEX}
eval `./notes/tdr runtime -sh`
cd notes/${PAPERINDEX}/trunk
tdr --style=an b ${PAPERINDEX}