#include <Engine.h>
#include <2D/Sprite.h>
#include <UI/Test.h>

void playerProcessInput(float deltaTime, E2D::Sprite& player) {
	if (Engine::Keys[GLFW_KEY_LEFT])
		player.position.x -= player.velocity.x * deltaTime;
	if (Engine::Keys[GLFW_KEY_RIGHT])
		player.position.x += player.velocity.x * deltaTime;
	if (Engine::Keys[GLFW_KEY_UP])
		player.position.y -= player.velocity.y * deltaTime;
	if (Engine::Keys[GLFW_KEY_DOWN])
		player.position.y += player.velocity.y * deltaTime;
}

int main() {
	Engine* engine{ new Engine{"Test"} };
	EUI::Test* ui{ new EUI::Test{engine->window} };

	engine->setKeyCallback([](GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (key == GLFW_KEY_ESCAPE && GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}
		
		if (key >= 0 && key <= 1024) {
			if (action == GLFW_PRESS) Engine::Keys[key] = true;
			if (action == GLFW_RELEASE) {
				Engine::Keys[key] = false;
				Engine::KeyProcessed[key] = false;
			}
		}
	});

	Shader shader{ "Shaders/Test.vert", "Shaders/Test.frag" };
	Texture texture{ "Assets/Images/awesomeface.png", true };

	glm::mat4 projection{ glm::ortho(0.0f, engine->fWidth(), engine->fHeight(), 0.0f) };
	shader.setMat4("projection", projection, true);

	E2D::Sprite* player{ new E2D::Sprite{shader, texture} };
	player->position = glm::vec2{ engine->fWidth() / 2.0f, engine->fHeight() / 2.0f };
	player->size = glm::vec2{ 60.0f };

	float deltaTime{ 0.0f };
	float lastFrame{ 0.0f };
    while (engine->isLoop()) {
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

        engine->newFrame();

		playerProcessInput(deltaTime, *player);
		player->draw();

		ui->newFrame();
		ImGui::Begin("Player");
		ImGui::Text("Position");
		ImGui::InputFloat("##playerPositionX", &player->position.x);
		ImGui::SameLine();
		ImGui::InputFloat("##playerPositionY", &player->position.y);
		ImGui::Text("Size");
		ImGui::InputFloat("##playerSizeX", &player->size.x);
		ImGui::SameLine();
		ImGui::InputFloat("##playerSizeY", &player->size.y);
		ImGui::Text("Velocity");
		ImGui::InputFloat("##playerVelocityX", &player->velocity.x);
		ImGui::SameLine();
		ImGui::InputFloat("##playerVelocityY", &player->velocity.y);
		ImGui::End();
		ui->renderFrame();

        engine->renderFrame();
	}

	ui->terminate();
	engine->terminate();
	return 0;
}