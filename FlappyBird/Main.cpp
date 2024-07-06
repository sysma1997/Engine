#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <Engine.h>
#include <2D/Sprite.h>

#include "Core/Obstacles.h"
#include "Core/Player.h"

int main() {
	srand(time(NULL));
	Engine* engine{ new Engine("Flappy Bird", 420, 612, false) };

	E2D::Sprite* background{ new E2D::Sprite{Texture{"Assets/Images/background-day.png", true}} };
	background->position = glm::vec2{ Engine::FWidth / 2.0f, Engine::FHeight / 2.0f };
	background->size = Engine::GetSize();
	E2D::Sprite* floor{ new E2D::Sprite{Texture{"Assets/Images/base.png", true}} };
	floor->position = glm::vec2{ Engine::FWidth / 2.0f, Engine::FHeight * 0.91f };
	floor->size = glm::vec2{ Engine::FWidth, Engine::FHeight * 0.25f };
	
	Obstacles* obstacles{ new Obstacles{} };
	Player* player{ new Player{} };

	auto resetPosition = [player] {
		player->sprite.size = glm::vec2{ Engine::FWidth * 0.08f, Engine::FWidth * 0.08f };
		player->sprite.position = glm::vec2{ Engine::FWidth / 2.0f, Engine::FHeight / 2.0f };
		player->sprite.rotate = 0.0f;
	};
	resetPosition();

	bool start = false;
	while (engine->isLoop()) {
		engine->newFrame([&]() {});



		obstacles->update(*floor);

		if (start) {
			player->processInput();
			player->update(*floor);
		}
		else if (Engine::KeyJustPressed(GLFW_KEY_SPACE))
			start = true;

		background->draw();
		obstacles->draw();
		floor->draw();
		player->sprite.draw();

		engine->renderFrame();
	}

	engine->terminate();

	return 0;
}