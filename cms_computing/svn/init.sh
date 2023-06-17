#!/bin/bash

[[ $0 != *bash* ]] && { echo use . init.sh or source init.sh; return 1; }

AN="AN-15-308"
CADI="HIN-16-001"

# >>>>>>>>>>>>>>> #
SUBFOLDER=""
DOCNO=""

TYPE=${1:-"note"}
[[ $TYPE == "note" ]] && { SUBFOLDER="notes"; DOCNO=$AN; }
[[ $TYPE == "paper" ]] && { SUBFOLDER="papers"; DOCNO=$CADI; }
[[ $TYPE == "pas" ]] && { SUBFOLDER="notes"; DOCNO=$CADI; }

[[ "x$DOCNO" == "x" || "x$SUBFOLDER" == "x" ]] && { echo invalid TYPE of document [note/paper/pas]; return 1; }

[[ ! -d ./${SUBFOLDER} ]] && { echo no ./${SUBFOLDER} is found.; return 1; }

eval `./${SUBFOLDER}/tdr runtime -sh`
cd ${SUBFOLDER}/${DOCNO}/trunk/