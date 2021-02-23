//
// Created by larsewi on 20.08.2020.
//

#include <cstring>
#include <stdexcept>

#include "Instance.h"
#include "Logger.h"
#include "DebugMessenger.h"

namespace Bogus {
    Instance::Instance(Window* window) :
            m_pHandle(nullptr), m_pDebugMessenger(nullptr),
            m_validationLayers({"VK_LAYER_KHRONOS_validation"}) {
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        auto extensions = Window::getRequiredExtensions();

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
        if (ENABLE_VALIDATION_LAYERS && validationLayerSupported()) {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

            createInfo.enabledLayerCount = static_cast<uint32_t>(m_validationLayers.size());
            createInfo.ppEnabledLayerNames = m_validationLayers.data();

            DebugMessenger::populateCreateInfo(debugCreateInfo);
            createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
        } else {
            createInfo.enabledLayerCount = 0;
            createInfo.pNext = nullptr;
        }
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        //LOG_DEBUG("Creating Vk Instance");
        if (vkCreateInstance(&createInfo, nullptr, &m_pHandle) != VK_SUCCESS) {
            throw std::runtime_error("failed to create instance!");
        }

        if(ENABLE_VALIDATION_LAYERS && validationLayerSupported()) {
            //LOG_DEBUG("Creating debug messenger");
            if (DebugMessenger::Create(m_pHandle, &debugCreateInfo, nullptr, &m_pDebugMessenger) != VK_SUCCESS)
                throw std::runtime_error("failed to set up debug messenger!");
        }
    }

    Instance::~Instance() {
        //LOG_INFO("Destroying debug messenger");
        DebugMessenger::Destroy(m_pHandle, m_pDebugMessenger, nullptr);

        //LOG_INFO("Destroying instance");
        vkDestroyInstance(m_pHandle, nullptr);
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


}

