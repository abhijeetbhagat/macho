#include "../include/describe.h"


/*DESCRIBE rtsp://184.72.239.149/vod/mp4:BigBuckBunny_175k.mov RTSP/1.0\r\n
    CSeq: 3\r\n
    User-Agent: LibVLC/2.2.2 (LIVE555 Streaming Media v2016.02.09)\r\n
    Accept: application/sdp\r\n
    \r\n
*/

Describe::Describe(const IConnection& conn){
  _payload = "DESCRIBE " + conn.get_url() + " RTSP/"+ std::to_string(conn.get_version()) + ".0\r\nCSeq: " + std::to_string(conn.get_seq()) + "\r\n" + "User-Agent: macho\r\nAccept: application/sdp\r\n\r\n";
}
