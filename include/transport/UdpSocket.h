#ifndef _UDPSOCKET_H_
#define _UDPSOCKET_H_
#include "../gsl-lite.hpp"
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

class UdpSocket {
public:
  UdpSocket();
  ~UdpSocket();
  void send(gsl::span<const gsl::byte> data);
  void send_to(gsl::span<const gsl::byte> data, const std::string &ip,
               uint16_t port);
  std::vector<gsl::byte> recv();
  void recv(std::string &buf);
  std::string recv_from(std::vector<gsl::byte> &buf);
  void bind_to(const std::string &ip, uint16_t port);
  int connect_to(const std::string &ip, uint16_t port);

private:
  int _sd;
  sockaddr_in _myip, _remoteip;
};
#endif
