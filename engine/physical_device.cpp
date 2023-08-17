#include <vector>

#include "logger.hpp"
#include "physical_device.hpp"

using namespace bogus;

static QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device) {
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
  }

  return indices;
}

static bool IsPhysicalDeviceSuitable(VkPhysicalDevice device) {
  VkPhysicalDeviceProperties properties;
  vkGetPhysicalDeviceProperties(device, &properties);

  VkPhysicalDeviceFeatures features;
  vkGetPhysicalDeviceFeatures(device, &features);

  QueueFamilyIndices indices = FindQueueFamilies(device);

  if (!indices.graphics_family.has_value()) {
    log::debug("   Device {} not suitable: missing graphics queue family",
               properties.deviceName);
    return false;
  }

  log::debug("   Found suitable physical device {}", properties.deviceName);
  return true;
}

PhysicalDevice::PhysicalDevice(Instance &instance) : m_device(VK_NULL_HANDLE) {
  uint32_t device_count;
  if (vkEnumeratePhysicalDevices(instance.m_instance, &device_count, nullptr) !=
      VK_SUCCESS) {
    throw PhysicalDeviceException("Failed to query number of physical devices");
  }

  if (device_count == 0) {
    throw PhysicalDeviceException(
        "Failed to find physical devices with Vulkan support");
  }

  std::vector<VkPhysicalDevice> devices(device_count);
  if (vkEnumeratePhysicalDevices(instance.m_instance, &device_count,
                                 devices.data()) != VK_SUCCESS) {
    throw PhysicalDeviceException("Failed to enumerate physical devices");
  }

  log::debug("Looking for suitable physical device:");
  for (const auto &device : devices) {
    VkPhysicalDeviceProperties properties;
    vkGetPhysicalDeviceProperties(device, &properties);

    VkPhysicalDeviceFeatures features;
    vkGetPhysicalDeviceFeatures(device, &features);

    if (IsPhysicalDeviceSuitable(device)) {
      m_device = device;
      break;
    }
  }

  if (m_device == VK_NULL_HANDLE) {
    throw PhysicalDeviceException("Failed to find a suitable physical device");
  }
}

VkDeviceQueueCreateInfo PhysicalDevice::GetDeviceQueueCreateInfo() const {
  QueueFamilyIndices indices = FindQueueFamilies(m_device);

  VkDeviceQueueCreateInfo create_info{};
  create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  create_info.queueFamilyIndex = indices.graphics_family.value();
  create_info.queueCount = 1;
  float queue_priority = 1.0f;
  create_info.pQueuePriorities = &queue_priority;

  return create_info;
}

VkPhysicalDeviceFeatures PhysicalDevice::GetPhysicalDeviceFeatures() const {
  VkPhysicalDeviceFeatures features{};
  return features;
}
