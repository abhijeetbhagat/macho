#include "../include/RTSPConnection.h"
#include "../include/gsl-lite.hpp"
#include "../include/requests/describe.h"
#include "../include/requests/options.h"
#include "../include/requests/play.h"
#include "../include/requests/setup.h"
#include "../include/rtp/rtp_session.h"
#include "../include/sdp_info.h"
#include "../include/server_ep.h"
#include "../libcircinus/include/poller.h"
#include "../libcircinus/include/AbstractIOMuxer.h"
#include "../third_party/include/spdlog/spdlog.h"
#include <chrono>
#include <thread>

int main() {
  RTSPConnection conn{"rtsp://184.72.239.149/vod/mp4:BigBuckBunny_175k.mov"};
  // auto options = Request<Options>{};
  Options options{conn};
  conn.send(options);

  // std::vector<char> output;
  conn.receive<std::string>(/*output*/);

  Describe describe{conn};
  conn.send(describe);
  // output.clear();
  const SDPInfo sdp = conn.receive<SDPInfo>();

  conn.set_session(sdp.get_session());
  // Setup audio_setup{conn, sdp.get_audio_url()};
  Setup video_setup{conn, sdp.get_video_url()};
  // conn.send(audio_setup);
  conn.send(video_setup);
  auto server_ep = conn.receive<ServerEndPoint>();

  std::thread rtp_thread([&]() {
    RTPSession session{std::unique_ptr<AbstractIOMuxer>(new Poller{}), conn.get_server(), 40102, 40103,
                       server_ep.get_rtp_port(), server_ep.get_rtcp_port()};
    session.start();
  });

  // give enough time for the rtp socket to open and start listening
  // std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  Play play{conn, sdp.get_video_url()};
  conn.send(play);
  conn.receive();

  rtp_thread.join();
  // For now, open only the video stream
}
