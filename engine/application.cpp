//
// Created by larsewi on 18.08.2020.
//

#define GLFW_INCLUDE_VULKAN

#include <algorithm>
#include <iostream>
#include <vector>

#include <spdlog/spdlog.h>

#include "application.hpp"

using namespace bogus;

#define ENGINE_NAME "bogus"
#define ENGINE_MAJOR 1
#define ENGINE_MINOR 0
#define ENGINE_PATCH 0

Application::Application(const std::string &app_name, int app_major,
                         int app_minor, int app_patch,
                         const std::string &window_title, int window_width,
                         int window_height) {
  spdlog::set_level(spdlog::level::debug);

  spdlog::debug("Creating window");
  m_window = new Window(window_title, window_width, window_height);

  spdlog::debug("Creating instance");
  m_instance =
      new Instance(app_name, app_major, app_minor, app_patch, m_window);
}

Application::~Application() {
  spdlog::debug("Destroying instance");
  delete m_instance;

  spdlog::debug("Destroying window");
  delete m_window;
}

bool Application::Run() {
  if (!OnInit()) {
    return false;
  }

  while (!m_window->ShouldClose()) {
    if (!Events()) {
      spdlog::error("Failed to handle events");
      return false;
    }

    if (!Update()) {
      spdlog::error("Failed to update");
      return false;
    }

    if (!Render()) {
      spdlog::error("Failed to render");
      return false;
    }
  }

  if (!OnExit()) {
    return false;
  }

  return true;
}

bool Application::Events() {
  if (!m_window->Events()) {
    spdlog::error("Failed to handle window events");
    return false;
  }

  if (!OnEvent()) {
    return false;
  }

  return true;
}

bool Application::Update() {
  if (!m_window->Update()) {
    spdlog::error("Failed to handle window updates");
    return false;
  }

  if (!OnUpdate()) {
    return false;
  }

  return true;
}

bool Application::Render() {
  if (!m_window->Render()) {
    spdlog::error("Failed to render window");
    return false;
  }

  if (!OnDraw()) {
    return false;
  }

  return true;
}
