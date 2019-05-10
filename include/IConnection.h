#ifndef _ICONNECTION_H_
#define _ICONNECTION_H_

struct IConnection{
  virtual std::string get_server() = 0;
  virtual uint16_t get_port() = 0;
  virtual std::string get_url() = 0;
  virtual uint8_t get_version() = 0;
}
#endif

