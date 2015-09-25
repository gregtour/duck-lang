/* Duck Programming Language SDL Bindings */

//#include <cstdio>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SDLlib.h"

#include "interpreter.h"

int game_is_running;

void SetupGL(int SCR_WIDTH, int SCR_HEIGHT)
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_CW);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, SCR_WIDTH, SCR_HEIGHT, 0, -1000.0f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void BindSDL()
{
    /* SDL NameSpace */
    VALUE duckSDL = LinkNamespace("SDL");
    VALUE makeWindow = CreateFunction(MakeWindow);
    AddParameter(makeWindow, "width");
    AddParameter(makeWindow, "height");
    AddParameter(makeWindow, "name");
    AddParameter(makeWindow, "fullscreen");

    VALUE clearScreen = CreateFunction(ClearScreen);
    VALUE pageFlip = CreateFunction(PageFlip);
    VALUE eventLoop = CreateFunction(EventLoop);
    VALUE isRunning = CreateFunction(StillRunning);
    VALUE waitKey = CreateFunction(WaitKey);
    VALUE quit = CreateFunction(Quit);

    LinkFunction(duckSDL, "MakeWindow", makeWindow);
    LinkFunction(duckSDL, "flip", pageFlip);
    LinkFunction(duckSDL, "event", eventLoop);
    LinkFunction(duckSDL, "clearScreen", clearScreen);
    LinkFunction(duckSDL, "running", isRunning);
    LinkFunction(duckSDL, "waitkey", waitKey);
    LinkFunction(duckSDL, "quit", quit);

    /* OpenGL functions */
    VALUE dglLoadIdentity = CreateFunction(GlLoadIdentity);
    VALUE dglTranslatef = CreateFunction(GlTranslatef);
    AddParameter(dglTranslatef, "x");
    AddParameter(dglTranslatef, "y");
    AddParameter(dglTranslatef, "z");

    VALUE dglRotatef = CreateFunction(GlRotatef);
    AddParameter(dglRotatef, "deg");
    AddParameter(dglRotatef, "x");
    AddParameter(dglRotatef, "y");
    AddParameter(dglRotatef, "z");

    VALUE dglScalef = CreateFunction(GlScalef);
    AddParameter(dglScalef, "x");
    AddParameter(dglScalef, "y");
    AddParameter(dglScalef, "z");

    VALUE dglBegin = CreateFunction(GlBegin);
    AddParameter(dglBegin, "primitive");

    VALUE dglEnd = CreateFunction(GlEnd);
    VALUE dglColor3f = CreateFunction(GlColor3f);
    AddParameter(dglColor3f, "r");
    AddParameter(dglColor3f, "g");
    AddParameter(dglColor3f, "b");

    VALUE dglVertex3f = CreateFunction(GlVertex3f);
    AddParameter(dglVertex3f, "x");
    AddParameter(dglVertex3f, "y");
    AddParameter(dglVertex3f, "z");

    VALUE dglNormal3f = CreateFunction(GlNormal3f);
    AddParameter(dglNormal3f, "x");
    AddParameter(dglNormal3f, "y");
    AddParameter(dglNormal3f, "z");

    LinkConstPrimitive(duckSDL, "GL_TRIANGLES", GL_TRIANGLES);

    LinkFunction(duckSDL, "glLoadIdentity", dglLoadIdentity);
    LinkFunction(duckSDL, "glTranslatef", dglTranslatef);
    LinkFunction(duckSDL, "glRotatef", dglRotatef);
    LinkFunction(duckSDL, "glScalef", dglScalef);
    LinkFunction(duckSDL, "glBegin", dglBegin);
    LinkFunction(duckSDL, "glColor3f", dglColor3f);
    LinkFunction(duckSDL, "glVertex3f", dglVertex3f);
    LinkFunction(duckSDL, "glNormal3f", dglNormal3f);
    LinkFunction(duckSDL, "glEnd", dglEnd);
    return;
}

/* SDL Functions */

int MakeWindow(int argument_count, void* data)
{
    int error = 0;
    //if (argument_count != 3) return 1;

    int width, height;
    const char* szClassName;

    VALUE r_width = GetRecord("width", gCurrentContext);
    VALUE r_height = GetRecord("height", gCurrentContext);
    VALUE r_title = GetRecord("name", gCurrentContext);
    VALUE r_fullscreen = GetRecord("fullscreen", gCurrentContext);

    width = TypeInt(r_width);
    height = TypeInt(r_height);
    szClassName = (r_title.type == VAL_STRING) ? r_title.data.string : "Untitled";

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE);
    SDL_ShowCursor(0);
    SDL_SetVideoMode(width, height, 24, SDL_OPENGL |
        SDL_GL_DOUBLEBUFFER |
        SDL_HWPALETTE |
        SDL_HWSURFACE |
        SDL_HWACCEL |
        (TypeInt(r_fullscreen) ? SDL_FULLSCREEN : 0)
/* | SDL_FULLSCREEN */
        );
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_WM_SetCaption(szClassName, szClassName);
    SetupGL(width, height);

    game_is_running = 1;

    gLastExpression.type = VAL_NIL;
    gLastExpression.data.primitive = 0;
    return error;
}

int ClearScreen(int argument_count, void* data)
{
    int error = 0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glLoadIdentity();

    gLastExpression.type = VAL_NIL;
    gLastExpression.data.primitive = 0;
    return error;
}

int PageFlip(int argument_count, void* data)
{
    int error = 0;

    glFinish();
    SDL_GL_SwapBuffers();

    gLastExpression.type = VAL_NIL;
    gLastExpression.data.primitive = 0;
    return error;
}

int EventLoop(int argument_count, void* data)
{
	SDL_Event event;	
    while (SDL_PollEvent(&event)) 
    {
        if (event.type == SDL_QUIT) 
        {
            game_is_running = 0;
		} else if ((event.type == SDL_KEYDOWN) 
                &&  event.key.keysym.sym == 27) 
        {
            game_is_running = 0;
        }
    }
    
    gLastExpression.type = VAL_NIL;
    gLastExpression.data.primitive = 0;
    return 0;
}

int StillRunning(int argument_count, void* data)
{
    gLastExpression.type = VAL_PRIMITIVE;
    gLastExpression.data.primitive = game_is_running;
    return 0;
}

int WaitKey(int argument_count, void* data)
{
	SDL_Event event;
    gLastExpression.type = VAL_NIL;

    for (;;) {
        while (SDL_PollEvent(&event)) 
        {
            if (event.type == SDL_QUIT) 
            {
                return 0;
		    } 
            else if (event.type == SDL_KEYDOWN)
            {
                return 0;
            }
        }
    }
    
    gLastExpression.type = VAL_NIL;
    gLastExpression.data.primitive = 0;
    return 0;
}

int Quit(int argument_count, void* data)
{
    SDL_Quit();
    gLastExpression.type = VAL_NIL;
    gLastExpression.data.primitive = 0;
    return 0;
}

/* OpenGL Functions */

int GlLoadIdentity(int argument_count, void* data)
{
    int error = 0;

    glLoadIdentity();

    gLastExpression.type = VAL_NIL;
    gLastExpression.data.primitive = 0;
    return error;
}

int GlTranslatef(int argument_count, void* data)
{
    int error = 0;

    VALUE X = GetRecord("x", gCurrentContext);
    VALUE Y = GetRecord("y", gCurrentContext);
    VALUE Z = GetRecord("z", gCurrentContext);

    glTranslatef(TypeFloat(X), 
                 TypeFloat(Y), 
                 TypeFloat(Z));

    gLastExpression.type = VAL_NIL;
    gLastExpression.data.primitive = 0;
    return error;
}

int GlRotatef(int argument_count, void* data)
{
    int error = 0;

    VALUE DEG = GetRecord("deg", gCurrentContext);
    VALUE X = GetRecord("x", gCurrentContext);
    VALUE Y = GetRecord("y", gCurrentContext);
    VALUE Z = GetRecord("z", gCurrentContext);

    glRotatef(TypeFloat(DEG),
              TypeFloat(X), 
              TypeFloat(Y), 
              TypeFloat(Z));

    gLastExpression.type = VAL_NIL;
    gLastExpression.data.primitive = 0;
    return error;
}

int GlScalef(int argument_count, void* data)
{
    int error = 0;

    VALUE X = GetRecord("x", gCurrentContext);
    VALUE Y = GetRecord("y", gCurrentContext);
    VALUE Z = GetRecord("z", gCurrentContext);

    glScalef(TypeFloat(X), 
             TypeFloat(Y), 
             TypeFloat(Z));

    gLastExpression.type = VAL_NIL;
    gLastExpression.data.primitive = 0;
    return error;
}


int GlBegin(int argument_count, void* data)
{
    int error = 0;

    VALUE mode = GetRecord("primitive", gCurrentContext);

    if (mode.type == VAL_PRIMITIVE) 
    {
        glBegin(mode.data.primitive);
    }

    gLastExpression.type = VAL_NIL;
    gLastExpression.data.primitive = 0;
    return error;
}

int GlEnd(int argument_count, void* data)
{
    int error = 0;
    
    glEnd();

    gLastExpression.type = VAL_NIL;
    gLastExpression.data.primitive = 0;
    return error;
}

int GlColor3f(int argument_count, void* data)
{
    int error = 0;

    VALUE R = GetRecord("r", gCurrentContext);
    VALUE G = GetRecord("g", gCurrentContext);
    VALUE B = GetRecord("b", gCurrentContext);

    glColor3f(TypeFloat(R), 
              TypeFloat(G), 
              TypeFloat(B));

    gLastExpression.type = VAL_NIL;
    gLastExpression.data.primitive = 0;
    return error;
}

int GlVertex3f(int argument_count, void* data)
{
    int error = 0;

    VALUE X = GetRecord("x", gCurrentContext);
    VALUE Y = GetRecord("y", gCurrentContext);
    VALUE Z = GetRecord("z", gCurrentContext);

    glVertex3f(TypeFloat(X), 
               TypeFloat(Y), 
               TypeFloat(Z));

    gLastExpression.type = VAL_NIL;
    gLastExpression.data.primitive = 0;
    return error;
}

int GlNormal3f(int argument_count, void* data)
{
    int error = 0;

    VALUE X = GetRecord("x", gCurrentContext);
    VALUE Y = GetRecord("y", gCurrentContext);
    VALUE Z = GetRecord("z", gCurrentContext);

    glNormal3f(TypeFloat(X), 
               TypeFloat(Y), 
               TypeFloat(Z));

    gLastExpression.type = VAL_NIL;
    gLastExpression.data.primitive = 0;
    return error;
}

