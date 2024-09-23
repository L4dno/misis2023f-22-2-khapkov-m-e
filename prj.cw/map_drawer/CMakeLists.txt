add_executable (generator "include/mesh_generator/point.hpp" "point.cpp" 
             /   "triangle.cpp" "include/mesh_generator/triangle.hpp"
             /   "hexagon.cpp" "include/mesh_generator/hexagon.hpp" 
             /   "include/mesh_generator/grid.hpp" "grid.cpp"
                / "generator_deprecated.cpp")
target_link_libraries(generator PRIVATE raylib)