cc_library(
  name="bz2",
  srcs=["blocksort.c", "huffman.c", "crctable.c", "randtable.c", 
        "compress.c", "decompress.c", "bzlib.c"],
  hdrs=["bzlib.h", "bzlib_private.h",],
  defines=["_FILE_OFFSET_BITS=64",],
  includes=["."],
  visibility=["//visibility:public"],
)
