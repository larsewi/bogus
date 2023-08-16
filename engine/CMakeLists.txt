
add_library(bogus
        application.cpp
        window.cpp
        instance.cpp
        debug_messenger.cpp
        physical_device.cpp
        logical_device.cpp
        )

find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

target_link_libraries(bogus PRIVATE
        Vulkan::Vulkan
        glfw
        glm::glm
        pthread
        spdlog
        fmt
        X11
        Xxf86vm
        Xrandr
        Xi)

target_include_directories(bogus PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_property(TARGET bogus PROPERTY CXX_STANDARD 23)
