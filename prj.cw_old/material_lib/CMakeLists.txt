add_library(material_lib "material.cpp" "include/material_lib/material.hpp")
set_property(TARGET material_lib PROPERTY CXX_STANDARD 20)

target_include_directories(material_lib PUBLIC
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
$<INSTALL_INTERFACE:include>
)

target_link_libraries(material_lib PUBLIC raylib)
install(TARGETS material_lib)
