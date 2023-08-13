//
// Created by larsewi on 18.08.2020.
//

#ifndef BOGUS_APPLICATION_HPP
#define BOGUS_APPLICATION_HPP

// #include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <iostream>
#include <memory>
#include <string>

#include "object.hpp"
#include "window.hpp"

namespace bogus {

class ApplicationException : public std::exception {
public:
  ApplicationException(const std::string &message) : m_message(message) {}
  virtual const char *what() const throw() { return m_message.c_str(); }

private:
  const std::string m_message;
};

class Application : public Object {
public:
  Application(const std::string &app_name, int app_major, int app_minor,
              int app_patch, const std::string &window_title, int window_width,
              int window_height);
  virtual ~Application();
  bool Run();

protected:
  virtual bool OnInit() { return true; };
  virtual bool OnEvent() { return true; };
  virtual bool OnUpdate() { return true; };
  virtual bool OnDraw() { return true; };
  virtual bool OnExit() { return true; };

private:
  const std::string m_app_name;
  const int m_app_major;
  const int m_app_minor;
  const int m_app_patch;

  bool m_should_run;

  std::unique_ptr<Window> m_window;
  VkInstance m_instance;

  bool Init();
  bool Events() override;
  bool Update() override;
  bool Render() override;
  bool Exit();
};

} // namespace bogus

#endif // BOGUS_APPLICATION_HPP
