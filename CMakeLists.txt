cmake_minimum_required(VERSION 3.20)

project(khapkov-m-e-22-2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_TOOLCHAIN_FILE "C:/src/vcpkg/scripts/buildsystems/vcpkg.cmake")

add_subdirectory(prj.codeforces)
add_subdirectory(prj.cw)

find_package(glfw3 CONFIG REQUIRED)


#DCMAKE_TOOLCHAIN_FILE=C:/src/vcpkg/scripts/buildsystems/vcpkg.cmake