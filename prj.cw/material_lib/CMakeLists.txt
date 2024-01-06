add_executable (test "mesh_generator.hpp" "mesh_generator.cpp" "test_cases.cpp")
add_executable (show "mesh_generator.hpp" "mesh_generator.cpp" "main.cpp")

target_link_libraries(test PRIVATE doctest::doctest)
target_link_libraries(show PRIVATE raylib)