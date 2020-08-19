//
// Created by larsewi on 18.08.2020.
//

#ifndef ACRYLIC_APPLICATION_H
#define ACRYLIC_APPLICATION_H

#include <string>
#include <vector>

#include "Window.h"

class Application {
public:
    Application(int width, int height, const std::string& title);
    virtual ~Application();

    void run();

protected:
    virtual void onBegin() {};
    virtual void onEvent() {};
    virtual void onUpdate() {};
    virtual void onDraw() {};
    virtual void onExit() {};

private:
    void handleEvents();
    void update();
    void render();

    bool m_isRunning;
    Window* m_pWindow;
};

#endif //ACRYLIC_APPLICATION_H
