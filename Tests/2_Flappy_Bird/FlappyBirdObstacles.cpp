#include "FlappyBirdObstacles.h"

const float FLAPPY_BIRD_OBSTACLES_VELOCITY = 100.0f;

FlappyBirdObstacles::FlappyBirdObstacles() : velocity{ 3.0f }, currentTime { 0.0f }, generate{ false } {
	srand(time(NULL));
}

void FlappyBirdObstacles::updateWindowSize() {
	for (int i = 0; i < obstacles.size(); i++) {
		ObstacleSprite obstacle{ obstacles[i] };
		obstacle.up.updateWindowSize();
		obstacle.down.updateWindowSize();
	}
}
void FlappyBirdObstacles::update(E2D::Sprite base) {
	currentTime += Engine::DeltaTime;
	if (currentTime > velocity) {
		currentTime = 0.0f;
		generate = true;

		int limitInit{ 30 };
		int limitEnd{ static_cast<int>((base.position.y - (base.size.y / 2.0f)) - 40.0f) };
		float randomPos{ static_cast<float>(rand() % (limitEnd - 40) + limitInit) };

		glm::vec2 position{ Engine::FWidth + (Engine::FWidth * 0.1f), randomPos};
		E2D::Sprite up{ Texture{ "2_Flappy_Bird/Assets/Images/pipe-green.png", true } };
		up.size = glm::vec2{ Engine::FWidth * 0.2f, Engine::FHeight };
		up.position = glm::vec2{ position.x, position.y - (up.size.y / 2.0f) - 80.0f };
		up.rotate = 180.0f;
		E2D::Sprite down{ Texture{ "2_Flappy_Bird/Assets/Images/pipe-green.png", true } };
		down.size = up.size;
		down.position = glm::vec2{ position.x, position.y + (down.size.y / 2.0f) + 80.0f };

		ObstacleSprite obstacle{ up, down };
		obstacles.push_back(obstacle);
	}
}
void FlappyBirdObstacles::draw() {
	for (int i = 0; i < obstacles.size(); i++) {
		ObstacleSprite& obstacle{ obstacles[i] };
		obstacle.up.position.x -= FLAPPY_BIRD_OBSTACLES_VELOCITY * Engine::DeltaTime;
		obstacle.down.position.x -= FLAPPY_BIRD_OBSTACLES_VELOCITY * Engine::DeltaTime;
		
		obstacle.up.draw();
		obstacle.down.draw();

		if (obstacle.up.position.x < (0.0f - obstacle.up.size.x / 2.0f)) {
			obstacles.erase(obstacles.begin() + i);
			i--;
		}
	}
}