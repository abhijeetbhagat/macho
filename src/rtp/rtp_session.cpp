#include <iostream>
#include <sys/epoll.h>
#include <sys/poll.h>
#include <sys/time.h>
#include "rtp_session.h"
#include "depacketizer.h"
#include "../../third_party/include/spdlog/spdlog.h"

RTPSession::RTPSession(const std::string &ip, uint16_t data_port,
                       uint16_t rtcp_port, uint16_t server_rtp_port,
                       uint16_t server_rtcp_port) {
  _video_rtp_socket = std::unique_ptr<UdpSocket>(new UdpSocket());
  _video_rtp_socket->set_blocking(false);
  _video_rtp_socket->bind_to(ip, data_port);
  
  //TODO if we dont do this, then we dont receive any packets
  _video_rtp_socket->send_to(ip, server_rtp_port, "Îúíþ");

  _video_rtcp_socket = std::unique_ptr<UdpSocket>(new UdpSocket());
  _video_rtp_socket->set_blocking(false);
  _video_rtcp_socket->bind_to(ip, rtcp_port);
}

/*void  RTPSession::register_back(std::function<void(RTPPacket)> callback){
  
}*/

//TODO this should IO multiplex rtp and rtcp sockets
void RTPSession::start() {
  std::string buffer;
  Depacketizer depacketizer;
  /*fd_set master_set, working_set;
  FD_ZERO(&master_set);
  FD_ZERO(&working_set);
  FD_SET(recv_sd, &master_set);
  timeval timeout;
  timeout.tv_sec = 3 * 60;
  timeout.tv_usec = 0;
  */
  int rtp_sd = _video_rtp_socket->get_desc();
  int rtcp_sd = _video_rtcp_socket->get_desc();
  pollfd pollfds[2];
  pollfds[0].fd = rtp_sd;
  pollfds[0].events = POLLIN;
  pollfds[1].fd = rtcp_sd;
  pollfds[1].events = POLLIN;

  while (true) {
    //memcpy(&working_set, &master_set, sizeof master_set);
    SPDLOG_INFO("waiting for packet...\n");
    int rc = poll(pollfds, 2, 50000);
    for(int i = 0; i < 2; i++){
      //if(FD_ISSET(i, &working_set)){
      if(pollfds[i].revents & POLLIN){
        if(pollfds[i].fd == rtp_sd){ //RTP socket ready to be read
          _video_rtp_socket->recv(buffer);
          auto packet = depacketizer.parse_rtp(buffer);
          //TODO put this packet in a shared queue and signal a packet processor thread (producer-consumer)
          std::cout << packet;
          buffer.clear();
        } else { //RTP socket ready to be read
          SPDLOG_INFO("this is an rtcp packet\n");
          _video_rtcp_socket->recv(buffer);
          auto packet = depacketizer.parse_rtcp(buffer);
          //TODO put this packet in a shared queue and signal a packet processor thread (producer-consumer)
          std::cout << packet;
          buffer.clear();
        }
      }
    }
  }
}
