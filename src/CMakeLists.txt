cmake_minimum_required(VERSION 2.8)

include(FindSDL)
include(FindOpenGL)

# duck
add_executable(duck
  ../duck/main.c
  ../duck/interpreter.c
  ../duck/arithmetic.c
  ../duck/lexer.c
  ../duck/parser.c
  ../duck/grammar.c
  ../duck/duck.c
  ../duck/tables.c
  ../duck/types.c
  ../duck/memory.c
  ../duck/garbage.c
  ../duck/lib/library.c
  ../duck/lib/stdduck.c
  ../duck/lib/dmath.c
  ../duck/lib/drand.c
)

# gduck
add_executable(gduck
  ../duck/main.c
  ../duck/interpreter.c
  ../duck/arithmetic.c
  ../duck/lexer.c
  ../duck/parser.c
  ../duck/grammar.c
  ../duck/duck.c
  ../duck/tables.c
  ../duck/types.c
  ../duck/memory.c
  ../duck/garbage.c
  ../duck/lib/library.c
  ../duck/lib/stdduck.c
  ../duck/lib/SDLlib.c
  ../duck/lib/dmath.c
  ../duck/lib/drand.c
)

#test
add_executable(unittest
  ../duck/test/unittest.c
  ../duck/interpreter.c
  ../duck/arithmetic.c
  ../duck/lexer.c
  ../duck/parser.c
  ../duck/grammar.c
  ../duck/duck.c
  ../duck/tables.c
  ../duck/types.c
  ../duck/memory.c
  ../duck/garbage.c
  ../duck/lib/library.c
  ../duck/lib/stdduck.c
  ../duck/lib/dmath.c
  ../duck/lib/drand.c
)

include_directories(../duck)

SET_TARGET_PROPERTIES(duck PROPERTIES COMPILE_FLAGS "-O2 ")
TARGET_LINK_LIBRARIES(duck -lm -lrt)
SET_TARGET_PROPERTIES(gduck PROPERTIES COMPILE_FLAGS "-O2 -D_GDUCK -D_LIB_SDL")
TARGET_LINK_LIBRARIES(gduck ${SDL_LIBRARY} ${OPENGL_LIBRARY} -lm -lrt)
SET_TARGET_PROPERTIES(unittest PROPERTIES COMPILE_FLAGS "-O2 -D_UNITTEST -D_MEM_TRACKING")
TARGET_LINK_LIBRARIES(unittest -lm -lrt)
