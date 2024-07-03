#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <Engine.h>
#include <2D/Sprite.h>

#include "Core/Obstacles.h"

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

	while (engine->isLoop()) {
		engine->newFrame([&]() {});

		obstacles->update(*floor);

		background->draw();
		obstacles->draw();
		floor->draw();

		engine->renderFrame();
	}

	engine->terminate();

	return 0;
}