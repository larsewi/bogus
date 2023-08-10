//
// Created by larsewi on 19.08.2020.
//

#include "sandbox.hpp"

#define APP_NAME "Sandbox"
#define APP_MAJOR 1
#define APP_MINOR 0
#define APP_PATCH 0

#define WINDOW_TITLE "Sandbox"
#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 480

int main() {
  auto app = Sandbox(APP_NAME, APP_MAJOR, APP_MINOR, APP_PATCH, WINDOW_TITLE,
                     WINDOW_WIDTH, WINDOW_HEIGHT);
  if (!app.Run()) {
    std::cerr << "Failed to run application" << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
