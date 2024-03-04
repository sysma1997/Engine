#include "BreakoutBricks.h"

BreakoutBricks::BreakoutBricks(int columns, int rows) : bricks{}, columns{ columns }, rows{ rows } {
	glm::vec2 size{ Engine::FWidth * 0.1f, Engine::FHeight * 0.05f };
	glm::vec2 position{ size / 2.0f };

	for (int y = 0; y < columns; y++) {
		std::vector<BreakoutBrick> bricksRows{};
		position.y = (size.y * (y + 1)) - (size.y / 2.0f);
		
		for (int x = 0; x < rows; x++) {
			position.x = (size.x * (x + 1)) - (size.x / 2.0f);

			std::string brickColor{ "3_Breakout/Assets/Images/brick-" };
			if (y == 0) brickColor += "red.png";
			else if (y == 2) brickColor += "green.png";
			else if (y == 1) brickColor += "blue.png";
			else if (y == 3) brickColor += "cian.png";

			E2D::Sprite sprite{ Texture{brickColor.c_str(), true} };
			sprite.size = size;
			sprite.position = position;
			BreakoutBrick brick{ sprite, false };

			bricksRows.push_back(brick);
		}
		
		bricks.push_back(bricksRows);
	}
}

void BreakoutBricks::draw() {
	for (int y = 0; y < columns; y++) {
		for (int x = 0; x < rows; x++) {
			BreakoutBrick& brick{ bricks[y][x] };

			if (!brick.isBreak) brick.sprite.draw();
		}
	}
}