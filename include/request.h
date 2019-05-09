#ifndef _REQUEST_H_
#define _REQUEST_H_

#include "RTSPConnection.h"
#include "ISerializable.h"
#include "../macho/include/gsl-lite.hpp"

typename<class T>
class Request : public ISerializable {
  private:
    gsl::span<const char> _payload;
  public:
    Request(const RTSPConnection& conn);
    gsl::span<gsl::byte> to_bytes();

}
#endif
