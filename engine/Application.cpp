//
// Created by larsewi on 18.08.2020.
//

#include <stdexcept>

#include "Application.h"
#include "Logger.h"

Bogus::Application::Application(int width, int height, const std::string& title) :
        m_bShouldRun(false), m_pWindow(nullptr), m_pInstance(nullptr) {
    try {
        auto logger = Logger::getInstance();
        logger->logDebug(tag, "creating window");
        m_pWindow = new Window(width, height, title);

        logger->logDebug(tag, "creating instance");
        m_pInstance = new Instance(m_pWindow);

        m_bShouldRun = true;
    } catch (const std::exception& e) {
        //logger->logError(tag, e.what());
    }
}

Bogus::Application::~Application() {
    //LOG_INFO("Deleting instance");
    delete m_pInstance;

    //LOG_INFO("Deleting window");
    delete m_pWindow;
}

void Bogus::Application::run() {
    onInit();
    while (m_bShouldRun) {
        handleEvents();
        update();
        render();
    }
    onExit();
}

void Bogus::Application::handleEvents() {
    Window::pollEvents();
    onEvent();
}

void Bogus::Application::update() {
    m_bShouldRun = !m_pWindow->shouldClose();
    onUpdate();
}

void Bogus::Application::render() {
    onDraw();
}
