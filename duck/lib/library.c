/*
    Export functions from user libraries into the Duck NameSpace
    Calls to import should merge a packages scope with the global
    NameSpace.
*/

#include "library.h"

void BindAdditionalLibraries() 
{
#ifdef _LIB_SDL
    //printf("Binding SDL...\n");
    BindSDL();
#endif
}

