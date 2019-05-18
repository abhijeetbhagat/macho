#ifndef _DESCRIBE_H_
#define _DESCRIBE_H_

#include "../IConnection.h"
#include "request.h"

struct Describe : public Request {
  Describe(const IConnection &conn);
};

#endif
