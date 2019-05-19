#ifndef _PLAY_H_
#define _PLAY_H_

#include "../IConnection.h"
#include "request.h"

struct Play : public Request {
  Play(const IConnection &conn, const std::string &url);
};

#endif
