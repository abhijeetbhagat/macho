#ifndef _H264_SOURCE_FILTER_H_
#define _H264_SOURCE_FILTER_H_
#include "../include/rtp/depacketizer.h"
#include "../include/RtpPacket.h"
#include <list>

class H264SourceFilter {
  public:
    H264SourceFilter();
    ~H264SourceFilter() { }
    std::unique_ptr<RTPPacket> packet;
    //TODO there should ideally be multiple input queues
    //each associated with an SSRC (esp. in video conferencing)
    //For now, deal with a single SSRC
    std::list<RTPPacket> input_queue;
    Depacketizer _depacketizer;
};

#endif
