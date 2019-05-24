#ifndef _DEPACKETIZER_H_
#define _DEPACKETIZER_H_

#include<string>
#include "../RtpPacket.h"
#include "../RtcpPacket.h"

class Depacketizer{
  public:
    Depacketizer();
    RtpPacket parse_rtp(const std::string& data);
    RtcpPacket parse_rtcp(const std::string& data);
};

#endif
