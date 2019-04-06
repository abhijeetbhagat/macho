#include "../include/UdpSocket.h"

UdpSocket::UdpSocket(){
  _sd = socket(AF_INET, SOCK_DGRAM, 0);
  if(_sd < 0) {
    throw;
  }
}

void UdpSocket::send(const std::string& ip, int port, gsl::span<int8_t> data){

}

std::vector<int8_t> recv(){
}
