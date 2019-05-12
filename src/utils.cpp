#include "../include/utils.h"

bool Utils::parse_url(const std::string& url, std::string& ip, uint16_t& port){
  bool is_success = false;
  auto n = url.find("//");
  if(n == std::string::npos)
    return false;
  int ip_start = n+2, ip_end = 0;
  int port_start = 0, colon = url.find(':', ip_start), port_end = 0;
  int first_fwd_slash = url.find('/', ip_start);
  if(colon == std::string::npos || colon > first_fwd_slash){//port not specified or colon is unrelated to the port?
    port = 554;
    ip_end = url.find('/', ip_start);
    if(ip_end == std::string::npos) //incorrect url
      return false;

    ip = url.substr(ip_start, ip_end - ip_start);
    return true;
  } else {
    port_start = colon + 1;
    ip_end = colon - 1;
    port_end =  url.find('/', ip_start);
    if(port_end == std::string::npos){ //incorrect url
      return false;
    }
    port_end--;
    port = std::stoi(url.substr(port_start, port_end));
    ip = url.substr(ip_start, colon-ip_start);
    return true;
  }

  return is_success;
}
