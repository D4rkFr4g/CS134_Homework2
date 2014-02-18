#include "tileLoader.h"

void tileLoader::loadTiles(const char* filename, TileLevel *level)
{
	using namespace std;
	string line = "";
	int width, height, tileWidth, tileHeight;
	string tileFile = "";
	int *tilesRead;
	int tileIndex = 0;

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

	// Load Tileset Texture
	GLuint tileSet = glTexImageTGAFile(tileFile.c_str(), NULL, NULL);
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
		if (1)
		{
			for (int i = 0; i < width * height; i++)
				cout << "tile[" << i << "] = " << tilesRead[i] << endl;
		}

	// Cleanup
	infile.close();
	delete tilesRead;
}

