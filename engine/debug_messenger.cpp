#include <iostream>

#include "debug_messenger.hpp"

using namespace bogus;

static VKAPI_ATTR VkBool32 VKAPI_CALL debug_messenger_callback(
    VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
    VkDebugUtilsMessageTypeFlagsEXT message_type,
    const VkDebugUtilsMessengerCallbackDataEXT *callback_data,
    void *pUserData) {

  std::cerr << "validation layer: " << callback_data->pMessage << std::endl;

  return VK_FALSE;
}

static VkResult CreateDebugUtilsMessengerEXT(
    VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *create_info,
    const VkAllocationCallbacks *allocator,
    VkDebugUtilsMessengerEXT *debug_messenger) {
  auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
      instance, "vkCreateDebugUtilsMessengerEXT");
  return (func != nullptr)
             ? func(instance, create_info, allocator, debug_messenger)
             : VK_ERROR_EXTENSION_NOT_PRESENT;
}

static void
DestroyDebugUtilsMessengerEXT(VkInstance instance,
                              VkDebugUtilsMessengerEXT debugMessenger,
                              const VkAllocationCallbacks *pAllocator) {
  auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
      instance, "vkDestroyDebugUtilsMessengerEXT");
  if (func != nullptr) {
    func(instance, debugMessenger, pAllocator);
  }
}

DebugMessenger::DebugMessenger(VkInstance &instance) : m_instance(instance) {
  VkDebugUtilsMessengerCreateInfoEXT create_info = GetCreateInfo();
  if (CreateDebugUtilsMessengerEXT(m_instance, &create_info, nullptr,
                                   &m_debug_messenger) != VK_SUCCESS) {
    throw DebugMessengerException("Failed to create debug utils messenger");
  }
}

DebugMessenger::~DebugMessenger() {
  DestroyDebugUtilsMessengerEXT(m_instance, m_debug_messenger, nullptr);
}

VkDebugUtilsMessengerCreateInfoEXT DebugMessenger::GetCreateInfo() {
  VkDebugUtilsMessengerCreateInfoEXT create_info{};
  create_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
  create_info.messageSeverity =
      VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
      VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
      VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
      VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
  create_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                            VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                            VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
  create_info.pfnUserCallback = debug_messenger_callback;
  create_info.pUserData = nullptr; // Optional
  return create_info;
}
