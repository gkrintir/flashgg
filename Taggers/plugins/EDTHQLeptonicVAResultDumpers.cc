#include "FWCore/Framework/interface/MakerMacros.h"
#include "flashgg/Taggers/interface/THQLeptonicMVAResultDumper.h"
#include "PhysicsTools/UtilAlgos/interface/EDAnalyzerWrapper.h"
typedef edm::AnalyzerWrapper<flashgg::THQLeptonicMVAResultDumper> THQLeptonicMVAResultDumper;
typedef edm::AnalyzerWrapper<flashgg::CutBasedTHQLeptonicMVAResultDumper> CutBasedTHQLeptonicMVAResultDumper;
DEFINE_FWK_MODULE( THQLeptonicMVAResultDumper );
DEFINE_FWK_MODULE( CutBasedTHQLeptonicMVAResultDumper );
// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

