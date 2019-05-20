#ifndef _RTPPACKET_H_
#define _RTPPACKET_H_

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
    int ptype;// : 7;
    short seq_num;// : 16;
    uint32_t timestamp;
    uint32_t ssrc;
  } header;
};

#endif
