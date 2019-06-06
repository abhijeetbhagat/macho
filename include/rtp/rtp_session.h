#ifndef _RTPSESSION_H
#define _RTPSESSION_H

#include "../../libcircinus/include/AbstractIOMuxer.h"
#include "../filters/h264_source_filter.h"
#include "../transport/UdpSocket.h"
#include <memory>
// Note: The design of this class is based on the RTP book by Colin Perkins.
// It was made generic by me.

// TODO abhi: Make this policy based class for choosing the transportation
// medium
class RTPSession {
public:
  RTPSession(std::unique_ptr<AbstractIOMuxer> io_muxer, const std::string &ip,
             uint16_t data_port, uint16_t rtcp_port, uint16_t server_rtp_port,
             uint16_t server_rtcp_port);
  void start();

private:
  std::string ip;
  uint16_t rtp_data_port;
  uint16_t rtcp_data_port;
  std::unique_ptr<UdpSocket> _audio_rtp_socket;  // rtp data listener
  std::unique_ptr<UdpSocket> _audio_rtcp_socket; // rtcp data listener
  std::unique_ptr<UdpSocket> _video_rtp_socket;  // rtp data listener
  std::unique_ptr<UdpSocket> _video_rtcp_socket; // rtcp data listener
  std::unique_ptr<AbstractIOMuxer> _io_muxer;
  std::unique_ptr<H264RTPSourceFilter> _source_filter;
};

#endif
