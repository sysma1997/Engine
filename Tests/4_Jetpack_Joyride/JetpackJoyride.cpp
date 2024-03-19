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
	JetpackJoyrideRocket* rocket{ new JetpackJoyrideRocket{} };
	JetpackJoyrideObstacles* obstacles{ new JetpackJoyrideObstacles{} };
	EUI::Label* label{ new EUI::Label{"Assets/Fonts/arial.ttf", 24} };

	int points{ 0 }, bestPoints{ 0 };
	std::ifstream readBestPoints{ "bestPoints.txt" };
	std::string line;
	while (std::getline(readBestPoints, line)) bestPoints = std::stoi(line);

	player->pause(true);
	int timeToShootRocket{ rand() % 3 };
	float currentTime{ 0.0f };

	auto resetGame = [&] {
		status = JetpackJoyrideStatus::MENU;
		map = new JetpackJoyrideMap{};
		player = new JetpackJoyridePlayer{ map->floorPosition };
		rocket = new JetpackJoyrideRocket{};
		obstacles = new JetpackJoyrideObstacles{};

		if (points > bestPoints) bestPoints = points;
		points = 0;
		player->pause(true);
		timeToShootRocket = rand() % 3;
		currentTime = 0.0f;
	};

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

			if (rocket->isPlayerCollision(player->getSprite()) || 
				obstacles->isPlayerCollision(player->getSprite())) {
				player->pause(true);
				status = JetpackJoyrideStatus::RESULT;

				if (points > bestPoints) {
					std::ofstream writeBestPoints{ "bestPoints.txt" };
					writeBestPoints << points;
					writeBestPoints.close();
				}
			}
		}
		else if (status == JetpackJoyrideStatus::PAUSE) {
			if (Engine::KeyJustPressed(GLFW_KEY_ESCAPE)) {
				status = JetpackJoyrideStatus::GAME;
				player->pause(false);
			}
		}
		else if (status == JetpackJoyrideStatus::RESULT) {
			if (Engine::KeyJustPressed(GLFW_KEY_SPACE)) {
				resetGame();
			}
			if (Engine::KeyJustPressed(GLFW_KEY_ESCAPE)) {
				engine->closeLoop();
			}
		}

		map->draw();
		player->draw();
		rocket->draw();
		obstacles->draw();

		std::string text{ "Points: " + std::to_string(points) };
		label->render(text, glm::vec2{ 10.0f });
		if (bestPoints != 0) {
			text = "Best points: " + std::to_string(bestPoints);
			glm::vec2 size{ label->getSizeText(text) };
			glm::vec2 position{ engine->getSizeCenter().x - (size.x / 2.0f), 10.0f };
			label->render(text, position);
		}

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
		if (status == JetpackJoyrideStatus::RESULT) {
			text = "You lose";
			glm::vec2 size{ label->getSizeText(text) };
			glm::vec2 position{ engine->getSizeCenter() - (size / 2.0f) };
			position.y -= size.y / 2.0f;
			label->render(text, position);
			text = ((points > bestPoints) ? "Your best score: " : "Your score: ") + std::to_string(points);
			size = label->getSizeText(text);
			position = engine->getSizeCenter() - (size / 2.0f);
			position.y += size.y / 2.0f;
			label->render(text, position);
			text = "Press 'SPACE' to reset game";
			size = label->getSizeText(text);
			position.x = engine->getSizeCenter().x - (size.x / 2.0f);
			position.y += size.y;
			label->render(text, position);
			text = "Press 'ESCAPE' to exit game";
			size = label->getSizeText(text);
			position.x = engine->getSizeCenter().x - (size.x / 2.0f);
			position.y += size.y;
			label->render(text, position);
		}

		engine->renderFrame();
	}

	engine->terminate();
}