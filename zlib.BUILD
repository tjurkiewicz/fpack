cc_library(
  name="zlib",
  srcs=["adler32.c", "crc32.c", "deflate.c", "infback.c", "inffast.c",
    "inflate.c", "inftrees.c", "trees.c", "zutil.c", "compress.c", "uncompr.c",
    "gzclose.c", "gzlib.c", "gzread.c", "gzwrite.c"],
  hdrs=glob(["*.h"]),
  includes=["."],
  defines=["_LARGEFILE64_SOURCE=1", "HAVE_HIDDEN"],
  visibility=["//visibility:public",],
)

