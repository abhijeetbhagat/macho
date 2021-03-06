#include "../include/poller.h"
#include <iostream>

Poller::Poller() : _count(0), _pollfds(nullptr) {}

Poller::~Poller() {}

void Poller::open(uint32_t size) {
  if (_pollfds == nullptr)
    _pollfds.reset(new pollfd[size]);
}

void Poller::close() {}

void Poller::subscribe(int fd, Events event) {
  _pollfds[_count].fd = fd;
  _pollfds[_count].events = static_cast<short int>(event);
  _count++;
}

void Poller::unsubscribe(int fd) {
  // linear search to find the right index of 'fd'
  // fd's wont be stored sorted
  int fd_i = -1;
  for (int i = 0; i < _count; i++) {
    if (_pollfds[i].fd == fd) {
      fd_i = i;
      break;
    }
  }
  if (fd_i == -1) {
    std::cout << "fd not found\n";
    return;
  }

  _pollfds[fd_i] = _pollfds[_count - 1];
  _count--;
}

int Poller::wait(const std::chrono::milliseconds &duration) {
  int timeout = duration.count();
  // TODO call poll in an infinite loop since poll can be interrupted by a
  // signal
  // before the polled fds are ready and will return with an error; hence, we
  // need
  // to restart polling.

  int rc = 0;
  while (true) {
    rc = poll(_pollfds.get(), _count, timeout);
    if (rc < 0) {
      std::cout << "Error with poll\n";
    } else {
      break;
    }
  }
  return rc;
}

std::vector<int> Poller::ready_set() {
  std::vector<int> set;

  for (uint32_t i = 0; i < _count; i++) {
    if (_pollfds[i].revents & _pollfds[i].events) {
      set.push_back(_pollfds[i].fd);
    }
  }
  return set;
}
