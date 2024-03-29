#include <iostream>

#include "logger.hpp"
#include "window.hpp"

#define GLFW_INCLUDE_VULKAN

using namespace bogus;

Window::Window(const std::string &title, int width, int height)
    : m_title(title), m_width(width), m_height(height), m_window(nullptr),
      m_should_close(false) {
  log::debug("Initializing GLFW");
  if (glfwInit() == GLFW_FALSE) {
    throw WindowException("Failed to initialize GLFW");
  }

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // We are not using OpenGL
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // Resizing windows not supported

  log::debug("Creating GLFW window");
  m_window =
      glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);

  if (!m_window) {
    throw WindowException("Failed to create GLFW window");
  }
}

Window::~Window() {
  log::debug("Destroying GLFW window");
  glfwDestroyWindow(m_window);
}

bool Window::Events() {
  glfwPollEvents();
  return true;
}

bool Window::Update() {
  m_should_close = glfwWindowShouldClose(m_window);
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
