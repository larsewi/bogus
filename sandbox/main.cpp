//
// Created by larsewi on 19.08.2020.
//

#include "sandbox_app.hpp"

#define TAG "main"
#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 480
#define WINDOW_TITLE "Bogus Game Engine"

int main() {
  auto logger = Bogus::Logger::getInstance();
  logger->setLogLevel(Bogus::Logger::LOG_LEVEL_DEBUG);

  Bogus::Application *app = nullptr;
  try {
    app = new SandboxApp(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    app->run();
  } catch (const std::exception &e) {
    logger->logError(TAG, e.what());
    delete app;
    delete logger;
    return EXIT_FAILURE;
  }

  delete app;
  delete logger;

  return EXIT_SUCCESS;
}
