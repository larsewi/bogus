//
// Created by larsewi on 18.08.2020.
//

#define GLFW_INCLUDE_VULKAN

#include <algorithm>
#include <iostream>
#include <vector>

#include "application.hpp"

using namespace bogus;

#define ENGINE_NAME "bogus"
#define ENGINE_MAJOR 1
#define ENGINE_MINOR 0
#define ENGINE_PATCH 0

Application::Application(const std::string &app_name, int app_major,
                         int app_minor, int app_patch,
                         const std::string &window_title, int window_width,
                         int window_height)
    : m_window(new Window(window_title, window_width, window_height)),
      m_instance(
          new Instance(app_name, app_major, app_minor, app_patch, m_window)) {}

Application::~Application() {
  delete m_instance;
  delete m_window;
}

bool Application::Run() {
  if (!OnInit()) {
    std::cerr << "Critical: Failed to initialize" << std::endl;
    return false;
  }

  while (!m_window->ShouldClose()) {
    if (!Events()) {
      std::cerr << "Critical: Failed to handle events" << std::endl;
      return false;
    }

    if (!OnEvent()) {
      return false;
    }

    if (!Update()) {
      std::cerr << "Critical: Failed to update" << std::endl;
      return false;
    }

    if (!OnUpdate()) {
      return false;
    }

    if (!Render()) {
      std::cerr << "Critical: Failed to render" << std::endl;
      return false;
    }

    if (!OnDraw()) {
      return false;
    }
  }

  if (!OnExit()) {
    std::cerr << "Critical: Failed to exit" << std::endl;
    return false;
  }

  return true;
}

bool Application::Events() {
  if (!m_window->Events()) {
    std::cerr << "Failed to handle window events" << std::endl;
    return false;
  }

  return true;
}

bool Application::Update() {
  if (!m_window->Update()) {
    std::cerr << "Failed to handle window update" << std::endl;
    return false;
  }

  return true;
}

bool Application::Render() {
  if (!m_window->Render()) {
    std::cerr << "Failed to render window" << std::endl;
    return false;
  }

  return true;
}
