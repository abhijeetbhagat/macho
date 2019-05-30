#ifndef _DEPACKETIZER_H_
#define _DEPACKETIZER_H_

#include "../RtcpPacket.h"
#include "../RtpPacket.h"
#include <string>

class Depacketizer {
public:
  Depacketizer();
  RtpPacket parse_rtp(const std::string &data);
  RtcpPacket parse_rtcp(const std::string &data);
};

#endif
