add_executable (test test.cpp)
target_link_libraries(test PRIVATE glfw)
target_link_libraries(test PRIVATE doctest::doctest)
target_link_libraries(test PRIVATE bgfx::bx bgfx::bgfx bgfx::bimg bgfx::bimg_decode)