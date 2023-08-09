//
// Created by larsewi on 18.08.2020.
//

#include <stdexcept>

#include "application.hpp"

using namespace Bogus;

Application::Application(int width, int height, const std::string& title) :
    shouldRun(false), window(nullptr), instance(nullptr), logger(nullptr) {
    logger = Logger::getInstance();

    window = new Window(width, height, title);
    instance = new Instance();

    shouldRun = true;
}

Application::~Application() {
    delete instance;
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
