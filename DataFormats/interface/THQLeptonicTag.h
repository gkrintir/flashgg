#ifndef FLASHgg_THQLeptonicTag_h
#define FLASHgg_THQLeptonicTag_h

#include "flashgg/DataFormats/interface/DiPhotonTagBase.h"
#include "flashgg/DataFormats/interface/Muon.h"
#include "flashgg/DataFormats/interface/Electron.h"
#include "flashgg/DataFormats/interface/Jet.h"

namespace flashgg {

    class THQLeptonicTag: public DiPhotonTagBase
    {
    public:
        THQLeptonicTag();
        THQLeptonicTag( edm::Ptr<DiPhotonCandidate>, edm::Ptr<DiPhotonMVAResult> );
        THQLeptonicTag( edm::Ptr<DiPhotonCandidate>, DiPhotonMVAResult );

        ~THQLeptonicTag();

        THQLeptonicTag *clone() const { return ( new THQLeptonicTag( *this ) ); }

        const std::vector<edm::Ptr<Muon> > muons() const { return Muons_;}
        const std::vector<edm::Ptr<flashgg::Electron> > electrons() const {return Electrons_;}
        const std::vector<edm::Ptr<Jet> > jets() const { return Jets_;}
        const std::vector<edm::Ptr<Jet> > bJets() const { return BJets_;}

        void setJets( std::vector<edm::Ptr<Jet> > Jets ) { Jets_ = Jets; }
        void setBJets( std::vector<edm::Ptr<Jet> > BJets )  { BJets_ = BJets;}
        void setMuons( std::vector<edm::Ptr<Muon> > Muons ) {Muons_ = Muons;}
        void setElectrons( std::vector<edm::Ptr<Electron> > Electrons ) {Electrons_ = Electrons;}

    private:
        std::vector<edm::Ptr<Muon> > Muons_;
        std::vector<edm::Ptr<Electron> > Electrons_;
        std::vector<edm::Ptr<Jet> > Jets_;
        std::vector<edm::Ptr<Jet> > BJets_;
    };
}

#endif
// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
