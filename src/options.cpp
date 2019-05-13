#include "../include/requests/options.h"
#include "../third_party/include/spdlog/spdlog.h"

Options::Options(const IConnection& conn){
   _payload = "OPTIONS " + conn.get_url() + " RTSP/" + std::to_string(conn.get_version()) + ".0\r\nCSeq: " + std::to_string(conn.get_seq()) + "\r\n\r\n";
}

