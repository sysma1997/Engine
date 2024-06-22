#pragma once

#include <Engine.h>
#include <2D/Rectangle.h>

class Opponent
{
private:
	E2D::Rectangle* sprite;

public:
	Opponent();

	void updateWindowSize();
	void progress(glm::vec2 ball);
	void draw();

	E2D::Object* getSprite();
	void reset();
};

