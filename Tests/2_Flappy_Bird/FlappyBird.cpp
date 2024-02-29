#include "FlappyBird.h"

void flappyBird() {
	srand(time(NULL));
	FlappyBirdState state{ FlappyBirdState::MENU };
	Engine* engine{ new Engine{"Flappy bird", 420, 612} };
	EUI::Test* imgui{ new EUI::Test{engine->window} };

	E2D::Sprite* background{ new E2D::Sprite{ Texture{ "2_Flappy_Bird/Assets/Images/background-day.png", true } } };
	E2D::Sprite* base{ new E2D::Sprite{ Texture{ "2_Flappy_Bird/Assets/Images/base.png", true } } };
	FlappyBirdPlayer* player{ new FlappyBirdPlayer{} };
	FlappyBirdObstacles* obstacles{ new FlappyBirdObstacles{} };
	EUI::Label* label{ new EUI::Label{ "2_Flappy_Bird/Assets/Fonts/flappy-font.ttf", 24 } };
	E2D::Sprite* gameOver{ new E2D::Sprite{Texture{"2_Flappy_Bird/Assets/Images/gameover.png", true}} };

	auto resetPosition = [&] {
		background->position = glm::vec2{ Engine::FWidth / 2.0f, Engine::FHeight / 2.0f };
		background->size = glm::vec2{ Engine::FWidth, Engine::FHeight };
		base->position = glm::vec2{ Engine::FWidth / 2.0f, Engine::FHeight * 0.91f };
		base->size = glm::vec2{ Engine::FWidth, Engine::FHeight * 0.25f };
		
		player->sprite.size = glm::vec2{ Engine::FWidth * 0.08f, Engine::FWidth * 0.08f };
		player->sprite.position = glm::vec2{ Engine::FWidth / 2.0f, Engine::FHeight / 2.0f };
		player->sprite.rotate = 0.0f;

		gameOver->position = glm::vec2{ Engine::FWidth / 2.0f, Engine::FHeight * 0.2f };
		gameOver->size = glm::vec2{ Engine::FWidth * 0.7, Engine::FHeight * 0.1f };
	};
	resetPosition();

	unsigned int points{ 0 }, bestPoints{ 0 };
	while (engine->isLoop()) {
		engine->newFrame([&] {
			background->updateWindowSize();
			base->updateWindowSize();
			player->sprite.updateWindowSize();
			obstacles->updateWindowSize();
			label->updateWindowSize();
			gameOver->updateWindowSize();

			resetPosition();
		});

		if (state == FlappyBirdState::MENU) {
			if (Engine::Keys[GLFW_KEY_ESCAPE] && !Engine::KeyProcessed[GLFW_KEY_ESCAPE]) {
				Engine::KeyProcessed[GLFW_KEY_ESCAPE] = true;
				engine->closeLoop();
			}
			if (Engine::Keys[GLFW_KEY_SPACE] && !Engine::KeyProcessed[GLFW_KEY_SPACE]) {
				Engine::KeyProcessed[GLFW_KEY_SPACE] = true;
				state = FlappyBirdState::GAME;
			}
		}
		else if (state == FlappyBirdState::GAME) {
			if (Engine::Keys[GLFW_KEY_ESCAPE] && !Engine::KeyProcessed[GLFW_KEY_ESCAPE]) {
				Engine::KeyProcessed[GLFW_KEY_ESCAPE] = true;
				state = FlappyBirdState::PAUSE;
			}

			player->processInput();
			if (player->update(base->position.y - (base->size.y / 2.0f)))
				state = FlappyBirdState::RESULT;
			obstacles->update(*base, *player, points, bestPoints);
		}
		else if (state == FlappyBirdState::PAUSE) {
			if (Engine::Keys[GLFW_KEY_ESCAPE] && !Engine::KeyProcessed[GLFW_KEY_ESCAPE]) {
				Engine::KeyProcessed[GLFW_KEY_ESCAPE] = true;
				state = FlappyBirdState::GAME;
			}
		}
		else if (state == FlappyBirdState::RESULT) {
			if (Engine::Keys[GLFW_KEY_ESCAPE] && !Engine::KeyProcessed[GLFW_KEY_ESCAPE]) {
				Engine::KeyProcessed[GLFW_KEY_ESCAPE] = true;
				engine->closeLoop();
			}
			if (Engine::Keys[GLFW_KEY_SPACE] && !Engine::KeyProcessed[GLFW_KEY_SPACE]) {
				Engine::KeyProcessed[GLFW_KEY_SPACE] = true;
				points = 0;
				player->reset();
				obstacles->reset();
				resetPosition();
				state = FlappyBirdState::GAME;
			}
		}

		background->draw();
		obstacles->draw();
		base->draw();
		player->sprite.draw();

		if (state == FlappyBirdState::MENU) {
			std::string text{ "Press SPACE to start game" };
			glm::vec2 size{ label->getSizeText(text) };
			glm::vec2 position{ Engine::FWidth / 2.0f, Engine::FHeight / 2.0f };
			position -= size / 2.0f;
			label->render(text, position);
		}
		else if (state == FlappyBirdState::GAME) {
			std::string text{ std::to_string(points) };
			glm::vec2 size{ label->getSizeText(text, 2.0f) };
			glm::vec2 position{ Engine::FWidth / 2.0f, 10.0f };
			position.x -= size.x / 2.0f;
			label->render(text, position, 2.0f);
		}
		else if (state == FlappyBirdState::PAUSE) {
			std::string text{ "PAUSE" };
			glm::vec2 size{ label->getSizeText(text) };
			glm::vec2 position{ Engine::FWidth / 2.0f, Engine::FHeight / 2.0f };
			position -= size / 2.0f;
			label->render(text, position);
		}
		else if (state == FlappyBirdState::RESULT) {
			gameOver->draw();

			std::string text{ "Points: " + std::to_string(points)};
			glm::vec2 size{ label->getSizeText(text, 1.5f) };
			float lastSizeY = size.y;
			glm::vec2 position{ Engine::FWidth / 2.0f, Engine::FHeight / 2.0f };
			position -= size / 2.0f;
			label->render(text, position, 1.5f);
			text = "Best points: " + std::to_string(bestPoints);
			size = label->getSizeText(text, 1.5f);
			position = glm::vec2{ Engine::FWidth / 2.0f, Engine::FHeight / 2.0f };
			position -= size / 2.0f;
			position.y += lastSizeY + 5.0f;
			label->render(text, position, 1.5f);
		}

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
	player->terminate();
	engine->terminate();
}