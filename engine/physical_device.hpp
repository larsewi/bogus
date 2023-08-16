#ifndef BOGUS_PHYSICAL_DEVICE_HPP
#define BOGUS_PHYSICAL_DEVICE_HPP

#include <stdexcept>
#include <vulkan/vulkan.h>

#include "instance.hpp"

namespace bogus {

class PhysicalDeviceException : public std::exception {
public:
  PhysicalDeviceException(const std::string &message) : m_message(message) {}
  virtual const char *what() const throw() { return m_message.c_str(); }

private:
  std::string m_message;
};

class PhysicalDevice {
public:
  PhysicalDevice(Instance &instance);

private:
  VkPhysicalDevice m_device;
};

} // namespace bogus

#endif // BOGUS_PHYSICAL_DEVICE_HPP
