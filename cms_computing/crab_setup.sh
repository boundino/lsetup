[[ "$(ls -lt /tmp/ | grep --color=no $USER | grep --color=no -m 1 x509)x" == x ]] && { voms-proxy-init --voms cms --valid 168:00 ; voms-proxy-info --all ; }
source /cvmfs/cms.cern.ch/crab3/crab.sh
which crab
