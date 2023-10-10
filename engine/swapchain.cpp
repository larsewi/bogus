#include <vector>

#include "logger.hpp"
#include "swapchain.hpp"

using namespace bogus;

SwapChainSupportDetails
SwapChain::QuerySwapChainSupport(VkPhysicalDevice device,
                                 VkSurfaceKHR surface) {
  log::debug("Querying physical device surface capabilities");
  SwapChainSupportDetails details;
  if (vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
          device, surface, &details.capabilities) != VK_SUCCESS) {
    throw SwapChainException(
        "Failed to query physical device surface capabilities");
  }

  log::debug("Querying number of physical device surface formats");
  uint32_t count = 0;
  if (vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &count, nullptr) !=
      VK_SUCCESS) {
    throw SwapChainException(
        "Failed to query number of physical device surface formats");
  }

  if (count > 0) {
    log::debug("Getting physical device surface formats");
    details.formats.resize(count);
    if (vkGetPhysicalDeviceSurfaceFormatsKHR(
            device, surface, &count, details.formats.data()) != VK_SUCCESS) {
      throw SwapChainException("Failed to get physical device surface formats");
    }
  }

  count = 0;
  log::debug("Querying number of physical device surface presentation modes");
  if (vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &count,
                                                nullptr) != VK_SUCCESS) {
    throw SwapChainException(
        "Failed to query number of physical device surface presentation modes");
  }

  if (count > 0) {
    log::debug("Getting physical device surface presentation modes");
    details.present_modes.resize(count);
    if (vkGetPhysicalDeviceSurfacePresentModesKHR(
            device, surface, &count, details.present_modes.data()) !=
        VK_SUCCESS) {
      throw SwapChainException(
          "Failed to get physical device surface presentation modes");
    }
  }

  return details;
}

SwapChain::SwapChain() {}

SwapChain::~SwapChain() {}
