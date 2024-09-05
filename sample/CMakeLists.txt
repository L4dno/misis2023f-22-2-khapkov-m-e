find_package(raylib REQUIRED)

add_executable(ter "game/main.cpp" "game/rlFPCamera.cpp" "game/rlFPCamera.h" game/rlights.h "map_drawer/main.cpp")
add_executable(gen_map "map_drawer/main.cpp")
target_link_libraries(ter raylib)
target_link_libraries(gen_map raylib)