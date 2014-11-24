cmake_minimum_required(VERSION 2.8)

# https://code.google.com/p/googletest/
find_package(GTest)
include_directories(${GTEST_INCLUDE_DIRS})

# gcov
if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ftest-coverage")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftest-coverage")
endif()

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

# gcov
if(CMAKE_COMPILER_IS_GNUCXX)
  add_library(gcov SHARED IMPORTED)
endif()
