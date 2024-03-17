find_package(raylib REQUIRED)
find_package(doctest REQUIRED)

set (GEN_PREFIX "../prj.cw/mesh_generator/include/mesh_generator/")

#add_executable(render_test)

add_executable (gen_test "${GEN_PREFIX}point.hpp" "${GEN_PREFIX}/../../point.cpp" 
             /   "${GEN_PREFIX}/../../triangle.cpp" "${GEN_PREFIX}triangle.hpp"
             /   "${GEN_PREFIX}/../../hexagon.cpp" "${GEN_PREFIX}hexagon.hpp" 
             /   "${GEN_PREFIX}grid.hpp" "${GEN_PREFIX}/../../grid.cpp"
                / "gen_test.cpp")

#target_link_libraries(render_test PUBLIC material_lib raylib doctest)
target_link_libraries(gen_test PUBLIC raylib)