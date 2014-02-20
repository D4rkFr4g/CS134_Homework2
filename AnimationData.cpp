#include "AnimationData.h"


AnimationData::AnimationData(void)
{
}

AnimationData::AnimationData(Animation def, float timeToNextFrame)
{
	this->def = def;
	this->timeToNextFrame = timeToNextFrame;
	this->elapsedTime = 0;
}

AnimationData::~AnimationData(void)
{
}

void AnimationData::resetElapsedTime()
{
	elapsedTime = 0;
}