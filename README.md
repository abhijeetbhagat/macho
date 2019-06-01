# macho
This is an RTSP/RTP library implementation in C++.

# why?
Learn software engineering - language, tools, low-level stuff, protocols, etc. without worrying about time management.

# example
```cpp
#include "../include/RTSPConnection.h"
#include "../include/requests/describe.h"
#include "../include/requests/options.h"
#include "../include/requests/play.h"
#include "../include/requests/setup.h"
#include "../include/rtp/rtp_session.h"
#include "../include/sdp_info.h"
#include "../include/server_ep.h"
#include "../libcircinus/include/poller.h"
#include "../libcircinus/include/AbstractIOMuxer.h"
#include <thread>

int main() {
  RTSPConnection conn{"rtsp://184.72.239.149/vod/mp4:BigBuckBunny_175k.mov"};

  Options options{conn};
  conn.send(options);
  conn.receive<std::string>();

  Describe describe{conn};
  conn.send(describe);
  const SDPInfo sdp = conn.receive<SDPInfo>();

  conn.set_session(sdp.get_session());
  
  Setup video_setup{conn, sdp.get_video_url()};
  conn.send(video_setup);
  auto server_ep = conn.receive<ServerEndPoint>();

  std::thread rtp_thread([&]() {
    RTPSession session{std::unique_ptr<AbstractIOMuxer>(new Poller{}),
                       conn.get_server(), 
                       40102, 
                       40103,
                       server_ep.get_rtp_port(), 
                       server_ep.get_rtcp_port()};
    session.start();
  });

  Play play{conn, sdp.get_video_url()};
  conn.send(play);
  conn.receive();

  rtp_thread.join();
}
```
