//
// Created by larsewi on 20.08.2020.
//

#ifndef ACRYLIC_INSTANCE_H
#define ACRYLIC_INSTANCE_H

#include <vector>
#include <vulkan/vulkan.h>

#include "Window.h"
#include "DebugMessenger.h"

class Instance {
public:
    explicit Instance(Window* window);
    ~Instance();

private:
    VkInstance m_pVkInstance;
    DebugMessenger* m_pDebugMessenger;

    const std::vector<const char*> m_validationLayers;

    bool validationLayerSupported();
};


#endif //ACRYLIC_INSTANCE_H
