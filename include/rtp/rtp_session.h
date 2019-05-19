#ifndef _RTPSESSION_H
#define _RTPSESSION_H

#include "../transport/UdpSocket.h"
// Note: The design of this class is based on the RTP book by Colin Perkins.
// It was made generic by me.

// TODO abhi: Make this policy based class for choosing the transportation
// medium
class RTPSession {
  std::string ip;
  uint16_t rtp_data_port;
  uint16_t rtcp_data_port;
  std::unique_ptr<UdpSocket> _audio_rtp_socket;  // rtp data listener
  std::unique_ptr<UdpSocket> _audio_rtcp_socket; // rtcp data listener
  std::unique_ptr<UdpSocket> _video_rtp_socket;  // rtp data listener
  std::unique_ptr<UdpSocket> _video_rtcp_socket; // rtcp data listener

public:
  RTPSession(const std::string &ip, uint16_t data_port, uint16_t rtcp_port,
             uint16_t server_rtp_port, uint16_t server_rtcp_port);
  void start();
};

#endif
