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
cmsRun /afs/cern.ch/work/g/gkrintir/private/CMSSW_8_0_10/src/flashgg/Taggers/test/MVATHQTraining/test_diphodijet_training/VBFDiPhoDiJetMVA_Training.py maxEvents=1000 useAAA=1 campaign=RunIISpring16DR80X-2_2_0-25ns_ICHEP16_MiniAODv2_Training processIdMap=/afs/cern.ch/work/g/gkrintir/private/CMSSW_8_0_10/src/flashgg/Taggers/test/MVATHQTraining/test_diphodijet_training/config.json dataset=/GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8 outputFile=/afs/cern.ch/work/g/gkrintir/private/CMSSW_8_0_10/src/flashgg/Taggers/test/MVATHQTraining/test_diphodijet_training/output_GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8.root nJobs=1 jobId=0
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

