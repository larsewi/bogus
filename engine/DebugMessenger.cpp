//
// Created by larsewi on 31.08.2020.
//

#include "DebugMessenger.h"
#include "Logger.h"

#if LOGGER_LOG_ERROR
#define VK_LOG_ERROR(...) \
logger::log_f("VALIDATION LAYER", "\b\b\b\b\b\b", 0, "ERROR", LOGGER_ERROR_COLOR, stderr, __VA_ARGS__)
#else
#define VK_LOG_ERROR(...)
#endif

#if LOGGER_LOG_WARNING
#define VK_LOG_WARNING(...) \
logger::log_f("VALIDATION LAYER", "\b\b\b\b\b\b", 0, "WARNING", LOGGER_WARNING_COLOR, stdout, __VA_ARGS__)
#else
#define VK_LOG_WARNING(...)
#endif

#if LOGGER_LOG_INFO
#define VK_LOG_INFO(...) \
logger::log_f("VALIDATION LAYER", "\b\b\b\b\b\b", 0, "INFO", LOGGER_INFO_COLOR, stdout, __VA_ARGS__)
#else
#define VK_LOG_INFO(...)
#endif

#if LOGGER_LOG_DEBUG
#define VK_LOG_DEBUG(...) \
logger::log_f("VALIDATION LAYER", "\b\b\b\b\b\b", 0, "DEBUG", LOGGER_DEBUG_COLOR, stdout, __VA_ARGS__)
#else
#define VK_LOG_DEBUG(...)
#endif


VkResult DebugMessenger::Create(
        VkInstance instance,
        const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
        const VkAllocationCallbacks *pAllocator,
        VkDebugUtilsMessengerEXT *pDebugMessenger) {
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr) {
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    } else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

void DebugMessenger::Destroy(
        VkInstance instance,
        VkDebugUtilsMessengerEXT debugMessenger,
        const VkAllocationCallbacks *pAllocator) {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
        func(instance, debugMessenger, pAllocator);
    }
}

VkBool32 callback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
        void *pUserData) {

    const char* typeStr;
    switch (messageType) {
        case VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT:
            typeStr = "general"; break;
        case VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT:
            typeStr = "validation"; break;
        default:
            typeStr = "performance";
    }

    switch (messageSeverity) {
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
            VK_LOG_DEBUG("%s:\n%s", typeStr, pCallbackData->pMessage); break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
            VK_LOG_INFO("%s:\n%s", typeStr, pCallbackData->pMessage); break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
            VK_LOG_WARNING("%s:\n%s", typeStr, pCallbackData->pMessage); break;
        default:
            VK_LOG_ERROR("%s:\n%s", typeStr, pCallbackData->pMessage);
    }

    return VK_FALSE;
}

void DebugMessenger::populateCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) {
    createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
            | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
            | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
            | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pfnUserCallback = callback;
}
