//
// Created by larsewi on 18.08.2020.
//

#define GLFW_INCLUDE_VULKAN
#define VULKAN_HPP_NO_EXCEPTIONS

#define ENGINE_NAME "bogus"
#define ENGINE_MAJOR 1
#define ENGINE_MINOR 0
#define ENGINE_PATCH 0

#include <iostream>
#include <vector>

#include "application.hpp"

using namespace bogus;

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
    std::cerr << "An error occured while initializing " << std::endl;
    return false;
  }

  while (m_should_run) {
    if (!Events()) {
      std::cerr << "An error occured while handling events" << std::endl;
      return false;
    }

    if (!Update()) {
      std::cerr << "An error occured while updating" << std::endl;
      return false;
    }

    if (!Render()) {
      std::cerr << "An error occured while rendering" << std::endl;
      return false;
    }
  }

  if (!Exit()) {
    std::cerr << "An error occured while exiting" << std::endl;
    return false;
  }

  return true;
}

static GLFWwindow *CreateWindow(const std::string &title, int width,
                                int height) {
  if (glfwInit() == GLFW_FALSE) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return nullptr;
  }
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // We are not using OpenGL
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // Resizing windows not supported
  GLFWwindow *window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (window == nullptr) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    return nullptr;
  }
  return window;
}

static bool CreateInstance(VkInstance *instance, const std::string &name, int major,
                                   int minor, int patch) {
  VkApplicationInfo app_info{};
  app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  app_info.pApplicationName = name.c_str();
  app_info.applicationVersion = VK_MAKE_VERSION(major, minor, patch);
  app_info.pEngineName = ENGINE_NAME;
  app_info.engineVersion = VK_MAKE_VERSION(ENGINE_MAJOR, ENGINE_MINOR, ENGINE_PATCH);
  app_info.apiVersion = VK_API_VERSION_1_3;

  uint32_t glfw_extension_count = 0;
  const char **glfw_extension_names =
      glfwGetRequiredInstanceExtensions(&glfw_extension_count);
  if (glfw_extension_names == nullptr) {
    std::cerr << "Failed to get required GLFW instance extensions" << std::endl;
    return false;
  }

  std::vector<const char *> required_extensions;
  for (uint32_t i = 0; i < glfw_extension_count; i++) {
    required_extensions.emplace_back(glfw_extension_names[i]);
  }
  required_extensions.emplace_back(
      VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);

  VkInstanceCreateInfo create_info{};
  create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  create_info.pApplicationInfo = &app_info;
  create_info.enabledExtensionCount = required_extensions.size();
  create_info.ppEnabledExtensionNames = required_extensions.data();
  create_info.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;

  VkResult result = vkCreateInstance(&create_info, nullptr, instance);
  if (result != VK_SUCCESS) {
    std::cerr << "Failed to create Vulkan instance (" << result << ")" << std::endl;
    return false;
  }

  return true;
}

bool Application::Init() {
  m_window = CreateWindow(m_window_title, m_window_width, m_window_height);
  if (m_window == nullptr) {
    return false;
  }

  if (!CreateInstance(&m_instance, m_app_name, m_app_major, m_app_minor, m_app_patch)) {
    return false;
  }

  m_should_run = true;

  if (!OnInit()) {
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
