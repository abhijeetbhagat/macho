#ifndef _ISERIALIZABLE_H_
#define _ISERIALIZABLE_H_

struct ISerializable{
  virtual gsl::span<gsl::byte> to_bytes() = 0;
}
#endif
