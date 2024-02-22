#pragma once

#include <Engine.h>
#include <2D/SpriteAnimated.h>

class FlappyBirdPlayer
{
private:
	float mass;

public:
	E2D::SpriteAnimated sprite;

	FlappyBirdPlayer(float width, float height);

	void processInput();
	void update(float basePositionY);
};

