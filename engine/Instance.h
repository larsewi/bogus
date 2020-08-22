//
// Created by larsewi on 20.08.2020.
//

#ifndef ACRYLIC_INSTANCE_H
#define ACRYLIC_INSTANCE_H

#ifdef NDEBUG
#define ENABLE_VALIDATION_LAYERS false
#else
#define ENABLE_VALIDATION_LAYERS true
#endif

#include <vector>
#include <vulkan/vulkan.h>

#include "Window.h"

class Instance {
public:
    explicit Instance(Window* window);
    ~Instance();

private:
    VkInstance m_pVkInstance;
    VkDebugUtilsMessengerEXT m_pDebugMessenger;

    const std::vector<const char*> m_validationLayers;

    bool validationLayerSupported();
};

#endif //ACRYLIC_INSTANCE_H
