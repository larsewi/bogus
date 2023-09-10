#ifndef BOGUS_PHYSICAL_DEVICE_HPP
#define BOGUS_PHYSICAL_DEVICE_HPP

#include <optional>
#include <stdexcept>
#include <vulkan/vulkan.h>

#include "instance.hpp"

namespace bogus {

struct QueueFamilyIndices {
  std::optional<uint32_t> graphics_family;
};

class PhysicalDeviceException : public std::exception {
public:
  PhysicalDeviceException(const std::string &message) : m_message(message) {}
  virtual const char *what() const throw() { return m_message.c_str(); }

private:
  const std::string m_message;
};

class PhysicalDevice {
public:
  PhysicalDevice(Instance &instance);
  VkDeviceQueueCreateInfo GetDeviceQueueCreateInfo() const;
  VkPhysicalDeviceFeatures GetPhysicalDeviceFeatures() const;

private:
  VkPhysicalDevice m_device;

  friend class LogicalDevice;
};

} // namespace bogus

#endif // BOGUS_PHYSICAL_DEVICE_HPP
