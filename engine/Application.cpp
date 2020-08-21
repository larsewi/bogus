//
// Created by larsewi on 18.08.2020.
//

#include <stdexcept>
#include "Application.h"
#include "Logger.h"

Application::Application(int width, int height, const std::string& title) :
        m_bShouldRun(false), m_pWindow(nullptr), m_pInstance(nullptr) {
    try {
        LOG_INFO("Creating window");
        m_pWindow = new Window(width, height, title);

        LOG_INFO("Creating instance");
        m_pInstance = new Instance(m_pWindow);

        m_bShouldRun = true;
    } catch (const std::exception& e) {
        LOG_ERROR(e.what());
    }
}

Application::~Application() {
    LOG_INFO("Deleting instance");
    delete m_pInstance;

    LOG_INFO("Deleting window");
    delete m_pWindow;
}

void Application::run() {
    onInit();
    while (m_bShouldRun) {
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
    m_bShouldRun = !m_pWindow->shouldClose();
    onUpdate();
}

void Application::render() {
    onDraw();
}
