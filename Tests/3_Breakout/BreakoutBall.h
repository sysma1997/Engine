#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <glm/glm.hpp>
#include <Engine.h>
#include <2D/Sprite.h>

class BreakoutBall
{
private:
	float timeCollision;
	bool isCollision;
	glm::vec2 direction;
	float velocity;

public:
	E2D::Sprite sprite;
	bool isSubject;

	BreakoutBall(float playerPositionY, float playerSizeY);

	void updateWindowSize(float playerPositionY, float playerSizeY);
	void processInput();
	void update(E2D::Sprite player, int& lives);

	void collisionBrick();
};