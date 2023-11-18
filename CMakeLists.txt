cmake_minimum_required(VERSION 3.20)

project(khapkov-m-e-22-2)

set(CMAKE_CXX_STANDARD 20)
#set(VCPKG_TARGET_TRIPLET x64-windows-static)
#set(CMAKE_TOOLCHAIN_FILE "C:/src/vcpkg/scripts/buildsystems/vcpkg.cmake")


find_package(doctest CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(bgfx CONFIG REQUIRED)

#add_subdirectory(prj.codeforces)
add_subdirectory(prj.cw)





# this is heuristically generated, and may not be correct
#
  # note: 1 additional targets are not displayed.
  #target_link_libraries(main PRIVATE bgfx::bx bgfx::bgfx bgfx::bimg bgfx::bimg_decode)

#DCMAKE_TOOLCHAIN_FILE=C:/src/vcpkg/scripts/buildsystems/vcpkg.cmake

