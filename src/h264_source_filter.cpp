#include "../include/h264_source_filter.h"

H264RTPSourceFilter::H264RTPSourceFilter(std::unique_ptr<AbstractIOMuxer> io_muxer, const std::string &ip, uint16_t data_port, uint16_t server_rtp_port) {
  _io_muxer = std::move(io_muxer);
  _video_rtp_socket = std::unique_ptr<UdpSocket>(new UdpSocket());
  _video_rtp_socket->set_blocking(false);
  _video_rtp_socket->bind_to(ip, data_port);
  // TODO if we dont do this, then we might not receive any packets
  // Found that this is used to overcome NAT traversal problem where we are behind a NAT
  // and so the server's streams can't reach us
  _video_rtp_socket->send_to(ip, server_rtp_port, "Îúíþ");
}
