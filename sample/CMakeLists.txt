find_package(raylib REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glad REQUIRED)

add_executable(ray "shader.cpp")
add_executable(gla "learn_triangle.cpp")
#add_executable(sample "triangle.cpp")


target_link_libraries(ray PUBLIC raylib)
target_link_libraries(gla PUBLIC glfw)
target_link_libraries(gla PUBLIC glad::glad)
