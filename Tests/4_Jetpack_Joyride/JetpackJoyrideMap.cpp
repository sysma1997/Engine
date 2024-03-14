#include "JetpackJoyrideMap.h"

JetpackJoyrideMap::JetpackJoyrideMap() : 
	background{
		E2D::Sprite{ Texture{"4_Jetpack_Joyride/Assets/Images/background.png", true} },
		E2D::Sprite{ Texture{"4_Jetpack_Joyride/Assets/Images/background.png", true} }
	},
	floor{ 
		E2D::Sprite{ Texture{"4_Jetpack_Joyride/Assets/Images/base.png", true} }, 
		E2D::Sprite{ Texture{"4_Jetpack_Joyride/Assets/Images/base.png", true} }
	},
	velocity{ 200.0f }, 
	floorPosition{ 0.0f } {
	background[0].size = glm::vec2{ Engine::FWidth, Engine::FHeight };
	background[0].position = glm::vec2{ Engine::FWidth / 2.0f, Engine::FHeight / 2.0f };
	background[1].position = glm::vec2{
		background[0].position.x + background[0].size.x, 
		background[0].position.y
	};
	background[1].size = background[0].size;

	floor[0].size = glm::vec2{ Engine::FWidth, Engine::FHeight * 0.1f };
	floor[0].position = glm::vec2{ Engine::FWidth / 2.0f, Engine::FHeight - (floor[0].size.y / 2.0f) };
	floor[1].size = floor[0].size;
	floor[1].position = glm::vec2{ floor[0].position.x + floor[0].size.x, floor[0].position.y };

	floorPosition = floor[0].position.y - (floor[0].size.y / 2.0f);
}

void JetpackJoyrideMap::updateWindowSize() {
	for (int i{ 0 }; i < 2; i++) {
		background[i].updateWindowSize();
		background[i].size = glm::vec2{ Engine::FWidth, Engine::FHeight };
		background[i].position = glm::vec2{ background[i].position.x, Engine::FHeight / 2.0f };
		floor[i].updateWindowSize();
		floor[i].size = glm::vec2{ Engine::FWidth, Engine::FHeight * 0.1f };
		floor[i].position = glm::vec2{ floor[i].position.x, Engine::FHeight - (floor[i].size.y / 2.0f) };
	}

	floorPosition = floor[0].position.y - (floor[0].size.y / 2.0f);
}
void JetpackJoyrideMap::update() {
	for (int i{ 0 }; i < 2; i++) {
		background[i].position.x -= velocity * Engine::DeltaTime;
		floor[i].position.x -= velocity * Engine::DeltaTime;

		if (background[i].position.x < -(background[i].size.x / 2.0f)) {
			int index = (i == 0) ? 1 : 0;

			glm::vec2 pos{ background[index].position };
			background[i].position = glm::vec2{
				(pos.x + background[i].size.x) - 4.0f,
				pos.y
			};
		}
		if (floor[i].position.x < -(floor[i].size.x / 2.0f)) {
			int index = (i == 0) ? 1 : 0;

			glm::vec2 pos{ floor[index].position };
			floor[i].position = glm::vec2{
				(pos.x + floor[i].size.x) - 10.0f,
				pos.y
			};
		}
	}
}
void JetpackJoyrideMap::draw() {
	for (int i{ 0 }; i < 2; i++) {
		background[i].draw();
		floor[i].draw();
	}
}