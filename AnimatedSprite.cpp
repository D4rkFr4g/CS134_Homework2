#include "AnimatedSprite.h"


AnimatedSprite::AnimatedSprite(void) : Sprite()
{
}

AnimatedSprite::AnimatedSprite(GLuint texture, int x, int y, int width, int height, GLfloat tu, GLfloat tv, GLfloat tSizeX, GLfloat tSizeY)
	: Sprite(texture, x, y, width, height, tu, tv, tSizeX, tSizeY)
{
	walkingAnimation = AnimationData();
	idleAnimation = AnimationData();
	this->isAnimated = true;
}

AnimatedSprite::~AnimatedSprite(void)
{
}

void AnimatedSprite::updateAnimation()
{
}

void AnimatedSprite::walking()
{
	curAnimation = walkingAnimation;
}

void AnimatedSprite::idle()
{
	curAnimation = idleAnimation;
}