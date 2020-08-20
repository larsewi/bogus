//
// Created by larsewi on 19.08.2020.
//

#include "Window.h"
#include "Logger.h"

int Window::count = 0;

Window::Window(int width, int height, const std::string& title) : m_pGLFWwindow(nullptr)  {
    if (count++ == 0) {
        LOG_DEBUG("Initializing GLFW");
        glfwInit();
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    LOG_DEBUG("Creating GLFW window");
    m_pGLFWwindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
}

Window::~Window() {
    LOG_DEBUG("Destroying GLFW window");
    glfwDestroyWindow(m_pGLFWwindow);

    if (count-- == 1) {
        LOG_DEBUG("Terminating GLFW");
        glfwTerminate();
    }
}
