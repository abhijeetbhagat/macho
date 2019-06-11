#ifndef _ISOURCE_FILTER_H
#define _ISOURCE_FILTER_H
#include <string>

struct ISourceFilter {
  virtual ~ISourceFilter() {}
  virtual void get_next_frame(std::string& buffer) = 0;
  virtual void open() = 0; //This should be called from a sink
};

#endif
