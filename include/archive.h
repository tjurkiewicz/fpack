// Copyright (c) 2016 Tomasz Jurkiewicz.

#ifndef INCLUDE_ARCHIVE_H_
#define INCLUDE_ARCHIVE_H_

#include <cstddef>
#include <cstdint>
#include <iterator>
#include <type_traits>
#include <fstream>
#include <string>

#include "boost/filesystem.hpp"

#include "proto/archive.pb.h"

using boost::filesystem::directory_entry;
using boost::filesystem::path;
using boost::filesystem::recursive_directory_iterator;

namespace multipack {

class PackageDirectoryIterator: public recursive_directory_iterator {
 public:
  PackageDirectoryIterator();
  explicit PackageDirectoryIterator(const path& path);
  PackageDirectoryIterator& operator++();
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

class Archive {
 public:
  explicit Archive(const std::string& archivePath);

  static void BuildArchive(const std::string& executablePath, \
    const PackageDirectory& package, const char* entryPath);

 private:
  std::string path_;
  Metadata metadata_;
};
}  // namespace multipack

#endif  // INCLUDE_ARCHIVE_H_

