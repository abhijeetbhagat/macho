#include "../include/RTSPConnection.h"
#include "../include/utils/utils.h"
#include <iostream>

RTSPConnection::RTSPConnection(const std::string &server, uint16_t port,
                               uint8_t version)
    : _server(server), _port(port), _version(version), _cseq(1),
      _stream(new TcpStream(server, port)), _url(""), _session("") {
  _stream->open();
}

RTSPConnection::RTSPConnection(const std::string &url)
    : _url(url), _version(1), _cseq(1), _stream(nullptr), _session("") {
  std::string server = "";
  uint16_t port;
  Utils::parse_url(url, server, port);
  _server = server;
  _port = port;
  _stream.reset(new TcpStream(server, port));
  _stream->open();
}

RTSPConnection::~RTSPConnection() {}

void RTSPConnection::send(const Request &request) {
  SPDLOG_INFO("request is {}\n", request.to_string());
  _stream->send_data(request.to_bytes());
  _cseq++;
}

const std::string &RTSPConnection::get_server() const { return _server; }

uint16_t RTSPConnection::get_port() const { return _port; }

const std::string &RTSPConnection::get_url() const { return _url; }

uint8_t RTSPConnection::get_version() const { return _version; }

uint8_t RTSPConnection::get_seq() const { return _cseq; }

void RTSPConnection::set_session(const std::string &session) {
  _session = session;
}

const std::string &RTSPConnection::get_session() const { return _session; }
