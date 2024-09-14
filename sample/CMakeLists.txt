find_package(raylib REQUIRED)

add_executable(ter "game/rlFPCamera.cpp" "game/rlFPCamera.h" game/rlights.h "game/main.cpp")
add_executable(gen_map "map_drawer/drawer.cpp")
target_link_libraries(ter raylib)
target_link_libraries(gen_map raylib)