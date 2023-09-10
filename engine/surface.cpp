#include "surface.hpp"
#include "logger.hpp"

using namespace bogus;

Surface::Surface(Instance &instance, Window &window) : m_instance(instance) {
  log::debug("Creating GLFW window surface");
  if (glfwCreateWindowSurface(m_instance.m_instance, window.m_window, nullptr,
                              &m_surface) != VK_SUCCESS) {
    throw SurfaceException("Failed to create window surface");
  }
}

Surface::~Surface() {
  log::debug("Destroying GLWF window surface");
  vkDestroySurfaceKHR(m_instance.m_instance, m_surface, nullptr);
}
