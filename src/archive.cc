// Copyright (c) 2016 Tomasz Jurkiewicz.

#include "multipack/archive.h"

#include <arpa/inet.h>

#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>

#include "boost/filesystem.hpp"
#include "boost/iostreams/copy.hpp"
#include "boost/iostreams/filtering_stream.hpp"
#include "boost/iostreams/filter/gzip.hpp"
#include "boost/iostreams/filter/bzip2.hpp"

#include "multipack/exception.h"
#include "proto/archive.pb.h"

using boost::filesystem::file_size;
using boost::filesystem::is_regular_file;
using boost::filesystem::recursive_directory_iterator;

namespace multipack {

std::ofstream ofstream(const std::string& path) {
  std::ofstream ofs(path,
    std::ofstream::out|std::ofstream::app|std::ofstream::binary);

  if (!ofs) {
    throw multipack::ArchiveException("Could not open file for writing.");
  }
  return ofs;
}

recursive_directory_iterator PackageDirectoryIterator::END = \
  recursive_directory_iterator();

PackageDirectoryIterator::PackageDirectoryIterator() {}

PackageDirectoryIterator::PackageDirectoryIterator(
  const boost::filesystem::path& p):
  it_(p) {
  if (!IsValid()) {
    increment();
  }
}

void PackageDirectoryIterator::increment() {
  do {
    it_++;
  } while (!IsValid());
}

bool PackageDirectoryIterator::IsValid() const {
  return it_ == END || is_regular_file(it_->path());
}

bool PackageDirectoryIterator::equal(
  PackageDirectoryIterator const& other) const {
  return it_ == other.it_;
}

directory_entry& PackageDirectoryIterator::dereference() const {
  return *it_;
}

PackageDirectory::Iterator PackageDirectory::begin() const {
  Iterator it(path_);
  return it;
}

PackageDirectory::PackageDirectory(const std::string& packagePath):
  path_(packagePath) {
}

PackageDirectory::Iterator PackageDirectory::end() const {
  Iterator it;
  return it;
}

ArchiveReader::ArchiveReader(const std::string& archivePath):
  archivePath_(archivePath) {
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

const Metadata& ArchiveReader::GetMetadata() const {
  return metadata_;
}

ArchiveWriter::ArchiveWriter(const std::string& executablePath):
  executablePath_(executablePath) {}

void ArchiveWriter::Build(const PDir& package) {
  multipack::Metadata metadata;
  std::stringstream buffer;

  PrepareBuffer(package, &buffer, &metadata);
  FlushBuffer(&buffer, &metadata);
  FlushMetadata(metadata);
}


void ArchiveWriter::PrepareBuffer(const PDir& package,
  std::stringstream* buffer, Metadata* metadata) {
  for (PDir::Iterator it=package.begin(); it != package.end(); ++it) {
    File* file = metadata->add_file();
    file->set_offset(buffer->tellp());
    file->set_file_name(it->path().string());

    std::ifstream ifs(it->path().string(), std::ifstream::binary);
    if (!ifs) {
      throw ArchiveException("Could not open file for reading.");
    }

    boost::iostreams::copy(ifs, *buffer);
  }
}

void ArchiveWriter::FlushBuffer(
  std::stringstream* buffer, Metadata* metadata) {
  std::ofstream ofs = ofstream(executablePath_);
  metadata->set_file_offset(ofs.tellp());

  boost::iostreams::filtering_ostream stream;
  stream.push(boost::iostreams::bzip2_compressor());
  stream.push(ofs);

  buffer->seekp(0);
  boost::iostreams::copy(*buffer, stream);
}

void ArchiveWriter::FlushMetadata(const Metadata& metadata) {
  std::ofstream ofs = ofstream(executablePath_);

  uint32_t metadataOffset = htonl(ofs.tellp());

  metadata.SerializeToOstream(&ofs);

  ofs.write(reinterpret_cast<const char*>(&metadataOffset),
    sizeof(metadataOffset));
}

}  // namespace multipack

