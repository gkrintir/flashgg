#!/usr/bin/env cmsRun

import FWCore.ParameterSet.Config as cms
import FWCore.Utilities.FileUtils as FileUtils
from FWCore.ParameterSet.VarParsing import VarParsing
from flashgg.MetaData.samples_utils import SamplesManager

process = cms.Process("VBFTagsDumper")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000))
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32( 1 )
process.source = cms.Source ("PoolSource",
                             fileNames = cms.untracked.vstring("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/cmshgg/ferriff/flashgg/RunIISpring16DR80X-2_2_0-25ns_ICHEP16_MiniAODv2/2_2_0/VBFHToGG_M-120_13TeV_powheg_pythia8/RunIISpring16DR80X-2_2_0-25ns_ICHEP16_MiniAODv2-2_2_0-v0-RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/160707_150027/0000/myMicroAODOutputFile_1.root"))

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("VBFTagsDump.root"),
                                   closeFileFast = cms.untracked.bool(True))


from flashgg.Taggers.flashggTagOutputCommands_cff import tagDefaultOutputCommand
import flashgg.Taggers.dumperConfigTools as cfgTools
from  flashgg.Taggers.tagsDumpers_cfi import createTagDumper

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

# set the VBF dumper
process.vbfTagDumper = createTagDumper("VBFTag")
process.vbfTagDumper.dumpTrees     = True
process.vbfTagDumper.dumpHistos    = True
process.vbfTagDumper.dumpWorkspace = False

# use the trigger-diphoton-preselection
#from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag
#massSearchReplaceAnyInputTag(process.flashggTagSequence,cms.InputTag("flashggDiPhotons"),cms.InputTag("flashggPreselectedDiPhotons"))

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

from flashgg.MetaData.JobConfig import customize
customize.setDefault("maxEvents" ,1000)    # max-number of events
customize.setDefault("targetLumi",2.11e+3) # define integrated lumi
customize(process)

process.p1 = cms.Path(
    process.flashggTagSequence*
    process.flashggTagTester* # Uncommment if you what to test VBFtag
    process.vbfTagDumper
)

print process.p1
