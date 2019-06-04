#include <iostream>
#include <sys/epoll.h>
//#include <sys/poll.h>
#include "../../libcircinus/include/poller.h"
#include "../../third_party/include/spdlog/spdlog.h"
#include "depacketizer.h"
#include "rtp_session.h"
#include <chrono>
#include <sys/time.h>

RTPSession::RTPSession(std::unique_ptr<AbstractIOMuxer> io_muxer, const std::string &ip, uint16_t data_port,
                       uint16_t rtcp_port, uint16_t server_rtp_port,
                       uint16_t server_rtcp_port) {
  _io_muxer = std::move(io_muxer);
  _source_filter = std::unique_ptr<H264SourceFilter>(new H264SourceFilter(_io_muxer, ip, data_port, server_rtp_port));
  /*_video_rtp_socket = std::unique_ptr<UdpSocket>(new UdpSocket());
  _video_rtp_socket->set_blocking(false);
  _video_rtp_socket->bind_to(ip, data_port);
  */

  // TODO if we dont do this, then we might not receive any packets
  // Found that this is used to overcome NAT traversal problem where we are behind a NAT
  // and so the server's streams can't reach us
  //_video_rtp_socket->send_to(ip, server_rtp_port, "Îúíþ");

  _video_rtcp_socket = std::unique_ptr<UdpSocket>(new UdpSocket());
  _video_rtcp_socket->set_blocking(false);
  _video_rtcp_socket->bind_to(ip, rtcp_port);

  // TODO if we dont do this, then we might not receive any packets
  // Found that this is used to overcome NAT traversal problem where we are behind a NAT
  // and so the server's streams can't reach us
  _video_rtcp_socket->send_to(ip, server_rtcp_port, "Îúíþ");
}

/*void  RTPSession::register_back(std::function<void(RTPPacket)> callback){

}*/

// TODO this should IO multiplex rtp and rtcp sockets
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
  /*pollfd pollfds[2];
  pollfds[0].fd = rtp_sd;
  pollfds[0].events = POLLIN;
  pollfds[1].fd = rtcp_sd;
  pollfds[1].events = POLLIN;
  */
  //Poller poller;
  _io_muxer->open(2);
  _io_muxer->subscribe(rtp_sd, Events::Read);
  _io_muxer->subscribe(rtcp_sd, Events::Read);

  while (true) {
    // memcpy(&working_set, &master_set, sizeof master_set);
    SPDLOG_INFO("waiting for packet...\n");
    int rc = _io_muxer->wait(std::chrono::milliseconds{50000});
    if (rc <= 0) {
      continue;
    }
    auto ready_set = _io_muxer->ready_set();
    for (int i = 0; i < ready_set.size(); i++) {
      // if(FD_ISSET(i, &working_set)){
      if (ready_set[i] == rtp_sd) { // RTP socket ready to be read
        _video_rtp_socket->recv(buffer);
        auto packet = depacketizer.parse_rtp(buffer);
        // TODO put this packet in a shared queue and signal a packet processor
        // thread (producer-consumer)
        std::cout << packet;
        buffer.clear();
      } else { // RTCP socket ready to be read
        SPDLOG_INFO("this is an rtcp packet\n");
        _video_rtcp_socket->recv(buffer);
        auto packet = depacketizer.parse_rtcp(buffer);
        // TODO put this packet in a shared queue and signal a packet processor
        // thread (producer-consumer)
        std::cout << packet;
        buffer.clear();
      }
    }
  }
}
