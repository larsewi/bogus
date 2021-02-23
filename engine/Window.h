//
// Created by larsewi on 19.08.2020.
//

#ifndef BOGUS_WINDOW_H
#define BOGUS_WINDOW_H

#include <string>
#include <vector>
#include <GLFW/glfw3.h>

#include "Logger.h"

namespace Bogus {
    class Window {
    public:
        Window(int width, int height, const std::string& title);
        ~Window();

        bool shouldClose() { return glfwWindowShouldClose(glfwWindow) != 0; }
        static void pollEvents() { glfwPollEvents(); }

        static std::vector<const char*> getRequiredExtensions();

    private:
        static int count;
        Logger *logger;
        GLFWwindow* glfwWindow;
    };
}

#endif //BOGUS_WINDOW_H
