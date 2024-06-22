#include "Opponent.h"

const float OPPONENT_VELOCITY{ 250.0f };

Opponent::Opponent() {
	sprite = new E2D::Rectangle{};

	sprite->size = glm::vec2{
		Engine::FWidth * 0.03f,
		Engine::FHeight * 0.25f
	};
	sprite->position = glm::vec2{
		Engine::FWidth - (sprite->size.x + 0.5f),
		Engine::FHeight / 2.0f
	};
}

void Opponent::updateWindowSize() {
	sprite->size = glm::vec2{
		Engine::FWidth * 0.03f,
		Engine::FHeight * 0.25f
	};
}
void Opponent::progress(glm::vec2 ball) {
	float diff{ ball.y - sprite->position.y };
	diff = (diff > 0) ? 1.0f : -1.0f;

	sprite->position.y += diff * OPPONENT_VELOCITY * Engine::DeltaTime;

	sprite->position.y = glm::clamp(sprite->position.y,
		sprite->size.y / 2.0f,
		Engine::FHeight - (sprite->size.y / 2.0f));
}
void Opponent::draw() {
	sprite->draw();
}

E2D::Object* Opponent::getSprite() {
	return sprite;
}
void Opponent::reset() {
	sprite->position = glm::vec2{
		Engine::FWidth - (sprite->size.x + 0.5f),
		Engine::FHeight / 2.0f
	};
}