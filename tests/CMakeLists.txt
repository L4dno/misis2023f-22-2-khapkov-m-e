find_package(raylib REQUIRED)
find_package(doctest REQUIRED)

set (GEN_PREFIX "../prj.cw/mesh_generator/include/mesh_generator/")
set (LIB_PREFIX "../prj.cw/material_lib/")

add_executable(lib_test lib_tests.cpp ${LIB_PREFIX}material.cpp ${LIB_PREFIX}include/material_lib/material.hpp)

add_executable (gen_test "${GEN_PREFIX}point.hpp" "${GEN_PREFIX}/../../point.cpp" 
             /   "${GEN_PREFIX}/../../triangle.cpp" "${GEN_PREFIX}triangle.hpp"
             /   "${GEN_PREFIX}/../../hexagon.cpp" "${GEN_PREFIX}hexagon.hpp" 
             /   "${GEN_PREFIX}grid.hpp" "${GEN_PREFIX}/../../grid.cpp"
                / "gen_test.cpp")

target_link_libraries(lib_test PUBLIC raylib doctest::doctest)
target_link_libraries(gen_test PUBLIC raylib doctest::doctest)