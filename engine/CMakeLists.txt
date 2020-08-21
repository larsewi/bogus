
add_library(acrylic Application.cpp Application.h Window.cpp Window.h Logger.h Instance.cpp Instance.h DebugMessenger.cpp DebugMessenger.h)

find_package(Vulkan REQUIRED)
target_link_libraries(acrylic Vulkan::Vulkan)

find_package(glfw3 REQUIRED)
target_link_libraries(acrylic glfw)

target_include_directories(acrylic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
