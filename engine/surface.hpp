#ifndef BOGUS_SURFACE_HPP
#define BOGUS_SURFACE_HPP

#include <vulkan/vulkan.h>

#include <stdexcept>

#include "instance.hpp"
#include "object.hpp"
#include "window.hpp"

namespace bogus {

class SurfaceException : public std::exception {
public:
  SurfaceException(const std::string &message) : m_message(message) {}
  virtual const char *what() const throw() { return m_message.c_str(); }

private:
  const std::string m_message;
};

class Surface {
public:
  Surface(Instance &instance, Window &window);
  ~Surface();

private:
  VkSurfaceKHR m_surface;
  Instance &m_instance;
};

} // namespace bogus

#endif // BOGUS_SURFACE_HPP
