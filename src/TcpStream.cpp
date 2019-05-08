#include "../include/TcpStream.h"
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#define BACKLOG 128 //standard
#define MAX_TCP_PACKET_SIZE 64 * 1024

TcpStream::TcpStream(const std::string& server, uint16_t port) : _server(server), _port(port){
  std::cout << "initialized Socket \n";
  _sd = socket(AF_INET, SOCK_STREAM, 0);
  if(_sd < 0){
    throw;
  } else {
    std::cout << "Socket initialized\n";
  }
}

TcpStream::~TcpStream(){
  close(_sd);
}

void TcpStream::bind_socket(){
  sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(_port);
  inet_pton(AF_INET, _server.c_str(), &addr.sin_addr);
  bind(_sd, (sockaddr*)&addr, sizeof addr);
}

void TcpStream::listen_incoming(){
  listen(_sd, BACKLOG);
}

void TcpStream::accept_conn(){
  sockaddr_in incoming;
  //std::unique_ptr<socklen_t> size(new socklen_t);
  //*size = sizeof incoming;
  socklen_t *len;
  accept(_sd, (sockaddr*)&incoming, len);
}

void TcpStream::open() {
  sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(_port);
  inet_pton(AF_INET, _server.c_str(), &addr.sin_addr);
  std::cout << "Connecting to the remote server..." << _server << ' ' << _port << "\n";

  if(connect(_sd, (sockaddr*)&addr, (socklen_t)sizeof addr) < 0){
    std::cout << "Error connecting\n";
    throw;
  } else {
    std::cout << "Connected!\n";
  }
}

void TcpStream::receive(std::vector<char> &buf){
  std::unique_ptr<char> temp(new char[MAX_TCP_PACKET_SIZE]);
  auto num_bytes = recv(_sd, temp.get(), MAX_TCP_PACKET_SIZE, 0);
  buf.resize(num_bytes);
  buf.assign(temp.get(), temp.get() + num_bytes);
}


void TcpStream::send_data(gsl::span<const gsl::byte> data){
  auto num_bytes = send(_sd, data.data(), data.size(), 0);
}
