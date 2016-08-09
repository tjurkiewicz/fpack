load("@protobuf//:protobuf.bzl", "cc_proto_library")

cc_proto_library(
  name="archive.proto",
  srcs=["proto/archive.proto"],
  protoc="@protobuf//:protoc",
  default_runtime="@protobuf//:protobuf",
)

cc_library(
  name="archive",
  srcs=["src/archive.cc", "src/exception.cc",],
  hdrs=["include/multipack/archive.h", "include/multipack/exception.h",],
  includes=["include"],
  copts=["-g"],
  deps=[":archive.proto", "@boost//:iostreams", "@boost//:filesystem"],
)

cc_binary(
  name="exec",
  srcs=["src/exec.cc"],
  deps=[":archive"],
)

cc_binary(
  name="pack",
  srcs=["src/pack.cc",],
  includes=["include"],
  copts=["-g"],
  deps=["@boost//:program_options", ":archive.proto", ":archive"],
)

sh_test(
  name="lint",
  srcs=["lint.sh"],
  data=["cpplint.py"] + glob(["include/**/*.h"]) + glob(["src/**/*.cc"]),
)

