#include "Ball.h"

Ball::Ball(E2D::Sprite& sprite) : sprite{ sprite }, direction{ 0.0f }, velocity{ 200.0f } {}

void Ball::processInput(bool& isPlaying) {
	if (Engine::Keys[GLFW_KEY_SPACE] && !Engine::KeyProcessed[GLFW_KEY_SPACE]) {
		Engine::KeyProcessed[GLFW_KEY_SPACE] = true;
		isPlaying = !isPlaying;

		int leftRight{ rand() % 2 }, topDown{ rand() % 2 };
		direction.x = (leftRight == 0) ? -1.0f : 1.0f;
		direction.y = (topDown == 0) ? -1.0f : 1.0f;
	}
}
void Ball::update(float width, float height) {
	sprite.position += direction * velocity * Engine::DeltaTime;

	float minX{ sprite.size.x / 2.0f };
	float maxX{ width - minX };
	float minY{ sprite.size.y / 2.0f };
	float maxY{ height - minY };
	if (sprite.position.x <= minX || sprite.position.x >= maxX)
		direction.x = -direction.x;
	if (sprite.position.y <= minY || sprite.position.y >= maxY)
		direction.y = -direction.y;
}