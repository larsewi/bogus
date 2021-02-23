//
// Created by larsewi on 20.08.2020.
//

#include <cstring>
#include <stdexcept>

#include "Instance.h"
#include "Logger.h"
#include "DebugMessenger.h"

#define TAG "Instance"

using namespace Bogus;

Instance::Instance() : handle(nullptr), debugMessenger(nullptr),
validationLayers({"VK_LAYER_KHRONOS_validation"}), logger(nullptr) {
    logger = Logger::getInstance();

    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    auto extensions = Window::getRequiredExtensions();

    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
    if (ENABLE_VALIDATION_LAYERS && validationLayerSupported()) {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();

        DebugMessenger::populateCreateInfo(debugCreateInfo);
        createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
    } else {
        createInfo.enabledLayerCount = 0;
        createInfo.pNext = nullptr;
    }
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    logger->logVerbose(TAG, "Creating VkInstance");
    if (vkCreateInstance(&createInfo, nullptr, &handle) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }

    if (ENABLE_VALIDATION_LAYERS && validationLayerSupported()) {
        logger->logVerbose(TAG, "Creating debug messenger");
        if (DebugMessenger::create(handle, &debugCreateInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
            throw std::runtime_error("failed to set up debug messenger!");
        }
    }
}

Instance::~Instance() {
    logger->logVerbose(TAG, "Destroying debug messenger");
    DebugMessenger::destroy(handle, debugMessenger, nullptr);

    logger->logVerbose(TAG, "Destroying VkInstance");
    vkDestroyInstance(handle, nullptr);
}

bool Instance::validationLayerSupported() {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const char* layerName : validationLayers) {
        bool layerFound = false;
        for (const auto& layerProperties : availableLayers) {
            if (strcmp(layerName, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }
        if (!layerFound) {
            return false;
        }
    }
    return true;
}
