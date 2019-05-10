#ifndef _RTSPCONNECTION_H_
#define _RTSPCONNECTION_H_
#include "TcpStream.h"

class RTSPConnection : public IConnection {
  public:
    RTSPConnection(const std::string& server, uint16_t port, uint8_t version = 1);
    ~RTSPConnection();
    void options();
    virtual std::string get_server();
    virtual uint16_t get_port();
    virtual std::string get_url();

  private:
    TcpStream _stream;
    std::string _server;
    int16_t _port;
    uint8_t _version;
    std::string _url;
};
#endif
