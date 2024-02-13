#include "Test.h"

using namespace ImGui;

namespace EUI {

    Test::Test(GLFWwindow* window) {
        IMGUI_CHECKVERSION();
        CreateContext();
        io = GetIO();
        (void)io;

        StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init();
    }
    Test::~Test() {}

    void Test::newFrame()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        NewFrame();
    }
    void Test::renderFrame()
    {
        Render();
        ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());
    }
    void Test::terminate()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        DestroyContext();
    }
}