#include "Test.h"

void test() {
	Engine* engine{ new Engine{"Test collisions"} };
	EUI::Test* ui{ new EUI::Test{engine->window} };

	E2D::Rectangle rectangle{};
	std::vector<E2D::Rectangle> collision;
	collision.push_back(E2D::Rectangle{});
	collision.push_back(E2D::Rectangle{});
	collision.push_back(E2D::Rectangle{});
	collision.push_back(E2D::Rectangle{});
	
	float width{ 150.0f }, height{ 100.0f };
	auto init = [&](glm::vec2 position, float rotate) {
		rectangle.size = glm::vec2{ width, height };

		rectangle.position = position;
		rectangle.rotate = rotate;

		glm::vec2 size{ 5.0f };
		for (int i{ 0 }; i < collision.size(); i++) {
			collision[i].size = size;
			collision[i].color = glm::vec3{ 1.0f, 0.0f, 0.0f };
			collision[i].rotate = rotate;
		}

		glm::vec2 radio{ width / 2.0f, height / 2.0f };
		float rrotate{ glm::radians(rotate) };
		float degrees{ glm::degrees(glm::atan(radio.y / radio.x)) };

		collision[3].position.x = (radio.x * glm::cos(rrotate) - radio.y * glm::sin(rrotate)) + rectangle.position.x;
		collision[3].position.y = (radio.x * glm::sin(rrotate) + radio.y * glm::cos(rrotate)) + rectangle.position.y;

		float rotationExtra{ glm::radians(180.0f - (degrees * 2)) };
		collision[2].position.x = (radio.x * glm::cos(rrotate + rotationExtra) - radio.y * glm::sin(rrotate + rotationExtra)) + rectangle.position.x;
		collision[2].position.y = (radio.x * glm::sin(rrotate + rotationExtra) + radio.y * glm::cos(rrotate + rotationExtra)) + rectangle.position.y;

		rotationExtra = glm::radians(180.0f);
		collision[1].position.x = (radio.x * glm::cos(rrotate + rotationExtra) - radio.y * glm::sin(rrotate + rotationExtra)) + rectangle.position.x;
		collision[1].position.y = (radio.x * glm::sin(rrotate + rotationExtra) + radio.y * glm::cos(rrotate + rotationExtra)) + rectangle.position.y;

		rotationExtra = glm::radians(-(degrees * 2));
		collision[0].position.x = (radio.x * glm::cos(rrotate + rotationExtra) - radio.y * glm::sin(rrotate + rotationExtra)) + rectangle.position.x;
		collision[0].position.y = (radio.x * glm::sin(rrotate + rotationExtra) + radio.y * glm::cos(rrotate + rotationExtra)) + rectangle.position.y;
	};

	glm::vec2 position{ Engine::GetSizeCenter() };
	float rotate{ 0.0f };
	init(position, rotate);
	while(engine->isLoop()) {
		engine->newFrame([&] {
			rectangle.updateWindowSize();
			for (int i{ 0 }; i < collision.size(); i++)
				collision[i].updateWindowSize();
		});

		if (Engine::KeyPressed(GLFW_KEY_LEFT) ||
			Engine::KeyPressed(GLFW_KEY_UP) ||
			Engine::KeyPressed(GLFW_KEY_RIGHT) ||
			Engine::KeyPressed(GLFW_KEY_DOWN)) {
			float move{ 120.0f * Engine::DeltaTime };

			if (Engine::KeyPressed(GLFW_KEY_LEFT))
				position.x -= move;
			if (Engine::KeyPressed(GLFW_KEY_UP))
				position.y -= move;
			if (Engine::KeyPressed(GLFW_KEY_RIGHT))
				position.x += move;
			if (Engine::KeyPressed(GLFW_KEY_DOWN))
				position.y += move;

			float maxWidth{ 0.0f };
			float maxHeight{ 0.0f };
			for (int i = 0; i < collision.size(); i++) {
				float x{ collision[i].position.x - rectangle.position.x };
				float y{ collision[i].position.y - rectangle.position.y };
				if (x > maxWidth) maxWidth = x;
				if (y > maxHeight) maxHeight = y;
			}

			position = glm::clamp(position, 
				glm::vec2{ maxWidth, maxHeight }, 
				Engine::GetSize() - (glm::vec2{ maxWidth, maxHeight }));

			init(position, rotate);
		}
		if (Engine::KeyPressed(GLFW_KEY_X) || 
			Engine::KeyPressed(GLFW_KEY_C)) {
			if (Engine::KeyPressed(GLFW_KEY_X))
				rotate -= 2.0f;
			if (Engine::KeyPressed(GLFW_KEY_C))
				rotate += 2.0f;

			if (rotate < -360.0f || 
				rotate > 360.0f)
				rotate = 0.0f;

			init(position, rotate);
		}

		rectangle.draw();
		for (int i{ 0 }; i < collision.size(); i++)
			collision[i].draw();

		ui->newFrame();
		ImGui::Begin("Cube collision");
		ImGui::Text("Position");
		ImGui::InputFloat("##positionX", &position.x);
		ImGui::SameLine();
		ImGui::InputFloat("##positionY", &position.y);
		ImGui::Text("Size");
		ImGui::InputFloat("##sizeX", &width);
		ImGui::SameLine();
		ImGui::InputFloat("##sizeY", &height);
		ImGui::Text("Rotate");
		ImGui::InputFloat("##rotate", &rotate);
		if (ImGui::Button("update")) init(position, rotate);
		ImGui::End();
		ui->renderFrame();

		engine->renderFrame();
	}

	ui->terminate();
	engine->terminate();
}