#include "PongBall.h"

PongBall::PongBall(E2D::Sprite& sprite) : audio{ },
	sprite{ sprite }, direction{ 0.0f }, velocity{ 200.0f }, 
	isTimeForNextCollision{ false }, timeForNextCollision{ 0.0f } {
	audio.load("collision", "1_Pong/Assets/Sounds/ballCollision.wav");
	audio.load("boo", "1_Pong/Assets/Sounds/boo.mp3");
	audio.load("cellebration", "1_Pong/Assets/Sounds/cellebration.mp3");
}

void PongBall::update(E2D::Rectangle& player, E2D::Rectangle& opponent) {
	if (isTimeForNextCollision) {
		if (timeForNextCollision > 0.1f) {
			isTimeForNextCollision = false;
			timeForNextCollision = 0.0f;
		}
		timeForNextCollision += Engine::DeltaTime;
	}

	sprite.position += direction * velocity * Engine::DeltaTime;

	float minY{ sprite.size.y / 2.0f };
	float maxY{ Engine::FHeight - minY };
	if (sprite.position.y <= minY || sprite.position.y >= maxY)
		direction.y = -direction.y;
	
	if (!isTimeForNextCollision && 
		(E2D::Object::CheckCollision(sprite, player) || 
		E2D::Object::CheckCollision(sprite, opponent))) {
		isTimeForNextCollision = true;
		
		direction.x = -direction.x;
		velocity += 10.0f;

		audio.play("collision");
	}
}
void PongBall::terminate() {
	audio.terminate();
}

void PongBall::initRandomDirection() {
	int leftRight{ rand() % 2 }, topDown{ rand() % 2 };
	direction.x = (leftRight == 0) ? -1.0f : 1.0f;
	direction.y = (topDown == 0) ? -1.0f : 1.0f;
}
bool PongBall::outScreen(int& pointsPlayer, int& pointsOpponent) {
	if (sprite.position.x < 0 || sprite.position.x > Engine::FWidth) {
		if (sprite.position.x < 0) {
			pointsOpponent++;
			audio.play("boo");
		}
		if (sprite.position.x > Engine::FWidth) {
			pointsPlayer++;
			audio.play("cellebration");
		}
		
		return true;
	}

	return false;
}