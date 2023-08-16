#ifndef BOGUS_LOGICAL_DEVICE_HPP
#define BOGUS_LOGICAL_DEVICE_HPP

#include <stdexcept>
#include <vulkan/vulkan.h>

#include "instance.hpp"

namespace bogus {

class LogicalDeviceException : public std::exception {
public:
  LogicalDeviceException(const std::string &message) : m_message(message){};
  virtual const char *what() const throw() { return m_message.c_str(); }

private:
  std::string m_message;
};

class LogicalDevice {
public:
  LogicalDevice(Instance &instance);

private:
  VkDevice m_device;
};

} // namespace bogus

#endif // BOGUS_LOGICAL_DEVICE_HPP
