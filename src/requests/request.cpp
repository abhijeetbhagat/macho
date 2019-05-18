#include "../../include/requests/request.h"

Request::Request() : _payload("") {}

const std::vector<char> Request::to_bytes() const {
  return std::vector<char>(_payload.begin(), _payload.end());
}

const std::string &Request::to_string() const { return _payload; }
