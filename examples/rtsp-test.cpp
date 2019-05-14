#include "../include/RTSPConnection.h"
#include "../include/requests/options.h"
#include "../include/requests/describe.h"
#include "../include/gsl-lite.hpp"
#include "../include/sdp_info.h"
//#include <vector>

int main(){
  RTSPConnection conn{"rtsp://184.72.239.149/vod/mp4:BigBuckBunny_175k.mov"};
  //auto options = Request<Options>{};
  Options options{conn};
  conn.send(options);

  //std::vector<char> output;
  conn.receive<std::string>(/*output*/);

  Describe describe{conn};
  conn.send(describe);
  //output.clear(); 
  const SDPInfo sdp = conn.receive<SDPInfo>();
  
}
