#include "Sprite.h"

	Sprite::Sprite(void)
	{
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
		this->tSize = 1;
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
		this->tSize = 1;
	}

	Sprite::Sprite(GLuint texture, int x, int y, int width, int height, int tu, int tv, int tSize)
	{
		this->texture = texture;
		this->width = width;
		this->height = height;
		this->x = x;
		this->y = y;
		this->tu = tu;
		this->tv = tv;
		this->tSize = tSize;
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
		glDrawSprite(texture, x - camX, y - camY, width, height, tu, tv, tSize);
	}
