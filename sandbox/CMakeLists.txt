
add_executable(sandbox
        main.cpp
        sandbox_app.cpp
        sandbox_app.hpp)

target_link_libraries(sandbox LINK_PUBLIC bogus)
