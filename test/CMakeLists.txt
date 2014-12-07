cmake_minimum_required(VERSION 2.8)

# https://code.google.com/p/googletest/
find_package(GTest)
include_directories(${GTEST_INCLUDE_DIRS})

# gduck deps
include(FindSDL)
include(FindOpenGL)

# gcov
if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ftest-coverage")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftest-coverage")
endif()

# duck headers
include_directories(../duck)

# libduck_core.so
FILE(GLOB DUCK_CORE ../duck/*.c)
add_library(duck_core SHARED ${DUCK_CORE})

# libduck.so
FILE(GLOB LIB_DUCK ../duck/lib/*.c)
add_library(duck SHARED ${LIB_DUCK})
target_link_libraries(duck
  ${SDL_LIBRARY}
  ${OPENGL_LIBRARY}
  -lm
)

# run_test
FILE(GLOB TEST_ALL ./**/*_test.cpp)
add_executable(run_test ${TEST_ALL})
target_link_libraries(run_test
  ${GTEST_BOTH_LIBRARIES}
  -pthread
  duck_core
  duck
)

# gcov
if(CMAKE_COMPILER_IS_GNUCXX)
  add_library(gcov SHARED IMPORTED)
endif()
