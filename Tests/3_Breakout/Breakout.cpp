#include "Breakout.h"

void breakout() {
	Engine* engine{ new Engine{"Breakout"} };
	
	BreakoutPlayer* player{ new BreakoutPlayer{} };
	BreakoutBall* ball{ new BreakoutBall{player->sprite.position.y, player->sprite.size.y} };
	BreakoutBricks* bricks{ new BreakoutBricks{4, 10} };

	while (engine->isLoop()) {
		engine->newFrame([&] {
			player->updateWindowSize();
			ball->updateWindowSize(player->sprite.position.y, player->sprite.size.y);
		});

		player->processInput();
		ball->processInput();
		ball->update(player->sprite);
		for (int y = 0; y < bricks->columns; y++) {
			for (int x = 0; x < bricks->rows; x++) {
				BreakoutBrick& brick{ bricks->bricks[y][x] };

				if (E2D::Object::CheckCollision(brick.sprite, ball->sprite)) {
					brick.isBreak = true;
				}
			}
		}

		player->sprite.draw();
		bricks->draw();
		ball->sprite.draw();

		engine->renderFrame();
	}

	engine->terminate();
}