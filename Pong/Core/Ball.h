#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <Engine.h>
#include <2D/Sprite.h>
#include <Audio.h>

class Ball
{
private:
	E2D::Sprite* sprite;
	glm::vec2 direction;
	float velocity;
	Audio audio;

public:
	Ball();

	void updateWindowSize();
	void progress(E2D::Object* player, E2D::Object* opponent);
	void draw();

	glm::vec2 getPosition();
	int isOut();
	void reset();
};
