#include <iostream>

#include <Engine.h>
#include <2D/Rectangle.h>

#include "Core/Player.h"

int main() {
	Engine* engine{ new Engine{"Pong"} };

	E2D::Rectangle* divition{ new E2D::Rectangle{} };
	divition->position = engine->getSizeCenter();
	divition->size = glm::vec2{ 5.0f, Engine::FHeight };

	Player* player{ new Player{} };

	while (engine->isLoop()) {
		engine->newFrame([&]() {
			divition->updateWindowSize();

			divition->position = engine->getSizeCenter();
			divition->size = glm::vec2{ 5.0f, Engine::FHeight };

			player->updateWindowSize();
		});

		player->progress();

		divition->draw();
		player->draw();

		engine->renderFrame();
	}

	engine->terminate();

	return 0;
}