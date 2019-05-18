#ifndef _TCPSTREAM_H_
#define _TCPSTREAM_H_

#include "../gsl-lite.hpp"
#include <sys/socket.h>
#include <sys/types.h>
#include <vector>

class TcpStream {
public:
  TcpStream(const std::string &server, uint16_t port);
  ~TcpStream();
  void bind_socket();
  void listen_incoming();
  void accept_conn();
  void open();
  void receive(std::vector<char> &);
  void send_data(const std::vector<char> &);

private:
  std::string _server;
  uint16_t _port;
  int _sd;
};

#endif
