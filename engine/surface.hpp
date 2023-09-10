/**
 * @file surface.hpp
 * @author Lars Erik Wik
 * @brief An abstract type of surface to present rendered images to.
 * @version 0.1
 * @date 2023-09-10
 *
 * @copyright Copyright (c) 2023
 *
 */

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

  friend class PhysicalDevice;
  friend class Device;
};

} // namespace bogus

#endif // BOGUS_SURFACE_HPP
