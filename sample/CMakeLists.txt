find_package(raylib REQUIRED)

add_executable(sample "triangle.cpp")


target_link_libraries(sample PUBLIC raylib)
