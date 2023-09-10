#ifndef BOGUS_DEVICE_HPP
#define BOGUS_DEVICE_HPP

#include <vulkan/vulkan.h>

#include <optional>
#include <stdexcept>
#include <string>

#include "instance.hpp"
#include "surface.hpp"

namespace bogus {

class DeviceException : public std::exception {
public:
  DeviceException(const std::string &message) : m_message(message) {}
  virtual const char *what() const throw() { return m_message.c_str(); }

private:
  const std::string m_message;
};

class Device {
public:
  Device(Instance &instance, Surface &surface);
  ~Device();

private:
  VkPhysicalDevice m_physical_device;
  VkDevice m_logical_device;
  VkQueue m_graphics_queue;
  VkQueue m_present_queue;
};

} // namespace bogus

#endif // BOGUS_PHYSICAL_DEVICE_HPP
