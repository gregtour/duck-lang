cmake_minimum_required(VERSION 2.8)

# https://code.google.com/p/googletest/
find_package(GTest)
include_directories(${GTEST_INCLUDE_DIRS})

# duck
include_directories(../duck)

add_executable(run_memory_tests
  ../duck/memory.c
  duck/memory_test.cpp
)

target_link_libraries(run_memory_tests
  ${GTEST_BOTH_LIBRARIES}
  -pthread
)

