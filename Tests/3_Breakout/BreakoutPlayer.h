#pragma once

#include <glm/glm.hpp>
#include <Engine.h>
#include <2D/Sprite.h>

class BreakoutPlayer
{
public:
	E2D::Sprite sprite;

	BreakoutPlayer();

	void updateWindowSize();
	void processInput();
};