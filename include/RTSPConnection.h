#ifndef _RTSPCONNECTION_H_
#define _RTSPCONNECTION_H_
#include "UdpSocket.h"

class RTSPConnection{
  public:
    RTSPConnection();
    ~RTSPConnection();

  private:
    UdpSocket _socket;
    std::string _server;
    int16_t _port;
};
#endif
