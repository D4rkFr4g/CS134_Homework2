#include "Sprite.h"

#pragma once
class TileLevel
{
public:
	TileLevel(void);
	TileLevel(int width, int height, int tileWidth, int tileHeight);
	~TileLevel(void);

	void drawLevel(int camX, int camY);

	// Global Variables
	int tilesWidth, tilesHeight;
	int width, height;
	Sprite *tileArray;
};

