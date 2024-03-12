#include "JetpackJoyrideMap.h"

JetpackJoyrideMap::JetpackJoyrideMap() : 
	background{
		E2D::Sprite{ Texture{"4_Jetpack_Joyride/Assets/Images/background.png", true} },
		E2D::Sprite{ Texture{"4_Jetpack_Joyride/Assets/Images/background.png", true} }
	},
	velocity{ 200.0f } {
	background[0].position = glm::vec2{ Engine::FWidth / 2.0f, Engine::FHeight / 2.0f };
	background[0].size = glm::vec2{ Engine::FWidth * 3, Engine::FHeight };
	background[1].position = glm::vec2{
		background[0].position.x + background[0].size.x, 
		background[0].position.y
	};
	background[1].size = background[0].size;
}

void JetpackJoyrideMap::updateWindowSize() {
	for (int i{ 0 }; i < 2; i++) {
		background[i].updateWindowSize();
		background[i].size = glm::vec2{ Engine::FWidth * 3, Engine::FHeight };
	}
}
void JetpackJoyrideMap::update() {
	for (int i{ 0 }; i < 2; i++) {
		background[i].position.x -= velocity * Engine::DeltaTime;

		if (background[i].position.x < -(background[i].size.x / 2.0f)) {
			int index = (i == 0) ? 1 : 0;

			glm::vec2 pos{ background[index].position };
			background[i].position = glm::vec2{
				(pos.x + background[i].size.x) - 4.0f,
				pos.y
			};
		}
	}
}
void JetpackJoyrideMap::draw() {
	for (int i{ 0 }; i < 2; i++) {
		background[i].draw();
	}
}