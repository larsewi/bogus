#ifndef BOGUS_SWAPCHAIN_HPP
#define BOGUS_SWAPCHAIN_HPP

#include <stdexcept>
#include <vulkan/vulkan.h>

namespace bogus {

struct SwapChainSupportDetails {
  VkSurfaceCapabilitiesKHR capabilities;
  std::vector<VkSurfaceFormatKHR> formats;
  std::vector<VkPresentModeKHR> present_modes;
};

class SwapChainException : public std::exception {
public:
  SwapChainException(const std::string &message) : m_message(message) {}
  virtual const char *what() const throw() { return m_message.c_str(); }

private:
  const std::string m_message;
};

class SwapChain {
public:
  SwapChain();
  ~SwapChain();

  static SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device,
                                                       VkSurfaceKHR surface);
};

} // namespace bogus

#endif // BOGUS_SWAPCHAIN_HPP
