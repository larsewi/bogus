#ifndef BOGUS_WINDOW_HPP
#define BOGUS_WINDOW_HPP

#include <GLFW/glfw3.h>

#include <memory>
#include <stdexcept>
#include <vector>

#include "object.hpp"

namespace bogus {

class WindowException : public std::exception {
public:
  WindowException(const std::string &message) : m_message(message) {}
  virtual const char *what() const throw() { return m_message.c_str(); }

private:
  const std::string m_message;
};

class Window : public Object {
public:
  Window(const std::string &title, int width, int height);
  std::unique_ptr<std::vector<const char *>> GetExtensions() const;
  bool ShouldClose() const;
  bool Events() override;
  bool Update() override;
  bool Render() override;

private:
  const std::string m_title;
  int m_width;
  int m_height;
  std::unique_ptr<GLFWwindow, void (*)(GLFWwindow *)> m_window;
  bool m_should_close;
};

} // namespace bogus

#endif // BOGUS_WINDOW_HPP
