/* Duck Programming Language SDL Bindings */
#ifndef _DUCK_SDLLIB_H
#define _DUCK_SDLLIB_H

#include "interpreter.h"

void BindSDL();
void SetupGL(int SCR_WIDTH, int SCR_HEIGHT);

int MakeWindow(int argument_count);
int EventLoop(int argument_count);
int PageFlip(int argument_count);
int ClearScreen(int argument_count);
int StillRunning(int argument_count);
int WaitKey(int argument_count);
int Quit(int argument_count);

int GlLoadIdentity(int argument_count);
int GlTranslatef(int argument_count);
int GlRotatef(int argument_count);
int GlScalef(int argument_count);
int GlBegin(int argument_count);
int GlEnd(int argument_count);
int GlColor3f(int argument_count);
int GlVertex3f(int argument_count);
int GlNormal3f(int argument_count);

#endif // _DUCK_SDLLIB_H

