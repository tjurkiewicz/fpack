// Copyright (c) 2016 Tomasz Jurkiewicz.

#ifndef INCLUDE_MULTIPACK_EXCEPTION_H_
#define INCLUDE_MULTIPACK_EXCEPTION_H_

#include <exception>
#include <string>

namespace multipack {
class ArchiveException: public std::exception {
 public:
  explicit ArchiveException(const std::string& msg);
  virtual const char* what() const noexcept;

 private:
  std::string msg_;
};
};  // namespace multipack

#endif  // INCLUDE_MULTIPACK_EXCEPTION_H_

