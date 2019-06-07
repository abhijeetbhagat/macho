#ifndef _ISOURCE_FILTER_H
#define _ISOURCE_FILTER_H
#include <string>

struct ISourceFilter {
  virtual ~ISourceFilter() {}
  virtual void get_next_frame(std::string& buffer) = 0;
};

#endif
