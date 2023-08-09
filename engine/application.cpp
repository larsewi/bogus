//
// Created by larsewi on 18.08.2020.
//

#include <iostream>

#include "application.hpp"

using namespace bogus;

Application::Application(int width, int height, const std::string &title)
    : m_should_run(false), m_goodbit(false) {
  m_goodbit = true;
}

Application::~Application() {}

bool Application::Run() {
  if (!Init()) {
    std::cerr << "Error occured while initializing" << std::endl;
    return false;
  }

  while (m_should_run) {
    if (!Events()) {
      std::cerr << "Error occured while handling events" << std::endl;
      return false;
    }

    if (!Update()) {
      std::cerr << "Error occured while updating" << std::endl;
      return false;
    }

    if (!Render()) {
      std::cerr << "Error occured while rendering" << std::endl;
      return false;
    }
  }

  if (!Exit()) {
    std::cerr << "Error occured while exiting" << std::endl;
    return false;
  }

  return true;
}

bool Application::Init() {
  if (!OnInit()) {
    return false;
  }
  return true;
}

bool Application::Events() {
  if (!OnEvent()) {
    return false;
  }
  return true;
}

bool Application::Update() {
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
  if (!OnExit()) {
    return false;
  }
  return true;
}
