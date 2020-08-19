//
// Created by larsewi on 19.08.2020.
//

#include "Window.h"

Window::Window(int width, int height, const std::string& title) : m_pGLFWwindow(nullptr)  {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    m_pGLFWwindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
}

Window::~Window() {
    glfwDestroyWindow(m_pGLFWwindow);
    glfwTerminate();
}
