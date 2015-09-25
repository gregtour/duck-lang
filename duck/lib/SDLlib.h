/* Duck Programming Language SDL Bindings */
#ifndef _DUCK_SDLLIB_H
#define _DUCK_SDLLIB_H

#include "interpreter.h"

void BindSDL();
void SetupGL(int SCR_WIDTH, int SCR_HEIGHT);
void PrintObject(CLOSURE*);

int MakeWindow(int argument_count, void* data);
int EventLoop(int argument_count, void* data);
int PageFlip(int argument_count, void* data);
int ClearScreen(int argument_count, void* data);
int StillRunning(int argument_count, void* data);
int WaitKey(int argument_count, void* data);
int Quit(int argument_count, void* data);

int GlLoadIdentity(int argument_count, void* data);
int GlTranslatef(int argument_count, void* data);
int GlRotatef(int argument_count, void* data);
int GlScalef(int argument_count, void* data);
int GlBegin(int argument_count, void* data);
int GlEnd(int argument_count, void* data);
int GlColor3f(int argument_count, void* data);
int GlVertex3f(int argument_count, void* data);
int GlNormal3f(int argument_count, void* data);

#endif // _DUCK_SDLLIB_H

