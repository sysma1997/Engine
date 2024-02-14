#include "Pong.h"

void pong() {
	srand(time(NULL));

	Engine* engine{ new Engine{"Pong"} };
	EUI::Test* ui{ new EUI::Test{engine->window} };

	E2D::Rectangle* division{ new E2D::Rectangle{engine->fWidth(), engine->fHeight()} };
	E2D::Rectangle* player{ new E2D::Rectangle{engine->fWidth(), engine->fHeight()} };
	E2D::Rectangle* opponent{ new E2D::Rectangle{engine->fWidth(), engine->fHeight()} };
	E2D::Sprite ballSprite{ E2D::Sprite{*(new Texture{"1_Pong/Assets/Images/Ball.png", true}),
		engine->fWidth(), engine->fHeight()} };
	Ball* ball{ new Ball{ballSprite} };

	auto resetPosition = [&]() {
		glm::vec2 centerPosition{ engine->fWidth() / 2.0f, engine->fHeight() / 2.0f };
		division->position = centerPosition;
		division->size = glm::vec2{ engine->fWidth() * 0.01f, engine->fHeight()};
		
		glm::vec2 size{ engine->fWidth() * 0.03f, (engine->fHeight() / 2.0f) * 0.3f };
		player->position = glm::vec2{ (engine->fWidth() * (0.03f / 2.0f)) + 5.0f, engine->fHeight() / 2.0f };
		player->size = size;
		opponent->position = glm::vec2{ engine->fWidth() - (player->position.x), engine->fHeight() / 2.0f };
		opponent->size = size;

		ball->sprite.position = centerPosition;
		ball->sprite.size = glm::vec2{ engine->fWidth() * 0.05f, engine->fWidth() * 0.05f };
	};
	resetPosition();

	bool isPlaying{ false };
	while (engine->isLoop()) {
		engine->newFrame([&]() {
			float width = engine->fWidth(), height = engine->fHeight();
			division->updateWindowSize(width, height);
			player->updateWindowSize(width, height);
			opponent->updateWindowSize(width, height);
			ball->sprite.updateWindowSize(width, height);

			resetPosition();
		});

		if (isPlaying) {
			playerProcessInput(*player, engine->fWidth(), engine->fHeight());
			ball->update(engine->fWidth(), engine->fHeight());
		}
		else ball->processInput(isPlaying);

		division->draw();
		player->draw();
		opponent->draw();
		ball->sprite.draw();

		ui->newFrame();
		ImGui::Begin("Position");
		ImGui::InputFloat("##y", &player->position.y);
		ImGui::End();
		ui->renderFrame();
		engine->renderFrame();
	}

	ui->terminate();
	engine->terminate();
}