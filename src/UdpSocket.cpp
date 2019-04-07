#include "../include/UdpSocket.h"
#include <iostream>
#include <cstring>
#define MAX_UDP_PACKET_SIZE 64 * 1024

UdpSocket::UdpSocket(){
  _sd = socket(AF_INET, SOCK_DGRAM, 0);
  if(_sd < 0) {
    throw;
  }
}

UdpSocket::~UdpSocket(){
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

std::vector<gsl::byte> UdpSocket::recv(){
  std::vector<gsl::byte> data;
  socklen_t *len;
  *len = sizeof _myip;
  recvfrom(_sd, data.data(), MAX_UDP_PACKET_SIZE, 0, (sockaddr*)&_myip, len);
}

void UdpSocket::bind_to(const std::string& ip, int port) {
  memset(&_myip, 0, sizeof _myip);
  _myip.sin_family = AF_INET;
  _myip.sin_port = htons(port);
  inet_pton(AF_INET, ip.c_str(), &_myip.sin_addr);
  if(bind(_sd, (sockaddr*)&_myip, sizeof _myip) == -1){
    std::cout << "Error naming the socket (bind).\n";
  }
}

void UdpSocket::connect_to(const std::string& ip, int port) {
  memset(&_remoteip, 0, sizeof _remoteip);
  _remoteip.sin_family = AF_INET;
  _remoteip.sin_port = htons(port);
  inet_pton(AF_INET, ip.c_str(), &_remoteip.sin_addr);
  if(connect(_sd, (sockaddr*)&_remoteip, sizeof _remoteip) == -1){
    std::cout << "Error connect to remote socket.\n";
  }
}
