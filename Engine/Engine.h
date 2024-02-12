#pragma once

#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Engine
{
private:
	std::string LOG{ "SYSMA::ENGINE::ENGINE::" };

	std::string title;
public:
	GLFWwindow* window;
	int width;
	int height;

	Engine(std::string title, int width = 800, int height = 600);
	~Engine();

	bool isLoop();
	void newFrame();
	void renderFrame();
	void terminate();

	void setKeyCallback(GLFWkeyfun callback);
};