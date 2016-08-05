// Copyright (c) 2016 Tomasz Jurkiewicz.

#include <cstdlib>
#include <iostream>

#include "boost/program_options.hpp"

#include "archive.h"

using boost::program_options::notify;
using boost::program_options::parse_command_line;
using boost::program_options::store;
using boost::program_options::value;

void check_options(const boost::program_options::variables_map& vm) {
  try {
    notify(vm);
  } catch(std::exception& ex) {
    std::cerr << ex.what() << "\n";
    exit(-1);
  }
}

int main(int argc, char** argv) {
  boost::program_options::options_description desc("Allowed options");
  boost::program_options::variables_map vm;

  std::string executablePath;
  std::string packagePath;

  desc.add_options()
  ("help,h", "print usage message")
  ("executable,e", value(&executablePath)->required(), "packfile executable")
  ("package,p", value(&packagePath)->required(), "packaging directory");

  store(parse_command_line(argc, argv, desc), vm);

  if (vm.count("help")) {
    std::cout << desc << "\n";
    return 0;
  }

  check_options(vm);

  multipack::PackageDirectory package(packagePath);
  multipack::Archive::BuildArchive(executablePath, package, "entry");
  return 0;
}

