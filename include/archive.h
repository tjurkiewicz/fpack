// Copyright (c) 2016 Tomasz Jurkiewicz.

#ifndef INCLUDE_ARCHIVE_H_
#define INCLUDE_ARCHIVE_H_

#include <cstdint>
#include <string>

#include "proto/archive.pb.h"

namespace fpack {
class Archive {
 public:
  explicit Archive(const char* archivePath);

 private:
  std::string archivePath_;
  Metadata metadata_;
};
}  // namespace fpack

#endif  // INCLUDE_ARCHIVE_H_

