#include "../macho/include/request.h"

Request::Request(const RTSPConnection& conn) {
  _payload = ""
}

gsl::span<gsl::byte> Request::to_bytes(){
  return as_bytes(_payload);
}

