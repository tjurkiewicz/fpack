// Copyright (c) 2016 Tomasz Jurkiewicz.

#include <iostream>
#include "multipack/archive.h"

int main(int argc, char ** argv) {
  multipack::ArchiveReader reader(argv[0]);

  for (auto it=reader.GetMetadata().file().begin();
         it != reader.GetMetadata().file().end(); it++) {
    std::cerr << it->file_name() << "\n";
  }


  return 0;
}
