#include "../../include/rtp/depacketizer.h"

Depacketizer::Depacketizer(){
}

RtpPacket Depacketizer::parse(const std::string& buf){
  RtpPacket packet;
  auto packet_len = (uint16_t)buf[2] << 8 | (uint16_t)buf[3];
  auto payload = buf.substr(4, packet_len - 4);

  auto version = payload[0] & 0x80 != 0 ? 2 : 1;
  auto padding = (payload[0] & 0x20) > 0;
  auto extension = (payload[0] & 0x10) > 0;
  auto cc = (payload[0] & 0xf);
  auto marker = (payload[1] & 0x80) > 0;
  auto payload_type = (payload[1] & 0x7f);
  auto seq_num = (uint16_t)payload[2] << 8 | (uint16_t)payload[3];
  auto timestamp = (uint32_t)payload[4] << 24 | (uint32_t)payload[5] << 16 | (uint16_t)payload[6] << 8 | (uint16_t)payload[7];
  auto ssrc = (uint32_t)payload[8] << 24 | (uint32_t)payload[9] << 16 | (uint16_t)payload[10] << 8 | (uint16_t)payload[11];

  packet.header = RtpPacket::RtpHeader{
    version = version,
    padding = padding,
    extension = extension,
    cc = cc,
    marker = marker,
    //ptype = payload_type,
    seq_num = seq_num,
    timestamp = timestamp,
    ssrc = ssrc
  };

  return packet;
}
