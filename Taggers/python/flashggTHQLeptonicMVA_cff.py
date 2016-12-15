import FWCore.ParameterSet.Config as cms

from flashgg.Taggers.flashggTags_cff import UnpackedJetCollectionVInputTag
import flashgg.Taggers.PUJID_wps as pujid
from flashgg.MicroAOD.flashggJets_cfi import flashggBTag, maxJetCollections

# legacy VBF MVA
flashggTHQLeptonicMVA = cms.EDProducer('FlashggTHQLeptonicMVAProducer',
                               DiPhotonTag=cms.InputTag('flashggPreselectedDiPhotons'),
                               #JetTag=cms.InputTag('flashggSelectedJets'),
                               inputTagJets= UnpackedJetCollectionVInputTag,
                               MVAMethod = cms.string("BDT"),
                               UsePuJetID  = cms.bool(False),
                               UseJetID    = cms.bool(True),
                               merge3rdJet = cms.bool(False),
                               thirdJetDRCut = cms.double(1.8),
                               JetIDLevel    = cms.string("Loose"),
                               # changes loose to another working point, or comment if you want to disable pujid
                               pujidWpPtBin1 = cms.vdouble(), # cms.vdouble(pujid.loose[0]),
                               pujidWpPtBin2 = cms.vdouble(), # cms.vdouble(pujid.loose[1]),
                               pujidWpPtBin3 = cms.vdouble(), # cms.vdouble(pujid.loose[2]), 
                               #UseLegacyMVA = cms.bool(True),
                               rmsforwardCut = cms.double(0.03), # default was 0.03 , running on loose pujid
                               MinDijetMinv = cms.double(0.0),
                               ElectronTag=cms.InputTag('flashggSelectedElectrons'),
                               MuonTag=cms.InputTag('flashggSelectedMuons'),
                               VertexTag=cms.InputTag('offlineSlimmedPrimaryVertices'),
                               leptonPtThreshold = cms.untracked.double(20),
                               leptonEtaThreshold = cms.untracked.double(2.4),
                               leadPhoOverMassThreshold = cms.untracked.double(0.5),
                               subleadPhoOverMassThreshold = cms.untracked.double(0.25),
                               MVAThreshold = cms.untracked.double(-1.0),
                               deltaRLepPhoThreshold = cms.untracked.double(0.5),
                               deltaRJetLepThreshold = cms.untracked.double(0.4),
                               jetsNumberThreshold = cms.untracked.double(2.),
                               bjetsNumberThreshold = cms.untracked.double(1.),
                               jetPtThreshold = cms.untracked.double(25.), 
                               jetEtaThreshold= cms.untracked.double(4.7),
                               deltaRJetLeadPhoThreshold = cms.untracked.double(0.4),
                               deltaRJetSubLeadPhoThreshold = cms.untracked.double(0.4),
                               bDiscriminator=cms.untracked.vdouble(0.605,0.890), 
                               bTag = cms.untracked.string(flashggBTag),
                               muPFIsoSumRelThreshold = cms.untracked.double(0.25), 
                               PuIDCutoffThreshold = cms.untracked.double(0.8),
                               PhoMVAThreshold = cms.untracked.double(-0.9), 
                               DeltaRTrkElec = cms.untracked.double(1.),
                               TransverseImpactParam = cms.untracked.double(0.02),
                               LongitudinalImpactParam = cms.untracked.double(0.2),
                               deltaRPhoElectronThreshold = cms.untracked.double(1.),
                               Zmass_ = cms.untracked.double(91.9),
                               deltaMassElectronZThreshold_ = cms.untracked.double(10.),
                               electronEtaCuts=cms.untracked.vdouble(1.4442,1.566,2.5),
                               nonTrigMVAThresholds = cms.untracked.vdouble(0.913286,0.805013,0.358969),
                               nonTrigMVAEtaCuts = cms.untracked.vdouble(0.8,1.479,2.5),
                               electronIsoThreshold = cms.untracked.double(0.15),
                               electronNumOfHitsThreshold = cms.untracked.double(1),
                               #vbfMVAweightfile = cms.FileInPath("flashgg/Taggers/data/TMVA_dijet_sherpa_scalewt50_2evenb_powheg200_maxdPhi_oct9_Gradient.weights.xml"),
                               #vbfMVAweightfile = cms.FileInPath("flashgg/Taggers/data/TMVAClassification_dijetMVA_Jan2016_rmscut_BDTG.weights.xml"),
                               #vbfMVAweightfile = cms.FileInPath("flashgg/Taggers/data/TMVAClassification_dijetMVA_76x_24_02_15_BDTG.weights.xml"),
                               thqleptonicMVAweightfile = cms.FileInPath("flashgg/Taggers/data/TMVA_classification_dijet-mva-80x-ICHEP-v04.weights.xml"),
)

'''
# Legacy DiPhoDiJet MVA
flashggVBFDiPhoDiJetMVA = cms.EDProducer('FlashggVBFDiPhoDiJetMVAProducer',
                                         DiPhotonTag=cms.InputTag('flashggPreselectedDiPhotons'),
                                         VBFMVAResultTag=cms.InputTag('flashggVBFMVA'),
                                         MVAResultTag=cms.InputTag('flashggDiPhotonMVA'),
                                         UseLegacyMVA = cms.bool(False),
                                         #vbfDiPhoDiJetMVAweightfile = cms.FileInPath("flashgg/Taggers/data/TMVA_vbf_dijet_dipho_evenbkg_scaledwt50_maxdPhi_Gradient.weights.xml"),
                                         #vbfDiPhoDiJetMVAweightfile = cms.FileInPath("flashgg/Taggers/data/TMVAClassification_combinedMVA_Jan2016_rmscut_BDTG.weights.xml"),
                                         #vbfDiPhoDiJetMVAweightfile = cms.FileInPath("flashgg/Taggers/data/TMVAClassification_combinedMVA_76x_25_02_15_0.03_BDTG.weights.xml"),
                                         vbfDiPhoDiJetMVAweightfile = cms.FileInPath("flashgg/Taggers/data/TMVA_classification_combined-mva-80x-ICHEP-v01_BDTG.weights.xml"),
                                         )

'''
