add_executable (test "point.hpp" "point.cpp" "tests.cpp" 
             /   "triangle.cpp" "triangle.hpp"
             /   "hexagon.cpp" "hexagon.hpp" 
             /   "grid.hpp" "grid.cpp")
add_executable (show "point.hpp" "point.cpp" "main.cpp" 
             /   "triangle.cpp" "triangle.hpp"
             /   "hexagon.cpp" "hexagon.hpp" 
             /   "grid.hpp" "grid.cpp")

target_link_libraries(test PRIVATE doctest::doctest)
target_link_libraries(show PRIVATE raylib)