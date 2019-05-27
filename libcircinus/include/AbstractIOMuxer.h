#ifndef _ABSTRACTIOMUXER_H_
#define _ABSTRACTIOMUXER_H_

#include <chrono>

enum class Events{
  Read,
  Write
};

//Class that represents abstraction over IO mux'ing
class AbstractIOMuxer{
  public:
    virtual ~AbstractIOMuxer(){}
    virtual void open(uint32_t size) = 0;
    virtual void close() = 0;
    virtual void subscribe(Events event) = 0;
    virtual void unsubscribe() = 0;
    virtual int wait(){
      return wait(std::chrono::milliseconds::max());
    }
    virtual int wait(const std::chrono::milliseconds&) = 0;
};

#endif