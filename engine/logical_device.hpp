#ifndef BOGUS_LOGICAL_DEVICE_HPP
#define BOGUS_LOGICAL_DEVICE_HPP

#include <stdexcept>
#include <vulkan/vulkan.h>

#include "instance.hpp"
#include "physical_device.hpp"

namespace bogus {

class LogicalDeviceException : public std::exception {
public:
  LogicalDeviceException(const std::string &message) : m_message(message){};
  virtual const char *what() const throw() { return m_message.c_str(); }

private:
  const std::string m_message;
};

class LogicalDevice {
public:
  LogicalDevice(Instance &instance, PhysicalDevice &physical_device);
  ~LogicalDevice();

private:
  VkDevice m_device;
  VkQueue m_graphics_queue;
};

} // namespace bogus

#endif // BOGUS_LOGICAL_DEVICE_HPP
