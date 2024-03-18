#pragma once

#include <Engine.h>
#include <2D/SpriteAnimated.h>

class JetpackJoyridePlayer
{
private:
	E2D::SpriteAnimated sprite;
	glm::vec2 velocity;
	float floorPosition;
	float propulsionForce;
	bool isNotKey;

public:
	JetpackJoyridePlayer(float floorPosition);

	void updateWindowSize(float floorPosition);
	void update(int& points);
	void draw();

	float getPositionY();
	void pause(bool isPause);
	E2D::Object& getSprite();
};