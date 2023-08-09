
add_executable(sandbox
        main.cpp
        sandbox.cpp
        sandbox.hpp)

target_link_libraries(sandbox LINK_PUBLIC bogus)
