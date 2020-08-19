//
// Created by larsewi on 18.08.2020.
//

#include "Application.h"
#include "Logger.h"

Application::Application(int width, int height, const std::string& title) :
m_isRunning(false), m_pWindow(nullptr) {
    m_pWindow = new Window(width, height, title);
    m_isRunning = true;
}

Application::~Application() {
    delete m_pWindow;
}

void Application::run() {
    onBegin();
    while (m_isRunning) {
        handleEvents();
        update();
        render();
    }
    onExit();
}

void Application::handleEvents() {
    Window::pollEvents();
    onEvent();
}

void Application::update() {
    m_isRunning = !m_pWindow->shouldClose();
    onUpdate();
}

void Application::render() {
    onDraw();
}
