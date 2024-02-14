#include "../Include/Engine.h"

bool Engine::Keys[1024];
bool Engine::KeyProcessed[1024];
float Engine::DeltaTime{ 0.0f };

Engine::Engine(const char* title, int width, int height, bool is2D) : 
    width{ width }, height{ height }, 
    lastFrame{ 0.0f } {
    if (!glfwInit()) {
        std::cout << "Failed to init GLFW.\n";
        return;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL) {
        std::cout << "Error to open window with GLFW, if use old GPU, "
            << "it's not compatible with OpenGL 4.5\n";
        return;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        std::cout << "Error to init GLEW." << '\n';
        return;
    }

    if (!is2D) glEnable(GL_DEPTH_TEST);
    else
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    setKeyCallback([](GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (key >= 0 && key <= 1024) {
            if (action == GLFW_PRESS) Engine::Keys[key] = true;
            if (action == GLFW_RELEASE) {
                Engine::Keys[key] = false;
                Engine::KeyProcessed[key] = false;
            }
        }
    });
}
Engine::~Engine() {}

float Engine::fWidth() {
    return static_cast<float>(width);
}
float Engine::fHeight() {
    return static_cast<float>(height);
}

bool Engine::isLoop() {
    return glfwWindowShouldClose(window) == 0;
}
void Engine::newFrame(std::function<void()> updateWindowSize) {
    float currentFrame = glfwGetTime();
    DeltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    /* glClearColor(0.2f, 0.3f, 0.3f, 1.0f); */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (width != lastWidth ||
        height != lastHeight) {
        if (width != lastWidth) lastWidth = width;
        if (height != lastHeight) lastHeight = height;

        updateWindowSize();
    }
}
void Engine::renderFrame() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}
void Engine::terminate() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Engine::setKeyCallback(GLFWkeyfun callback) {
    glfwSetKeyCallback(window, callback);
}