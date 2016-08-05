// Copyright (c) 2016 Tomasz Jurkiewicz.

#include "exception.h"
#include <exception>

namespace multipack {
ArchiveException::ArchiveException(const std::string& msg):
  msg_(msg) {}

const char* ArchiveException::what() const noexcept {
  return msg_.c_str();
}
}  // namespace multipack

