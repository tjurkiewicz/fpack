// Copyright (c) 2016 Tomasz Jurkiewicz.

#include "archive.h"

#include <arpa/inet.h>

#include <cstdint>
#include <fstream>
#include <iostream>

#include "boost/filesystem.hpp"

#include "exception.h"
#include "proto/archive.pb.h"

using boost::filesystem::path;
using boost::filesystem::recursive_directory_iterator;

namespace fpack {

PackageDirectoryIterator::PackageDirectoryIterator():
 recursive_directory_iterator() {}

PackageDirectoryIterator::PackageDirectoryIterator(const path& path): 
  recursive_directory_iterator(path) {
}

PackageDirectory::PackageDirectory(const std::string& packagePath):
  path_(packagePath) {
}

PackageDirectoryIterator& PackageDirectoryIterator::operator++() {
  /* skip files here */
  recursive_directory_iterator::operator++();
  return *this;
}

PackageDirectory::Iterator PackageDirectory::begin() const {
  Iterator it(path_);
  return it;
}

PackageDirectory::Iterator PackageDirectory::end() const {
  Iterator it;
  return it;
}

Archive::Archive(const std::string& archivePath): path_(archivePath) {
  std::ifstream ifs(archivePath, std::ifstream::binary|std::ifstream::ate);

  if (!ifs) {
    throw ArchiveException("Could not open file for reading");
  }

  uint32_t metadataOffset;
  ifs.seekg(-sizeof(uint32_t), ifs.end);
  ifs.read(reinterpret_cast<char*>(&metadataOffset), sizeof(uint32_t));
  metadataOffset = ntohl(metadataOffset);

  ifs.seekg(metadataOffset, ifs.beg);
  metadata_.ParseFromIstream(&ifs);
}

void Archive::BuildArchive(const std::string& executablePath, \
    const PackageDirectory& package, const char* entryPath) {
  fpack::Metadata metadata;


  for(PackageDirectory::Iterator it=package.begin(); it!=package.end(); ++it) {
    std::cout << it->path().string() << "\n";
  }

  std::ofstream ofs(executablePath,
    std::ofstream::out|std::ofstream::app|std::ofstream::binary);

  if (!ofs) {
    throw fpack::ArchiveException("Could not open file for writing");
  }

  uint32_t metadataOffset = htonl(ofs.tellp());

  metadata.SerializeToOstream(&ofs);

  ofs.write(reinterpret_cast<const char*>(&metadataOffset),
    sizeof(metadataOffset));
  ofs.close();
}
}  // namespace fpack

