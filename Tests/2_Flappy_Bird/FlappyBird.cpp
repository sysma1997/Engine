#include "FlappyBird.h"

void flappyBird() {
	srand(time(NULL));
	Engine* engine{ new Engine{"Flappy bird", 420, 612} };
	EUI::Test* imgui{ new EUI::Test{engine->window} };

	E2D::Sprite* background{ new E2D::Sprite{ Texture{ "2_Flappy_Bird/Assets/Images/background-day.png", true } } };
	E2D::Sprite* base{ new E2D::Sprite{ Texture{ "2_Flappy_Bird/Assets/Images/base-2.png", true } } };
	FlappyBirdPlayer* player{ new FlappyBirdPlayer{} };
	FlappyBirdObstacles* obstacles{ new FlappyBirdObstacles{} };

	auto resetPosition = [&] {
		background->position = glm::vec2{ Engine::FWidth / 2.0f, Engine::FHeight / 2.0f };
		background->size = glm::vec2{ Engine::FWidth, Engine::FHeight };
		base->position = glm::vec2{ Engine::FWidth / 2.0f, Engine::FHeight * 0.91f };
		base->size = glm::vec2{ Engine::FWidth, Engine::FHeight * 0.25f };
		
		player->sprite.size = glm::vec2{ Engine::FWidth * 0.08f, Engine::FWidth * 0.08f };
		player->sprite.position = glm::vec2{ Engine::FWidth / 2.0f, Engine::FHeight / 2.0f };
	};
	resetPosition();

	bool isGame{ false };
	while (engine->isLoop()) {
		engine->newFrame([&] {
			background->updateWindowSize();
			base->updateWindowSize();
			player->sprite.updateWindowSize();
			obstacles->updateWindowSize();

			resetPosition();
		});

		if (isGame) {
			player->processInput();
			player->update(base->position.y - (base->size.y / 2.0f));
			obstacles->update(*base);
		}
		else {
			if (Engine::Keys[GLFW_KEY_SPACE] && !Engine::KeyProcessed[GLFW_KEY_SPACE]) {
				Engine::KeyProcessed[GLFW_KEY_SPACE] = true;
				isGame = true;
			}
		}

		background->draw();
		obstacles->draw();
		base->draw();
		player->sprite.draw();

		imgui->newFrame();
		//ImGui::Begin("base position");
		//ImGui::Text("Position");
		//ImGui::InputFloat("##basePosX", &base->position.x);
		//ImGui::SameLine();
		//ImGui::InputFloat("##basePosY", &base->position.y);
		//ImGui::Text("Size");
		//ImGui::InputFloat("##baseSizeX", &base->size.x);
		//ImGui::SameLine();
		//ImGui::InputFloat("##baseSizeY", &base->size.y);
		//ImGui::End();
		imgui->renderFrame();
		engine->renderFrame();
	}

	imgui->terminate();
	engine->terminate();
}