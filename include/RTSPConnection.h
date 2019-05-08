#ifndef _RTSPCONNECTION_H_
#define _RTSPCONNECTION_H_
#include "TcpStream.h"

class RTSPConnection{
  public:
    RTSPConnection(const std::string& server, uint16_t port);
    ~RTSPConnection();
    void options();

  private:
    TcpStream _stream;
    std::string _server;
    int16_t _port;
};
#endif
