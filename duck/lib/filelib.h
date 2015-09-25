/* Duck Programming Language Standard Library */
#ifndef _FILELIB_H
#define _FILELIB_H

#include "interpreter.h"

void BindFileLibrary();

int FileOpen(int argc, void* data);
int FileClose(int argc, void* data);
int FileRead(int argc, void* data);
int FileWrite(int argc, void* data);

#endif // _FILELIB_H

