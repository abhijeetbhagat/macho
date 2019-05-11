#ifndef _REQUEST_H_
#define _REQUEST_H_

#include <vector>
#include "RTSPConnection.h"
#include "ISerializable.h"
#include "gsl-lite.hpp"

class RTSPConnection;

class Request : public ISerializable {
  protected:
    std::string _payload;
  public:
    Request();
    const std::vector<char> to_bytes() const;
    const std::string& to_string() const;
};
#endif
