//
// Created by larsewi on 18.08.2020.
//

#define GLFW_INCLUDE_VULKAN

#define ENGINE_TITLE "bogus"
#define ENGINE_MAJOR 1
#define ENGINE_MINOR 0
#define ENGINE_PATCH 0

#include <iostream>

#include "application.hpp"

using namespace bogus;

Application::Application(const std::string &app_name, int app_major,
                         int app_minor, int app_patch,
                         const std::string &window_title, int window_width,
                         int window_height)
    : m_app_name(app_name), m_app_major(app_major), m_app_minor(app_minor),
      m_app_patch(app_patch), m_window_title(window_title),
      m_window_width(window_width), m_window_height(window_height) {}

Application::~Application() {}

bool Application::Run() {
  if (!Init()) {
    std::cerr << "An error occured while initializing " << std::endl;
    return false;
  }

  while (m_should_run) {
    if (!Events()) {
      std::cerr << "An error occured while handling events" << std::endl;
      return false;
    }

    if (!Update()) {
      std::cerr << "An error occured while updating" << std::endl;
      return false;
    }

    if (!Render()) {
      std::cerr << "An error occured while rendering" << std::endl;
      return false;
    }
  }

  if (!Exit()) {
    std::cerr << "An error occured while exiting" << std::endl;
    return false;
  }

  return true;
}

static GLFWwindow *CreateWindow(const std::string &title, int width,
                                int height) {
  if (glfwInit() == GLFW_FALSE) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return nullptr;
  }
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // We are not using OpenGL
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // Resizing windows not supported
  return glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
}

static vk::Instance *CreateInstance(const std::string &name, int major,
                                    int minor, int patch) {
  vk::ApplicationInfo app_info(
      name.c_str(), VK_MAKE_VERSION(major, minor, patch), ENGINE_TITLE,
      VK_MAKE_VERSION(ENGINE_MAJOR, ENGINE_MINOR, ENGINE_PATCH),
      VK_API_VERSION_1_1);

  return nullptr;
}

bool Application::Init() {
  m_window = CreateWindow(m_window_title, m_window_width, m_window_height);
  if (m_window == nullptr) {
    std::cerr << "Failed to create GLFW window" << std::endl;
  }

  m_should_run = true;

  if (!OnInit()) {
    return false;
  }
  return true;
}

bool Application::Events() {
  glfwPollEvents();

  if (!OnEvent()) {
    return false;
  }
  return true;
}

bool Application::Update() {
  if (glfwWindowShouldClose(m_window)) {
    m_should_run = false;
  }

  if (!OnUpdate()) {
    return false;
  }
  return true;
}

bool Application::Render() {
  if (!OnDraw()) {
    return false;
  }
  return true;
}

bool Application::Exit() {
  glfwDestroyWindow(m_window);
  glfwTerminate();

  if (!OnExit()) {
    return false;
  }
  return true;
}
