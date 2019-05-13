
#ifndef _SETUP_H_
#define _SETUP_H_

#include "../IConnection.h"
#include "request.h"

struct Setup : public Request{
  Setup(const IConnection& conn);
};

#endif
