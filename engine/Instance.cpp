//
// Created by larsewi on 20.08.2020.
//

#include <cstring>
#include <stdexcept>

#include "Instance.h"
#include "Logger.h"


Instance::Instance(Window* window) :
        m_pVkInstance(nullptr), m_pDebugMessenger(nullptr),
        m_validationLayers({"VK_LAYER_KHRONOS_validation"}) {
#ifndef NDEBUG
    if (!validationLayerSupported())
        throw std::runtime_error("Validation layer(s) requested, but not supported");
#endif
}

Instance::~Instance() {

}

bool Instance::validationLayerSupported() {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const char* layerName : m_validationLayers) {
        bool layerFound = false;

        for (const auto& layerProperties : availableLayers) {
            if (strcmp(layerName, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }
        if (!layerFound)
            return false;
    }
    return true;
}
