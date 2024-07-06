#pragma once

#include <Engine.h>
#include <2D/Sprite.h>
#include <2D/SpriteAnimated.h>
#include <Audio.h>

class Player {
private:
	float velocity;
	Audio audio;

public:
	E2D::SpriteAnimated sprite;
	bool isLose;

	Player();

	void processInput();
	void update(E2D::Sprite floor);
	void terminate();

	void reset();
};