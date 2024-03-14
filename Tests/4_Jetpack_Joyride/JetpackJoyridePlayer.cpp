#include "JetpackJoyridePlayer.h"

const float JETPACK_JOYRIDE_PLAYER_GRAVITY = 980.0f;
const float JETPACK_JOYRIDE_PLAYER_JUMP_FORCE = -220.0f;

JetpackJoyridePlayer::JetpackJoyridePlayer(float floorPosition) :
	sprite{ "run", {
		Texture{"4_Jetpack_Joyride/Assets/Images/Player/Run1.png", true},
		Texture{"4_Jetpack_Joyride/Assets/Images/Player/Run2.png", true},
		Texture{"4_Jetpack_Joyride/Assets/Images/Player/Run3.png", true},
		Texture{"4_Jetpack_Joyride/Assets/Images/Player/Run4.png", true},
		Texture{"4_Jetpack_Joyride/Assets/Images/Player/Run5.png", true},
		Texture{"4_Jetpack_Joyride/Assets/Images/Player/Run6.png", true}
	} },
	velocity{ 0.0f }, 
	floorPosition{ floorPosition }, 
	propulsionForce{ 0.0f }, 
	isNotKey{ true } {
	sprite.load("fly", {
		Texture{"4_Jetpack_Joyride/Assets/Images/Player/Rising1.png", true},
		Texture{"4_Jetpack_Joyride/Assets/Images/Player/Rising2.png", true},
		Texture{"4_Jetpack_Joyride/Assets/Images/Player/Rising3.png", true},
		Texture{"4_Jetpack_Joyride/Assets/Images/Player/Rising4.png", true},
		Texture{"4_Jetpack_Joyride/Assets/Images/Player/Rising5.png", true},
		Texture{"4_Jetpack_Joyride/Assets/Images/Player/Rising6.png", true}
	});
	sprite.load("fall", {
		Texture{"4_Jetpack_Joyride/Assets/Images/Player/Falling1.png", true},
		Texture{"4_Jetpack_Joyride/Assets/Images/Player/Falling2.png", true},
		Texture{"4_Jetpack_Joyride/Assets/Images/Player/Falling3.png", true},
		Texture{"4_Jetpack_Joyride/Assets/Images/Player/Falling4.png", true},
		Texture{"4_Jetpack_Joyride/Assets/Images/Player/Falling5.png", true},
		Texture{"4_Jetpack_Joyride/Assets/Images/Player/Falling6.png", true}
	});
	sprite.size = glm::vec2{ Engine::FWidth * 0.05f };
	sprite.position = glm::vec2{ Engine::FWidth * 0.3f, floorPosition - (sprite.size.y / 2.0f) };
	sprite.timeChangeTexture = 0.07f;
}

void JetpackJoyridePlayer::updateWindowSize(float floorPosition) {
	this->floorPosition = floorPosition;
	sprite.updateWindowSize();
	sprite.size = glm::vec2{ Engine::FWidth * 0.05f };
	sprite.position = glm::vec2{ Engine::FWidth * 0.3f, floorPosition - (sprite.size.y / 2.0f) };
}
void JetpackJoyridePlayer::update() {
	if (sprite.position.y < (floorPosition - (sprite.size.y / 2.0f))) {
		velocity.y += JETPACK_JOYRIDE_PLAYER_GRAVITY * Engine::DeltaTime;
		sprite.play("fall");
	}
	else sprite.play("run");
	if (Engine::KeyPressed(GLFW_KEY_SPACE)) {
		sprite.play("fly");
		velocity.y = JETPACK_JOYRIDE_PLAYER_JUMP_FORCE + propulsionForce;
		velocity.y = glm::clamp(velocity,
			glm::vec2{ 0.0f, -500.0f },
			glm::vec2{ 0.0f, -JETPACK_JOYRIDE_PLAYER_JUMP_FORCE }).y;
		propulsionForce -= 30.0f;
		isNotKey = false;
	}
	else if(!isNotKey) {
		isNotKey = true;
		velocity.y = JETPACK_JOYRIDE_PLAYER_JUMP_FORCE;
		propulsionForce = 0.0f;
	}

	sprite.position += velocity * Engine::DeltaTime;
	sprite.position = glm::clamp(sprite.position,
		glm::vec2{ 0.0f, sprite.size.x / 2.0f },
		glm::vec2{ 
			Engine::FWidth - (sprite.size.x / 2.0f), 
			floorPosition - (sprite.size.y / 2.0f)
		});
}
void JetpackJoyridePlayer::draw() {
	sprite.draw();
}

float JetpackJoyridePlayer::getPositionY() {
	return sprite.position.y;
}