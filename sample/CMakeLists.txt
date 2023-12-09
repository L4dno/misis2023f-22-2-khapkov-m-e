# CMakeList.txt : CMake project for sample, include source and define
# project specific logic here.
#

# Add source to this project's executable.
#add_executable (simple_texturing "plain_rectangle.cpp")
#add_executable (simple_texturing "simple_transition.cpp")
add_executable (simple_texturing "complex_transition.cpp")
#add_executable (sample "glfw_compability.cpp")

#if (CMAKE_VERSION VERSION_GREATER 3.12)
#  set_property(TARGET sample PROPERTY CXX_STANDARD 20)
#endif()

target_link_libraries(simple_texturing PRIVATE raylib)
#target_link_libraries(sample PRIVATE glfw)
#target_include_directories(sample "resources")

# TODO: Add tests and install targets if needed.
