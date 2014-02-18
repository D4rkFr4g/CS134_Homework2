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
	}

	Sprite::Sprite(GLuint texture, int x, int y, int width, int height)
	{
		this->texture = texture;
		this->width = width;
		this->height = height;
		this->x = x;
		this->y = y;
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
