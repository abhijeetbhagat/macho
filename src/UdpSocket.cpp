#include "../include/UdpSocket.h"
#include <unistd.h>
#include <iostream>
#include <cstring>
#define MAX_UDP_PACKET_SIZE 64 * 1024

UdpSocket::UdpSocket(){
  std::cout << "UdpSocket ctor called\n";
  _sd = socket(AF_INET, SOCK_DGRAM, 0);
  if(_sd < 0) {
    throw;
  }
}

UdpSocket::~UdpSocket(){
  close(_sd);
}

void UdpSocket::send(gsl::span<const gsl::byte> data){ 
  int result = sendto(_sd,
                      data.data(),
                      data.size(),
                      0,
                      (sockaddr*)&_remoteip,
                      sizeof _remoteip);
  if(result == -1){
    std::cout << "Error sending data\n";
  }
}

void UdpSocket::send_to(gsl::span<const gsl::byte> data, const std::string& ip, int16_t port){
  sockaddr_in remoteip;
  remoteip.sin_family = AF_INET;
  remoteip.sin_port = htons(port);
  inet_pton(AF_INET, ip.c_str(), &remoteip.sin_addr);
  sendto(_sd,
         data.data(),
         data.size(),
         0,
         (sockaddr*)&remoteip,
         sizeof remoteip);
}

std::vector<gsl::byte> UdpSocket::recv(){
  std::vector<gsl::byte> data(MAX_UDP_PACKET_SIZE);
  recvfrom(_sd, data.data(), MAX_UDP_PACKET_SIZE, 0, nullptr, 0);
  std::cout << "socket recvd " << data.size() << " bytes\n";
  return data;
}

void UdpSocket::recv(std::string& buf){
  std::unique_ptr<char[]> cbuf(new char[MAX_UDP_PACKET_SIZE]);
  auto num_bytes = recvfrom(_sd, cbuf.get(), MAX_UDP_PACKET_SIZE, 0, nullptr, 0);
  buf.resize(num_bytes);
  buf.assign(cbuf.get(), num_bytes);
}


std::string UdpSocket::recv_from(std::vector<gsl::byte>& buf){ 
  sockaddr_in srcip;
  socklen_t *len;
  *len = sizeof srcip;
  recvfrom(_sd, buf.data(), MAX_UDP_PACKET_SIZE, 0, (sockaddr*)&srcip, len);
  char out[INET_ADDRSTRLEN];
  inet_ntop(AF_INET, &(srcip.sin_addr), out, INET_ADDRSTRLEN);
  return std::string(out); 
}

void UdpSocket::bind_to(const std::string& ip, uint16_t port) {
  memset(&_myip, 0, sizeof _myip);
  _myip.sin_family = AF_INET;
  _myip.sin_port = htons(port);
  inet_pton(AF_INET, ip.c_str(), &_myip.sin_addr);
  if(bind(_sd, (sockaddr*)&_myip, sizeof _myip) == -1){
    std::cout << "Error naming the socket (bind).\n";
  }
}

void UdpSocket::connect_to(const std::string& ip, uint16_t port) {
  memset(&_remoteip, 0, sizeof _remoteip);
  _remoteip.sin_family = AF_INET;
  _remoteip.sin_port = htons(port);
  inet_pton(AF_INET, ip.c_str(), &_remoteip.sin_addr);
  if(connect(_sd, (sockaddr*)&_remoteip, sizeof _remoteip) == -1){
    std::cout << "Error connect to remote socket.\n";
  }
}
