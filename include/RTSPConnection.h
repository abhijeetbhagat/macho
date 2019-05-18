#ifndef _RTSPCONNECTION_H_
#define _RTSPCONNECTION_H_
#include "../third_party/include/spdlog/spdlog.h"
#include "IConnection.h"
#include "requests/request.h"
#include "transport/TcpStream.h"

class Request;

class RTSPConnection : public IConnection {
public:
  RTSPConnection(const std::string &server, uint16_t port, uint8_t version = 1);
  RTSPConnection(const std::string &url);
  ~RTSPConnection();
  void send(const Request &request);
  template <class T = std::string> T receive(/*std::vector<char>& response*/) {
    std::vector<char> response;
    _stream->receive(response);
    std::string out(response.begin(), response.end());
    SPDLOG_INFO("response: {}\n", out);
    return T(out);
  }
  virtual const std::string &get_server() const;
  virtual uint16_t get_port() const;
  virtual const std::string &get_url() const;
  virtual uint8_t get_version() const;
  virtual uint8_t get_seq() const;
  virtual void set_session(const std::string &session);
  virtual const std::string &get_session() const;

private:
  std::unique_ptr<TcpStream> _stream;
  std::string _server;
  int16_t _port;
  uint8_t _version;
  std::string _url;
  int _cseq;
  std::string _session;
};
#endif
