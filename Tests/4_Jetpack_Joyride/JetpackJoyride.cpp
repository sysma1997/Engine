#include "JetpackJoyride.h"

void jetpackJoyride() {
	Engine* engine{ new Engine{ "Jetpack Joyride", 420, 612 } };

	JetpackJoyrideMap* map{ new JetpackJoyrideMap{} };
	JetpackJoyridePlayer* player{ new JetpackJoyridePlayer{map->floorPosition} };

	while (engine->isLoop()) {
		engine->newFrame([&] {
			map->updateWindowSize();
		});

		map->update();
		player->update();

		map->draw();
		player->draw();

		engine->renderFrame();
	}

	engine->terminate();
}