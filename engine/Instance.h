//
// Created by larsewi on 20.08.2020.
//

#ifndef BOGUS_INSTANCE_H
#define BOGUS_INSTANCE_H

#include <vector>
#include <vulkan/vulkan.h>

#include "Window.h"
#include "DebugMessenger.h"
#include "Logger.h"

namespace Bogus {
    class Instance {
    public:
        explicit Instance();
        ~Instance();

        inline VkInstance getHandle() { return handle; }

    private:
        VkInstance handle;
        VkDebugUtilsMessengerEXT debugMessenger;

        Logger *logger;

        const std::vector<const char*> validationLayers;

        bool validationLayerSupported();
    };
}

#endif //BOGUS_INSTANCE_H
