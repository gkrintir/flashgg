#ifndef FLASHgg_THQLeptonicMVAResult_h
#define FLASHgg_THQLeptonicMVAResult_h

#include "DataFormats/Common/interface/Ptr.h"
#include "flashgg/DataFormats/interface/DiPhotonCandidate.h"
#include "flashgg/DataFormats/interface/Jet.h"

namespace flashgg {
    
    class THQLeptonicMVAResult
    {
        
    public:
        THQLeptonicMVAResult();
        THQLeptonicMVAResult( edm::Ptr<THQLeptonicMVAResult> );
        virtual ~THQLeptonicMVAResult() {}
        // diJet Info
        //flashgg::Jet leadJet;
        //flashgg::Jet subleadJet;
        // 3rd jet
        //flashgg::Jet subsubleadJet;
        reco::Candidate::LorentzVector leadJet;
        reco::Candidate::LorentzVector subleadJet;
        reco::Candidate::LorentzVector subsubleadJet;
        
        edm::Ptr<flashgg::Jet> leadJet_ptr;
        edm::Ptr<flashgg::Jet> subleadJet_ptr;
        // 3rd jet
        edm::Ptr<flashgg::Jet> subsubleadJet_ptr; 
        // 4-vec of the 3 jets
        
        
        bool hasValidVBFTriJet;
        
        // di-photon info 
        // flashgg::DiPhotonCandidate diphoton;
        
        // event based variables
        int  n_rec_jets;
        int  n_gen_jets;
        int  n_diphotons;
        
        // Input variables
        float dijet_leadEta ;
        float dijet_subleadEta;
        float dijet_abs_dEta;
        float dijet_LeadJPt ;
        float dijet_SubJPt;
        float dijet_Zep;
        float dijet_dphi_trunc;
        float dijet_dipho_dphi;
        float dijet_Mjj;
        float dijet_dy;
        float dijet_leady ;
        float dijet_subleady;
        float dijet_dipho_pt;
        float dijet_minDRJetPho;
        
        float dipho_PToM;
        float leadPho_PToM;
        float sublPho_PToM;
        
        // some 3-jet based variables 
        
        float THQLeptonicMVAValue() const {return thqLeptonicMvaResult_value;}
        
        // Output
        float thqLeptonicMvaResult_value;
        float thqLeptonicMvaResult_value_bdt;
        float thqLeptonicMvaResult_value_bdtg;
    };
    
    typedef std::map<edm::Ptr<DiPhotonCandidate>, THQLeptonicMVAResult> THQLeptonicMVAResultMap;
    
}

#endif
// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

