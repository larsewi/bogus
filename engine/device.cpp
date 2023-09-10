#include <optional>
#include <set>
#include <vector>

#include "device.hpp"
#include "logger.hpp"

using namespace bogus;

struct QueueFamilyIndices {
  std::optional<uint32_t> graphics_family;
  std::optional<uint32_t> present_family;
};

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
      indices.present_family = i;
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

  if (!indices.present_family.has_value()) {
    log::debug("   Device {} not suitable: missing present queue family",
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

  std::set<uint32_t> uniqueue_queue_families = {indices.graphics_family.value(),
                                                indices.present_family.value()};

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

  if (vkCreateDevice(m_physical_device, &logical_device_create_info, nullptr,
                     &m_logical_device) != VK_SUCCESS) {
    throw DeviceException("Failed to create logical device");
  }

  vkGetDeviceQueue(m_logical_device, indices.graphics_family.value(), 0,
                   &m_graphics_queue);
  vkGetDeviceQueue(m_logical_device, indices.present_family.value(), 0,
                   &m_present_queue);
}

Device::~Device() { vkDestroyDevice(m_logical_device, nullptr); }
