#ifndef _OPTIONS_H_
#define _OPTIONS_H_

#include "../IConnection.h"
#include "request.h"

struct Options : public Request{
  Options(const IConnection& conn);
};

#endif
