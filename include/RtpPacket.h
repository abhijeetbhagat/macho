#ifndef _RTPPACKET_H_
#define _RTPPACKET_H_

#include <ostream>
#include <vector>
#include <memory>

// TODO: will this struct work on Win too?
// according to
// https://stackoverflow.com/questions/25345691/bit-fields-portability/25345750
// it looks like it will
struct RtpPacket {
  struct RtpHeader {
    int version;// : 2;
    int padding; // : 1;
    int extension; // : 1;
    int cc;// : 4;
    int marker;// : 1;
    int payload_type;// : 7;
    uint16_t seq_num;// : 16;
    uint32_t timestamp;
    uint32_t ssrc;
    std::vector<uint32_t> csrcs;
    uint16_t profile_specific_extn_id;
    uint16_t extension_len;
    uint16_t payload_len;
    std::unique_ptr<uint8_t[]> raw_data;

  } header;

  friend std::ostream& operator<<(std::ostream& o, const RtpPacket& packet){
    o << "version: " << packet.header.version << "\npadding: " << packet.header.padding  << "\nextension: " << packet.header.extension 
      << "\ncc: " << packet.header.cc  << "\nmarker: " << packet.header.marker  << "\nptype: " << packet.header.payload_type  << "\nseq_num: " << packet.header.seq_num
      << "\ntimestamp: " << packet.header.timestamp << "\nssrc: " << packet.header.ssrc << '\n';
    std::ios_base::fmtflags f(o.flags());
    for(uint16_t i = 0; i < packet.header.payload_len; i ++){
      o << std::hex << (int)packet.header.raw_data.get()[i] << ' ';
    }
    o.flags(f);
    o << '\n';
    return o;
  }
};

#endif
