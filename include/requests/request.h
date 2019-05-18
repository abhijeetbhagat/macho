#ifndef _REQUEST_H_
#define _REQUEST_H_

#include "../ISerializable.h"
#include <string>
#include <vector>

class Request : public ISerializable {
protected:
  std::string _payload;

public:
  Request();
  const std::vector<char> to_bytes() const;
  const std::string &to_string() const;
};
#endif
