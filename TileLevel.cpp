#include "TileLevel.h"


TileLevel::TileLevel(void)
{
}

TileLevel::TileLevel(int tilesWidth, int tilesHeight)
{
	this->tilesWidth = tilesWidth;
	this->tilesHeight = tilesHeight;

	tileArray = new Sprite*[tilesWidth];

	for (int i = 0; i < tilesWidth; i++)
	{
		tileArray[i] = new Sprite[tilesHeight];
	}
}


TileLevel::~TileLevel(void)
{
	for (int i = 0; i < tilesWidth; i++)
	{
		delete[] tileArray[i];
	}
	//delete[] tileArray;
}


void TileLevel::drawLevel(int camX, int camY)
{
	for (int i = 0; i < tilesWidth; i++)
	{
		for (int j = 0; j < tilesHeight; j++)
			tileArray[i][j].drawTile(camX, camY);
	}
}