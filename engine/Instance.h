//
// Created by larsewi on 20.08.2020.
//

#ifndef BOGUS_INSTANCE_H
#define BOGUS_INSTANCE_H

#include <vector>
#include <vulkan/vulkan.h>

#include "Window.h"
#include "Logger.h"

namespace Bogus {
    class Instance {
    public:
        Instance();

        ~Instance();

    private:
        Logger *logger;
        const std::string tag = "Instance";

        VkInstance instance;
        VkDebugUtilsMessengerEXT debugUtilsMessenger;
        VkPhysicalDevice physicalDevice;

        const std::vector<const char *> validationLayers{
                "VK_LAYER_KHRONOS_validation"
        };

        bool validationLayerSupported();
    };
}

#endif //BOGUS_INSTANCE_H
