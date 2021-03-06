#ifndef incl_HPHP_NEWRELIC_PROFILER_H_
#define incl_HPHP_NEWRELIC_PROFILER_H_


#include "hphp/runtime/ext/hotprofiler/ext_hotprofiler.h"
#include "hphp/runtime/base/php-globals.h"
#include "hphp/runtime/server/server-stats.h"
#include "newrelic_transaction.h"
#include "newrelic_collector_client.h"
#include "newrelic_common.h"

namespace HPHP {
    ///////////////////////////////////////////////////////////////////////////////

    class NewRelicProfiler : public Profiler {

    public:
        // NEWOBJ existsonly until HHVM 3.4
        #ifdef NEWOBJ
            explicit NewRelicProfiler(int64_t mdepth) : max_depth(mdepth)  {}
        #else
            explicit NewRelicProfiler(int64_t mdepth) : Profiler(true), max_depth(mdepth)  {}
        #endif

        virtual void beginFrameEx(const char *symbol);
        virtual void endFrameEx(const TypedValue *retval, const char *given_symbol);

        virtual Frame *allocateFrame() override {
            return new NewRelicProfilerFrame();
        }

        void vscan(IMarker& mark) const override {
        }

    private:

        class NewRelicProfilerFrame : public Frame {
            public:
            virtual ~NewRelicProfilerFrame() {
            }

            int             m_nr_depth;
            int64_t         m_nr_segement_code;

        };

        int max_depth;
    };

}

#endif // incl_HPHP_NEWRELIC_PROFILER_H_
