//
// Created by larsewi on 20.08.2020.
//

#ifndef BOGUS_INSTANCE_HPP
#define BOGUS_INSTANCE_HPP

#include <vector>
#include <vulkan/vulkan.h>

#include "window.hpp"
#include "logger.hpp"

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

#endif // BOGUS_INSTANCE_HPP