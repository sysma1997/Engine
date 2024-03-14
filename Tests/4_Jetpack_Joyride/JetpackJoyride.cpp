#include "JetpackJoyride.h"

void jetpackJoyride() {
	srand(time(NULL));
	Engine* engine{ new Engine{ "Jetpack Joyride", 800, 500 } };

	JetpackJoyrideMap* map{ new JetpackJoyrideMap{} };
	JetpackJoyridePlayer* player{ new JetpackJoyridePlayer{map->floorPosition} };
	JetpackJoyrideRocket* rocket{ new JetpackJoyrideRocket{} };

	int timeToShootRocket{ rand() % 3 };
	float currentTime{ 0.0f };
	while (engine->isLoop()) {
		engine->newFrame([&] {
			map->updateWindowSize();
			player->updateWindowSize(map->floorPosition);
			
			rocket->updateWindowSize();
		});

		if (rocket->isOutWindow()) {
			currentTime += Engine::DeltaTime;
			if (currentTime > static_cast<float>(timeToShootRocket)) {
				rocket = new JetpackJoyrideRocket{};
				timeToShootRocket = rand() % 3;
				currentTime = 0.0f;
			}
		}

		map->update();
		player->update();
		rocket->update(player->getPositionY());

		map->draw();
		player->draw();
		rocket->draw();

		engine->renderFrame();
	}

	engine->terminate();
}