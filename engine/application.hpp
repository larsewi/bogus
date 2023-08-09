//
// Created by larsewi on 18.08.2020.
//

#ifndef BOGUS_APPLICATION_HPP
#define BOGUS_APPLICATION_HPP

#include <string>

#include "window.hpp"
#include "instance.hpp"
#include "logger.hpp"

namespace Bogus {
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
        Logger *logger;
        const std::string tag = "Application";

        Window *window;
        Instance *instance;

        bool shouldRun;

        void handleEvents();
        void update();
        void render();
    };
}

#endif // BOGUS_APPLICATION_HPP
