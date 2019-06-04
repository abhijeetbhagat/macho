#ifndef _H264_SOURCE_FILTER_H_
#define _H264_SOURCE_FILTER_H_
#include "../include/rtp/depacketizer.h"
#include "../include/transport/UdpSocket.h"
#include "../include/RtpPacket.h"
#include "../libcircinus/include/AbstractIOMuxer.h"
#include <list>
#include <memory>

class H264RTPSourceFilter {
  public:
    H264RTPSourceFilter(std::unique_ptr<AbstractIOMuxer> io_muxer, const std::string &ip, uint16_t data_port, uint16_t server_rtp_port);
    ~H264RTPSourceFilter() { }
    std::unique_ptr<RTPPacket> packet;
    //TODO there should ideally be multiple input queues
    //each associated with an SSRC (esp. in video conferencing)
    //For now, deal with a single SSRC
    std::list<RTPPacket> input_queue;
    Depacketizer _depacketizer;
    std::unique_ptr<UdpSocket> _video_rtp_socket;  // rtp data listener
    std::unique_ptr<AbstractIOMuxer> _io_muxer;
};

#endif
