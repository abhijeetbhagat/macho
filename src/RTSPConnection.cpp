#include "../include/RTSPConnection.h"
#include <iostream>
#include "../include/gsl-lite.hpp"

RTSPConnection::RTSPConnection(const std::string& server, uint16_t port) : _server(server), _port(port), _stream(server, port){ 
  _stream.open();//){
    //std::cout << "Error connecting to server\n";
  //}
}

RTSPConnection::~RTSPConnection(){
}

void RTSPConnection::options(){
  gsl::span<const char> command = "OPTIONS rtsp://184.72.239.149/vod/mp4:BigBuckBunny_175k.mov RTSP/1.0\r\nCSeq: 2\r\n\r\n";
  _stream.send_data(as_bytes(command));
  std::vector<char> output;
  _stream.receive(output);
  std::string out(output.begin(), output.end());
  std::cout << "OPTIONS response: " << out << '\n';
}
