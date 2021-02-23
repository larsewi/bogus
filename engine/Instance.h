//
// Created by larsewi on 20.08.2020.
//

#ifndef BOGUS_INSTANCE_H
#define BOGUS_INSTANCE_H

#include <vector>
#include <vulkan/vulkan.h>

#include "Window.h"
#include "DebugMessenger.h"

namespace Bogus {
    class Instance {
    public:
        explicit Instance(Window* window);
        ~Instance();

        inline VkInstance getHandle() { return m_pHandle; }

    private:
        VkInstance m_pHandle;
        VkDebugUtilsMessengerEXT m_pDebugMessenger;

        const std::vector<const char*> m_validationLayers;

        bool validationLayerSupported();
    };
}

#endif //BOGUS_INSTANCE_H
