//
// Created by larsewi on 19.08.2020.
//

#include <stdexcept>
#include <vulkan/vulkan.h>

#include "Window.h"

using namespace Bogus;

int Window::count = 0;

Window::Window(int width, int height, const std::string& title) : glfwWindow(nullptr), logger(nullptr)  {
    logger = Logger::getInstance();

    if (count++ == 0) {
        logger->logDebug(tag, "Initializing GLFW");
        glfwInit();
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    logger->logDebug(tag, "Creating GLFW window");
    glfwWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!glfwWindow)
        throw std::runtime_error("GLFW window creation failed");
}

Window::~Window() {
    logger->logDebug(tag, "Destroying GLFW window");
    glfwDestroyWindow(glfwWindow);
    if (count-- == 1) {
        logger->logDebug(tag, "Terminating GLFW");
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
