add_executable (generator drawer.cpp)
target_link_libraries(generator PUBLIC raylib)

install(TARGETS generator)