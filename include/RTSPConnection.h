#ifndef _RTSPCONNECTION_H_
#define _RTSPCONNECTION_H_
#include "TcpStream.h"
#include "request.h"
#include "IConnection.h"

class Request;

class RTSPConnection : public IConnection {
  public:
    RTSPConnection(const std::string& server, uint16_t port, uint8_t version = 1);
    RTSPConnection(const std::string& url);
    ~RTSPConnection();
    void send(const Request& request);
    virtual const std::string& get_server() const;
    virtual uint16_t get_port() const;
    virtual const std::string& get_url() const;
    virtual uint8_t get_version() const;
    virtual uint8_t get_seq() const;

  private:
    std::unique_ptr<TcpStream> _stream;
    std::string _server;
    int16_t _port;
    uint8_t _version;
    std::string _url;
    int _cseq;
};
#endif
