#include "../include/RTSPConnection.h"
#include "../include/gsl-lite.hpp"
#include "../include/requests/describe.h"
#include "../include/requests/options.h"
#include "../include/requests/play.h"
#include "../include/requests/setup.h"
#include "../include/sdp_info.h"
#include "../third_party/include/spdlog/spdlog.h"

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
  conn.receive();

  Play play{conn, sdp.get_video_url()};
  conn.send(play);
  conn.receive();

  // RTPSession session{};
  // session.start();
}
