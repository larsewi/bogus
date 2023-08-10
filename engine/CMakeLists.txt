
add_library(bogus
        application.hpp
        application.cpp
        )

find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

target_link_libraries(bogus Vulkan::Vulkan glfw glm::glm)

target_include_directories(bogus PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_property(TARGET bogus PROPERTY CXX_STANDARD 23)
