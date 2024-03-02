#include "Breakout.h"

void breakout() {
	Engine* engine{ new Engine{"Breakout"} };
	
	BreakoutPlayer* player{ new BreakoutPlayer{} };
	BreakoutBall* ball{ new BreakoutBall{player->sprite.position.y, player->sprite.size.y} };
	BreakoutBricks* bricks{ new BreakoutBricks{} };

	while (engine->isLoop()) {
		engine->newFrame([&] {
			player->sprite.updateWindowSize();
			ball->sprite.updateWindowSize();
			bricks->updateWindowsSize();
		});

		player->processInput();
		ball->processInput();
		ball->update(player->sprite);

		player->sprite.draw();
		ball->sprite.draw();
		bricks->draw();

		engine->renderFrame();
	}

	engine->terminate();
}