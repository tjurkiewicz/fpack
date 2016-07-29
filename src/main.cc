// Copyright (c) 2016 Tomasz Jurkiewicz.

#include <arpa/inet.h>

#include <iostream>
#include <fstream>

#include "archive.h"
#include "exception.h"
#include "proto/archive.pb.h"

int main(int argc, char** argv) {
  fpack::Metadata metadata;

  metadata.set_entry_path("abcd");
  metadata.set_data_offset(10);

  std::ofstream ofs(argv[1],
    std::ofstream::out|std::ofstream::app|std::ofstream::binary);

  if (!ofs) {
    throw fpack::ArchiveException();
  }

  std::streampos pos = ofs.tellp();
  metadata.SerializeToOstream(&ofs);

  uint32_t size = htonl(ofs.tellp() - pos);
  ofs.write(reinterpret_cast<const char*>(&size), sizeof(size));

  ofs.close();

  return 0;
}

