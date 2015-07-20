/*
    Export functions from user libraries into the Duck namespace
    Calls to import should merge a packages scope with the global
    namespace.
*/

#include "library.h"

void BindAdditionalLibraries() 
{
#ifdef _LIB_SDL
    //printf("Binding SDL...\n");
    BindSDL();
#endif
}

