#include "FlappyBird.h"

void flappyBird() {
	Engine* engine{ new Engine{"Flappy bird", 288, 512} };
	EUI::Test* imgui{ new EUI::Test{engine->window} };

	E2D::Sprite* background{ new E2D::Sprite{
		*(new Texture{"2_Flappy_Bird/Assets/Images/background-day.png", true}),
		engine->fWidth(), engine->fHeight()} };
	E2D::Sprite* base{ new E2D::Sprite{
		*(new Texture{"2_Flappy_Bird/Assets/Images/base-2.png", true}),
		engine->fWidth(), engine->fHeight()} };
	FlappyBirdPlayer* player{ new FlappyBirdPlayer{engine->fWidth(), engine->fHeight()} };

	auto resetPosition = [&] {
		background->position = glm::vec2{ engine->fWidth() / 2.0f, engine->fHeight() / 2.0f };
		background->size = glm::vec2{ engine->fWidth(), engine->fHeight() };
		base->position = glm::vec2{ engine->fWidth() / 2.0f, engine->fHeight() * 0.91f };
		base->size = glm::vec2{ engine->fWidth(), engine->fHeight() * 0.25f };
		
		player->sprite.size = glm::vec2{ engine->fWidth() * 0.12f, engine->fWidth() * 0.12f };
		player->sprite.position = glm::vec2{ engine->fWidth() / 2.0f, engine->fHeight() / 2.0f };
	};
	resetPosition();

	while (engine->isLoop()) {
		engine->newFrame([&] {
			float width{ engine->fWidth() }, height{ engine->fHeight() };
			background->updateWindowSize(width, height);
			base->updateWindowSize(width, height);
			player->sprite.updateWindowSize(width, height);

			resetPosition();
		});

		player->processInput();
		player->update(base->position.y - (base->size.y / 2.0f));

		background->draw();
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