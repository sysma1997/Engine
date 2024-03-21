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
		collision[0].position = glm::vec2{
			ro.position.x - (width / 2.0f),
			ro.position.y - (height / 2.0f)
		};
		collision[0].position.x =
			((width / 2.0f) * glm::cos(rotate * Engine::DeltaTime) -
			(height / 2.0f) * glm::sin(rotate * Engine::DeltaTime)) +
			ro.position.x;
		collision[0].position.y =
			((width / 2.0f) * glm::sin(rotate * Engine::DeltaTime) +
			(height / 2.0f) * glm::cos(rotate * Engine::DeltaTime)) +
			ro.position.y;
		collision[1].position = glm::vec2{
			ro.position.x + (width / 2.0f),
			ro.position.y - (height / 2.0f)
		};
		collision[2].position = glm::vec2{
			ro.position.x - (width / 2.0f),
			ro.position.y + (height / 2.0f)
		};
		collision[3].position = glm::vec2{
			ro.position.x + (width / 2.0f),
			ro.position.y + (height / 2.0f)
		};
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
		ui->renderFrame();

		engine->renderFrame();
	}

	ui->terminate();
	engine->terminate();
}