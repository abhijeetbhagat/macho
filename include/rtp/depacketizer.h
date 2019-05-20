#ifndef _DEPACKETIZER_H_
#define _DEPACKETIZER_H_

#include<string>
#include "../RtpPacket.h"

class Depacketizer{
  public:
    Depacketizer();
    RtpPacket parse(const std::string& data);
};

#endif
