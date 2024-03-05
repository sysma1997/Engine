#pragma once

#include <string>
#include <vector>
#include <functional>
#include <glm/glm.hpp>
#include <Engine.h>
#include <2D/Sprite.h>

struct BreakoutBrick {
	E2D::Sprite sprite;
	bool isBreak;
};

class BreakoutBricks
{
public:
	std::vector<std::vector<BreakoutBrick>> bricks;
	int columns, rows;

	BreakoutBricks(int columns, int rows);

	void draw();
};