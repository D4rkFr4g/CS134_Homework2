#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <GL/glew.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "DrawUtils.h"
#include "Sprite.h"
#include "Camera.h"
#include "TileLevel.h"
#include "tileLoader.h"

static void keyboard();
static void clearBackground();
static void makeChicken();

enum {R, G, B};
int currentColor = R;
float color[] = {0,0,0};
float currentDirection = 1;
int g_windowWidth = 640;
int g_windowHeight = 480;
int g_windowMaxWidth = g_windowWidth * 2;
int g_windowMaxHeight = g_windowHeight * 2;
Camera g_cam;
int camDelta = 20;
TileLevel *level0;
int spriteSize = 64;
int g_spriteArraySize;
std::vector<Sprite> spriteList;
GLuint spriteTexture;

unsigned char kbPrevState[SDL_NUM_SCANCODES] = {0};
const unsigned char* kbState = NULL;
bool shouldExit = false;

static void init2D()
{
	g_cam = Camera(g_windowWidth, g_windowHeight, 0, g_windowMaxWidth, 0, g_windowMaxHeight);

	// OpenGL calls
	//glViewport(0,0,(GLsizei) g_windowWidth, (GLsizei) g_windowHeight);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0, g_windowWidth, g_windowHeight, 0, 0, 1);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

static void loadSprites()
{
	spriteTexture = glTexImageTGAFile("./Sprites/sprite_chicken.tga", NULL, NULL);
	
	// Load the Initial chickens
	for (int i = 0; i < 5; i++)
		makeChicken();
}

static void makeChicken()
{
	int x = rand() % ((g_windowWidth * 3) - spriteSize);
	int y = rand() % ((g_windowHeight *3) - spriteSize);

	Sprite sprite_chicken = Sprite(spriteTexture, x, y, spriteSize, spriteSize);
	spriteList.push_back(sprite_chicken);
}

static void drawSprites()
{
	for (int i = 0; i < (int) spriteList.size(); i++)	
		spriteList.at(i).draw(g_cam.x, g_cam.y);
}

static void loadLevel()
{
	level0 = new TileLevel();
	tileLoader::loadTiles("./Levels/level0.txt", level0);
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
	"TileGame",
	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	g_windowHeight, g_windowHeight,
	SDL_WINDOW_OPENGL);// | SDL_WINDOW_FULLSCREEN );


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
	loadLevel();

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
		clearBackground();
		level0->drawLevel(g_cam.x, g_cam.y);
		drawSprites();
		
		SDL_GL_SwapWindow( window );
	}

	SDL_Quit();
	return 0;
}

static void clearBackground()
{
	float r,g,b;
	r = 0;
	g = 0;
	b = 0;
	glClearColor(r,g,b,1);
	glClear(GL_COLOR_BUFFER_BIT);
}

static void keyboard()
{
	if (kbState[ SDL_SCANCODE_LEFT ])
	{
		g_cam.updateX(-camDelta);
	}
	else if (kbState[ SDL_SCANCODE_RIGHT ])
	{
		g_cam.updateX(camDelta);
	}
	else if (kbState[ SDL_SCANCODE_UP ])
	{
		g_cam.updateY(-camDelta);
	}
	else if (kbState[ SDL_SCANCODE_DOWN ])
	{
		g_cam.updateY(camDelta);
	}
	else if (kbState[ SDL_SCANCODE_ESCAPE ])
	{
		shouldExit = true;
	}
	else if (kbState[ SDL_SCANCODE_EQUALS] | kbState[ SDL_SCANCODE_KP_PLUS ])
	{
		makeChicken();
	}
else if (kbState[SDL_SCANCODE_MINUS] || kbState[SDL_SCANCODE_KP_MINUS])
	{
		if (spriteList.size() > 0)
		{
			spriteList.pop_back();
		}
	}
}