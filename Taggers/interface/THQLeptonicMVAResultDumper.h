#ifndef flashgg_THQLeptonicMVAResultDumpers_h
#define flashgg_THQLeptonicMVAResultDumpers_h
#include "flashgg/DataFormats/interface/THQLeptonicMVAResult.h"
#include "flashgg/Taggers/interface/CollectionDumper.h"
namespace flashgg {
    typedef CollectionDumper<std::vector<THQLeptonicMVAResult> > THQLeptonicMVAResultDumper;
    typedef CollectionDumper<std::vector<THQLeptonicMVAResult> ,
            THQLeptonicMVAResult,
            CutBasedClassifier<THQLeptonicMVAResult> > CutBasedTHQLeptonicMVAResultDumper;
}
#endif
// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

