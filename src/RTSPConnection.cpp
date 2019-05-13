#include "../include/RTSPConnection.h"
#include <iostream>
#include "../include/utils.h"
#include "../third_party/include/spdlog/spdlog.h"

RTSPConnection::RTSPConnection(const std::string& server, uint16_t port, uint8_t version) : _server(server), _port(port), _version(version), _cseq(1), _stream(new TcpStream(server, port)), _url(""){
  _stream->open();
}

RTSPConnection::RTSPConnection(const std::string& url) : _url(url), _version(1), _cseq(1), _stream(nullptr){
  std::string server = "";
  uint16_t port;
  Utils::parse_url(url, server, port);
  _server = server;
  _port = port;
  _stream.reset(new TcpStream(server, port));
  _stream->open();
}

RTSPConnection::~RTSPConnection(){ }

void RTSPConnection::send(const Request& request){
  SPDLOG_INFO("request is {}\n", request.to_string());
  _stream->send_data(request.to_bytes());
  _cseq++;
}

void RTSPConnection::receive(std::vector<char>& response){
  _stream->receive(response);
  std::string out(response.begin(), response.end());
  SPDLOG_INFO("response: {}\n", out);
}

const std::string& RTSPConnection::get_server() const{
  return _server;
}

uint16_t RTSPConnection::get_port() const{
  return _port;
}

const std::string& RTSPConnection::get_url() const{
  return _url;
}

uint8_t RTSPConnection::get_version() const{
  return _version;
}

uint8_t RTSPConnection::get_seq() const{
  return _cseq;
}
