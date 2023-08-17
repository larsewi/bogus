#include "logical_device.hpp"

using namespace bogus;

LogicalDevice::LogicalDevice(Instance &instance,
                             PhysicalDevice &physical_device) {
  VkDeviceCreateInfo create_info{};
  create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

  VkDeviceQueueCreateInfo queue_create_info =
      physical_device.GetDeviceQueueCreateInfo();
  create_info.pQueueCreateInfos = &queue_create_info;
  create_info.queueCreateInfoCount = 1;

  VkPhysicalDeviceFeatures device_features =
      physical_device.GetPhysicalDeviceFeatures();
  create_info.pEnabledFeatures = &device_features;

  if (vkCreateDevice(physical_device.m_device, &create_info, nullptr,
                     &m_device) != VK_SUCCESS) {
    throw LogicalDeviceException("Failed to create logical device");
  }

  vkGetDeviceQueue(m_device, queue_create_info.queueFamilyIndex, 0,
                   &m_graphics_queue);
}

LogicalDevice::~LogicalDevice() { vkDestroyDevice(m_device, nullptr); }
