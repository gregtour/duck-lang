cmake_minimum_required(VERSION 2.8)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )

# source directory
add_subdirectory(src)

install_programs(/bin # dest
  bin/duck
  bin/gduck
  bin/unittest
)
