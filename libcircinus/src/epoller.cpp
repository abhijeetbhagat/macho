#include "../include/epoller.h"
#include <chrono>

EPoller::EPoller() : _epollfd(-1), _events(nullptr) {}

void EPoller::open(uint32_t size){
  _events.reset(new epoll_event[size]);
}

void EPoller::close(){
}

void EPoller::subscribe(int fd, Events event){
}

void EPoller::unsubscribe(){
}

int EPoller::wait(const std::chrono::milliseconds &duration){
}

