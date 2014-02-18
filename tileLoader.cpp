#include "tileLoader.h"

void tileLoader::loadTiles(const char* filename, TileLevel *level)
{
	using namespace std;
	string line = "";
	int x, y, width, height, tileWidth, tileHeight;
	string tileFile = "";
	int *tilesRead = NULL;
	int tileIndex = 0;
	GLfloat tu, tv;

	// Opens a Flare map file .txt
	ifstream infile;
	infile.open(filename);

	getline(infile, line);
	if (!line.compare("[header]\n"))
	{
		cout << "Header information not found" << endl;
		return;
	}
	
	// Read Width
	getline(infile, line);
	line = line.substr(6);
	width = atoi(line.c_str());

	// Read Height
	getline(infile, line);
	line = line.substr(7);
	height = atoi(line.c_str());

	// Read Tile Width
	getline(infile, line);
	line = line.substr(10);
	tileWidth = atoi(line.c_str());

	// Read Tile Height
	getline(infile, line);
	line = line.substr(11);
	tileHeight = atoi(line.c_str());

	getline(infile, line); // Blank line

	// Read tileset filename
	getline(infile, line); // [tilesets]
	getline(infile, line);
	int extension = line.find('.');
	extension -= 8;
	line = line.substr(8,extension);
	tileFile = "./Sprites/" + line + ".tga";

	getline(infile, line); // Blank line
	getline(infile, line); // [layer]
	getline(infile, line); // type=Tile Layer 1
	getline(infile, line); // data = 

	// Debug Checks
	if (0)
	{
		cout << "width = " << width << endl;
		cout << "heigth = " << height << endl;
		cout << "tileWidth = " << tileWidth << endl;
		cout << "tileHeight = " << tileHeight << endl;
		cout << "tileSet = " << tileFile << endl;
	}

	// Create array for tile data
	tilesRead = new int [width * height];

	// Read Data
	while(!infile.eof())
	{
		getline(infile, line, ',');
		if (line.compare("\n"))
		{
			tilesRead[tileIndex] = atoi(line.c_str());
			tileIndex++;

			// Debug Check
			if (0)
			{
				cout << line << endl;
			}
		}
	}
	
	// Debug Check all tiles read
	if (0)
	{
		for (int i = 0; i < width * height; i++)
			cout << "tile[" << i << "] = " << tilesRead[i] << endl;
		cout << "Tiles Read = " << tileIndex << endl;
	}

	// Load Tileset Texture
	GLuint tileSet = glTexImageTGAFile(tileFile.c_str(), NULL, NULL);

	// Load tiles to level
	tileIndex = 0;
	GLfloat tSizeX = (GLfloat) 1.0 / width;
	GLfloat tSizeY = (GLfloat) 1.0 / height;

	level = new TileLevel(width, height);
	

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			// Find Row / Column texture coords
			int tilePos = tilesRead[tileIndex];
			int row = tilePos % height + 1;
			int column = tilePos % width + 1;
			tu = row * tSizeX;
			tv = column * tSizeY;
			
			x = j * tileWidth;
			y = i * tileHeight;

			level->tileArray[j][i] = Sprite(tileSet, x, y, tileWidth, tileHeight, tu, tv, tSizeX, tSizeY);
			tileIndex++;
		}

	// Cleanup
	infile.close();
	delete[] tilesRead;
}