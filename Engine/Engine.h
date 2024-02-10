#pragma once

#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Engine
{
private:
	const std::string LOG{ "ENGINE::" };

	GLFWwindow* window;
	std::string title;
	int width;
	int height;
public:
	Engine(std::string title, int width = 800, int height = 600);
	~Engine();

	bool isLoop();
	void newFrame();
	void renderFrame();
	void terminate();

	void setKeyCallback(GLFWkeyfun callback);
};