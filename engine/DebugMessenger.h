//
// Created by larsewi on 31.08.2020.
//

#ifndef ACRYLIC_DEBUGMESSENGER_H
#define ACRYLIC_DEBUGMESSENGER_H

#include "Instance.h"
#include "vulkan/vulkan.h"

#ifdef NDEBUG
#define ENABLE_VALIDATION_LAYERS false
#else
#define ENABLE_VALIDATION_LAYERS true
#endif


namespace DebugMessenger {

    VkResult Create(
            VkInstance instance,
            const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
            const VkAllocationCallbacks* pAllocator,
            VkDebugUtilsMessengerEXT* pDebugMessenger);

    void Destroy(
            VkInstance instance,
            VkDebugUtilsMessengerEXT debugMessenger,
            const VkAllocationCallbacks* pAllocator);

    void populateCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
};


#endif //ACRYLIC_DEBUGMESSENGER_H
