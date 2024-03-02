#include "BreakoutBricks.h"


BreakoutBricks::BreakoutBricks() {
	glm::vec2 size{ Engine::FWidth * 0.1f, Engine::FHeight * 0.05f };
	glm::vec2 position{ size / 2.0f };

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 10; x++) {
			position.x = (size.x / 2.0f) * (x + 1);
			position.y = (size.y / 2.0f) * (y + 1);

			std::string brickColor{ "3_Breakout/Assets/Images/brick-" };
			if (y == 0) brickColor += "red.png";
			else if (y == 2) brickColor += "green.png";
			else if (y == 1) brickColor += "blue.png";
			else if (y == 3) brickColor += "cian.png";

			E2D::Sprite sprite{ Texture{brickColor.c_str(), true} };
			sprite.size = size;
			sprite.position = position;
			Brick brick{ sprite, false };

			bricks[x][y] = brick;
		}
	}
}

void BreakoutBricks::updateWindowsSize() {
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 10; x++) {
			Brick& brick{ bricks[x][y] };
			if (!brick.isBreak) brick.sprite.updateWindowSize();
		}
	}
}
void BreakoutBricks::draw() {
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 10; x++) {
			Brick& brick{ bricks[x][y] };
			if (!brick.isBreak) brick.sprite.draw();
		}
	}
}