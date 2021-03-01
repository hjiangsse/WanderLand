cmake_minimum_required(VERSION 3.10)

project(Mini_Prject VERSION 1.0)

#specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#add the MathFunctions library
add_subdirectory("${PROJECT_SOURCE_DIR}/lib/")
list(APPEND EXTRA_LIBS reflib)

add_executable(test_a "${PROJECT_SOURCE_DIR}/src/app_generic/test_a.cxx")
target_link_libraries(test_a PUBLIC ${EXTRA_LIBS})

target_include_directories(test_a
  PUBLIC
  "${PROJECT_BINARY_DIR}"
  "${PROJECT_SOURCE_DIR}/include/reflib/"
  )
