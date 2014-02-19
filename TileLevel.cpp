#include "TileLevel.h"


TileLevel::TileLevel(void)
{
}

TileLevel::TileLevel(int width, int height, int tilesWidth, int tilesHeight)
{
	this->width = width; // Columns
	this->height = height; // Rows
	this->tilesWidth = tilesWidth;
	this->tilesHeight = tilesHeight;

	this->tileArray = new Sprite*[height];

	for (int i = 0; i < height; i++)
	{
		tileArray[i] = new Sprite[width];
	}
	
/*
	// Initialize array to be empty
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			tileArray[i][j] = Sprite();
*/
	tileArray;
}


TileLevel::~TileLevel(void)
{
	for (int i = 0; i < height; i++)
	{
		delete[] tileArray[i];
	}
	delete[] tileArray;
}


void TileLevel::drawLevel(int camX, int camY)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
			tileArray[i][j].drawTile(camX, camY);
	}
}