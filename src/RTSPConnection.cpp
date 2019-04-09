#include "../include/RTSPConnection.h"
#include <iostream>
#include "../include/gsl-lite.hpp"

RTSPConnection::RTSPConnection(const std::string& server, uint16_t port) : _server(server), _port(port){ 
  if(_socket.connect_to(_server, port) < 0){
    std::cout << "Error connecting to server\n";
  }
}

RTSPConnection::~RTSPConnection(){
}

void RTSPConnection::options(){
  gsl::span<const char> command = "OPTIONS rtsp://184.72.239.149/vod/mp4:BigBuckBunny_175k.mov RTSP/1.0\r\nCSeq: 2\r\n\r\n";
  _socket.send(as_bytes(command));
  std::string output;
  _socket.recv(output);
  std::cout << "OPTIONS response: " << output << '\n';
}
