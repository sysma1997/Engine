#pragma once

#include <Engine.h>
#include <2D/SpriteAnimated.h>

class FlappyBirdPlayer
{
private:
	float velocity;

public:
	E2D::SpriteAnimated sprite;

	FlappyBirdPlayer();

	void processInput();
	void update(float basePositionY);
};

