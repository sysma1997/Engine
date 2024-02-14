#pragma once

#include <iostream>
#include <functional>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Engine {
private:
    float lastFrame;

public:
    static bool Keys[1024];
    static bool KeyProcessed[1024];
    static float DeltaTime;

    int width, height;
    int lastWidth, lastHeight;
    GLFWwindow* window;

    Engine(const char* title, int width = 800, int height = 600, bool is2D = true);
    ~Engine();

    float fWidth();
    float fHeight();

    bool isLoop();
    void newFrame(std::function<void()> updateWindowSize);
    void renderFrame();
    void terminate();

    void setKeyCallback(GLFWkeyfun callback);
};