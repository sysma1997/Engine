#include "JetpackJoyride.h"

void jetpackJoyride() {
	Engine* engine{ new Engine{"Jetpack Joyride", 420, 612 } };

	JetpackJoyrideMap* map{ new JetpackJoyrideMap{} };

	while (engine->isLoop()) {
		engine->newFrame([&] {
			map->updateWindowSize();
		});

		map->update();

		map->draw();

		engine->renderFrame();
	}

	engine->terminate();
}