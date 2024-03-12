#pragma once

#include <Engine.h>
#include <2D/Sprite.h>

class JetpackJoyrideMap
{
private:
	E2D::Sprite background[2];
	E2D::Sprite floor;
	float velocity;

public:

	JetpackJoyrideMap();

	void updateWindowSize();
	void update();
	void draw();
};