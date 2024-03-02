#pragma once

#include <string>
#include <glm/glm.hpp>
#include <Engine.h>
#include <2D/Sprite.h>

struct Brick {
	E2D::Sprite sprite;
	bool isBreak;
};

class BreakoutBricks
{
private:
	

	Brick bricks[10][4];

public:
	BreakoutBricks();

	void updateWindowsSize();
	void draw();
};