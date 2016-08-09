// Copyright (c) 2016 Tomasz Jurkiewicz.

#ifndef INCLUDE_MULTIPACK_ARCHIVE_H_
#define INCLUDE_MULTIPACK_ARCHIVE_H_

#include <fstream>
#include <ostream>
#include <string>

#include "boost/filesystem.hpp"
#include "boost/iterator/iterator_facade.hpp"

#include "proto/archive.pb.h"

using boost::filesystem::directory_entry;
using boost::filesystem::recursive_directory_iterator;

namespace multipack {

std::ofstream ofstream(const std::string& filename);

class PackageDirectoryIterator: 
  public boost::iterator_facade<PackageDirectoryIterator, 
    directory_entry, boost::forward_traversal_tag> {
 public:
  PackageDirectoryIterator();
  explicit PackageDirectoryIterator(const boost::filesystem::path&);

 private:
  static recursive_directory_iterator END;
  friend class boost::iterator_core_access;
  recursive_directory_iterator it_;
  bool IsValid() const;
  void increment();
  bool equal(PackageDirectoryIterator const& other) const;
  directory_entry& dereference() const;
};

class PackageDirectory {
 public:
  explicit PackageDirectory(const std::string& packagePath);
  typedef PackageDirectoryIterator Iterator;

  Iterator begin() const;
  Iterator end() const;

 private:
  std::string path_;
};

class ArchiveReader {
 public:
  explicit ArchiveReader(const std::string& archivePath);
  const Metadata& GetMetadata() const;
 private:
  std::string archivePath_;
  Metadata metadata_;
};

class ArchiveWriter {
 public:
  typedef PackageDirectory PDir;
  explicit ArchiveWriter(const std::string& executablePath);
  void Build(const PDir& package);
 private:
  std::string executablePath_;

  void PrepareBuffer(const PDir& package, std::stringstream* buffer,
    Metadata* metadata);
  void FlushBuffer(std::stringstream* buffer, Metadata* metadata);
  void FlushMetadata(const Metadata& metadata);
};

}  // namespace multipack

#endif  // INCLUDE_MULTIPACK_ARCHIVE_H_

