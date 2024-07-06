#include "Player.h"

const float PLAYER_GRAVITY = 980.0f;
const float PLAYER_JUMP_FORCE = -380.0f;

Player::Player() : audio{}, velocity{ 0.0f }, isLose{ false },
	sprite{ "flap", {
		Texture{"Assets/Images/yellowbird-downflap.png", true},
		Texture{"Assets/Images/yellowbird-midflap.png", true},
		Texture{"Assets/Images/yellowbird-upflap.png", true}
	} } {
	audio.load("wing", "Assets/Sounds/wing.wav");
	audio.load("die", "Assets/Sounds/die.wav");
	audio.load("hit", "Assets/Sounds/hit.wav");
	audio.load("point", "Assets/Sounds/point.wav");
}

void Player::processInput() {
	if (isLose) return;

	if (Engine::KeyJustPressed(GLFW_KEY_SPACE)) {
		sprite.rotate = -35.0f;
		velocity = PLAYER_JUMP_FORCE;

		audio.play("wing");
	}
}
void Player::update(E2D::Sprite floor) {
	if ((sprite.position.y + (sprite.size.y / 2.0f)) <= (floor.position.y - (floor.size.y / 2.0f))) {
		velocity += PLAYER_GRAVITY * Engine::DeltaTime;

		sprite.rotate += 1.0f;
		sprite.rotate = glm::clamp(glm::vec2{ sprite.rotate }, glm::vec2{ -35.0f }, glm::vec2{ 50.0f }).x;
		sprite.position.y += velocity * Engine::DeltaTime;

		return;
	}

	isLose = true;
	velocity = 0.0f;
	sprite.pauseAnimation = true;

	audio.play("die");
}
void Player::terminate() {
	audio.terminate();
}

void Player::reset() {
	isLose = false;
	sprite.pauseAnimation = false;
}