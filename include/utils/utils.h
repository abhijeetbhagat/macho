#ifndef _UTILS_H_
#define _UTILS_H_

#include <string>

struct Utils {
  enum AudioCodec { MPEG4 };

  enum VideoCodec { H264 };

  static bool parse_url(const std::string &url, std::string &ip,
                        uint16_t &port);
};

#endif
