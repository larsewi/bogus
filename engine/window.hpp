//
// Created by larsewi on 19.08.2020.
//

#ifndef BOGUS_WINDOW_HPP
#define BOGUS_WINDOW_HPP

#include <GLFW/glfw3.h>
#include <string>
#include <vector>

#include "logger.hpp"

namespace Bogus {
class Window {
public:
  Window(int width, int height, const std::string &title);
  ~Window();

  bool shouldClose() { return glfwWindowShouldClose(glfwWindow) != 0; }
  static void pollEvents() { glfwPollEvents(); }

  static std::vector<const char *> getRequiredExtensions();

private:
  Logger *logger;
  const std::string tag = "Window";

  static int count;
  GLFWwindow *glfwWindow;
};
} // namespace Bogus

#endif // BOGUS_WINDOW_HPP
