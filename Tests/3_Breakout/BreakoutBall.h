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
	glm::vec2 direction;

public:
	E2D::Sprite sprite;
	bool isSubject;

	BreakoutBall(float playerPositionY, float playerSizeY);

	void updateWindowSize(float playerPositionY, float playerSizeY);
	void processInput();
	void update(E2D::Sprite player);
};