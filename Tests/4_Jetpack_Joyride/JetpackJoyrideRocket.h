#pragma once

#include <Engine.h>
#include <2D/Sprite.h>
#include <2D/SpriteAnimated.h>

class JetpackJoyrideRocket
{
private:
	enum class State {
		ALERTING, 
		SHOOT
	};

	State state;
	E2D::Sprite alert;
	E2D::Sprite rocket;
	E2D::SpriteAnimated flames;
	float playerPos;
	float timeToShoot;

	void alerting(float playerPos);
	void shoot();

public:
	JetpackJoyrideRocket();

	void updateWindowSize();
	void update(float playerPos);
	void draw();

	bool isOutWindow();
	bool isPlayerCollision(E2D::Object& player);
};