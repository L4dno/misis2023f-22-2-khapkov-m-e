add_executable(generator "generator.cpp"
    "include/mesh_generator/grid.hpp" "grid.cpp"
    "include/mesh_generator/hexagon.hpp" "hexagon.cpp"
    "include/mesh_generator/point.hpp" "point.cpp"
    "include/mesh_generator/triangle.hpp" "triangle.cpp"
)
set_property(TARGET generator PROPERTY CXX_STANDARD 20)

target_link_libraries(generator PUBLIC raylib)
install(TARGETS generator DESTINATION bin)