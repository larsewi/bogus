//
// Created by larsewi on 18.08.2020.
//

#define GLFW_INCLUDE_VULKAN

#include <algorithm>
#include <iostream>
#include <vector>

#include "application.hpp"
#include "logger.hpp"

using namespace bogus;

#define ENGINE_NAME "bogus"
#define ENGINE_MAJOR 1
#define ENGINE_MINOR 0
#define ENGINE_PATCH 0

Application::Application(const std::string &app_name, int app_major,
                         int app_minor, int app_patch,
                         const std::string &window_title, int window_width,
                         int window_height) {
  log::debug("Creating window");
  m_window = new Window(window_title, window_width, window_height);

  log::debug("Creating instance");
  m_instance =
      new Instance(app_name, app_major, app_minor, app_patch, m_window);
}

Application::~Application() {
  log::debug("Destroying instance");
  delete m_instance;

  log::debug("Destroying window");
  delete m_window;
}

bool Application::Run() {
  if (!OnInit()) {
    return false;
  }

  while (!m_window->ShouldClose()) {
    if (!Events()) {
      log::error("Failed to handle events");
      return false;
    }

    if (!Update()) {
      log::error("Failed to update");
      return false;
    }

    if (!Render()) {
      log::error("Failed to render");
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
    log::error("Failed to handle window events");
    return false;
  }

  if (!OnEvent()) {
    return false;
  }

  return true;
}

bool Application::Update() {
  if (!m_window->Update()) {
    log::error("Failed to handle window updates");
    return false;
  }

  if (!OnUpdate()) {
    return false;
  }

  return true;
}

bool Application::Render() {
  if (!m_window->Render()) {
    log::error("Failed to render window");
    return false;
  }

  if (!OnDraw()) {
    return false;
  }

  return true;
}
