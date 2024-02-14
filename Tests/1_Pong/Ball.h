#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Engine.h>
#include <2D/Sprite.h>

class Ball {
public:
	E2D::Sprite sprite;
	glm::vec2 direction;
	float velocity;

	Ball(E2D::Sprite& sprite);

	void processInput(bool& isPlaying);
	void update(float width, float height);
};