#include "../include/sdp_info.h"
#include <sstream>
#include <iterator>
#include <vector>
#include "../third_party/include/spdlog/spdlog.h"

SDPInfo::SDPInfo(const std::string& data) : str(data){
  SPDLOG_INFO("constructing sdp info... \n");
  std::istringstream stream(str);
  std::string s;
  int content_length = 0;
  std::vector<std::string> sdp_lines;
  while(getline(stream, s, '\n')){
    sdp_lines.push_back(s);
  }
  SPDLOG_INFO("sdp lines pushed \n");

  std::vector<std::string>::iterator it = sdp_lines.begin();
  std::vector<std::string>::iterator next;
  while(it != sdp_lines.end()){
    if(it->find("Content-Length") != std::string::npos){
      content_length = std::stoi(it->substr(16));
      next = std::next(it, 1);
      break;
    }
    it++;
  }
  
  SPDLOG_INFO("content_length is {}\n", content_length);

  while(next != sdp_lines.end()){
    if(next->find("Content-Base") != std::string::npos){
      base_url = next->substr(14);
      it = std::next(next, 1);
      break;
    }
    next++;
  }
  SPDLOG_INFO("content_base is {}\n", base_url);

  while(it != sdp_lines.end()){
    if(it->find("Session") != std::string::npos){
      int semi_colon = it->find(';');
      session = it->substr(9, semi_colon - 9);
    }
    it++;
  }
  SPDLOG_INFO("session is {}\n", session);
}
