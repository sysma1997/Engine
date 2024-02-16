#include "Pong.h"

enum class PongState {
	MENU,
	GAME,
	PAUSE, 
	RESULTS
};

void pong() {
	srand(time(NULL));
	PongState state{ PongState::MENU };
	Engine* engine{ new Engine{"Pong"} };
	EUI::Test* imgui{ new EUI::Test{engine->window} };

	E2D::Rectangle* division{ new E2D::Rectangle{engine->fWidth(), engine->fHeight()} };
	E2D::Rectangle* player{ new E2D::Rectangle{engine->fWidth(), engine->fHeight()} };
	E2D::Rectangle* opponent{ new E2D::Rectangle{engine->fWidth(), engine->fHeight()} };
	E2D::Sprite ballSprite{ E2D::Sprite{*(new Texture{"1_Pong/Assets/Images/Ball.png", true}),
		engine->fWidth(), engine->fHeight()} };
	Ball* ball{ new Ball{ballSprite} };

	EUI::Label* label{ new EUI::Label{"1_Pong/Assets/Fonts/Robot_Font.otf", 64, engine->fWidth(), engine->fHeight()} };

	auto resetPosition = [&]() {
		glm::vec2 centerPosition{ engine->fWidth() / 2.0f, engine->fHeight() / 2.0f };
		division->position = centerPosition;
		division->size = glm::vec2{ engine->fWidth() * 0.01f, engine->fHeight() };

		glm::vec2 size{ engine->fWidth() * 0.03f, (engine->fHeight() / 2.0f) * 0.3f };
		player->position = glm::vec2{ (engine->fWidth() * (0.03f / 2.0f)) + 5.0f, engine->fHeight() / 2.0f };
		player->size = size;
		opponent->position = glm::vec2{ engine->fWidth() - (player->position.x), engine->fHeight() / 2.0f };
		opponent->size = size;

		ball->sprite.position = centerPosition;
		ball->sprite.size = glm::vec2{ engine->fWidth() * 0.05f, engine->fWidth() * 0.05f };
		};
	resetPosition();

	int pointsPlayer{ 0 }, pointsOpponent{ 0 };

	bool isPlaying{ false };
	bool isPause{ false };
	while (engine->isLoop()) {
		engine->newFrame([&]() {
			float width = engine->fWidth(), height = engine->fHeight();
			division->updateWindowSize(width, height);
			player->updateWindowSize(width, height);
			opponent->updateWindowSize(width, height);
			ball->sprite.updateWindowSize(width, height);

			resetPosition();
			});

		if (state == PongState::MENU) {
			if (Engine::Keys[GLFW_KEY_SPACE] && !Engine::KeyProcessed[GLFW_KEY_SPACE]) {
				Engine::KeyProcessed[GLFW_KEY_SPACE] = true;
				state = PongState::GAME;
				
				ball->initRandomDirection();
			}
			if (Engine::Keys[GLFW_KEY_ESCAPE] && !Engine::KeyProcessed[GLFW_KEY_ESCAPE]) {
				Engine::KeyProcessed[GLFW_KEY_ESCAPE] = true;
				engine->closeLoop();
			}
		}
		if (state == PongState::GAME || 
			state == PongState::PAUSE) {
			if (Engine::Keys[GLFW_KEY_ESCAPE] && !Engine::KeyProcessed[GLFW_KEY_ESCAPE]) {
				Engine::KeyProcessed[GLFW_KEY_ESCAPE] = true;
				state = (state == PongState::GAME) ? PongState::PAUSE : PongState::GAME;
			}

			if (state == PongState::GAME) {
				playerProcessInput(*player, engine->fHeight());
				ball->update(engine->fHeight(), *player, *opponent);
				if (ball->outScreen(engine->fWidth(), pointsPlayer, pointsOpponent)) {
					resetPosition();
					ball->velocity = 200.0f;
					ball->initRandomDirection();
				}
				iaOpponent(*opponent, ball->sprite, engine->fHeight());
			}
		}

		division->draw();
		player->draw();
		opponent->draw();
		ball->sprite.draw();

		float posPlayerX{ (engine->fWidth() / 2.0f) - 100.0f };
		label->render(std::to_string(pointsPlayer), glm::vec2{ posPlayerX, 5.0f });
		float posOpponentX{ (engine->fWidth() / 2.0f) + 80.0f };
		label->render(std::to_string(pointsOpponent), glm::vec2{ posOpponentX, 5.0f });

		if (state == PongState::MENU) {
			label->render("Press SPACE to init game", glm::vec2{ 200.0f, engine->fHeight() / 2.0f }, 0.5f);
			label->render("Press ESCAPE to exit",
				glm::vec2{ 250.0f, (engine->fHeight() / 2.0f + 20.0f) }, 0.4f,
				glm::vec3{ 1.0f, 0.0f, 0.0f });
		}

		//imgui->newFrame();
		//ImGui::Begin("Pos");
		//ImGui::Text("pos player x");
		//ImGui::InputFloat("##posPlayerX", &posPlayerX);
		//ImGui::End();
		//imgui->renderFrame();
		engine->renderFrame();
	}

	imgui->terminate();
	engine->terminate();
}