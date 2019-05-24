#include "rtp_session.h"
#include "depacketizer.h"
#include <iostream>
#include "../../third_party/include/spdlog/spdlog.h"

RTPSession::RTPSession(const std::string &ip, uint16_t data_port,
                       uint16_t rtcp_port, uint16_t server_rtp_port,
                       uint16_t server_rtcp_port) {
  _video_rtp_socket = std::unique_ptr<UdpSocket>(new UdpSocket());
  _video_rtp_socket->bind_to(ip, data_port);
  _video_rtp_socket->send_to(ip, server_rtp_port, "Îúíþ");
  _video_rtcp_socket = std::unique_ptr<UdpSocket>(new UdpSocket());
  _video_rtcp_socket->bind_to(ip, rtcp_port);
}

/*void  RTPSession::register_back(std::function<void(RTPPacket)> callback){
  
}*/

//TODO this should IO multiplex rtp and rtcp sockets
void RTPSession::start() {
  std::string buffer;
  Depacketizer depacketizer;
  while (true) {
    SPDLOG_INFO("waiting for packet...\n");
    _video_rtp_socket->recv(buffer);
    auto packet = depacketizer.parse_rtp(buffer);
    std::cout << packet;
    buffer.clear();
  }
}
