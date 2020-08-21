//
// Created by larsewi on 18.08.2020.
//

#ifndef ACRYLIC_APPLICATION_H
#define ACRYLIC_APPLICATION_H

#include <string>

#include "Window.h"
#include "Instance.h"

class Application {
public:
    Application(int width, int height, const std::string& title);
    virtual ~Application();

    void run();

protected:
    virtual void onInit() {};
    virtual void onEvent() {};
    virtual void onUpdate() {};
    virtual void onDraw() {};
    virtual void onExit() {};

private:
    void handleEvents();
    void update();
    void render();

    Window* m_pWindow;
    Instance* m_pInstance;

    bool m_bShouldRun;
};

#endif //ACRYLIC_APPLICATION_H
