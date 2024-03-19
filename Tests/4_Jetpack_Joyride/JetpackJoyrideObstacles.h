#pragma once

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <Engine.h>
#include <2D/SpriteAnimated.h>

class JetpackJoyrideObstacles
{
private:
	struct Obstacle {
		E2D::SpriteAnimated sprite;
		bool isSpinning;
	};

	float velocity;
	float currentTime;
	float generateNextObstacle;
	bool generate;
	std::vector<Obstacle> obstacles;

public:
	JetpackJoyrideObstacles();

	void updateWindowSize();
	void update();
	void draw();

	bool isPlayerCollision(E2D::Object& player);
};