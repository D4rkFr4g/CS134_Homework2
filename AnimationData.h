#pragma once
#include "Animation.h"
class AnimationData
{
public:
	AnimationData(void);
	AnimationData(Animation def, float timeToNextFrame);
	~AnimationData(void);

	// Functions
	void resetElapsedTime();

	// Variables
	Animation def;
	int currentFrame;
	float timeToNextFrame;
	float elapsedTime;
};

