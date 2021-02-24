//
// Created by larsewi on 20.08.2020.
//

#include <cstring>
#include <stdexcept>

#include "Instance.h"

#ifdef NDEBUG
#define ENABLE_VALIDATION_LAYERS false
#else
#define ENABLE_VALIDATION_LAYERS true
#endif

using namespace Bogus;

static VkResult createDebugMessenger(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
                                     const VkAllocationCallbacks *pAllocator,
                                     VkDebugUtilsMessengerEXT *pDebugMessenger);

static void destroyDebugMessenger(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
                                  const VkAllocationCallbacks *pAllocator);

static VkBool32 debugMessengerCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                       VkDebugUtilsMessageTypeFlagsEXT messageType,
                                       const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData, void *pUserData);

Instance::Instance() : instance(nullptr), debugMessenger(nullptr), logger(nullptr), physicalDevice(nullptr) {
    logger = Logger::getInstance();

    VkApplicationInfo appInfo {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Sandbox";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "Bogus";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_2;

    std::vector<const char*> extensions = Window::getRequiredExtensions();

    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo {};
    if (ENABLE_VALIDATION_LAYERS == validationLayerSupported()) {
        debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        debugCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        debugCreateInfo.pfnUserCallback = debugMessengerCallback;
    }

    VkInstanceCreateInfo instanceCreateInfo {};
    instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceCreateInfo.pApplicationInfo = &appInfo;
    if (ENABLE_VALIDATION_LAYERS == validationLayerSupported()) {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        instanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        instanceCreateInfo.ppEnabledLayerNames = validationLayers.data();
        instanceCreateInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT *) &debugCreateInfo;
    } else {
        instanceCreateInfo.enabledLayerCount = 0;
        instanceCreateInfo.pNext = nullptr;
    }
    instanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    instanceCreateInfo.ppEnabledExtensionNames = extensions.data();

    logger->logDebug(tag, "Creating VkInstance");
    if (vkCreateInstance(&instanceCreateInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }

    if (ENABLE_VALIDATION_LAYERS && validationLayerSupported()) {
        logger->logDebug(tag, "Creating debug messenger");
        if (createDebugMessenger(instance, &debugCreateInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
            throw std::runtime_error("failed to set up debug messenger!");
        }
    }
}

Instance::~Instance() {
    logger->logDebug(tag, "Destroying debug messenger");
    destroyDebugMessenger(instance, debugMessenger, nullptr);

    logger->logDebug(tag, "Destroying VkInstance");
    vkDestroyInstance(instance, nullptr);
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

static VkResult createDebugMessenger(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
                                     const VkAllocationCallbacks *pAllocator,
                                     VkDebugUtilsMessengerEXT *pDebugMessenger) {
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance,"vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr) {
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    } else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

static void destroyDebugMessenger(VkInstance instance,VkDebugUtilsMessengerEXT debugMessenger,
                                  const VkAllocationCallbacks *pAllocator) {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance,"vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
        func(instance, debugMessenger, pAllocator);
    }
}

static VkBool32 debugMessengerCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData, void *pUserData) {
    const char* typeStr;
    switch (messageType) {
        case VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT:
            typeStr = "general";
            break;
        case VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT:
            typeStr = "validation";
            break;
        default:
            typeStr = "performance";
    }
    auto logger = Logger::getInstance();
    const std::string tag = "Vulkan";
    switch (messageSeverity) {
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
            logger->logDebug(tag, "%s:\n%s", typeStr, pCallbackData->pMessage);
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
            logger->logInfo(tag, "%s:\n%s", typeStr, pCallbackData->pMessage);
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
            logger->logWarning(tag, "%s:\n%s", typeStr, pCallbackData->pMessage);
            break;
        default:
            logger->logError(tag, "%s:\n%s", typeStr, pCallbackData->pMessage);
    }
    return VK_FALSE;
}
