#include "Test.h"

void test() {
	Engine* engine{ new Engine{"Test collisions"} };
	EUI::Test* ui{ new EUI::Test{engine->window} };

	E2D::Rectangle rectangle{};
	E2D::Rectangle collision[5]{
		E2D::Rectangle{}, E2D::Rectangle{}, 
		E2D::Rectangle{}, E2D::Rectangle{}, 
		E2D::Rectangle{}
	};

	float width{ 100.0f }, height{ 100.0f };
	auto init = [&](glm::vec2 position, float rotate) {
		rectangle.size = glm::vec2{ width, height };

		rectangle.position = position;
		collision[4].position = position;
		rectangle.rotate = rotate;
		collision[4].rotate = rotate;

		glm::vec2 size{ 5.0f };
		for (int i{ 0 }; i < 5; i++) {
			collision[i].size = size;
			collision[i].color = glm::vec3{ 1.0f, 0.0f, 0.0f };
			collision[i].rotate = rotate;
		}

		E2D::Rectangle ro{ collision[4] };
		glm::vec2 radio{ width / 2.0f, height / 2.0f };
		float rrotate{ glm::radians(rotate) };
		
		float rextra{ glm::radians(270.0f) };
		collision[0].position.x = (radio.x * glm::cos(rrotate + rextra) - radio.y * glm::sin(rrotate + rextra)) + ro.position.x;
		collision[0].position.y = (radio.x * glm::sin(rrotate + rextra) + radio.y * glm::cos(rrotate + rextra)) + ro.position.y;
		float rextra1{ glm::radians(180.0f) };
		collision[1].position.x = (radio.x * glm::cos(rrotate + rextra1) - radio.y * glm::sin(rrotate + rextra1)) + ro.position.x;
		collision[1].position.y = (radio.x * glm::sin(rrotate + rextra1) + radio.y * glm::cos(rrotate + rextra1)) + ro.position.y;
		float rextra2{ glm::radians(90.0f) };
		collision[2].position.x = (radio.x * glm::cos(rrotate + rextra2) - radio.y * glm::sin(rrotate + rextra2)) + ro.position.x;
		collision[2].position.y = (radio.x * glm::sin(rrotate + rextra2) + radio.y * glm::cos(rrotate + rextra2)) + ro.position.y;
		collision[3].position.x = (radio.x * glm::cos(rrotate) - radio.y * glm::sin(rrotate)) + ro.position.x;
		collision[3].position.y = (radio.x * glm::sin(rrotate) + radio.y * glm::cos(rrotate)) + ro.position.y;
	};

	glm::vec2 position{ engine->getSizeCenter() };
	float rotate{ 0.0f };
	init(position, rotate);
	while(engine->isLoop()) {
		engine->newFrame([&] {
			rectangle.updateWindowSize();
			for (int i{ 0 }; i < 5; i++)
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

			position = glm::clamp(position, 
				glm::vec2{ width, height } / 2.0f, 
				engine->getSize() - (glm::vec2{ width, height } / 2.0f));

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
		for (int i{ 0 }; i < 5; i++)
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

		for (int i{ 0 }; i < 4; i++) {
			ImGui::Begin(("Cube small collision " + std::to_string(i)).c_str());
			ImGui::Text("Position");
			ImGui::InputFloat("##positionX", &collision[i].position.x);
			ImGui::SameLine();
			ImGui::InputFloat("##positionY", &collision[i].position.y);
			ImGui::NewLine();
			ImGui::Text("Degress");
			float degress = glm::degrees(glm::atan(collision[i].position.y - position.y, collision[i].position.x - position.x));
			ImGui::InputFloat("##degress", &degress);
			ImGui::End();
		}
		ui->renderFrame();

		engine->renderFrame();
	}

	ui->terminate();
	engine->terminate();
}