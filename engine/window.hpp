/**
 * @file window.hpp
 * @author Lars Erik Wik
 * @brief The windows to render images on.
 * @version 0.1
 * @date 2023-09-10
 *
 * @copyright Copyright (c) 2023
 *
 */

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
  ~Window();
  std::unique_ptr<std::vector<const char *>> GetExtensions() const;
  bool ShouldClose() const;
  bool Events() override;
  bool Update() override;
  bool Render() override;

private:
  const std::string m_title;
  int m_width;
  int m_height;
  GLFWwindow *m_window;
  bool m_should_close;

  friend class Surface;
};

} // namespace bogus

#endif // BOGUS_WINDOW_HPP
