#ifndef BOGUS_DEBUG_MESSENGER_HPP
#define BOGUS_DEBUG_MESSENGER_HPP

#include <vulkan/vulkan.h>

namespace bogus {

class DebugMessengerException : public std::exception {
public:
  DebugMessengerException(const std::string &message) : m_message(message) {}
  virtual const char *what() const throw() { return m_message.c_str(); }

private:
  std::string m_message;
};

class DebugMessenger {
public:
  DebugMessenger() = default;
  DebugMessenger(VkInstance &m_instance);
  ~DebugMessenger();

private:
  VkInstance m_instance;
  VkDebugUtilsMessengerEXT m_debug_messenger;
};

} // namespace bogus

#endif // BOGUS_DEBUG_MESSENGER_HPP
