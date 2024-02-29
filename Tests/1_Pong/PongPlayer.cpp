#include "PongPlayer.h"

const float PONG_PLAYER_VELOCITY{ 250.0f };

void pongPlayerProcessInput(E2D::Rectangle& player) {
	if (Engine::Keys[GLFW_KEY_UP] || Engine::Keys[GLFW_KEY_DOWN]) {
		if (Engine::Keys[GLFW_KEY_UP])
			player.position.y -= PONG_PLAYER_VELOCITY * Engine::DeltaTime;
		if (Engine::Keys[GLFW_KEY_DOWN])
			player.position.y += PONG_PLAYER_VELOCITY * Engine::DeltaTime;

		player.position.y = glm::clamp(player.position.y,
			player.size.y / 2.0f,
			Engine::FHeight - (player.size.y / 2.0f));
	}
}