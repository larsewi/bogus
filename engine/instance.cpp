#include <iostream>

#include "instance.hpp"
#include "logger.hpp"

#define ENGINE_NAME "bogus"
#define ENGINE_MAJOR 1
#define ENGINE_MINOR 0
#define ENGINE_PATCH 0

using namespace bogus;

#ifndef NDEBUG
static const std::vector<const char *> RequiredValidationLayers = {
    "VK_LAYER_KHRONOS_validation",
};
#endif

static bool CheckInstanceExtensionSupport(
    std::unique_ptr<std::vector<const char *>> &required_extensions) {
#ifndef NDEBUG
  log::debug("Required instance extensions:");
  for (auto const &required : *required_extensions) {
    log::debug("   {}", required);
  }
#endif // NDEBUG

  uint32_t extension_count;
  if ((vkEnumerateInstanceExtensionProperties(nullptr, &extension_count,
                                              nullptr) != VK_SUCCESS)) {
    log::error("Failed to query number of available instance extensions");
    ;
    return false;
  }
  std::vector<VkExtensionProperties> available_extensions(extension_count);
  if (vkEnumerateInstanceExtensionProperties(nullptr, &extension_count,
                                             available_extensions.data()) !=
      VK_SUCCESS) {
    log::error("Failed to enumerate available instance extensions");
    return false;
  }

#ifndef NDEBUG
  log::debug("Available instance extensions:");
  for (const auto &extension : available_extensions) {
    auto available = extension.extensionName;
    log::debug("   {}", available);
  }
#endif

  for (const std::string &required : *required_extensions) {
    if (!std::any_of(
            available_extensions.begin(), available_extensions.end(),
            [&required](const VkExtensionProperties &extension_property) {
              const std::string available(extension_property.extensionName);
              return required == available;
            })) {
      log::error("Required instance extension '{}' not available", required);
      return false;
    }
  }

  return true;
}

#ifndef NDEBUG
static bool
CheckValidationLayerSupport(std::vector<const char *> required_layers) {
  log::debug("Required validation layers:");
  for (auto required : required_layers) {
    log::debug("   {}", required);
  }

  uint32_t layer_count;
  if (vkEnumerateInstanceLayerProperties(&layer_count, nullptr) != VK_SUCCESS) {
    log::error("Failed to query number of available validation layers");
    return false;
  }
  std::vector<VkLayerProperties> available_layers(layer_count);
  if (vkEnumerateInstanceLayerProperties(
          &layer_count, available_layers.data()) != VK_SUCCESS) {
    log::error("Failed to enumerate available validation layers");
    return false;
  }

  spdlog::debug("Available validation layers:");
  for (const auto layer : available_layers) {
    auto available = layer.layerName;
    log::debug("   {}", available);
  }

  for (const std::string required : required_layers) {
    if (!std::any_of(available_layers.begin(), available_layers.end(),
                     [&required](const VkLayerProperties &layer_property) {
                       const std::string available(layer_property.layerName);
                       return required == available;
                     })) {
      log::error("Required validation layer '{}' is not available", required);
      return false;
    }
  }

  return true;
}
#endif

Instance::Instance(const std::string &name, int major, int minor, int patch,
                   Window *window)
    : m_name(name), m_major(major), m_minor(minor), m_patch(patch) {
  VkApplicationInfo app_info{};
  app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  app_info.pApplicationName = name.c_str();
  app_info.applicationVersion = VK_MAKE_VERSION(major, minor, patch);
  app_info.pEngineName = ENGINE_NAME;
  app_info.engineVersion =
      VK_MAKE_VERSION(ENGINE_MAJOR, ENGINE_MINOR, ENGINE_PATCH);
  app_info.apiVersion = VK_API_VERSION_1_3;

  VkInstanceCreateInfo create_info{};
  create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  create_info.pApplicationInfo = &app_info;
  create_info.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;

  auto required_extensions = window->GetExtensions();
  required_extensions->push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
#ifndef NDEBUG
  required_extensions->push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif

  if (!CheckInstanceExtensionSupport(required_extensions)) {
    throw InstanceException("Unsupported required instance extensions");
  }

  create_info.enabledExtensionCount = required_extensions->size();
  create_info.ppEnabledExtensionNames = required_extensions->data();

#ifndef NDEBUG
  if (!CheckValidationLayerSupport(RequiredValidationLayers)) {
    throw InstanceException("Unsupported required validation layer");
  }
  create_info.enabledLayerCount = RequiredValidationLayers.size();
  create_info.ppEnabledLayerNames = RequiredValidationLayers.data();

  // This debug messenger is only used during instance create and destroy
  VkDebugUtilsMessengerCreateInfoEXT debug_create_info =
      DebugMessenger::GetCreateInfo();
  create_info.pNext = &debug_create_info;
#else
  create_info.enabledLayerCount = 0;
#endif

  VkResult result = vkCreateInstance(&create_info, nullptr, &m_instance);
  if (result != VK_SUCCESS) {
    throw InstanceException("Failed to create vulkan instance");
  }

#ifndef NDEBUG
  log::debug("Creating debug messenger");
  m_debug_messenger = new DebugMessenger(m_instance);
#else
  m_debug_messenger = nullptr;
#endif
}

Instance::~Instance() {
  log::debug("Destroying debug messenger");

  delete m_debug_messenger;
  vkDestroyInstance(m_instance, nullptr);
}

bool Instance::Events() { return true; }

bool Instance::Update() { return true; }

bool Instance::Render() { return true; }
