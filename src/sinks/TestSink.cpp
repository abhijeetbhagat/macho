#include "../../include/sinks/TestSink.h"

TestSink::TestSink(std::shared_ptr<ISourceFilter> source_filter) {
  _source_filter = source_filter;
}

TestSink::~TestSink() { }

void TestSink::start() {
  std::string buffer;
  _source_filter->get_next_frame(buffer);
}
