#ifndef _SDP_INFO_H
#define _SDP_INFO_H

#include <string>
#include "utils.h"
/*
[2019-05-14 08:17:43.132] [info] [RTSPConnection.cpp:31] response: RTSP/1.0 200 OK
CSeq: 2
Server: Wowza Streaming Engine 4.7.5.01 build21752
Cache-Control: no-cache
Expires: Tue, 14 May 2019 02:47:43 UTC
Content-Length: 590
Content-Base: rtsp://184.72.239.149/vod/mp4:BigBuckBunny_175k.mov/
Date: Tue, 14 May 2019 02:47:43 UTC
Content-Type: application/sdp
Session: 1354643379;timeout=60

v=0
o=- 1354643379 1354643379 IN IP4 184.72.239.149
s=BigBuckBunny_175k.mov
c=IN IP4 184.72.239.149
t=0 0
a=sdplang:en
a=range:npt=0- 596.458
a=control:*
m=audio 0 RTP/AVP 96
a=rtpmap:96 mpeg4-generic/48000/2
a=fmtp:96 profile-level-id=1;mode=AAC-hbr;sizelength=13;indexlength=3;indexdeltalength=3;config=1190
a=control:trackID=1
m=video 0 RTP/AVP 97
a=rtpmap:97 H264/90000
a=fmtp:97 packetization-mode=1;profile-level-id=42C01E;sprop-parameter-sets=Z0LAHtkDxWhAAAADAEAAAAwDxYuS,aMuMsg==
a=cliprect:0,0,160,240
a=framesize:97 240-160
a=framerate:24.0
a=control:trackID=2
*/

struct SDPInfo{
  SDPInfo(const std::string& data);
  struct AudioTrack{
    Utils::AudioCodec codec;
    int rtp_type;
    std::string track_id;
  };

  struct VideoTrack{
    Utils::VideoCodec codec;
    int rtp_type;
    std::string track_id;
  };

  inline const std::string& get_audio_url() const{
    return base_url + audio_track.track_id;
  }

  inline const std::string& get_video_url() const{
    return base_url + video_track.track_id;
  }

  inline const std::string& get_session() const{
    return session;
  }

  private:
    std::string base_url;
    std::string session;
    std::string str;
    AudioTrack audio_track;
    VideoTrack video_track;

};

#endif
