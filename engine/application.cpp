//
// Created by larsewi on 18.08.2020.
//

#define GLFW_INCLUDE_VULKAN
#define VULKAN_HPP_NO_EXCEPTIONS

#include <algorithm>
#include <iostream>
#include <vector>

#include "application.hpp"

using namespace bogus;

#define ENGINE_NAME "bogus"
#define ENGINE_MAJOR 1
#define ENGINE_MINOR 0
#define ENGINE_PATCH 0

#ifndef NDEBUG
static const std::vector<const char *> RequiredValidationLayers = {
    "VK_LAYER_KHRONOS_validation",
};
#endif // NDEBUG

Application::Application(const std::string &app_name, int app_major,
                         int app_minor, int app_patch,
                         const std::string &window_title, int window_width,
                         int window_height)
    : m_app_name(app_name), m_app_major(app_major), m_app_minor(app_minor),
      m_app_patch(app_patch), m_window_title(window_title),
      m_window_width(window_width), m_window_height(window_height) {}

Application::~Application() {}

bool Application::Run() {
  if (!Init()) {
    std::cerr << "Critical: Failed to initialize" << std::endl;
    return false;
  }

  while (m_should_run) {
    if (!Events()) {
      std::cerr << "Critical: Failed to handle events" << std::endl;
      return false;
    }

    if (!Update()) {
      std::cerr << "Critical: Failed to update" << std::endl;
      return false;
    }

    if (!Render()) {
      std::cerr << "Critical: Failed to render" << std::endl;
      return false;
    }
  }

  if (!Exit()) {
    std::cerr << "Critical: Failed to exit" << std::endl;
    return false;
  }

  return true;
}

static GLFWwindow *CreateWindow(const std::string &title, int width,
                                int height) {
  std::cout << "Debug: Initializing GLFW" << std::endl;
  if (glfwInit() == GLFW_FALSE) {
    std::cerr << "Critical: Failed to initialize GLFW" << std::endl;
    return nullptr;
  }

  std::cout << "Debug: Creating GLFW window" << std::endl;
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // We are not using OpenGL
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // Resizing windows not supported
  GLFWwindow *window =
      glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (window == nullptr) {
    std::cerr << "Critical: Failed to create GLFW window" << std::endl;
    return nullptr;
  }
  return window;
}

static bool
CheckInstanceExtensionSupport(std::vector<const char *> required_extensions) {
#ifndef NDEBUG
  for (auto required : required_extensions) {
    std::cout << "Debug: Found required instance extension '" << required << "'"
              << std::endl;
  }
#endif // NDEBUG

  uint32_t extension_count;
  if ((vkEnumerateInstanceExtensionProperties(nullptr, &extension_count,
                                              nullptr) != VK_SUCCESS)) {
    std::cout
        << "Critical: Failed to query number of available instance extensions"
        << std::endl;
    return false;
  }
  std::vector<VkExtensionProperties> available_extensions(extension_count);
  if (vkEnumerateInstanceExtensionProperties(nullptr, &extension_count,
                                             available_extensions.data()) !=
      VK_SUCCESS) {
    std::cout << "Critical: Failed to query available instance extensions"
              << std::endl;
    return false;
  }

#ifndef NDEBUG
  for (const auto &extension : available_extensions) {
    auto available = extension.extensionName;
    std::cout << "Debug: Found available instance extension '" << available
              << "'" << std::endl;
  }
#endif // NDEBUG

  for (const std::string required : required_extensions) {
    if (!std::any_of(
            available_extensions.begin(), available_extensions.end(),
            [&required](const VkExtensionProperties &extension_property) {
              const std::string available(extension_property.extensionName);
              return required == available;
            })) {
      std::cerr << "Critical: Required instance extension '" << required
                << "' not available" << std::endl;
      return false;
    }
  }

  return true;
}

#ifndef NDEBUG
static bool
CheckValidationLayerSupport(std::vector<const char *> required_layers) {
  for (auto required : required_layers) {
    std::cout << "Debug: Found required validation layer '" << required << "'"
              << std::endl;
  }

  uint32_t layer_count;
  if (vkEnumerateInstanceLayerProperties(&layer_count, nullptr) != VK_SUCCESS) {
    std::cout
        << "Critical: Failed to query number of available validation layers"
        << std::endl;
    return false;
  }
  std::vector<VkLayerProperties> available_layers(layer_count);
  if (vkEnumerateInstanceLayerProperties(
          &layer_count, available_layers.data()) != VK_SUCCESS) {
    std::cout << "Critical: Failed to query available validation layers"
              << std::endl;
    return false;
  }

  for (const auto layer : available_layers) {
    auto available = layer.layerName;
    std::cout << "Debug: Found available validation layer '" << available << "'"
              << std::endl;
  }

  for (const std::string required : required_layers) {
    if (!std::any_of(available_layers.begin(), available_layers.end(),
                     [&required](const VkLayerProperties &layer_property) {
                       const std::string available(layer_property.layerName);
                       return required == available;
                     })) {
      std::cerr << "Critical: Required validation layer '" << required
                << "' not available" << std::endl;
      return false;
    }
  }

  return true;
}
#endif // NDEBUG

static bool CreateInstance(VkInstance *instance, const std::string &name,
                           int major, int minor, int patch) {
  VkApplicationInfo app_info{};
  app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  app_info.pApplicationName = name.c_str();
  app_info.applicationVersion = VK_MAKE_VERSION(major, minor, patch);
  app_info.pEngineName = ENGINE_NAME;
  app_info.engineVersion =
      VK_MAKE_VERSION(ENGINE_MAJOR, ENGINE_MINOR, ENGINE_PATCH);
  app_info.apiVersion = VK_API_VERSION_1_3;

  std::cout << "Debug: Getting required instance extensions" << std::endl;
  uint32_t extension_count = 0;
  const char **glfw_extension_names =
      glfwGetRequiredInstanceExtensions(&extension_count);
  if (glfw_extension_names == nullptr) {
    std::cerr << "Critical: Failed to get required GLFW instance extensions"
              << std::endl;
    return false;
  }

  std::vector<const char *> required_extensions;
  for (uint32_t i = 0; i < extension_count; i++) {
    required_extensions.emplace_back(glfw_extension_names[i]);
  }
  required_extensions.emplace_back(
      VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);

  std::cout << "Debug: Checking instance extenstion support" << std::endl;
  if (!CheckInstanceExtensionSupport(required_extensions)) {
    std::cerr << "Critical: Found unsupported instance extension" << std::endl;
    return false;
  }

  VkInstanceCreateInfo create_info{};
  create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  create_info.pApplicationInfo = &app_info;
  create_info.enabledExtensionCount = required_extensions.size();
  create_info.ppEnabledExtensionNames = required_extensions.data();
  create_info.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;

#ifndef NDEBUG
  std::cout << "Debug: Checking validation layer support" << std::endl;
  if (!CheckValidationLayerSupport(RequiredValidationLayers)) {
    std::cerr << "Critical: Found unsupported validation layer" << std::endl;
    return false;
  }
  create_info.enabledLayerCount = RequiredValidationLayers.size();
  create_info.ppEnabledLayerNames = RequiredValidationLayers.data();
#endif // NDEBUG

  VkResult result = vkCreateInstance(&create_info, nullptr, instance);
  if (result != VK_SUCCESS) {
    std::cerr << "Critical: Failed to create Vulkan instance (" << result << ")"
              << std::endl;
    return false;
  }

  return true;
}

bool Application::Init() {
  std::cout << "Verbose: Creating window" << std::endl;
  m_window = CreateWindow(m_window_title, m_window_width, m_window_height);
  if (m_window == nullptr) {
    std::cerr << "Critical: Failed to create window" << std::endl;
    return false;
  }

  std::cout << "Verbose: Creating instance" << std::endl;
  if (!CreateInstance(&m_instance, m_app_name, m_app_major, m_app_minor,
                      m_app_patch)) {
    std::cerr << "Critical: Failed to create instance" << std::endl;
    return false;
  }

  return true;
}

bool Application::Events() {
  glfwPollEvents();

  if (!OnEvent()) {
    return false;
  }
  return true;
}

bool Application::Update() {
  if (glfwWindowShouldClose(m_window)) {
    m_should_run = false;
  }

  if (!OnUpdate()) {
    return false;
  }
  return true;
}

bool Application::Render() {
  if (!OnDraw()) {
    return false;
  }
  return true;
}

bool Application::Exit() {
  vkDestroyInstance(m_instance, nullptr);

  glfwDestroyWindow(m_window);
  glfwTerminate();

  if (!OnExit()) {
    return false;
  }
  return true;
}
