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

void AnimatedSprite::update(int ms)
{
	//std::cout << "Updating" << std::endl;
	curAnimation.updateTime(ms);
	int currentFrame = curAnimation.currentFrame;
	AnimationFrame frame = curAnimation.def.frames[currentFrame];
	tu = frame.tu;
	tv = frame.tv;
	tSizeX = frame.tWidth;
	tSizeY = frame.tHeight;
}

void AnimatedSprite::walking()
{
	curAnimation = walkingAnimation;
}

void AnimatedSprite::idle()
{
	curAnimation = idleAnimation;
}