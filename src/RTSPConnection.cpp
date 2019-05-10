#include "../include/RTSPConnection.h"
#include <iostream>
#include "../include/gsl-lite.hpp"

RTSPConnection::RTSPConnection(const std::string& server, uint16_t port, uint8_t version = 1) : _server(server), _port(port), _version(version) _stream(server, port), _url(""){
  _stream.open();//){
    //std::cout << "Error connecting to server\n";
  //}
}

RTSPConnection::RTSPConnection(const std::string& url) : _url(url){ }

RTSPConnection::~RTSPConnection(){ }

void RTSPConnection::send(const Request& request){
  gsl::span<const char> command = "OPTIONS rtsp://184.72.239.149/vod/mp4:BigBuckBunny_175k.mov RTSP/1.0\r\nCSeq: 2\r\n\r\n";
  _stream.send_data(as_bytes(command));
  std::vector<char> output;
  _stream.receive(output);
  std::string out(output.begin(), output.end());
  std::cout << "OPTIONS response: " << out << '\n';
}

std::string get_server(){
  return _server;
}

uint16_t get_port(){
  return _port;
}

std::string get_url(){
  return _url;
}
