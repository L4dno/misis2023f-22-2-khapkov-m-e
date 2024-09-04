cmake_minimum_required(VERSION 3.20)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

set (CMAKE_VERBOSE_MAKEFILE True)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED True)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set (CMAKE_RUNTIME_OUTPUT_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin.dbg)
set (CMAKE_RUNTIME_OUTPUT_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin.rel)
set (CMAKE_RUNTIME_OUTPUT_RELWITHDEBINFO ${CMAKE_CURRENT_SOURCE_DIR}/bin.relwithdbg)

project(khapkov-m-e-22-2)

#add_subdirectory(prj.cw)
#add_subdirectory(prj.codeforces)
add_subdirectory(tests)
add_subdirectory(sample)

