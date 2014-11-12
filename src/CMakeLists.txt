cmake_minimum_required(VERSION 3.0)

include(FindSDL)
include(FindOpenGL)

# duck
add_executable(duck
  interpreter.c
  lexer.c
  parser.c
  grammar.c
  duck.c
  tables.c
  stdduck.c
)

# gduck
add_executable(gduck
  sdllib.c
  interpreter.c
  lexer.c
  parser.c
  grammar.c
  duck.c
  tables.c
  stdduck.c
)

SET_TARGET_PROPERTIES(gduck PROPERTIES COMPILE_FLAGS "-DFLAG_GDUCK")
TARGET_LINK_LIBRARIES(gduck ${SDL_LIBRARY} ${OPENGL_LIBRARY})

