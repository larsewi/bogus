
add_library(bogus
        application.hpp
        application.cpp
        window.hpp
        window.cpp
        logger.hpp
        logger.cpp
        instance.hpp
        instance.cpp
        )

find_package(Vulkan REQUIRED)
target_link_libraries(bogus Vulkan::Vulkan)

find_package(glfw3 REQUIRED)
target_link_libraries(bogus glfw glm)

target_include_directories(bogus PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
