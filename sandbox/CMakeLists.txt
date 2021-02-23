
add_executable(sandbox
        main.cpp
        SandboxApp.cpp
        SandboxApp.h)

target_link_libraries(sandbox LINK_PUBLIC bogus)
