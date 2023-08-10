//
// Created by larsewi on 19.08.2020.
//

#include "sandbox.hpp"

#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 480
#define WINDOW_TITLE std::string("Bogus Game Engine")

int main() {
  auto app = Sandbox(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
  if (!app.Run()) {
    std::cerr << "Failed to run application" << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
