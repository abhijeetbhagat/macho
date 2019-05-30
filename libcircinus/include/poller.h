#ifndef _POLLER_H_
#define _POLLER_H_

#include "../include/AbstractIOMuxer.h"
#include <memory>
#include <sys/poll.h>
#include <vector>

class Poller : public AbstractIOMuxer {
public:
  Poller();
  ~Poller();
  void open(uint32_t size);
  void close();
  void subscribe(int fd, Events event);
  void unsubscribe();
  int wait(const std::chrono::milliseconds &);
  std::vector<int> ready_set();

private:
  std::unique_ptr<pollfd[]> _pollfds;
  uint32_t _count;
};

#endif
