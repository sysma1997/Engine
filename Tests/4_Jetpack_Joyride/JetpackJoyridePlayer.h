#pragma once

#include <Engine.h>
#include <2D/SpriteAnimated.h>

class JetpackJoyridePlayer
{
private:
	E2D::SpriteAnimated sprite;
	glm::vec2 velocity;
	float floorPosition;

public:
	JetpackJoyridePlayer(float floorPosition);

	void update();
	void draw();
};