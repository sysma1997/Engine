#include "Breakout.h"

enum class BreakoutStatus {
	GAME,
	PAUSE, 
	RESULT
};

void breakoutBricksUpdateWindowSize(BreakoutBricks* bricks);
void breakoutCheckCollisionBricksBall(BreakoutBricks* bricks, BreakoutBall* ball, 
	int& points, int& bestPoints);

void breakout() {
	srand(time(NULL));
	Engine* engine{ new Engine{"Breakout"} };
	
	BreakoutStatus status{ BreakoutStatus::GAME };
	EUI::Label* label{ new EUI::Label{"3_Breakout/Assets/Fonts/OCRAEXT.TTF", 24} };
	BreakoutPlayer* player{ new BreakoutPlayer{} };
	BreakoutBall* ball{ new BreakoutBall{player->sprite.position.y, player->sprite.size.y} };
	BreakoutBricks* bricks{ new BreakoutBricks{4, 10} };

	int points{ 0 }, bestPoints{ 0 }, lives{ 3 };
	auto resetGame = [&] {
		status = BreakoutStatus::GAME;

		for (int y = 0; y < bricks->columns; y++) {
			for (int x = 0; x < bricks->rows; x++) {
				BreakoutBrick& brick{ bricks->bricks[y][x] };
				brick.isBreak = false;
			}
		}
		player->sprite.position = glm::vec2{
			Engine::FWidth / 2.0f,
			Engine::FHeight - (player->sprite.size.y / 2.0f) - 10.0f
		};
		ball->isSubject = true;
		ball->updateWindowSize(player->sprite.position.y, player->sprite.size.y);

		points = 0;
		lives = 3;
	};

	std::ifstream readBestPoints{ "bestPoints.txt" };
	std::string line;
	while (std::getline(readBestPoints, line)) {
		bestPoints = std::stoi(line);
	}

	while (engine->isLoop()) {
		engine->newFrame([&] {
			label->updateWindowSize();
			player->updateWindowSize();
			ball->updateWindowSize(player->sprite.position.y, player->sprite.size.y);
			breakoutBricksUpdateWindowSize(bricks);
		});

		if (status == BreakoutStatus::GAME ||
			status == BreakoutStatus::PAUSE) {
			if (Engine::KeyJustPressed(GLFW_KEY_ESCAPE)) {
				status = (status == BreakoutStatus::GAME) ?
					BreakoutStatus::PAUSE : BreakoutStatus::GAME;
			}
			if (status == BreakoutStatus::PAUSE && Engine::KeyJustPressed(GLFW_KEY_Q))
				engine->closeLoop();
		}

		if (status == BreakoutStatus::GAME) {
			player->processInput();
			ball->processInput();
			ball->update(player->sprite, lives);
			breakoutCheckCollisionBricksBall(bricks, ball, points, bestPoints);
		}

		ball->sprite.draw();
		player->sprite.draw();
		bricks->draw();

		std::string text{ "Points: " + std::to_string(points) };
		glm::vec2 position{ 5.0f };
		label->render(text, position);
		text = "Best points: " + std::to_string(bestPoints);
		glm::vec2 size{ label->getSizeText(text) };
		position = glm::vec2{
			position.x,
			position.y
		};
		text = "Lives: " + std::to_string(lives);
		size = label->getSizeText(text);
		position = glm::vec2{ Engine::FWidth - size.x - 5.0f, 5.0f };
		label->render(text, position);
		if (status == BreakoutStatus::PAUSE) {
			text = "PAUSE";
			size = label->getSizeText(text);
			float lastSizeY = size.y;
			position = glm::vec2{ (Engine::FWidth / 2.0f) - (size.x / 2.0f), (Engine::FHeight / 2.0f) - (size.y / 2.0f) };
			label->render(text, position);
			text = "Press 'Q' to exit game";
			size = label->getSizeText(text);
			position = glm::vec2{
				(Engine::FWidth / 2.0f) - (size.x / 2.0f), 
				(Engine::FHeight / 2.0f) - (size.y / 2.0f) + lastSizeY + 10.0f
			};
			label->render(text, position);
		}
		else if (status == BreakoutStatus::RESULT) {
			text = "YOU WIN!!";
			size = label->getSizeText(text);
			float lastSizeY = size.y;
			position = glm::vec2{ (Engine::FWidth / 2.0f) - (size.x / 2.0f), (Engine::FHeight / 2.0f) - (size.y / 2.0f) };
			label->render(text, position);
			text = "Points: " + std::to_string(points);
			size = label->getSizeText(text);
			lastSizeY = size.y;
			position = glm::vec2{
				(Engine::FWidth / 2.0f) - (size.x / 2.0f),
				(Engine::FHeight / 2.0f) - (size.y / 2.0f) + lastSizeY + 10.0f
			};
			label->render(text, position);
			text = "Best points: " + std::to_string(bestPoints);
			size = label->getSizeText(text);
			position.x = (Engine::FWidth / 2.0f) - (size.x / 2.0f);
			position.y += lastSizeY + 10.0f;
			label->render(text, position);
		}

		if (lives == 0)
			resetGame();

		engine->renderFrame();
	}

	engine->terminate();
}

void breakoutBricksUpdateWindowSize(BreakoutBricks* bricks) {
	glm::vec2 size{ Engine::FWidth * 0.1f, Engine::FHeight * 0.05f };
	glm::vec2 position{ size / 2.0f };

	for (int y = 0; y < bricks->columns; y++) {
		position.y = (size.y * (y + 1)) - (size.y / 2.0f);

		for (int x = 0; x < bricks->rows; x++) {
			position.x = (size.x * (x + 1)) - (size.x / 2.0f);
			BreakoutBrick& brick{ bricks->bricks[y][x] };
			
			brick.sprite.updateWindowSize();
			brick.sprite.size = size;
			brick.sprite.position = position;
		}
	}
}
void breakoutCheckCollisionBricksBall(BreakoutBricks* bricks, BreakoutBall* ball, 
	int& points, int& bestPoints) {
	for (int y = 0; y < bricks->columns; y++) {
		for (int x = 0; x < bricks->rows; x++) {
			BreakoutBrick& brick{ bricks->bricks[y][x] };
			if (brick.isBreak) continue;

			if (E2D::Object::CheckCollision(brick.sprite, ball->sprite)) {
				brick.isBreak = true;
				points += 1;
				ball->collisionBrick();

				if (points > bestPoints) {
					bestPoints = points;
					
					std::ofstream writeBestPoints{ "bestPoints.txt" };
					writeBestPoints << bestPoints;
					writeBestPoints.close();
				}
			}
		}
	}
}