#include "../../include/requests/setup.h"
#include "../../third_party/include/spdlog/spdlog.h"

Setup::Setup(const IConnection& conn, const std::string& url){
  //TODO implement setup
  //SPDLOG_INFO("url is {}", url);
  _payload = "SETUP " + url + " RTSP/" + std::to_string(conn.get_version()) + ".0\r\nCSeq: " + std::to_string(conn.get_seq()) + "\r\nUser-agent: macho\r\nSession: " + conn.get_session() + "\r\nRange: npt=0.000-\r\n\r\n" ;
}

    /*Request: SETUP rtsp://184.72.239.149/vod/mp4:BigBuckBunny_175k.mov/trackID=1 RTSP/1.0\r\n
    CSeq: 4\r\n
    User-Agent: LibVLC/2.2.2 (LIVE555 Streaming Media v2016.02.09)\r\n
    Transport: RTP/AVP;unicast;client_port=40102-40103
    \r\n
    */
