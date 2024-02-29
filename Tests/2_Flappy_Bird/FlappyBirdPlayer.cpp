#include "FlappyBirdPlayer.h"

const float FLAPPY_BIRD_PLAYER_GRAVITY = 980.0f;
const float FLAPPY_BIRD_PLAYER_JUMP_FORCE = -380.0f;

FlappyBirdPlayer::FlappyBirdPlayer() : 
	velocity{ 0.0f },
	sprite{ {
			Texture{"2_Flappy_Bird/Assets/Images/yellowbird-downflap.png", true},
			Texture{"2_Flappy_Bird/Assets/Images/yellowbird-midflap.png", true},
			Texture{"2_Flappy_Bird/Assets/Images/yellowbird-upflap.png", true}
		} } {}

void FlappyBirdPlayer::processInput() {
	if (Engine::Keys[GLFW_KEY_SPACE] && !Engine::KeyProcessed[GLFW_KEY_SPACE]) {
		Engine::KeyProcessed[GLFW_KEY_SPACE] = true;

		sprite.rotate = -35.0f;
		velocity = FLAPPY_BIRD_PLAYER_JUMP_FORCE;
	}
}
void FlappyBirdPlayer::update(float basePositionY) {
	if (sprite.position.y <= (basePositionY - (sprite.size.y / 2.0f))) {
		velocity += FLAPPY_BIRD_PLAYER_GRAVITY * Engine::DeltaTime;

		sprite.rotate += 1.0f;
		sprite.rotate = glm::clamp(glm::vec2{ sprite.rotate }, glm::vec2{ -35.0f }, glm::vec2{ 50.0f }).x;
		sprite.position.y += velocity * Engine::DeltaTime;
	}
	else velocity = 0.0f;
}