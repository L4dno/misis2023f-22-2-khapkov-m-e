add_executable (generator drawer.cpp)
target_link_libraries(generator PRIVATE raylib)

install(TARGETS generator)