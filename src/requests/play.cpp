#include "../../include/requests/play.h"

/*DESCRIBE rtsp://184.72.239.149/vod/mp4:BigBuckBunny_175k.mov RTSP/1.0\r\n
    CSeq: 3\r\n
    User-Agent: LibVLC/2.2.2 (LIVE555 Streaming Media v2016.02.09)\r\n
    Accept: application/sdp\r\n
    \r\n
*/

Play::Play(const IConnection &conn, const std::string &url) {
  _payload = "PLAY " + url + " RTSP/" + std::to_string(conn.get_version()) +
             ".0\r\nCSeq: " + std::to_string(conn.get_seq()) +
             "\r\nUser-Agent: macho\r\nSession: " + conn.get_session() +
             "\r\nRange: npt=0.000-\r\n\r\n";
}
