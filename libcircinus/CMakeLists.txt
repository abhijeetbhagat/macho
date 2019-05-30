cmake_minimum_required(VERSION 3.5.1)
project(circinus)
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")
add_library(circinus SHARED
  src/poller.cpp
  src/epoller.cpp
  )


