#include "../include/sdp_info.h"
#include "../third_party/include/spdlog/spdlog.h"
#include <iterator>
#include <sstream>
#include <vector>

// TODO abhi: The following SDP parsing is based on what was observed in VLC
// with
// the public url. If that SDP isn't standard, then we have a problem.
SDPInfo::SDPInfo(const std::string &data)
    : str(data), audio_track(AudioTrack()), video_track(VideoTrack()) {
  SPDLOG_INFO("constructing sdp info... \n");
  std::istringstream stream(str);
  std::string s;
  int content_length = 0;
  std::vector<std::string> sdp_lines;
  while (getline(stream, s, '\n')) {
    s = s.erase(s.find_last_not_of('\r') + 1);
    sdp_lines.push_back(s);
  }
  SPDLOG_INFO("sdp lines pushed \n");

  std::vector<std::string>::iterator it = sdp_lines.begin();
  std::vector<std::string>::iterator next;
  while (it != sdp_lines.end()) {
    if (it->find("Content-Length") != std::string::npos) {
      content_length = std::stoi(it->substr(16));
      next = std::next(it, 1);
      break;
    }
    it++;
  }

  SPDLOG_INFO("content_length is {}\n", content_length);

  while (next != sdp_lines.end()) {
    if (next->find("Content-Base") != std::string::npos) {
      base_url = next->substr(14);
      it = std::next(next, 1);
      break;
    }
    next++;
  }
  SPDLOG_INFO("content_base is {}\n", base_url);

  while (it != sdp_lines.end()) {
    if (it->find("Session") != std::string::npos) {
      int semi_colon = it->find(';');
      session = it->substr(9, semi_colon - 9);
      next = std::next(it, 1);
      break;
    }
    it++;
  }
  SPDLOG_INFO("session is {}\n", session);

  while (next != sdp_lines.end()) {
    if (next->find("a=control:*") != std::string::npos) {
      it = std::next(next, 4);
      audio_track.track_id = it->substr(10);
      next = std::next(it, 7);
      video_track.track_id = next->substr(10);
      break;
    }
    next++;
  }
  SPDLOG_INFO("AudioTrack track_id is {}\n", audio_track.track_id);
  SPDLOG_INFO("VideoTrack track_id is {}\n", video_track.track_id);
}
