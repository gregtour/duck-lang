cmake_minimum_required(VERSION 3.0)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )

# source directory
add_subdirectory(src)

install_programs(bin/ lrparser duck gduck)

