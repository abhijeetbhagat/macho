#include "../include/RTSPConnection.h"
#include "../include/requests/options.h"
#include "../include/requests/describe.h"
#include "../include/gsl-lite.hpp"
#include <vector>

int main(){
  RTSPConnection conn{"rtsp://184.72.239.149/vod/mp4:BigBuckBunny_175k.mov"};
  //auto options = Request<Options>{};
  Options options{conn};
  conn.send(options);

  std::vector<char> output;
  conn.receive(output);

  Describe describe{conn};
  conn.send(describe);
  output.clear();
  conn.receive(output);
}
