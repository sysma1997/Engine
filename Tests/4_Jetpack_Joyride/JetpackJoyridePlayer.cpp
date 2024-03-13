#include "JetpackJoyridePlayer.h"

const float JETPACK_JOYRIDE_PLAYER_GRAVITY = 980.0f;
const float JETPACK_JOYRIDE_PLAYER_JUMP_FORCE = -220.0f;

JetpackJoyridePlayer::JetpackJoyridePlayer(float floorPosition) :
	sprite{ {
		Texture{"4_Jetpack_Joyride/Assets/Images/Player/Run1.png", true},
		Texture{"4_Jetpack_Joyride/Assets/Images/Player/Run2.png", true}, 
		Texture{"4_Jetpack_Joyride/Assets/Images/Player/Run3.png", true}, 
		Texture{"4_Jetpack_Joyride/Assets/Images/Player/Run4.png", true}, 
		Texture{"4_Jetpack_Joyride/Assets/Images/Player/Run5.png", true}, 
		Texture{"4_Jetpack_Joyride/Assets/Images/Player/Run6.png", true}
	} }, 
	velocity{ 0.0f }, floorPosition{ floorPosition } {
	sprite.size = glm::vec2{ Engine::FWidth * 0.15f };
	sprite.position = glm::vec2{ 0.0f, floorPosition - (sprite.size.y / 2.0f) };
	sprite.timeChangeTexture = 0.07f;
}

void JetpackJoyridePlayer::update() {
	if (sprite.position.y < (floorPosition - (sprite.size.y / 2.0f)))
		velocity.y += JETPACK_JOYRIDE_PLAYER_GRAVITY * Engine::DeltaTime;
	if (sprite.position.x != (Engine::FWidth / 2.0f)) {
		float diff = (Engine::FWidth / 2.0f) - sprite.position.x;
		velocity.x = diff * 1.0f * Engine::DeltaTime;
	}
	if (Engine::KeyPressed(GLFW_KEY_SPACE)) 
		velocity.y = JETPACK_JOYRIDE_PLAYER_JUMP_FORCE;

	sprite.position += velocity * Engine::DeltaTime;
	sprite.position = glm::clamp(sprite.position,
		glm::vec2{ 0.0f },
		glm::vec2{ 
			Engine::FWidth - (sprite.size.x / 2.0f), 
			floorPosition - (sprite.size.y / 2.0f)
		});
}
void JetpackJoyridePlayer::draw() {
	sprite.draw();
}