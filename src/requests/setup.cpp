#include "../../include/requests/setup.h"

Setup::Setup(const IConnection& conn){
  //TODO implement setup
  _payload = "SETUP " + conn.get_url();
}

    /*Request: SETUP rtsp://184.72.239.149/vod/mp4:BigBuckBunny_175k.mov/trackID=1 RTSP/1.0\r\n
    CSeq: 4\r\n
    User-Agent: LibVLC/2.2.2 (LIVE555 Streaming Media v2016.02.09)\r\n
    Transport: RTP/AVP;unicast;client_port=40102-40103
    \r\n
    */
