#ifndef _H264_SOURCE_FILTER_H_
#define _H264_SOURCE_FILTER_H_
#include "../../include/RtpPacket.h"
#include "../../include/rtp/depacketizer.h"
#include "../../include/transport/UdpSocket.h"
#include "../../libcircinus/include/AbstractIOMuxer.h"
#include "ISourceFilter.h"
#include <list>
#include <memory>

class H264RTPSourceFilter : public ISourceFilter {
public:
  H264RTPSourceFilter(const std::string &ip, uint16_t data_port,
                      uint16_t server_rtp_port,
                      std::shared_ptr<AbstractIOMuxer> io_muxer = nullptr);
  ~H264RTPSourceFilter();
  void get_next_frame(unsigned char *buffer);

private:
  std::unique_ptr<RtpPacket> packet;
  // TODO there should ideally be multiple input queues
  // each associated with an SSRC (esp. in video conferencing)
  // For now, deal with a single SSRC
  std::list<RtpPacket> input_queue;
  Depacketizer _depacketizer;
  std::unique_ptr<UdpSocket> _video_rtp_socket; // rtp data listener
  std::shared_ptr<AbstractIOMuxer> _io_muxer;
};

#endif
