cmake_minimum_required(VERSION 3.10)

# specify the compiler
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_MAKE_PROGRAM make)

# set the project name
project(Tutorial VERSION 1.0)

# configure a header file to pass the version number to the source code
configure_file(TutorialConfig.h.in TutorialConfig.h)

target_include_directories(Tutorial PUBLIC
	                   "${PROJECT_BINARY_DIR}"
	                  )

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# add the executable
add_executable(Tutorial tutorial.cxx)
