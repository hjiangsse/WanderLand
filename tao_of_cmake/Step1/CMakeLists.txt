cmake_minimum_required(VERSION 3.10)

project(Tutorial VERSION 1.1)

option(USE_MYMATH "Use tutorial provided math implementation" ON)

#cmake use TutorialConfig.h.in to construct TutorialConfig.h
configure_file(TutorialConfig.h.in TutorialConfig.h)

#specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(USE_MYMATH)
    #add the MathFunctions library
    add_subdirectory(MathFunctions)
    list(APPEND EXTRA_LIBS MathFunctions)
    message(STATUS "project source dir: ${PROJECT_SOURCE_DIR}")
    #list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/MathFunctions")
endif()

add_executable(Tutorial tutorial.cxx)
target_link_libraries(Tutorial PUBLIC ${EXTRA_LIBS})

target_include_directories(Tutorial PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          #"${EXTRA_INCLUDES}"
                          )

#install executable file and source file
install(TARGETS Tutorial DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h"
  DESTINATION include
  )
