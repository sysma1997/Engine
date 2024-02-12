#include "Engine.h"

Engine::Engine(std::string title, int width, int height) : 
	title{ title }, width{ width }, height{ height } {
	std::string log{ "ENGINE::" };
	if (!glfwInit()) {
		std::cout << LOG << log << "Failed to init GLFW.\n";
		return;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (window == NULL) {
		std::cout << LOG << log << "Error to open windows with GLFW, if old use GPU, " 
			<< "it's not compatible with OpenGL 4.5.\n";
		return;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	
	//glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		std::cout << LOG << log << "Error to init GLEW.\n";
		return;
	}

	// for 2D
	glEnable(GL_DEPTH_TEST);
	// for 3D
	// glEnable(GL_BLEND);
	// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
Engine::~Engine() {}

bool Engine::isLoop()
{
	return glfwWindowShouldClose(window) == 0;
}
void Engine::newFrame()
{
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Engine::renderFrame()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}
void Engine::terminate()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Engine::setKeyCallback(GLFWkeyfun callback)
{
	glfwSetKeyCallback(window, callback);
}