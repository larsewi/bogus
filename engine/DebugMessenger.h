//
// Created by larsewi on 31.08.2020.
//

#ifndef BOGUS_DEBUG_MESSENGER_H
#define BOGUS_DEBUG_MESSENGER_H

#include "Instance.h"
#include "vulkan/vulkan.h"

#ifdef NDEBUG
#define ENABLE_VALIDATION_LAYERS false
#else
#define ENABLE_VALIDATION_LAYERS true
#endif


namespace Bogus {

    class DebugMessenger {
    public:
        static VkResult create(VkInstance instance,
                               const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
                               const VkAllocationCallbacks* pAllocator,
                               VkDebugUtilsMessengerEXT* pDebugMessenger);

        static void destroy(VkInstance instance,
                            VkDebugUtilsMessengerEXT debugMessenger,
                            const VkAllocationCallbacks* pAllocator);

        static void populateCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    };
}

#endif //BOGUS_DEBUG_MESSENGER_H
