#ifndef _ISERIALIZABLE_H_
#define _ISERIALIZABLE_H_

#include <vector>

struct ISerializable {
  virtual const std::vector<char> to_bytes() const = 0;
};
#endif
