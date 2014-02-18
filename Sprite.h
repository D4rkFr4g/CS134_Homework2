#pragma once
#include<GL/glew.h>
#include "DrawUtils.h"

class Sprite
{
public:
	Sprite(void);
	Sprite::Sprite(GLuint texture, int width, int height);
	Sprite::Sprite(GLuint texture, int x, int y, int width, int height);
	~Sprite(void);
	void Sprite::draw(void);

	// Variables
	GLuint texture;
	int width, height;
	int x, y;

private:

};

