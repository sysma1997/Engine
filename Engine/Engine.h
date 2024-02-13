#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Engine {
public:
    static bool Keys[1024];
    static bool KeyProcessed[1024];

    int width;
    int height;
    GLFWwindow* window;

    Engine(const char* title, int width = 800, int height = 600, bool is2D = true);
    ~Engine();

    float fWidth();
    float fHeight();

    bool isLoop();
    void newFrame();
    void renderFrame();
    void terminate();

    void setKeyCallback(GLFWkeyfun callback);
};