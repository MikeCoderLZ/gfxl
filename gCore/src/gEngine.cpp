//============================================================================
// Name        : gEngine.cpp
// Author      : Michael Oliver
// Version     :
// Copyright   : Not sure yet...
// Description : Hello World in C++, Ansi-style
//============================================================================

#define GL3_PROTOTYPES 1
#include "gl3.h"

#include <iostream>
#include <string>
#include <cstdlib>

#include "SDL.h"
#include "gMath.hpp"

float testVerts[][] = { {  0.5f,  0.5f, 0.0f},
                        {  0.5f, -0.5f, 0.0f},
                        { -0.5f, -0.5f, 0.0f},
                        { -0.5f,  0.5f, 0.0f} };

using namespace std;

static string program_name( "SDL Testing" );

/* A simple function that prints a message, the error code returned by SDL,
 * and quits the application */
void sdldie(string& msg)
{
	string sdl_error(SDL_GetError());
    cout << msg << sdl_error << endl;
    SDL_Quit();
    exit(1);
}


void checkSDLError(int line = -1)
{
#ifndef NDEBUG
	string sdl_error(SDL_GetError());
	if ( !sdl_error.empty()) {
		cout << "SDL Error: " << sdl_error;
		if (line != -1)
			cout << "\tat line " << line << endl;
		SDL_ClearError();
	}
#endif
}

int main( int argc, char* argv[])
{

	gfx::Vec3 testVec(2.0f, 5.0f, 1.2f);

	cout << "gEngine active." << endl; // prints gEngine active.
	cout << testVec << "There we go!" << endl;

	SDL_Window *mainwindow; /* Our window handle */
	SDL_GLContext maincontext; /* Our opengl context handle */

	if (SDL_Init(SDL_INIT_VIDEO) < 0) { /* Initialize SDL's Video subsystem */
		string msg("Unable to initialize SDL");
		sdldie( msg ); /* Or die on error */
	}

	/* Request opengl 3.2 context.
	 * SDL doesn't have the ability to choose which profile at this time of writing,
	 * but it should default to the core profile */
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	/* Turn on double buffering with a 24bit Z buffer.
	 * You may need to change this to 16 or 32 for your system */
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	/* Create our window centered at 512x512 resolution */
	mainwindow = SDL_CreateWindow( program_name.c_str(),
								   SDL_WINDOWPOS_CENTERED,
								   SDL_WINDOWPOS_CENTERED,
								   512, 512,
								   SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
	if (!mainwindow) {/* Die if creation failed */
		string msg("Unable to initialize SDL");
		sdldie( msg ); /* Or die on error */
	}

	checkSDLError(__LINE__);

	/* Create our opengl context and attach it to our window */
	maincontext = SDL_GL_CreateContext(mainwindow);
	checkSDLError(__LINE__);


	/* This makes our buffer swap synchronized with the monitor's vertical refresh */
	SDL_GL_SetSwapInterval(1);

	/* Clear our buffer with a red background */
	glClearColor( 1.0, 0.0, 0.0, 1.0 );
	glClear( GL_COLOR_BUFFER_BIT );
	/* Swap our back buffer to the front */
	SDL_GL_SwapWindow(mainwindow);
	/* Wait 2 seconds */
	SDL_Delay(2000);

	/* Same as above, but green */
	glClearColor ( 0.0, 1.0, 0.0, 1.0 );
	glClear ( GL_COLOR_BUFFER_BIT );
	SDL_GL_SwapWindow(mainwindow);
	SDL_Delay(2000);

	/* Same as above, but blue */
	glClearColor ( 0.0, 0.0, 1.0, 1.0 );
	glClear ( GL_COLOR_BUFFER_BIT );
	SDL_GL_SwapWindow(mainwindow);
	SDL_Delay(2000);

	// Square Test
	glClearColor ( 0.0, 0.0, 0.0, 1.0 );
	glClear ( GL_COLOR_BUFFER_BIT );

	// RENDER HERE

	SDL_GL_SwapWindow(mainwindow);
	SDL_Delay(2000);

	/* Delete our opengl context, destroy our window, and shutdown SDL */
	SDL_GL_DeleteContext(maincontext);
	SDL_DestroyWindow(mainwindow);
	SDL_Quit();

	return 0;
}
