#!/usr/bin/env cmsRun

import FWCore.ParameterSet.Config as cms
import FWCore.Utilities.FileUtils as FileUtils
from FWCore.ParameterSet.VarParsing import VarParsing
from flashgg.MetaData.samples_utils import SamplesManager

process = cms.Process("VBFTagsDumper")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1))
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32( 1 )
process.source = cms.Source ("PoolSource",
                             fileNames = cms.untracked.vstring(
        #"root://cmsxrootd.fnal.gov//store/user/gkrintir/flashgg/RunIISpring15-ReMiniAOD-BetaV7-25ns/Spring15BetaV7/THQ_HToGG_13TeV-madgraph-pythia8_TuneCUETP8M1/RunIISpring15-ReMiniAOD-BetaV7-25ns-Spring15BetaV7-v0-RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/151203_202839/0000/myMicroAODOutputFile_1.root"
        #"/store/group/phys_higgs/cmshgg/sethzenz/flashgg/RunIISpring15-FinalPrompt-BetaV7-25ns/Spring15BetaV7/DoubleEG/RunIISpring15-FinalPrompt-BetaV7-25ns-Spring15BetaV7-v0-Run2015D-PromptReco-v4/151124_234634/0000/myMicroAODOutputFile_2.root"
        "/store/group/phys_higgs/cmshgg/sethzenz/flashgg/RunIISpring15-ReMiniAOD-BetaV7-25ns/Spring15BetaV7/ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring15-ReMiniAOD-BetaV7-25ns-Spring15BetaV7-v0-RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/151021_153138/0000/myMicroAODOutputFile_2.root"
        #"/store/group/phys_higgs/cmshgg/sethzenz/flashgg/RunIISpring15-ReMiniAOD-BetaV7-25ns/Spring15BetaV7/ttHJetToGG_M120_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring15-ReMiniAOD-BetaV7-25ns-Spring15BetaV7-v0-RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/151021_153102/0000/myMicroAODOutputFile_1.root"
        ))

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("VBFTagsDump.root"),
                                   closeFileFast = cms.untracked.bool(True))


from flashgg.Taggers.flashggTagOutputCommands_cff import tagDefaultOutputCommand
#import flashgg.Taggers.dumperConfigTools as cfgTools
#from  flashgg.Taggers.tagsDumpers_cfi import createTagDumper

process.load("flashgg.Taggers.flashggTagSequence_cfi")
process.load("flashgg.Taggers.flashggTagTester_cfi")

# Use JetID
process.flashggVBFMVA.UseJetID      = cms.bool(True)
process.flashggVBFMVA.JetIDLevel    = cms.string("Loose")

# use custum TMVA weights
process.flashggVBFMVA.vbfMVAweightfile = cms.FileInPath("flashgg/Taggers/data/Flashgg_VBF_CHS_STD_BDTG.weights.xml")
process.flashggVBFMVA.MVAMethod        = cms.string("BDTG")

# QCD Recovery 
# process.flashggVBFMVA.merge3rdJet   = cms.untracked.bool(False)
# process.flashggVBFMVA.thirdJetDRCut = cms.untracked.double(1.5)

# combined MVA boundary set
process.flashggVBFTag.Boundaries    = cms.vdouble(-2,0,2)


# use the trigger-diphoton-preselection
from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag
massSearchReplaceAnyInputTag(process.flashggTagSequence,cms.InputTag("flashggDiPhotons"),cms.InputTag("flashggPreselectedDiPhotons"))

'''
# set the VBF dumper
process.vbfTagDumper = createTagDumper("VBFTag")
process.vbfTagDumper.dumpTrees     = True
process.vbfTagDumper.dumpHistos    = True
process.vbfTagDumper.dumpWorkspace = False

# get the variable list
import flashgg.Taggers.VBFTagVariables as var
all_variables = var.dijet_variables + var.dipho_variables + var.truth_variables

cfgTools.addCategories(process.vbfTagDumper,
                       [
                           ("VBFDiJet","leadingJet.pt>0",0),
                           ("excluded","1",0)
                       ],
                       variables  = all_variables,
                       histograms = []
)

#process.vbfTagDumper.nameTemplate ="$PROCESS_$SQRTS_$LABEL_$SUBCAT_$CLASSNAME"
process.vbfTagDumper.nameTemplate = "$PROCESS_$SQRTS_$CLASSNAME_$SUBCAT_$LABEL"
'''

## TAGS DUMPERS ##
from flashgg.Taggers.tagsDumpers_cfi import *

process.untaggedDumper = createTagDumper("Untagged")
process.vbfTagDumper = createTagDumper("VBFTag")
process.thqLeptonicTagDumper = createTagDumper("THQLeptonicTag")
process.tthLeptonicTagDumper = createTagDumper("TTHLeptonicTag")
process.tthHadronicTagDumper = createTagDumper("TTHHadronicTag")
process.vhLooseTagDumper = createTagDumper("VHLooseTag")
process.vhTightTagDumper = createTagDumper("VHTightTag")
process.vhHadronicTagDumper = createTagDumper("VHHadronicTag")

process.untaggedDumper.dumpTrees = True
process.vbfTagDumper.dumpTrees = True
process.thqLeptonicTagDumper.dumpTrees = True
# split tree, histogram and datasets by process
process.thqLeptonicTagDumper.nameTemplate ="$PROCESS_$SQRTS_$LABEL_$SUBCAT"
process.tthLeptonicTagDumper.dumpTrees = True
process.tthHadronicTagDumper.dumpTrees = True
process.vhLooseTagDumper.dumpTrees = True
process.vhTightTagDumper.dumpTrees = True
process.vhHadronicTagDumper.dumpTrees = True


## define categories and associated objects to dump
import flashgg.Taggers.dumperConfigTools as cfgTools


dipho_variables=["dipho_sumpt      := diPhoton.sumPt",
                 "dipho_cosphi     := abs(cos(diPhoton.leadingPhoton.phi - diPhoton.subLeadingPhoton.phi))",
                 "mass             := diPhoton.mass",
                 "leadPt           := diPhoton.leadingPhoton.pt",
                 "leadEt           := diPhoton.leadingPhoton.et",
                 "leadEta          := diPhoton.leadingPhoton.eta",
                 "leadPhi          := diPhoton.leadingPhoton.phi",
                 "lead_sieie       := diPhoton.leadingPhoton.sigmaIetaIeta",
                 "lead_hoe         := diPhoton.leadingPhoton.hadronicOverEm",
                 "lead_sigmaEoE    := diPhoton.leadingPhoton.sigEOverE",
                 "lead_ptoM        := diPhoton.leadingPhoton.pt/diPhoton.mass",
                 "leadR9           := diPhoton.leadingPhoton.r9",
                 "subleadPt        := diPhoton.subLeadingPhoton.pt",
                 "subleadEt        := diPhoton.subLeadingPhoton.et",
                 "subleadEta       := diPhoton.subLeadingPhoton.eta",
                 "subleadPhi       := diPhoton.subLeadingPhoton.phi",
                 "sublead_sieie    := diPhoton.subLeadingPhoton.sigmaIetaIeta",
                 "sublead_hoe      := diPhoton.subLeadingPhoton.hadronicOverEm",
                 "sublead_sigmaEoE := diPhoton.subLeadingPhoton.sigEOverE",
                 "sublead_ptoM     := diPhoton.subLeadingPhoton.pt/diPhoton.mass",
                 "subleadR9        := diPhoton.subLeadingPhoton.r9",
                 "leadIDMVA        := diPhoton.leadingView.phoIdMvaWrtChosenVtx",
                 "subleadIDMVA     := diPhoton.subLeadingView.phoIdMvaWrtChosenVtx",]

## Untagged ##
cfgTools.addCategories(process.untaggedDumper,
                       ## categories definition
                       [("all","1",0)
                    ],                       
                       ## variables to be dumped in trees/datasets. Same variables for all categories
                       variables=dipho_variables,
                       

                       ## histograms
                       histograms=[]
)
                       

## VBF ##
cfgTools.addCategories(process.vbfTagDumper,
                       ## categories definition
                       [("all","1",0)
                    ],                       
                       ## variables to be dumped in trees/datasets. Same variables for all categories
                       variables=dipho_variables+                       
                       ["dRphoLeadJ    := min(deltaR(leadingJet.eta, leadingJet.phi, diPhoton.leadingPhoton.eta, diPhoton.leadingPhoton.phi), deltaR(leadingJet.eta, leadingJet.phi, diPhoton.subLeadingPhoton.eta, diPhoton.subLeadingPhoton.phi))",
                        "dRphoSubleadJ := min(deltaR(subLeadingJet.eta, subLeadingJet.phi, diPhoton.leadingPhoton.eta, diPhoton.leadingPhoton.phi), deltaR(subLeadingJet.eta, subLeadingJet.phi, diPhoton.subLeadingPhoton.eta, diPhoton.subLeadingPhoton.phi))",
                        "leadJPt       := leadingJet.pt",
                        "leadJEta      := leadingJet.eta",
                        "leadJAbsEta   := abs(leadingJet.eta)",
                        "partleadJet   := tagTruth().closestParticleToLeadingJet().pdgId",
                        "subleadJPt    := subLeadingJet.pt",
                        "subleadJEta   := leadingJet.eta",
                        "subleadJAbsEta:= abs(leadingJet.eta)",
                        "Mjj           := sqrt((leadingJet.energy+subLeadingJet.energy)^2-(leadingJet.px+subLeadingJet.px)^2-(leadingJet.py+subLeadingJet.py)^2-(leadingJet.pz+subLeadingJet.pz)^2)",
                        "dijet_dEta    := abs(leadingJet.eta - subLeadingJet.eta)",
                        "dijet_dPhi    := deltaPhi(leadingJet.phi, subLeadingJet.phi)",  
                        "dijet_Zep     := VBFMVA.dijet_Zep",
                        "dijet_MVA     := VBFMVA.VBFMVAValue",
                        "vbfcat        := categoryNumber",
                    ],
                       ## histograms
                       histograms=[]
)

## THQ leptonic ##
cfgTools.addCategories(process.thqLeptonicTagDumper,
                       ## categories definition
                       [("all","1",0)
                    ],                       
                       ## variables to be dumped in trees/datasets. Same variables for all categories
                       variables=dipho_variables+
                       ["n_ele    := electrons.size",
                        "ele1_pt  := ?(electrons.size>0)? electrons.at(0).pt : -1",
                        "ele2_pt  := ?(electrons.size>1)? electrons.at(1).pt : -1",
                        "ele1_ch  := ?(electrons.size>0)? electrons.at(0).charge : -999",
                        "ele2_ch  := ?(electrons.size>1)? electrons.at(1).charge : -999",
                        "n_muons  := muons.size",
                        "muon1_pt := ?(muons.size>0)? muons.at(0).pt : -1",
                        "muon2_pt := ?(muons.size>1)? muons.at(1).pt : -1",
                        "muon1_ch  := ?(muons.size>0)? muons.at(0).charge : -999",
                        "muon2_ch  := ?(muons.size>1)? muons.at(1).charge : -999",
                        "n_bjets  := bJets.size",
                        "n_jets   := jets.size",
                        "bjet1_pt := ?bJets.size>0? bJets.at(0).pt : -1",
                        "bjet2_pt := ?bJets.size>1? bJets.at(1).pt : -1",
                        "bjet1_eta:= ?bJets.size>0? bJets.at(0).eta: -1",
                        "bjet2_eta:= ?bJets.size>1? bJets.at(1).eta:-1",
                        "bjet1_abseta := ?bJets.size>0? abs(bJets.at(0).eta): -1",
                        "bjet2_abseta := ?bJets.size>1? abs(bJets.at(1).eta): -1",
                        "jet1_pt  := ?(jets.size>0)? jets.at(0).pt : -1",
                        "jet2_pt  := ?(jets.size>1)? jets.at(1).pt : -1",
                        "jet1_eta := ?(jets.size>0)? jets.at(0).eta : -1",
                        "jet2_eta := ?(jets.size>1)? jets.at(1).eta: -1",
                        "jet1_abseta := ?(jets.size>0)? abs(jets.at(0).eta): -1",
                        "jet2_abseta := ?(jets.size>1)? abs(jets.at(1).eta): -1",
                        "electronjet1deta := ?(electrons.size>0)? abs(electrons.at(0).eta - jets.at(0).eta) : -1",
                        "electronjet2deta := ?(electrons.size>0)? abs(electrons.at(0).eta - jets.at(1).eta) : -1",
                        "muonjet1deta := ?(muons.size>0)? abs(muons.at(0).eta - jets.at(0).eta) : -1",
                        "muonjet2deta := ?(muons.size>0)? abs(muons.at(0).eta - jets.at(1).eta) : -1",
                        "particleleadJet := tagTruth().closestParticleToLeadingJet().pdgId",
                        "partonleadJet   := tagTruth().closestPartonToLeadingJet().pdgId",
                        "genJetdrleadJetParton := tagTruth().dR_genJetMatchingTopartonJ1",
                        #"genJetIDleadJet   := tagTruth().closestGenJetToLeadingJet().genParton()..mother().pdgId",
                        "Mjj      := ?(jets.size>1)?"
                        +"sqrt((jets.at(0).energy+jets.at(1).energy)^2-(jets.at(0).px+jets.at(1).px)^2-(jets.at(0).py+jets.at(1).py)^2-(jets.at(0).pz+jets.at(1).pz)^2)"
                        +": -1",
                    ],
                       ## histograms
                       histograms=["jet1_pt>>jet1_pt(100,0,200)"]
)


## TTH leptonic ##
cfgTools.addCategories(process.tthLeptonicTagDumper,
                       ## categories definition
                       [("all","1",0)
                    ],                       
                       ## variables to be dumped in trees/datasets. Same variables for all categories
                       variables=dipho_variables+
                       ["n_ele    := electrons.size",
                        "ele1_pt  := ?(electrons.size>0)? electrons.at(0).pt : -1",
                        "ele2_pt  := ?(electrons.size>1)? electrons.at(1).pt : -1",
                        "ele1_ch  := ?(electrons.size>0)? electrons.at(0).charge : -999",
                        "ele2_ch  := ?(electrons.size>1)? electrons.at(1).charge : -999",
                        "n_muons  := muons.size",
                        "muon1_pt := ?(muons.size>0)? muons.at(0).pt : -1",
                        "muon2_pt := ?(muons.size>1)? muons.at(1).pt : -1",
                        "muon1_ch  := ?(muons.size>0)? muons.at(0).charge : -999",
                        "muon2_ch  := ?(muons.size>1)? muons.at(1).charge : -999",
                        "n_bjets  := bJets.size",
                        "n_jets   := jets.size",
                        "bjet1_pt := ?bJets.size>0? bJets.at(0).pt : -1",
                        "bjet2_pt := ?bJets.size>1? bJets.at(1).pt : -1",
                        "bjet1_eta:= ?bJets.size>0? bJets.at(0).eta: -1",
                        "bjet2_eta:= ?bJets.size>1? bJets.at(1).eta:-1",
                        "bjet1_abseta := ?bJets.size>0? abs(bJets.at(0).eta): -1",
                        "bjet2_abseta := ?bJets.size>1? abs(bJets.at(1).eta): -1",
                        "jet1_pt  := ?(jets.size>0)? jets.at(0).pt : -1",
                        "jet2_pt  := ?(jets.size>1)? jets.at(1).pt : -1",
                        "jet1_eta := ?(jets.size>0)? jets.at(0).eta : -1",
                        "jet2_eta := ?(jets.size>1)? jets.at(1).eta: -1",
                        "jet1_abseta := ?(jets.size>0)? abs(jets.at(0).eta): -1",
                        "jet2_abseta := ?(jets.size>1)? abs(jets.at(1).eta): -1",
                        "electronjet1deta := ?(electrons.size>0)? abs(electrons.at(0).eta - jets.at(0).eta) : -1",
                        "electronjet2deta := ?(electrons.size>0)? abs(electrons.at(0).eta - jets.at(1).eta) : -1",
                        "muonjet1deta := ?(muons.size>0)? abs(muons.at(0).eta - jets.at(0).eta) : -1",
                        "muonjet2deta := ?(muons.size>0)? abs(muons.at(0).eta - jets.at(1).eta) : -1",
                        "Mjj      := ?(jets.size>1)?"
                        +"sqrt((jets.at(0).energy+jets.at(1).energy)^2-(jets.at(0).px+jets.at(1).px)^2-(jets.at(0).py+jets.at(1).py)^2-(jets.at(0).pz+jets.at(1).pz)^2)"
                        +": -1",
                    ],
                       ## histograms
                       histograms=[]
)

## TTH hadronic ##
cfgTools.addCategories(process.tthHadronicTagDumper,
                       ## categories definition
                       [("all","1",0)
                    ],                       
                       ## variables to be dumped in trees/datasets. Same variables for all categories
                       variables=dipho_variables+
                       ["n_bjets  := nBMedium",
                        "n_jets   := jetVector.size",
                        "bjet1_pt := bJetVector.at(0).pt",
                        "bjet2_pt := ?nBMedium>1? bJetVector.at(1).pt : -1",
                        "jet1_pt  := ?(jetVector.size>0)? jetVector.at(0).pt : -1",
                        "jet2_pt  := ?(jetVector.size>1)? jetVector.at(1).pt : -1",
                        "jet3_pt  := ?(jetVector.size>2)? jetVector.at(2).pt : -1",
                        "jet4_pt  := ?(jetVector.size>3)? jetVector.at(3).pt : -1"
                    ],
                       ## histograms
                       histograms=[]
)

## VH Loose ##
cfgTools.addCategories(process.vhLooseTagDumper,
                       ## categories definition
                       [("all","1",0)
                    ],                       
                       ## variables to be dumped in trees/datasets. Same variables for all categories
                       variables=dipho_variables+
                       ["met      := ?met.size>0? met.at(0).NoShift : -1",
                        "n_ele    := electrons.size",
                        "ele1_pt  := ?(electrons.size>0)? electrons.at(0).pt : -1",
                        "ele2_pt  := ?(electrons.size>1)? electrons.at(1).pt : -1",
                        "ele1_ch  := ?(electrons.size>0)? electrons.at(0).charge : -999",
                        "ele2_ch  := ?(electrons.size>1)? electrons.at(1).charge : -999",
                        "n_muons  := muons.size",
                        "muon1_pt := ?(muons.size>0)? muons.at(0).pt : -1",
                        "muon2_pt := ?(muons.size>1)? muons.at(1).pt : -1",
                        "muon1_ch  := ?(muons.size>0)? muons.at(0).charge : -999",
                        "muon2_ch  := ?(muons.size>1)? muons.at(1).charge : -999",
                        "n_jets   := jets.size",
                        "jet1_pt  := ?(jets.size>0)? jets.at(0).pt : -1",
                        "jet2_pt  := ?(jets.size>1)? jets.at(1).pt : -1",
                        "Mjj      := ?(jets.size>1)?"
                        +"sqrt((jets.at(0).energy+jets.at(1).energy)^2-(jets.at(0).px+jets.at(1).px)^2-(jets.at(0).py+jets.at(1).py)^2-(jets.at(0).pz+jets.at(1).pz)^2)"
                        +": -1",
                    ],
                       ## histograms
                       histograms=[]
)

## VH Tight ##
cfgTools.addCategories(process.vhTightTagDumper,
                       ## categories definition
                       [("all","1",0)
                    ],                       
                       ## variables to be dumped in trees/datasets. Same variables for all categories
                       variables=dipho_variables+
                       ["met      := ?met.size>0? met.at(0).NoShift : -1",
                        "n_ele    := electrons.size",
                        "ele1_pt  := ?(electrons.size>0)? electrons.at(0).pt : -1",
                        "ele2_pt  := ?(electrons.size>1)? electrons.at(1).pt : -1",
                        "n_muons  := muons.size",
                        # "muon1_pt := ?(muons.size>0)? muons.at(0).pt : -1",
                        # "muon2_pt := ?(muons.size>1)? muons.at(1).pt : -1",
                        "n_jets   := jets.size",
                        "jet1_pt  := ?(jets.size>0)? jets.at(0).pt : -1",
                        "jet2_pt  := ?(jets.size>1)? jets.at(1).pt : -1",
                        "Mjj      := ?(jets.size>1)?"
                        +"sqrt((jets.at(0).energy+jets.at(1).energy)^2-(jets.at(0).px+jets.at(1).px)^2-(jets.at(0).py+jets.at(1).py)^2-(jets.at(0).pz+jets.at(1).pz)^2)"
                        +": -1",
                    ],
                       ## histograms
                       histograms=[]
)

## VH hadronic ##
cfgTools.addCategories(process.vhHadronicTagDumper,
                       ## categories definition
                       [("all","1",0)
                    ],                       
                       ## variables to be dumped in trees/datasets. Same variables for all categories
                       variables=dipho_variables+
                       ["dRphoLeadJ    := min(deltaR(leadingJet.eta, leadingJet.phi, diPhoton.leadingPhoton.eta, diPhoton.leadingPhoton.phi), deltaR(leadingJet.eta, leadingJet.phi, diPhoton.subLeadingPhoton.eta, diPhoton.subLeadingPhoton.phi))",
                        "dRphoSubleadJ := min(deltaR(subLeadingJet.eta, subLeadingJet.phi, diPhoton.leadingPhoton.eta, diPhoton.leadingPhoton.phi), deltaR(subLeadingJet.eta, subLeadingJet.phi, diPhoton.subLeadingPhoton.eta, diPhoton.subLeadingPhoton.phi))",
                        "leadJPt       := leadingJet.pt",
                        "leadJEta      := leadingJet.eta",
                        "subleadJPt    := subLeadingJet.pt",
                        "subleadJEta   := leadingJet.eta",
                        "Mjj           := sqrt((leadingJet.energy+subLeadingJet.energy)^2-(leadingJet.px+subLeadingJet.px)^2-(leadingJet.py+subLeadingJet.py)^2-(leadingJet.pz+subLeadingJet.pz)^2)",
                    ],
                       ## histograms
                       histograms=[]
)

from flashgg.MetaData.JobConfig import customize
customize.setDefault("maxEvents" ,-1)    # max-number of events
customize.setDefault("targetLumi",2.11e+3) # define integrated lumi
customize(process)

process.p1 = cms.Path(
    process.flashggTagSequence*
    #    process.flashggTagTester* # Uncommment if you what to test VBFtag
    process.untaggedDumper
    +process.vbfTagDumper
    +process.thqLeptonicTagDumper
    +process.tthLeptonicTagDumper
    +process.tthHadronicTagDumper
    +process.vhLooseTagDumper                      
    +process.vhTightTagDumper
    +process.vhHadronicTagDumper
)

print process.p1
