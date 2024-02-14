#pragma once

#include <GLFW/glfw3.h>
#include "../../Libs/imgui/imgui.h"
#include "../../Libs/imgui/imgui_impl_glfw.h"
#include "../../Libs/imgui/imgui_impl_opengl3.h"

namespace EUI {
    class Test
    {
    public:
        ImGuiIO io;
        
        Test(GLFWwindow* window);
        ~Test();

        void newFrame();
        void renderFrame();
        void terminate();
    };
}