#include "Player.h"

const float PLAYER_VELOCITY{ 250.0f };

Player::Player() {
	sprite = new E2D::Rectangle{};

	sprite->size = glm::vec2{
		Engine::FWidth * 0.03f,
		Engine::FHeight * 0.25f
	};
	sprite->position = glm::vec2{
		sprite->size.x + 0.5f, 
		Engine::FHeight / 2.0f
	};
}

void Player::updateWindowSize() {
	sprite->size = glm::vec2{
		Engine::FWidth * 0.03f,
		Engine::FHeight * 0.25f
	};
}
void Player::progress() {
	if (Engine::KeyPressed(GLFW_KEY_UP)) 
		sprite->position.y -= PLAYER_VELOCITY * Engine::DeltaTime;
	if (Engine::KeyPressed(GLFW_KEY_DOWN))
		sprite->position.y += PLAYER_VELOCITY * Engine::DeltaTime;

	sprite->position.y = glm::clamp(sprite->position.y,
		sprite->size.y / 2.0f,
		Engine::FHeight - (sprite->size.y / 2.0f));
}
void Player::draw() {
	sprite->draw();
}