#include <iostream>

#include "window.hpp"

#define GLFW_INCLUDE_VULKAN

using namespace bogus;

Window::Window(const std::string &title, int width, int height)
    : m_title(title), m_width(width), m_height(height),
      m_window(nullptr, nullptr), m_should_close(false) {
  std::cout << "Debug: Initializing GLFW" << std::endl;
  if (glfwInit() == GLFW_FALSE) {
    throw WindowException("Failed to initialize GLFW");
  }

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // We are not using OpenGL
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // Resizing windows not supported

  std::cout << "Debug: Creating GLFW window" << std::endl;
  m_window = std::unique_ptr<GLFWwindow, void (*)(GLFWwindow *)>(
      glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr),
      &glfwDestroyWindow);

  if (!m_window) {
    throw WindowException("Failed to create GLFW window");
  }
}

bool Window::Events() {
  glfwPollEvents();
  return true;
}

bool Window::Update() {
  m_should_close = glfwWindowShouldClose(m_window.get());
  return true;
}

bool Window::Render() { return true; }

std::unique_ptr<std::vector<const char *>> Window::GetExtensions() const {
  uint32_t extension_count;
  const char **extension_names =
      glfwGetRequiredInstanceExtensions(&extension_count);
  if (extension_names == nullptr) {
    return nullptr;
  }

  auto extensions = std::make_unique<std::vector<const char *>>();
  for (uint32_t i = 0; i < extension_count; i++) {
    extensions->push_back(extension_names[i]);
  }

  return extensions;
}

bool Window::ShouldClose() const { return m_should_close; }
