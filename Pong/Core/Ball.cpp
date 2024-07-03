#include "Ball.h"

bool isTimeCollision{ true };
float timeCollision{ 0.0f };

Ball::Ball() : velocity{ 200.0f } {
	sprite = new E2D::Sprite{ Texture{"Assets/Images/Ball.png", true} };

	sprite->size = glm::vec2{ Engine::FWidth * 0.05f };
	sprite->position = Engine::GetSizeCenter();

	int leftRight{ rand() % 2 }, upDown{ rand() % 2 };
	direction = glm::vec2{
		(leftRight == 0) ? -1.0f : 1.0f,
		(upDown == 0) ? -1.0f : 1.0f
	};

	audio.load("collision", "Assets/Sounds/ballCollision.wav");
	audio.load("boo", "Assets/Sounds/boo.mp3");
	audio.load("cellebration", "Assets/Sounds/cellebration.mp3");
}

void Ball::updateWindowSize() {
	sprite->size = glm::vec2{ Engine::FWidth * 0.05f };
}
void Ball::progress(E2D::Object* player, E2D::Object* opponent) {
	if (!isTimeCollision) {
		timeCollision += Engine::DeltaTime;

		if (timeCollision > 0.5f) {
			isTimeCollision = true;
			timeCollision = 0.0f;
		}
	}

	sprite->position += direction * velocity * Engine::DeltaTime;

	glm::vec2 middle{ sprite->size / 2.0f };
	float limitY{ Engine::FHeight - middle.y };
	if (sprite->position.y < middle.y ||
		sprite->position.y > limitY) 
		direction.y *= -1;
	if (isTimeCollision && 
		(E2D::Object::CheckCollision(*sprite, *player) ||
		E2D::Object::CheckCollision(*sprite, *opponent))) {
		direction.x *= -1;
		
		velocity += 15.0f;
		isTimeCollision = false;

		audio.play("collision");
	}
}
void Ball::draw() {
	sprite->draw();
}

glm::vec2 Ball::getPosition() {
	return glm::vec2{ sprite->position.x, sprite->position.y };
}
int Ball::isOut() {
	glm::vec2 middle{ sprite->size / 2.0f };
	if (sprite->position.x < middle.x) {
		audio.play("boo");
		return 2;
	}
	else if (sprite->position.x > (Engine::FWidth + middle.x)) {
		audio.play("cellebration");
		return 1;
	}
	else return 0;
}
void Ball::reset() {
	int leftRight{ rand() % 2 }, upDown{ rand() % 2 };
	direction = glm::vec2{
		(leftRight == 0) ? -1.0f : 1.0f,
		(upDown == 0) ? -1.0f : 1.0f
	};

	sprite->position = Engine::GetSizeCenter();
	velocity = 200.0f;
}