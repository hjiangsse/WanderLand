add_library(reflib
  reflib/reflib_a.cxx
  reflib/reflib_b.cxx
  reflib/reflib_c.cxx)

#any one linking this libary with include "current src dir"
target_include_directories(reflib
  INTERFACE "${PROJECT_SOURCE_DIR}/include/reflib"
  )
