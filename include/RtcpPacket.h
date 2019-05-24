#ifndef _RTCPPACKET_H_
#define _RTCPPACKET_H_
#include <ostream>

struct RtcpPacket{
  int version;// : 2;
  int padding; // : 1;
  int reception_report_cnt;
  int packet_type;
  uint16_t packet_len;
  uint32_t ssrc;
  RtcpPacket(int version, int padding, int reception_report_cnt, int packet_type, uint16_t packet_len, uint32_t ssrc) : version(version), padding(padding), reception_report_cnt(reception_report_cnt), packet_type(packet_type), packet_len(packet_len), ssrc(ssrc){ }

  friend std::ostream& operator<<(std::ostream& o, const RtcpPacket& packet){
    o << "version: " << packet.version << "\npadding: " << packet.padding << "\nreception_report_cnt: " << packet.reception_report_cnt << "\npacket_type: " << packet.packet_type << "\npacket_len: " << packet.packet_len << "\nssrc: " << packet.ssrc;
  }
};

#endif
