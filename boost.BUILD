
filegroup(
  name="boost-headers",
  srcs=glob(["boost/**/*.hpp", "boost/**/*.h", "boost/**/*.ipp"]),
)

cc_library(
  name="system",
  srcs=glob(["libs/system/src/*.cpp"]),
  hdrs=[":boost-headers"],
  includes=["."],
  visibility=["//visibility:public"],
)

cc_library(
  name="filesystem",
  srcs=glob(["libs/filesystem/src/*.cpp"]),
  hdrs=[":boost-headers"],
  includes=["."],
  visibility=["//visibility:public"],
  deps=[":system"], 
)


cc_library(
  name="program_options",
  srcs=glob(["libs/program_options/src/*.cpp"]),
  hdrs=[":boost-headers"],
  includes=["."],
  visibility=["//visibility:public"],
)

cc_library(
  name="iostreams",
  srcs=glob(["libs/iostreams/src/*.cpp"]),
  hdrs=[":boost-headers"],
  includes=["."],
  visibility=["//visibility:public"],
  deps=["@zlib//:zlib", "@bz2//:bz2"],
)

