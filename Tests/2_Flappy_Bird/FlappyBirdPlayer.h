#pragma once

#include <Engine.h>
#include <2D/SpriteAnimated.h>
#include <Audio.h>

class FlappyBirdPlayer
{
private:
	float velocity;
	Audio audio;

public:
	E2D::SpriteAnimated sprite;
	bool isLose;

	FlappyBirdPlayer();

	void processInput();
	bool update(float basePositionY);
	void terminate();

	void reset();
	void setAudioHit();
	void setAudioPoint();
};

