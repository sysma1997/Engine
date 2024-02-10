#include <iostream>

#include <Engine.h>

int main() {
	Engine* engine{ new Engine{"Tests"} };

	engine->setKeyCallback([](GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (key == GLFW_KEY_ESCAPE && GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}
	});

	while (engine->isLoop()) {
		engine->newFrame();

		engine->renderFrame();
	}

	engine->terminate();
	return 0;
}