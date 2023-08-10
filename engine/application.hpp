//
// Created by larsewi on 18.08.2020.
//

#ifndef BOGUS_APPLICATION_HPP
#define BOGUS_APPLICATION_HPP

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>
#include <string>

namespace bogus {

class Application {
public:
  Application(const int width, const int height, const std::string &title);
  virtual ~Application();
  bool Run();

protected:
  virtual bool OnInit() { return true; };
  virtual bool OnEvent() { return true; };
  virtual bool OnUpdate() { return true; };
  virtual bool OnDraw() { return true; };
  virtual bool OnExit() { return true; };

private:
  const int m_width;
  const int m_height;
  const std::string m_title;
  bool m_should_run;
  GLFWwindow *m_window;

  bool Init();
  bool Events();
  bool Update();
  bool Render();
  bool Exit();

  bool InitWindow();
};

} // namespace bogus

#endif // BOGUS_APPLICATION_HPP
