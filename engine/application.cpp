//
// Created by larsewi on 18.08.2020.
//

#include <iostream>

#include "application.hpp"

using namespace bogus;

Application::Application(const int width, const int height, const std::string &title)
    : m_width(width), m_height(height), m_title(title), m_should_run(false),
      m_window(nullptr) {}

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

bool Application::Init(void) {
  if (glfwInit() == GLFW_FALSE) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return false;
  }

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // We are not using OpenGL
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // Resizing windows not supported

  m_window =
      glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
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
