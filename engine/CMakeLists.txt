
add_library(bogus
        Application.h
        Application.cpp
        Window.h
        Window.cpp
        Logger.h
        Logger.cpp
        Instance.h
        Instance.cpp
        )

find_package(Vulkan REQUIRED)
target_link_libraries(bogus Vulkan::Vulkan)

find_package(glfw3 REQUIRED)
target_link_libraries(bogus glfw glm)

target_include_directories(bogus PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
