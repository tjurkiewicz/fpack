// Copyright (c) 2016 Tomasz Jurkiewicz.

#include "archive.h"

#include <arpa/inet.h>

#include <cstdint>
#include <fstream>
#include <iostream>

#include "exception.h"
#include "proto/archive.pb.h"

namespace fpack {
Archive::Archive(const char* archivePath): archivePath_(archivePath) {
  std::ifstream ifs(archivePath, std::ifstream::binary|std::ifstream::ate);

  if (!ifs) {
    throw ArchiveException();
  }

  uint32_t metadataOffset;
  ifs.seekg(-sizeof(uint32_t), ifs.end);
  ifs.read(reinterpret_cast<char*>(&metadataOffset), sizeof(uint32_t));
  metadataOffset = ntohl(metadataOffset);

  ifs.seekg(-(sizeof(uint32_t)+metadataOffset), ifs.end);
  metadata_.ParseFromIstream(&ifs);

  std::cout << metadata_.data_offset() << " " << metadata_.entry_path();
}
}  // namespace fpack

