#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Engine.h>
#include <2D/Sprite.h>
#include <2D/Rectangle.h>

class Ball {
private:
	bool checkCollision(E2D::Rectangle& pallet);
public:
	E2D::Sprite sprite;
	glm::vec2 direction;
	float velocity;

	Ball(E2D::Sprite& sprite);

	void update(float height, E2D::Rectangle& player, E2D::Rectangle& opponent);
	void initRandomDirection();
	bool outScreen(float width, int& pointsPlayer, int& pointsOpponent);
};