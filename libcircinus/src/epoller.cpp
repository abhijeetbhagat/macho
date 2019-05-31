#include "../include/epoller.h"
#include <chrono>
#include <iostream>

EPoller::EPoller() : _epfd(-1), _events(nullptr) {}

void EPoller::open(uint32_t size){
  _events.reset(new epoll_event[size]);
  _epfd = epoll_create(size);
  if (_epfd < 0) {
    //TODO log error
  }
}

void EPoller::close(){
}

void EPoller::subscribe(int fd, Events event){
  epoll_event ev;
  ev.events = static_cast<short int>(event);
  ev.data.fd = fd;
  if (epoll_ctl(_epfd, EPOLL_CTL_ADD, fd, &ev) < 0) {
    //TODO log error
  }
}

void EPoller::unsubscribe(){
}

int EPoller::wait(const std::chrono::milliseconds &duration){
  int timeout = duration.count();
  int rc = 0;
  while (true) {
    rc = epoll_wait(_epfd, _events.get(), 2, timeout);
    if (rc < 0) {
      std::cout << "Error with epol\n";
    } else {
      break;
    }
  }
  return rc;
}

