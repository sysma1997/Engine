#include "Ball.h"

Ball::Ball(E2D::Sprite& sprite) : sprite{ sprite }, direction{ 0.0f }, velocity{ 200.0f } {}

bool Ball::checkCollision(E2D::Rectangle& pallet) {
	bool collisionX{
		sprite.position.x + sprite.size.x >= pallet.position.x && 
		pallet.position.x + pallet.size.x >= sprite.position.x
	};
	bool collisionY{
		sprite.position.y + sprite.size.y >= pallet.position.y &&
		pallet.position.y + pallet.size.y >= sprite.position.y
	};

	return collisionX && collisionY;
}

void Ball::update(float height, E2D::Rectangle& player, E2D::Rectangle& opponent) {
	sprite.position += direction * velocity * Engine::DeltaTime;

	float minY{ sprite.size.y / 2.0f };
	float maxY{ height - minY };
	if (sprite.position.y <= minY || sprite.position.y >= maxY)
		direction.y = -direction.y;
	
	if (checkCollision(player) || checkCollision(opponent)) {
		direction.x = -direction.x;
		velocity += 50.0f;
	}
}
void Ball::initRandomDirection() {
	int leftRight{ rand() % 2 }, topDown{ rand() % 2 };
	direction.x = (leftRight == 0) ? -1.0f : 1.0f;
	direction.y = (topDown == 0) ? -1.0f : 1.0f;
}
bool Ball::outScreen(float width, int& pointsPlayer, int& pointsOpponent) {
	if (sprite.position.x < 0 || sprite.position.x > width) {
		if (sprite.position.x < 0) pointsOpponent++;
		if (sprite.position.x > width) pointsPlayer++;
		
		return true;
	}

	return false;
}