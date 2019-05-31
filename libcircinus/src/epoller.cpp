#include "../include/epoller.h"
#include <chrono>
#include <iostream>
#include <vector>

EPoller::EPoller() : _epfd(-1), _events(nullptr), _events_cnt(0) {}

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
  while (true) {
    _events_cnt = epoll_wait(_epfd, _events.get(), 2, timeout);
    if (_events_cnt < 0) {
      std::cout << "Error with epol\n";
    } else {
      break;
    }
  }
  return _events_cnt;
}

std::vector<int> EPoller::ready_set() {
  std::vector<int> set;
  for (int i = 0; i < _events_cnt; i++) {
    set.push_back(i);
  }
  return set;
}
