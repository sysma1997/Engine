#include "Player.h"

const float PLAYER_VELOCITY{ 250.0f };

void playerProcessInput(E2D::Rectangle& player, float height) {
	if (Engine::Keys[GLFW_KEY_UP] || Engine::Keys[GLFW_KEY_DOWN]) {
		if (Engine::Keys[GLFW_KEY_UP])
			player.position.y -= PLAYER_VELOCITY * Engine::DeltaTime;
		if (Engine::Keys[GLFW_KEY_DOWN])
			player.position.y += PLAYER_VELOCITY * Engine::DeltaTime;

		player.position.y = glm::clamp(player.position.y,
			player.size.y / 2.0f,
			height - (player.size.y / 2.0f));
	}
}