#ifndef _EPOLLER_H
#define _EPOLLER_H

#include "AbstractIOMuxer.h"
#include <sys/epoll.h>
#include <memory>
// NOTE: The inspiration for the design of this class came from the Tango
// library written in D.
class EPoller : public AbstractIOMuxer{
public:
  EPoller();
  ~EPoller() {}
  void open(uint32_t size) = 0;
  void close() = 0;
  void subscribe(int fd, Events event) = 0;
  void unsubscribe(int fd) = 0;
  int wait() { return wait(std::chrono::milliseconds::max()); }
  int wait(const std::chrono::milliseconds &) = 0;
  std::vector<int> ready_set();

private:
  int _epfd, _events_cnt;
  std::unique_ptr<epoll_event[]> _events;
};

#endif
