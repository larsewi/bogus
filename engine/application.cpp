//
// Created by larsewi on 18.08.2020.
//

#include <iostream>

#include "application.hpp"

using namespace Bogus;

Application::Application(int width, int height, const std::string &title)
    : m_shouldRun(true), m_goodbit(false) {
  m_goodbit = true;
}

Application::~Application() {}

bool Application::run() {
  if (!Init()) {
  }

  while (m_shouldRun) {
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
  OnInit();
  return true;
}

bool Application::Events() {
  OnEvent();
  return true;
}

bool Application::Update() {
  OnUpdate();
  return true;
}

bool Application::Render() {
  OnDraw();
  return true;
}

bool Application::Exit() {
  OnExit();
  return true;
}
