#pragma once

#include <Engine.h>
#include <2D/Sprite.h>

class Ball
{
private:
	E2D::Sprite* sprite;

public:
	Ball();

	void updateWindowSize();
	void progress();
	void draw();
};
