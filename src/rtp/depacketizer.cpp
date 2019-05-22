#include "../../include/rtp/depacketizer.h"

Depacketizer::Depacketizer(){
}

RtpPacket Depacketizer::parse(const std::string& buf){
  RtpPacket packet;
  //The following check is only valid for embedded (interleaved) binary data
  //if(buf[0] == 0x24){ //'$' means start of packet
  //auto packet_len = (uint16_t)buf[2] << 8 | (uint16_t)buf[3];
  auto payload = buf;

  auto version = (payload[0] & 0xc0) >> 6;
  auto padding = (payload[0] & 0x20) >> 5;
  auto extension = (payload[0] & 0x10) >> 4;
  auto cc = (payload[0] & 0xf);
  auto marker = (payload[1] & 0x80) >> 7;
  auto payload_type = (payload[1] & 0x7f);
  auto seq_num = uint16_t((uint16_t)payload[2] << (uint16_t)8 | (uint16_t)payload[3]);
  auto timestamp = (uint32_t)payload[4] << 24 | (uint32_t)payload[5] << 16 | (uint32_t)payload[6] << 8 | (uint32_t)payload[7];
  auto ssrc = (uint32_t)payload[8] << 24 | (uint32_t)payload[9] << 16 | (uint32_t)payload[10] << 8 | (uint32_t)payload[11];

  std::vector<uint32_t> csrcs;
  uint32_t j = 12;
  if(cc > 0){
    csrcs.reserve(cc);
    for(uint32_t i = 0; i < cc; i++){ 
      uint32_t csrc = payload[j] << 24 | payload[++j] << 16 | payload[++j] << 8 | payload[++j];
      csrcs.push_back(csrc);
    }
  }

  uint16_t profile_specific_extn_id = 0;
  uint16_t extension_len = 0;
  if(extension > 0){
    profile_specific_extn_id = payload[j] << 8 | payload[++j];
    extension_len = payload[j] << 8 | payload[++j];
  }

  //std::unique_ptr<uint8_t[]> payload_data();
  //std::copy(payload)
  uint16_t payload_len = buf.size() - j;
  packet.header = RtpPacket::RtpHeader{
    version = version,
    padding = padding,
    extension = extension,
    cc = cc,
    marker = marker,
    payload_type = payload_type,
    seq_num = seq_num,
    timestamp = timestamp,
    ssrc = ssrc,
    csrcs = csrcs,
    profile_specific_extn_id = profile_specific_extn_id,
    extension_len = extension_len,
    payload_len = payload_len
  };
  packet.header.raw_data.reset(new uint8_t[payload_len]());
  std::copy(payload.data() + j, payload.data() + payload.size(), packet.header.raw_data.get());

  return packet;
}
