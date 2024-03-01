#pragma once

#include <iostream>
#include <functional>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Engine {
private:
    static bool Keys[1024];
    static bool KeyProcessed[1024];

    float lastFrame;

public:
    static int Width, Height;
    static float FWidth, FHeight;
    static float DeltaTime;

    int lastWidth, lastHeight;
    GLFWwindow* window;

    Engine(const char* title, int width = 800, int height = 600);
    ~Engine();

    static bool KeyPressed(int key);
    static bool KeyJustPressed(int key);

    bool isLoop();
    void closeLoop();
    void newFrame(std::function<void()> updateWindowSize);
    void renderFrame();
    void terminate();

    void setKeyCallback(GLFWkeyfun callback);
};