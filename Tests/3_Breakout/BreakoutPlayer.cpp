#include "BreakoutPlayer.h"

const float BREAKOUT_PLAYER_VELOCITY = 380.0f;

BreakoutPlayer::BreakoutPlayer() : sprite{ Texture{ "3_Breakout/Assets/Images/pallet.png", true } } {
	updateWindowSize();
}

void BreakoutPlayer::updateWindowSize() {
	sprite.updateWindowSize();
	sprite.size = glm::vec2{ Engine::FWidth * 0.13, Engine::FHeight * 0.03f };
	sprite.position = glm::vec2{
		Engine::FWidth / 2.0f,
		Engine::FHeight - (sprite.size.y / 2.0f) - 10.0f
	};
}
void BreakoutPlayer::processInput() {
	if (Engine::KeyPressed(GLFW_KEY_LEFT) || Engine::KeyPressed(GLFW_KEY_RIGHT)) {
		if (Engine::KeyPressed(GLFW_KEY_LEFT)) 
			sprite.position.x -= BREAKOUT_PLAYER_VELOCITY * Engine::DeltaTime;
		if (Engine::KeyPressed(GLFW_KEY_RIGHT)) 
			sprite.position.x += BREAKOUT_PLAYER_VELOCITY * Engine::DeltaTime;

		sprite.position.x = glm::clamp(sprite.position,
			glm::vec2{ sprite.size.x / 2.0f, 0 },
			glm::vec2{ Engine::FWidth - (sprite.size.x / 2.0f), 0 }).x;
	}
}