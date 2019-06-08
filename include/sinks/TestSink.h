#ifndef _TEST_SINK_H_
#define _TEST_SINK_H_

#include "../../include/filters/ISourceFilter.h"
#include <memory>

class TestSink {
  public:
    TestSink(std::shared_ptr<ISourceFilter>);
    ~TestSink();
    void start();
  private:
    std::shared_ptr<ISourceFilter> _source_filter;
};

#endif
