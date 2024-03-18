#include "JetpackJoyride.h"

enum class JetpackJoyrideStatus {
	MENU,
	GAME,
	PAUSE,
	RESULT
};

void jetpackJoyride() {
	srand(time(NULL));
	Engine* engine{ new Engine{ "Jetpack Joyride", 800, 500 } };

	JetpackJoyrideStatus status{ JetpackJoyrideStatus::MENU };
	JetpackJoyrideMap* map{ new JetpackJoyrideMap{} };
	JetpackJoyridePlayer* player{ new JetpackJoyridePlayer{map->floorPosition} };
	player->pause(true);
	JetpackJoyrideRocket* rocket{ new JetpackJoyrideRocket{} };
	JetpackJoyrideObstacles* obstacles{ new JetpackJoyrideObstacles{} };
	EUI::Label* label{ new EUI::Label{"Assets/Fonts/arial.ttf", 24} };

	int points{ 0 }, bestPoints{ 0 };
	int timeToShootRocket{ rand() % 3 };
	float currentTime{ 0.0f };
	while (engine->isLoop()) {
		engine->newFrame([&] {
			map->updateWindowSize();
			player->updateWindowSize(map->floorPosition);
			rocket->updateWindowSize();
			obstacles->updateWindowSize();
			label->updateWindowSize();
		});

		if (rocket->isOutWindow()) {
			currentTime += Engine::DeltaTime;
			if (currentTime > static_cast<float>(timeToShootRocket)) {
				rocket = new JetpackJoyrideRocket{};
				timeToShootRocket = rand() % 3;
				currentTime = 0.0f;
			}
		}

		if (status == JetpackJoyrideStatus::MENU) {
			if (Engine::KeyJustPressed(GLFW_KEY_SPACE)) {
				status = JetpackJoyrideStatus::GAME;
				player->pause(false);
			}
		}
		else if (status == JetpackJoyrideStatus::GAME) {
			if (Engine::KeyJustPressed(GLFW_KEY_ESCAPE)) {
				status = JetpackJoyrideStatus::PAUSE;
				player->pause(true);
			}

			map->update();
			player->update(points);
			rocket->update(player->getPositionY());
			obstacles->update();

			if (rocket->isPlayerCollision(player->getSprite())) {
				player->pause(true);
				status = JetpackJoyrideStatus::RESULT;
			}
		}
		else if (status == JetpackJoyrideStatus::PAUSE) {
			if (Engine::KeyJustPressed(GLFW_KEY_ESCAPE)) {
				status = JetpackJoyrideStatus::GAME;
				player->pause(false);
			}
		}

		map->draw();
		player->draw();
		rocket->draw();
		obstacles->draw();

		std::string text{ "Points: " + std::to_string(points) };
		label->render(text, glm::vec2{ 10.0f });

		if (status == JetpackJoyrideStatus::MENU) {
			text = "Press 'SPACE' to start game";
			glm::vec2 size{ label->getSizeText(text) };
			glm::vec2 position{
				(Engine::FWidth / 2.0f) - (size.x / 2.0f),
				(Engine::FHeight / 2.0f) - (size.y / 2.0f)
			};
			label->render(text, position);
		}
		if (status == JetpackJoyrideStatus::PAUSE) {
			text = "PAUSE";
			glm::vec2 size{ label->getSizeText(text) };
			glm::vec2 position{ engine->getSizeCenter() - (size / 2.0f) };
			label->render(text, position);
		}

		engine->renderFrame();
	}

	engine->terminate();
}