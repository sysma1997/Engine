#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>

#include <Engine.h>
#include <2D/Rectangle.h>
#include <UI/Label.h>

#include "Core/Player.h"
#include "Core/Ball.h"
#include "Core/Opponent.h"

enum Status {
	MENU, 
	GAME, 
	PAUSE, 
	RESULT
};

int main() {
	srand(time(NULL));
	Engine* engine{ new Engine{"Pong"} };
	EUI::Label* label{ new EUI::Label{"Assets/Fonts/Robot_Font.otf", 32} };

	E2D::Rectangle* divition{ new E2D::Rectangle{} };
	divition->position = Engine::GetSizeCenter();
	divition->size = glm::vec2{ 5.0f, Engine::FHeight };

	Player* player{ new Player{} };
	Ball* ball{ new Ball{} };
	Opponent* opponent{ new Opponent{} };

	Status status{ Status::MENU };

	int playerPoints{ 0 }, opponentPoints{ 0 }, pointsToWin{ 9 };
	auto reset = [&](bool level = false) {
		player->reset();
		ball->reset();
		opponent->reset();

		if (level) {
			playerPoints = 0;
			opponentPoints = 0;
		}
	};

	while (engine->isLoop()) {
		engine->newFrame([&]() {
			divition->updateWindowSize();

			divition->position = Engine::GetSizeCenter();
			divition->size = glm::vec2{ 5.0f, Engine::FHeight };

			player->updateWindowSize();
			ball->updateWindowSize();
			opponent->updateWindowSize();
		});

		if (status == Status::GAME ||
			status == Status::PAUSE) {
			if (Engine::KeyJustPressed(GLFW_KEY_ESCAPE))
				status = (status == Status::GAME) ? Status::PAUSE : Status::GAME;
		}

		if (status == Status::MENU) {
			if (Engine::KeyJustPressed(GLFW_KEY_SPACE)) {
				status = Status::GAME;
			}
		}
		else if (status == Status::GAME) {
			player->progress();
			ball->progress(player->getSprite(), opponent->getSprite());
			opponent->progress(ball->getPosition());

			int isPoint{ ball->isOut() };
			if (isPoint == 1) {
				playerPoints++;
				reset();
			}
			else if (isPoint == 2) {
				opponentPoints++;
				reset();
			}
		}
		else if (status == Status::RESULT) {
			if (Engine::KeyJustPressed(GLFW_KEY_SPACE)) {
				reset(true);
				status = Status::GAME;
			}
		}

		if (playerPoints > pointsToWin ||
			opponentPoints > pointsToWin) {
			status = Status::RESULT;
		}

		divition->draw();
		player->draw();
		ball->draw();
		opponent->draw();

		std::string text{ std::to_string(playerPoints) + " - " + std::to_string(opponentPoints) };
		glm::vec2 textSize{ label->getSizeText(text)};
		glm::vec2 textPos{ Engine::GetSizeCenter().x - (textSize.x / 2.0f), textSize.y + 5.0f };
		label->render(text, textPos);
		if (status == Status::MENU) {
			text = "Press SPACE to init game.";
			textSize = label->getSizeText(text);
			textPos = glm::vec2{ Engine::GetSizeCenter() - (textSize / 2.0f) };
			label->render(text, textPos, 1.0f, glm::vec3{ 0.0f, 1.0f, 0.0f });
		}
		if (status == Status::PAUSE) {
			text = "PAUSE";
			textSize = label->getSizeText(text);
			textPos = glm::vec2{ Engine::GetSizeCenter() - (textSize / 2.0f) };
			label->render(text, textPos);
		}
		if (status == Status::RESULT) {
			glm::vec3 color{ 0.0f };
			if (playerPoints > pointsToWin) {
				text = "You WIN!";
				color = glm::vec3{ 0.0f, 1.0f, 0.0f };
			}
			if (opponentPoints > pointsToWin) {
				text = "You LOSE!";
				color = glm::vec3{ 1.0f, 0.0f, 0.0f };
			}
			textSize = label->getSizeText(text);
			textPos = glm::vec2{ Engine::GetSizeCenter() - (textSize / 2.0f) };
			label->render(text, textPos, 1.0f, color);
			text = "Press SPACE to reset game.";
			textSize = label->getSizeText(text);
			textPos.x = Engine::GetSizeCenter().x - (textSize.x / 2.0f);
			textPos.y = textPos.y + textSize.y + 0.5f;
			label->render(text, textPos, 1.0f, color);
		}

		engine->renderFrame();
	}

	engine->terminate();

	return 0;
}