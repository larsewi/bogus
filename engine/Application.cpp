//
// Created by larsewi on 18.08.2020.
//

#include <stdexcept>

#include "Application.h"

#define TAG "Application"

using namespace Bogus;

Application::Application(int width, int height, const std::string& title) :
    shouldRun(false), window(nullptr), instance(nullptr), logger(nullptr) {
    logger = Logger::getInstance();

    logger->logVerbose(TAG, "Creating window");
    window = new Window(width, height, title);

    logger->logVerbose(TAG, "Creating instance");
    instance = new Instance();

    shouldRun = true;
}

Application::~Application() {
    logger->logVerbose(TAG, "Deleting instance");
    delete instance;

    logger->logVerbose(TAG, "Deleting window");
    delete window;
}

void Application::run() {
    onInit();
    while (shouldRun) {
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
    shouldRun = !window->shouldClose();
    onUpdate();
}

void Application::render() {
    onDraw();
}
