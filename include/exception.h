// Copyright (c) 2016 Tomasz Jurkiewicz.

#ifndef INCLUDE_EXCEPTION_H_
#define INCLUDE_EXCEPTION_H_

#include <exception>
#include <string>

namespace fpack {
class ArchiveException: public std::exception {
 public:
  explicit ArchiveException(const std::string& msg);
  virtual const char* what() const noexcept;

 private:
  std::string msg_;
};
};  // namespace fpack

#endif  // INCLUDE_EXCEPTION_H_

