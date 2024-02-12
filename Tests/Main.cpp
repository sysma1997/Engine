#include <iostream>
#include <string>
#include <filesystem>

#include <Engine.h>
#include <UI/Label.h>

#include <Libs/imgui/imgui.h>
#include <Libs/imgui/imgui_impl_glfw.h>
#include <Libs/imgui/imgui_impl_opengl3.h>

int main() {
	Engine* engine{ new Engine{"Tests"} };
	UI::Label* label{ new UI::Label{static_cast<unsigned int>(engine->width), static_cast<unsigned int>(engine->height)} };
	label->load("Assets/Fonts/OCRAEXT.TTF", 24);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(engine->window, true);
	ImGui_ImplOpenGL3_Init();

	engine->setKeyCallback([](GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (key == GLFW_KEY_ESCAPE && GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}
	});

	float color[3]{ 1.0f, 1.0f, 1.0f };
	while (engine->isLoop()) {
		engine->newFrame();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		label->render("Sebastian Moreno Acero", 5.0f, 100.0f, 1.0f, glm::vec3{ color[0], color[1], color[2] });

		ImGui::Begin("Change color triangle", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

		ImGui::Text("Color");
		ImGui::ColorEdit3("##color", color);

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		engine->renderFrame();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	engine->terminate();
	return 0;
}