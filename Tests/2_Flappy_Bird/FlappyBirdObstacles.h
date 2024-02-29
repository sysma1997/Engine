#pragma once

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <glm/glm.hpp>
#include <Engine.h>
#include <2D/Sprite.h>
#include <2D/Rectangle.h>

#include "FlappyBirdPlayer.h"

class FlappyBirdObstacles {
private:
	struct ObstacleSprite {
		E2D::Sprite up;
		E2D::Sprite down;
		bool overcome;
	};

	float velocity;
	float currentTime;
	bool generate;
	std::vector<ObstacleSprite> obstacles;

public:
	FlappyBirdObstacles();

	void updateWindowSize();
	void update(E2D::Sprite base, FlappyBirdPlayer& player, unsigned int& points, unsigned int& bestPoints);
	void draw();

	void reset();
};