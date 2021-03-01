add_library(MathFunctions mysqrt.cxx)

#any one linking this libary with include "current src dir"
target_include_directories(MathFunctions
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} 
  )

#add install rules
install(TARGETS MathFunctions DESTINATION lib)
install(FILES MathFunctions.h DESTINATION include)


