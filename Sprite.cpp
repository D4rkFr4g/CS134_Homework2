#include "Sprite.h"

	Sprite::Sprite(void)
	{
		texture = NULL;
		width = 0;
		height = 0;
		x = 0;
		y = 0;
		tu = 0;
		tv = 0;
		tSizeX = 1;
		tSizeY = 1;
	}

	Sprite::Sprite(GLuint texture, int width, int height)
	{
		this->texture = texture;
		this->width = width;
		this->height = height;
		x = 0;
		y = 0;
		this->tu = 0;
		this->tv = 0;
		this->tSizeX = 1;
		this->tSizeY = 1;
	}

	Sprite::Sprite(GLuint texture, int x, int y, int width, int height)
	{
		this->texture = texture;
		this->width = width;
		this->height = height;
		this->x = x;
		this->y = y;
		this->tu = 0;
		this->tv = 0;
		this->tSizeX = 1;
		this->tSizeY = 1;
	}

	Sprite::Sprite(GLuint texture, int x, int y, int width, int height, GLfloat tu, GLfloat tv, GLfloat tSizeX, GLfloat tSizeY)
	{
		this->texture = texture;
		this->width = width;
		this->height = height;
		this->x = x;
		this->y = y;
		this->tu = tu;
		this->tv = tv;
		this->tSizeX = tSizeX;
		this->tSizeY = tSizeY;
	}

	Sprite::~Sprite(void)
	{
	}

	void Sprite::draw(void)
	{
		glDrawSprite(texture, x, y, width, height);
	}

	void Sprite::draw(int camX, int camY)
	{
		glDrawSprite(texture, x - camX, y - camY, width, height);
	}

	void Sprite::drawTile(int camX, int camY)
	{
		glDrawSprite(texture, x - camX, y - camY, width, height, tu, tv, tSizeX, tSizeY);
	}

	void Sprite::print()
	{
		using namespace std;
		cout << "x = " << x << "\t y = " << y << endl;

	}
