#include "BreakoutBall.h"

const float BREAKOUT_BALL_VELOCITY = 320.0f;

BreakoutBall::BreakoutBall(float playerPositionY, float playerSizeY) :
	timeCollision{ 0.0f },
	isCollision{ false },
	direction{ 0 }, 
	sprite{ Texture{"3_Breakout/Assets/Images/ball.png", true} }, 
	isSubject{ true } {
	srand(time(NULL));
	
	updateWindowSize(playerPositionY, playerSizeY);
}

void BreakoutBall::updateWindowSize(float playerPositionY, float playerSizeY) {
	sprite.updateWindowSize();
	sprite.size = glm::vec2{ Engine::FWidth * 0.03f };
	sprite.position = glm::vec2{
		(Engine::FWidth / 2.0f) - (sprite.size.x / 2.0f),
		(playerPositionY - (playerSizeY / 2.0f)) - (sprite.size.y / 2.0f)
	};
}
void BreakoutBall::processInput() {
	if (isSubject && Engine::KeyJustPressed(GLFW_KEY_SPACE)) {
		isSubject = false;

		direction.x = (rand() % 2 == 0) ? -1 : 1;
		direction.y = -1;
	}
}
void BreakoutBall::update(E2D::Sprite player) {
	if (isSubject) {
		glm::vec2 diff{ player.position - sprite.position };
		sprite.position.x += diff.x;

		return;
	}
	if (isCollision) {
		timeCollision += Engine::DeltaTime;
		if (timeCollision > 0.5f) {
			timeCollision = 0.0f;
			isCollision = false;
		}
	}

	sprite.position += direction * BREAKOUT_BALL_VELOCITY * Engine::DeltaTime;

	if (sprite.position.x < (sprite.size.x / 2.0f) ||
		sprite.position.x > (Engine::FWidth - (sprite.size.x / 2.0f))) 
		direction.x *= -1;
	if (sprite.position.y < (sprite.size.y / 2.0f)) 
		direction.y *= -1;
	if (E2D::Object::CheckCollision(sprite, player)) {
		float diff{ sprite.position.x - player.position.x };
		float percentaje{ diff / (player.size.x / 2.0f) };
		float strenght{ 2.0f };

		direction.x = percentaje * strenght;
		direction.y *= -1;
	}
}

void BreakoutBall::collisionBrick() {
	if (isCollision) return;

	direction.y *= -1;
	isCollision = true;
}