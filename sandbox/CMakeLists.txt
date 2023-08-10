
add_executable(sandbox
        main.cpp
        sandbox.cpp
        sandbox.hpp)

target_link_libraries(sandbox LINK_PUBLIC bogus)

set_property(TARGET sandbox PROPERTY CXX_STANDARD 23)
