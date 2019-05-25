#ifndef _SERVER_EP_H_
#define _SERVER_EP_H_

#include <sstream>
#include <string>

struct ServerEndPoint {
private:
  uint16_t rtp_data_port;
  uint16_t rtcp_data_port;

public:
  ServerEndPoint(const std::string &data) {
    std::string str = data;
    std::istringstream stream(str);
    std::string s;
    bool ports_found = false;
    while (getline(stream, s, '\n')) {
      if (s.find("Transport") != std::string::npos) {
        std::istringstream stream2(s);
        std::string line;
        while (getline(stream2, line, ';')) {
          if (line.find("server_port") != std::string::npos) {
            std::string port_range = line.substr(12);
            auto hyphen_index = 0;
            if ((hyphen_index = port_range.find('-')) != std::string::npos) {
              //auto semi_colon_index = port_range.find(';');
              rtp_data_port = std::stoi(port_range.substr(0, hyphen_index));
              rtcp_data_port = std::stoi(port_range.substr(hyphen_index + 1));
            } else { // there's only single port?
              rtp_data_port = std::stoi(port_range.substr(12));
              rtcp_data_port = 0;
            }
            ports_found = true;
            break;
          }
        }
      }
      if (ports_found)
        break;
    }
  }

  uint16_t get_rtp_port() const { return rtp_data_port; }

  uint16_t get_rtcp_port() const { return rtcp_data_port; }
};
#endif
