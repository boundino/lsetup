echo $0
which grid-proxy-info
echo $SCRAM_ARCH
source /cvmfs/cms.cern.ch/crab3/crab.sh
which crab
voms-proxy-init --voms cms --valid 168:00
voms-proxy-info --all
