#include "../../include/filters/h264_source_filter.h"
#include <chrono>

H264RTPSourceFilter::H264RTPSourceFilter(
    const std::string &ip, uint16_t data_port, uint16_t server_rtp_port,
    std::unique_ptr<AbstractIOMuxer> io_muxer) {
  _io_muxer = std::move(io_muxer);
  _video_rtp_socket = std::unique_ptr<UdpSocket>(new UdpSocket());
  _video_rtp_socket->set_blocking(false);
  _video_rtp_socket->bind_to(ip, data_port);
  // TODO if we dont do this, then we might not receive any packets
  // Found that this is used to overcome NAT traversal problem where we are
  // behind a NAT
  // and so the server's streams can't reach us
  _video_rtp_socket->send_to(ip, server_rtp_port, "Îúíþ");
  _io_muxer->subscribe(_video_rtp_socket->get_desc(), Events::Read);
}

H264RTPSourceFilter::~H264RTPSourceFilter() {}

void H264RTPSourceFilter::get_next_frame(unsigned char *buffer) {
  // TODO somehow, poll the rtp socket and call recv on it if ready
  int rc = _io_muxer->wait(std::chrono::milliseconds{50000});
  if (rc <= 0) {
    return;
  }
  auto ready_set = _io_muxer->ready_set();
  for (int i = 0; i < ready_set.size(); i++) {
    // if(FD_ISSET(i, &working_set)){
    if (ready_set[i] ==
        _video_rtp_socket->get_desc()) { // RTP socket ready to be read
    }
  }
}
