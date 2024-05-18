#pragma once

#include <Engine.h>
#include <2D/Rectangle.h>

class Player
{
private:
	E2D::Rectangle* sprite;
public:
	Player();

	void updateWindowSize();
	void progress();
	void draw();
};

