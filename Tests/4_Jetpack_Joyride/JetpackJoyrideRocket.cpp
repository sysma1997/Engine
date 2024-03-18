#include "JetpackJoyrideRocket.h"

const float JETPACK_JOYRIDE_ROCKET_VELOCITY_ALERT = 2.0f;
const float JETPACK_JOYRIDE_ROCKET_VELOCITY_SHOOT = 800.0f;
const float JETPACK_JOYRIDE_ROCKET_TIME_TO_SHOOT = 3.0f;

JetpackJoyrideRocket::JetpackJoyrideRocket() : 
	state{ State::ALERTING }, 
	alert{ Texture{"4_Jetpack_Joyride/Assets/Images/alert.png", true} },
	rocket{ Texture{"4_Jetpack_Joyride/Assets/Images/rocket.png", true} }, 
	flames{ "flame", {
		Texture{"4_Jetpack_Joyride/Assets/Images/rocket_flame1.png", true},
		Texture{"4_Jetpack_Joyride/Assets/Images/rocket_flame2.png", true}
	} }, 
	playerPos{ 0.0f }, 
	timeToShoot{ 0.0 } {
	alert.size = glm::vec2{ Engine::FWidth * 0.1f };
	alert.position = glm::vec2{ Engine::FWidth - (alert.size.x / 2.0f), Engine::FHeight / 2.0f };
	rocket.size = glm::vec2{ Engine::FWidth * 0.03f };
	rocket.position = glm::vec2{ Engine::FWidth + rocket.size.x , 0.0f};
	rocket.rotate = 180.0f;
	flames.size = glm::vec2{ Engine::FWidth * 0.03f };
	flames.position = glm::vec2{
		rocket.position.x + (rocket.size.x / 2.0f) + (flames.size.x / 2.0f),
		rocket.position.y
	};
	flames.timeChangeTexture = 0.08f;
}

void JetpackJoyrideRocket::alerting(float playerPos) {
	float diff{ playerPos - alert.position.y };
	alert.position.y += diff * JETPACK_JOYRIDE_ROCKET_VELOCITY_ALERT * Engine::DeltaTime;
}
void JetpackJoyrideRocket::shoot() {
	rocket.position.y = alert.position.y;
	rocket.position.x -= JETPACK_JOYRIDE_ROCKET_VELOCITY_SHOOT * Engine::DeltaTime;
	flames.position = glm::vec2{
		rocket.position.x + (rocket.size.x / 2.0f) + (flames.size.x / 2.0f),
		rocket.position.y
	};
}

void JetpackJoyrideRocket::updateWindowSize() {
	alert.updateWindowSize();
	rocket.updateWindowSize();
	flames.updateWindowSize();

	alert.size = glm::vec2{ Engine::FWidth * 0.1f };
	alert.position = glm::vec2{ Engine::FWidth - (alert.size.x / 2.0f), Engine::FHeight / 2.0f };
	rocket.size = glm::vec2{ Engine::FWidth * 0.03f };
	rocket.position = glm::vec2{ Engine::FWidth + rocket.size.x , 0.0f };
	flames.size = glm::vec2{ Engine::FWidth * 0.03f };
	flames.position = glm::vec2{
		rocket.position.x + (rocket.size.x / 2.0f) + (flames.size.x / 2.0f),
		rocket.position.y
	};
}
void JetpackJoyrideRocket::update(float playerPos) {
	if (state == State::ALERTING) {
		alerting(playerPos);

		timeToShoot += Engine::DeltaTime;
		if (timeToShoot > JETPACK_JOYRIDE_ROCKET_TIME_TO_SHOOT) state = State::SHOOT;
	}
	else shoot();
}
void JetpackJoyrideRocket::draw() {
	if (state == State::ALERTING) {
		alert.draw();
	}
	else {
		rocket.draw();
		flames.draw();
	}
}

bool JetpackJoyrideRocket::isOutWindow() {
	if (rocket.position.x < 0.0f) return true;

	return false;
}
bool JetpackJoyrideRocket::isPlayerCollision(E2D::Object& player) {
	return E2D::Object::CheckCollision(rocket, player);
}