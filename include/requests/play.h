#ifndef _DESCRIBE_H_
#define _DESCRIBE_H_

#include "../IConnection.h"
#include "request.h"

struct Play : public Request{
  Play(const IConnection& conn, const std::string& url);
};

#endif
