#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <vector>
#include <glm/glm.hpp>

#include <Engine.h>
#include <2D/Sprite.h>

#include "Subject.h"
#include "Score.h"

class Obstacles : public Subject {
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
	Obstacles();

	void update(E2D::Sprite base);
	void draw();

	void reset();
};