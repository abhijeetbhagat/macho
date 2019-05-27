#ifndef _ICONNECTION_H_
#define _ICONNECTION_H_

#include <string>

struct IConnection {
  virtual ~IConnection(){}
  virtual const std::string &get_server() const = 0;
  virtual uint16_t get_port() const = 0;
  virtual const std::string &get_url() const = 0;
  virtual uint8_t get_version() const = 0;
  virtual uint8_t get_seq() const = 0;
  virtual void set_session(const std::string &session) = 0;
  virtual const std::string &get_session() const = 0;
};
#endif
