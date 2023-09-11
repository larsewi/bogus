#include <optional>
#include <set>
#include <vector>

#include "device.hpp"
#include "logger.hpp"

using namespace bogus;

static const std::vector<const char *> required_extensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME};

struct QueueFamilyIndices {
  std::optional<uint32_t> graphics_family;
  std::optional<uint32_t> presentation_family;
};

struct SwapChainSupportDetails {
  VkSurfaceCapabilitiesKHR capabilities;
  std::vector<VkSurfaceFormatKHR> formats;
  std::vector<VkPresentModeKHR> present_modes;
};

SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device,
                                              VkSurfaceKHR surface) {
  log::debug("Querying physical device surface capabilities");
  SwapChainSupportDetails details;
  if (vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
          device, surface, &details.capabilities) != VK_SUCCESS) {
    throw DeviceException(
        "Failed to query physical device surface capabilities");
  }

  log::debug("Querying number of physical device surface formats");
  uint32_t count = 0;
  if (vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &count, nullptr) !=
      VK_SUCCESS) {
    throw DeviceException(
        "Failed to query number of physical device surface formats");
  }

  if (count > 0) {
    log::debug("Getting physical device surface formats");
    details.formats.resize(count);
    if (vkGetPhysicalDeviceSurfaceFormatsKHR(
            device, surface, &count, details.formats.data()) != VK_SUCCESS) {
      throw DeviceException("Failed to get physical device surface formats");
    }
  }

  count = 0;
  log::debug("Querying number of physical device surface presentation modes");
  if (vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &count,
                                                nullptr) != VK_SUCCESS) {
    throw DeviceException(
        "Failed to query number of physical device surface presentation modes");
  }

  if (count > 0) {
    log::debug("Getting physical device surface presentation modes");
    details.present_modes.resize(count);
    if (vkGetPhysicalDeviceSurfacePresentModesKHR(
            device, surface, &count, details.present_modes.data()) !=
        VK_SUCCESS) {
      throw DeviceException(
          "Failed to get physical device surface presentation modes");
    }
  }

  return details;
}

static bool CheckDeviceExtensionSupport(VkPhysicalDevice device) {
#ifndef NDEBUG
  log::debug("Required device extensions:");
  for (auto const &required : required_extensions) {
    log::debug("   {}", required);
  }
#endif // NDEBUG

  log::debug("Querying number of available device extenstions");
  uint32_t count;
  if (vkEnumerateDeviceExtensionProperties(device, nullptr, &count, nullptr) !=
      VK_SUCCESS) {
    log::error("Failed to query number of available device extensions");
    return false;
  }

  log::debug("Enumerating available device extenstions");
  std::vector<VkExtensionProperties> available_extensions(count);
  if (vkEnumerateDeviceExtensionProperties(
          device, nullptr, &count, available_extensions.data()) != VK_SUCCESS) {
    log::error("Failed to enumerate available device extenstions");
    return false;
  }

  for (const std::string &required : required_extensions) {
    if (!std::any_of(
            available_extensions.begin(), available_extensions.end(),
            [&required](const VkExtensionProperties &extension_property) {
              const std::string available(extension_property.extensionName);
              return required == available;
            })) {
      log::error("Required device extension '{}' not available", required);
      return false;
    }
  }

  return true;
}

static QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device,
                                            VkSurfaceKHR surface) {
  QueueFamilyIndices indices;

  uint32_t count;
  vkGetPhysicalDeviceQueueFamilyProperties(device, &count, nullptr);

  std::vector<VkQueueFamilyProperties> families(count);
  vkGetPhysicalDeviceQueueFamilyProperties(device, &count, families.data());

  for (uint32_t i = 0; i < count; i++) {
    const auto &family = families[i];

    if (family.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
      indices.graphics_family = i;
    }

    VkBool32 present_support = false;
    vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &present_support);
    if (present_support) {
      indices.presentation_family = i;
    }
  }

  return indices;
}

static bool IsPhysicalDeviceSuitable(VkPhysicalDevice device,
                                     QueueFamilyIndices indices) {
  VkPhysicalDeviceProperties properties;
  vkGetPhysicalDeviceProperties(device, &properties);

  VkPhysicalDeviceFeatures features;
  vkGetPhysicalDeviceFeatures(device, &features);

  if (!indices.graphics_family.has_value()) {
    log::debug("   Device {} not suitable: missing graphics queue family",
               properties.deviceName);
    return false;
  }

  if (!indices.presentation_family.has_value()) {
    log::debug("   Device {} not suitable: missing present queue family",
               properties.deviceName);
    return false;
  }

  if (!CheckDeviceExtensionSupport(device)) {
    log::debug("   Device {} not suitable: missing required extenstion support",
               properties.deviceName);
    return false;
  }

  log::debug("   Found suitable physical device {}", properties.deviceName);
  return true;
}

Device::Device(Instance &instance, Surface &surface)
    : m_physical_device(VK_NULL_HANDLE) {
  log::debug("Querying number of physical devices");
  uint32_t physical_device_count;
  if (vkEnumeratePhysicalDevices(instance.m_instance, &physical_device_count,
                                 nullptr) != VK_SUCCESS) {
    throw DeviceException("Failed to query number of physical devices");
  }

  if (physical_device_count == 0) {
    throw DeviceException(
        "Failed to find physical devices with Vulkan support");
  }

  log::debug("Enumerating physical devices");
  std::vector<VkPhysicalDevice> physical_devices(physical_device_count);
  if (vkEnumeratePhysicalDevices(instance.m_instance, &physical_device_count,
                                 physical_devices.data()) != VK_SUCCESS) {
    throw DeviceException("Failed to enumerate physical devices");
  }

  QueueFamilyIndices indices;
  for (const auto &physical_device : physical_devices) {
    VkPhysicalDeviceProperties properties;
    vkGetPhysicalDeviceProperties(physical_device, &properties);

    VkPhysicalDeviceFeatures features;
    vkGetPhysicalDeviceFeatures(physical_device, &features);

    indices = FindQueueFamilies(physical_device, surface.m_surface);

    if (IsPhysicalDeviceSuitable(physical_device, indices)) {
      m_physical_device = physical_device;
      break;
    }
  }

  if (m_physical_device == VK_NULL_HANDLE) {
    throw DeviceException("Failed to find a suitable physical device");
  }

  std::set<uint32_t> uniqueue_queue_families = {
      indices.graphics_family.value(), indices.presentation_family.value()};

  std::vector<VkDeviceQueueCreateInfo> queue_create_infos;
  float queue_priority = 1.0f;
  for (uint32_t queue_family : uniqueue_queue_families) {
    VkDeviceQueueCreateInfo create_info{};
    create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    create_info.queueFamilyIndex = queue_family;
    create_info.queueCount = 1;
    create_info.pQueuePriorities = &queue_priority;
    queue_create_infos.push_back(create_info);
  }

  VkPhysicalDeviceFeatures physical_device_features = {};

  VkDeviceCreateInfo logical_device_create_info{};
  logical_device_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  logical_device_create_info.queueCreateInfoCount =
      static_cast<uint32_t>(queue_create_infos.size());
  logical_device_create_info.pQueueCreateInfos = queue_create_infos.data();
  logical_device_create_info.pEnabledFeatures = &physical_device_features;
  logical_device_create_info.enabledExtensionCount =
      static_cast<uint32_t>(required_extensions.size());
  logical_device_create_info.ppEnabledExtensionNames =
      required_extensions.data();

  if (vkCreateDevice(m_physical_device, &logical_device_create_info, nullptr,
                     &m_logical_device) != VK_SUCCESS) {
    throw DeviceException("Failed to create logical device");
  }

  vkGetDeviceQueue(m_logical_device, indices.graphics_family.value(), 0,
                   &m_graphics_queue);
  vkGetDeviceQueue(m_logical_device, indices.presentation_family.value(), 0,
                   &m_presentation_queue);
}

Device::~Device() { vkDestroyDevice(m_logical_device, nullptr); }
