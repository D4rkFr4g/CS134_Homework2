#include "Sprite.h"

#pragma once
class TileLevel
{
public:
	TileLevel(void);
	TileLevel(int tilesWidth, int tilesHeight);
	~TileLevel(void);

	void drawLevel(int camX, int camY);

	// Global Variables
	int tilesWidth, tilesHeight;
	int textureSize;
	Sprite **tileArray;
};

