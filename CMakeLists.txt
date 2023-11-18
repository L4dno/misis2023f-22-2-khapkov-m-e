cmake_minimum_required(VERSION 3.20)

project(khapkov-m-e-22-2)

set(CMAKE_CXX_STANDARD 20)

find_package(doctest CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(bgfx CONFIG REQUIRED)

#add_subdirectory(prj.codeforces)
add_subdirectory(prj.cw)
