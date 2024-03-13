#pragma once

#include <Engine.h>
#include <2D/Sprite.h>

class JetpackJoyrideMap
{
private:
	E2D::Sprite background[2];
	E2D::Sprite floor[2];
	float velocity;

public:
	float floorPosition;

	JetpackJoyrideMap();

	void updateWindowSize();
	void update();
	void draw();
};