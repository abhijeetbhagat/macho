#ifndef _UDPSOCKET_H_
#define _UDPSOCKET_H_
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<vector>
#include "gsl-lite.hpp"

class UdpSocket {
  public:
    UdpSocket();
    ~UdpSocket();
    void send(const std::string& ip, int port, gsl::span<int8_t> data);
    std::vector<int8_t> recv();
    
  private:
    int _sd;
    addrinfo *_ai;
};
#endif
