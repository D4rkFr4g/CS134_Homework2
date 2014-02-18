#define SDL_MAIN_HANDLED
#include<SDL.h>
#include<GL/glew.h>
#include<stdio.h>
#include <cstdlib>
#include <iostream>
#include "DrawUtils.h"
#include "Sprite.h"

static void keyboard();
static void backgroundColor();

enum {R, G, B};
int currentColor = R;
float color[] = {0,0,0};
float currentDirection = 1;
int g_windowWidth = 640;
int g_windowHeight = 480;
float cam[2] = {g_windowWidth / 2.0f, g_windowHeight / 2.0f};
int g_spriteArraySize;
Sprite *spriteArray;

unsigned char kbPrevState[SDL_NUM_SCANCODES] = {0};
const unsigned char* kbState = NULL;
bool shouldExit = false;

static void init2D()
{
	glViewport(0,0,(GLsizei) g_windowWidth, (GLsizei) g_windowHeight);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0, g_windowWidth, g_windowHeight, 0, 0, 1);
	glEnable(GL_TEXTURE_2D);
}

static void loadSprites()
{
	g_spriteArraySize = 1;
	spriteArray = new Sprite[g_spriteArraySize];

	GLuint texture = glTexImageTGAFile("./Sprites/sprite_chicken.tga", NULL, NULL);
	Sprite sprite_chicken = Sprite(texture, g_windowWidth/2, g_windowHeight/2, 80, 80);
	spriteArray[0] = sprite_chicken;
}

using namespace std;
int main( void )
{	
	// Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) 
	{
		return 1;
	}
 
	// Create the window, OpenGL context
	SDL_GL_SetAttribute( SDL_GL_BUFFER_SIZE, 32 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
	SDL_Window* window = SDL_CreateWindow(
	"TestSDL",
	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	g_windowHeight, g_windowHeight,
	SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN );


	if( !window ) 
	{
		SDL_Quit();
		return 1;
	}
	SDL_GL_CreateContext( window );

	// Make sure we have a recent version of OpenGL
	GLenum glewError = glewInit();
	if( glewError != GLEW_OK ) 
	{
		SDL_Quit();
		return 1;
	}
	if( !GLEW_VERSION_1_5 ) 
	{
		SDL_Quit();
		return 1;
	}

	// Setup calls
	init2D();
	loadSprites();

	// Read keyboard status
	kbState = SDL_GetKeyboardState( NULL );

	// The game loop
	while( !shouldExit ) 
	{
		memcpy (kbPrevState, kbState, sizeof( kbPrevState ));

		// Handle OS message pump
		SDL_Event event;
		while( SDL_PollEvent( &event )) 
		{
			switch( event.type ) 
			{
				case SDL_QUIT:
				return 0;
			}
		}

		// Game logic goes here
		keyboard();
		
		// All calls to glDrawSprite go here
		for (int i = 0; i < g_spriteArraySize; i++)
			spriteArray[i].draw();

		SDL_GL_SwapWindow( window );
	}

	SDL_Quit();
	return 0;
}

static void backgroundColor()
{
	color[currentColor] += currentDirection;

	if (color[currentColor] > 255 || color[currentColor] < 0)
		currentDirection *= -1;

	float r,g,b;
	r = color[0] / 255;
	g = color[1] / 255;
	b = color[2] / 255;
	glClearColor(r,g,b,1);
	glClear(GL_COLOR_BUFFER_BIT);
}

static void keyboard()
{
	if (kbState[ SDL_SCANCODE_LEFT ] && !kbPrevState[ SDL_SCANCODE_LEFT ])
	{
		currentColor--;
		if (currentColor < 0)
			currentColor = 2;

		//cout << "currentColor = " << currentColor << endl;
	}
	else if (kbState[ SDL_SCANCODE_RIGHT ] && !kbPrevState[ SDL_SCANCODE_RIGHT ])
	{
		currentColor++;
		if (currentColor > 2)
			currentColor = 0;

		//cout << "currentColor = " << currentColor << endl;
	}
	else if (kbState[ SDL_SCANCODE_UP ] && !kbPrevState[ SDL_SCANCODE_UP ])
	{
		currentDirection = 1;
	}
	else if (kbState[ SDL_SCANCODE_DOWN ] && !kbPrevState[ SDL_SCANCODE_DOWN])
	{
		currentDirection = -1;
	}
	else if (kbState[ SDL_SCANCODE_ESCAPE ])
	{
		shouldExit = true;
	}
}