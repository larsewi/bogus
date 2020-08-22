//
// Created by larsewi on 19.08.2020.
//

#include <stdexcept>
#include <vulkan/vulkan.h>

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
    if (!m_pGLFWwindow)
        throw std::runtime_error("GLFW window creation failed");
}

Window::~Window() {
    LOG_DEBUG("Destroying GLFW window");
    glfwDestroyWindow(m_pGLFWwindow);

    if (count-- == 1) {
        LOG_DEBUG("Terminating GLFW");
        glfwTerminate();
    }
}

std::vector<const char*> Window::getRequiredExtensions() {
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

    return extensions;
}
