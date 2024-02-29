#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Engine.h>
#include <2D/Sprite.h>
#include <2D/Rectangle.h>
#include <Audio.h>

class PongBall {
private:
	Audio audio;

	bool isTimeForNextCollision;
	float timeForNextCollision;
	
	bool checkCollision(E2D::Rectangle& pallet);
public:
	E2D::Sprite sprite;
	glm::vec2 direction;
	float velocity;

	PongBall(E2D::Sprite& sprite);

	void update(E2D::Rectangle& player, E2D::Rectangle& opponent);
	void initRandomDirection();
	bool outScreen(int& pointsPlayer, int& pointsOpponent);
};