find_package(raylib REQUIRED)

add_executable(ter "game/main.cpp" "game/rlFPCamera.cpp" "game/rlFPCamera.h" game/rlights.h)

target_link_libraries(ter raylib)