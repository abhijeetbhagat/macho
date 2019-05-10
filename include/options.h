#ifndef _OPTIONS_H_
#define _OPTIONS_H_

struct Options : IRequest{
  Options(const IConnection& conn){
    _payload = "OPTIONS " + conn.get_url() + " RTSP/" + conn.get_version() + ".0\r\nCSeq: " + conn.get_seq() + "\r\n\r\n");
  }

  private:
    std::string& _payload;
}

#endif
