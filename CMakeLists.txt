cmake_minimum_required(VERSION 3.20)

project(khapkov-m-e-22-2)

set(CMAKE_CXX_STANDARD 20)

find_package(doctest REQUIRED)
#find_package(glfw3 CONFIG REQUIRED)
find_package(raylib REQUIRED)
#find_path(EARCUT_HPP_INCLUDE_DIRS "mapbox/earcut.hpp")
    

#add_subdirectory(prj.codeforces)
add_subdirectory(prj.cw)
#add_subdirectory(sample)
