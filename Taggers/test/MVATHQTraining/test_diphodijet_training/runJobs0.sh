#!/bin/bash
export XRD_NETWORKSTACK=IPv4
WD=$PWD
echo
echo
echo
cd /afs/cern.ch/work/g/gkrintir/private/CMSSW_8_0_10
eval $(scram runtime -sh)
cd $WD
mkdir /afs/cern.ch/work/g/gkrintir/private/CMSSW_8_0_10/src/flashgg/Taggers/test/MVATHQTraining/test_diphodijet_training
export EOS_MGM_URL=root://eosuser.cern.ch
echo "ls $X509_USER_PROXY"
ls $X509_USER_PROXY
cmsRun /afs/cern.ch/work/g/gkrintir/private/CMSSW_8_0_10/src/flashgg/Taggers/test/MVATHQTraining/test_diphodijet_training/VBFDiPhoDiJetMVA_Training.py maxEvents=1000 useAAA=1 campaign=RunIISpring16DR80X-2_2_0-25ns_ICHEP16_MiniAODv2_Training processIdMap=/afs/cern.ch/work/g/gkrintir/private/CMSSW_8_0_10/src/flashgg/Taggers/test/MVATHQTraining/test_diphodijet_training/config.json dataset=/VBFHToGG_M125_13TeV_amcatnlo_pythia8/sethzenz-RunIISpring16DR80X-2_1_2-25ns_ICHEP16-2_1_2-v0-RunIISpring16MiniAODv1-PUSpring16RAWAODSIM_80X_mcRun2_asymptotic_2016_v3_ext1-v1-eb6bbc3cad299015f6746e16daa092ae/USER outputFile=/afs/cern.ch/work/g/gkrintir/private/CMSSW_8_0_10/src/flashgg/Taggers/test/MVATHQTraining/test_diphodijet_training/output_VBFHToGG_M125_13TeV_amcatnlo_pythia8_sethzenz-RunIISpring16DR80X-2_1_2-25ns_ICHEP16-2_1_2-v0-RunIISpring16MiniAODv1-PUSpring16RAWAODSIM_80X_mcRun2_asymptotic_2016_v3_ext1-v1-eb6bbc3cad299015f6746e16daa092ae_USER.root nJobs=1 jobId=0
retval=$?
if [[ $retval == 0 ]]; then
    errors=""
    for file in $(find -name '*.root' -or -name '*.xml'); do
        cp -pv $file /afs/cern.ch/work/g/gkrintir/private/CMSSW_8_0_10/src/flashgg/Taggers/test/MVATHQTraining/test_diphodijet_training
        if [[ $? != 0 ]]; then
            errors="$errors $file($?)"
        fi
    done
    if [[ -n "$errors" ]]; then
       echo "Errors while staging files"
       echo "$errors"
       exit -2
    fi
fi

exit $retval

