#include "Opponent.h"

const float OPPONENT_VELOCITY{ 250.0f };

void iaOpponent(E2D::Rectangle& opponent, E2D::Sprite& ball, float height) {
	float difference{ (ball.position.y - opponent.position.y) };
	int direction{ (difference > 0) ? 1 : -1 };

	opponent.position.y += (direction * OPPONENT_VELOCITY) * Engine::DeltaTime;
	opponent.position.y = glm::clamp(opponent.position.y,
		opponent.size.y / 2.0f,
		height - (opponent.size.y / 2.0f));
}