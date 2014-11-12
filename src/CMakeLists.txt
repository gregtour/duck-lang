cmake_minimum_required(VERSION 3.0)

include(FindSDL)
include(FindOpenGL)

add_subdirectory(parser)

add_custom_command(
  OUTPUT  duck.c
  COMMAND mkdir -p parser/output
  COMMAND cd parser && echo "" | ../../bin/lrparser 
  COMMAND cp parser/output/duck_syntax.c ./duck.c
  COMMAND cp parser/output/duck_syntax.h ./duck.h
  DEPENDS lrparser
)

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

