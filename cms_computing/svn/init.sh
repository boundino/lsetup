
eval `./notes/tdr runtime -sh`

TYPE=${1:-"note"}
if [[ $TYPE = "note" ]]
then
    SUBFOLDER="notes"
    CADI="AN-15-308"
elif [[ $TYPE = "paper" ]]
then
    SUBFOLDER="papers"
    CADI="HIN-16-001"
elif [[ $TYPE = "pas" ]]
then
    SUBFOLDER="notes"
    CADI="HIN-16-001"
else
    return 1;
fi

cd ${SUBFOLDER}/${CADI}/trunk/