#ifdef _ISOURCE_FILTER_H
#define  _ISOURCE_FILTER_H

struct ISourceFilter {
  virtual ~ISourceFilter() { }
  virtual void get_next_frame(unsigned char* buffer) = 0;
};

#endif
