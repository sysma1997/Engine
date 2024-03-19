#include "JetpackJoyrideObstacles.h"

JetpackJoyrideObstacles::JetpackJoyrideObstacles() : 
	velocity{ 150.0f }, generateNextObstacle{ 0.0f },
	currentTime{ 0.0f }, generate{ false } {
	int time = rand() % 10;
	generateNextObstacle = static_cast<float>(time);
}

void JetpackJoyrideObstacles::updateWindowSize() {
	for (int i{ 0 }; i < obstacles.size(); i++)
		obstacles[i].sprite.updateWindowSize();
}
void JetpackJoyrideObstacles::update() {
	currentTime += Engine::DeltaTime;
	if (currentTime > generateNextObstacle) {
		currentTime = 0.0f;
		generateNextObstacle = static_cast<float>(rand() % 10);

		std::string path{ "4_Jetpack_Joyride/Assets/Images/Obstacles/obstacle" };
		E2D::SpriteAnimated sprite{ "normal", {
			Texture{(path + "1.png").c_str(), true},
			Texture{(path + "2.png").c_str(), true},
			Texture{(path + "3.png").c_str(), true},
			Texture{(path + "4.png").c_str(), true},
			Texture{(path + "5.png").c_str(), true},
			Texture{(path + "6.png").c_str(), true},
			Texture{(path + "7.png").c_str(), true},
			Texture{(path + "8.png").c_str(), true},
			Texture{(path + "9.png").c_str(), true},
			Texture{(path + "10.png").c_str(), true}
		} };
		sprite.size = glm::vec2{ Engine::FWidth * 0.05f, Engine::FHeight * 0.2f };
		sprite.size.y += static_cast<float>(rand() % 250);
		sprite.timeChangeTexture = 0.08f;
		sprite.rotate = static_cast<float>(rand() % 360);
		int randomY = rand() % Engine::Height;
		sprite.position = glm::vec2{ Engine::FWidth + sprite.size.x, static_cast<float>(randomY)};

		Obstacle obstacle{ sprite, ((rand() % 2) > 0) ? true : false };
		obstacles.push_back(obstacle);
	}
	
	for (int i{ 0 }; i < obstacles.size(); i++) {
		Obstacle& obstacle{ obstacles[i] };

		obstacle.sprite.position.x -= velocity * Engine::DeltaTime;
		if (obstacle.isSpinning) {
			obstacle.sprite.rotate += 1.0f;
		}

		if (obstacle.sprite.position.x < -(obstacle.sprite.size.x)) {
			obstacles.erase(obstacles.begin() + i);
			i--;
		}
	}
}
void JetpackJoyrideObstacles::draw() {
	for (int i{ 0 }; i < obstacles.size(); i++) {
		Obstacle& obstacle{ obstacles[i] };
		obstacle.sprite.draw();
	}
}

bool JetpackJoyrideObstacles::isPlayerCollision(E2D::Object& player) {
	for (int i{ 0 }; i < obstacles.size(); i++) {
		Obstacle& obstacle{ obstacles[i] };

		if (E2D::Object::CheckCollision(obstacle.sprite, player))
			return true;
	}

	return false;
}