#pragma once
#include<GL/glew.h>
#include "DrawUtils.h"

class Sprite
{
public:
	// Constructors
	Sprite(void);
	Sprite::Sprite(GLuint texture, int width, int height);
	Sprite::Sprite(GLuint texture, int x, int y, int width, int height);
	Sprite::Sprite(GLuint texture, int x, int y, int width, int height, int tu, int tv, int tSize);
	~Sprite(void);

	//Functions
	void Sprite::draw(void);
	void Sprite::draw(int camX, int camY);
	void Sprite::drawTile(int camX, int camY);

	// Variables
	GLuint texture;
	int width, height;
	int x, y;
	int tu, tv;
	int tSize;

private:

};

