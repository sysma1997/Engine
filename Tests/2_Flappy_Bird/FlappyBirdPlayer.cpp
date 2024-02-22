#include "FlappyBirdPlayer.h"

const float FLAPPY_BIRD_PLAYER_GRAVITY = 30.0f;
const float FLAPPY_BIRD_PLAYER_JUMP_FORCE = 300.0f;

FlappyBirdPlayer::FlappyBirdPlayer(float width, float height) : 
	mass{ 0.0f }, 
	sprite{ {
			Texture{"2_Flappy_Bird/Assets/Images/yellowbird-downflap.png", true},
			Texture{"2_Flappy_Bird/Assets/Images/yellowbird-midflap.png", true},
			Texture{"2_Flappy_Bird/Assets/Images/yellowbird-upflap.png", true}
		}, width, height } {}

void FlappyBirdPlayer::processInput() {
	if (Engine::Keys[GLFW_KEY_SPACE] && !Engine::KeyProcessed[GLFW_KEY_SPACE]) {
		Engine::KeyProcessed[GLFW_KEY_SPACE] = true;

		mass = -4.0f;
		sprite.position.y -= FLAPPY_BIRD_PLAYER_JUMP_FORCE * Engine::DeltaTime;
	}
}
void FlappyBirdPlayer::update(float basePositionY) {
	if (sprite.position.y <= basePositionY) {
		sprite.position.y += mass + (FLAPPY_BIRD_PLAYER_GRAVITY * Engine::DeltaTime);
		mass += 0.1f;
	}
	else {
		mass = 0.0f;
		sprite.rotate = 0.0f;
	}
}