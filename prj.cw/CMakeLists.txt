find_package(raylib REQUIRED)
find_package(Doxygen)

add_executable(test_app "test_app.cpp")

add_subdirectory("material_lib")
target_link_libraries(test_app PRIVATE material_lib raylib)

set(DOXYGEN_RECURSIVE YES)
set(DOXYGEN_EXCLUDE_PATTERNS "*/_deps/*")
set(DOXYGEN_GENERATE_RTF YES)
set(DOXYGEN_OUTPUT_LANGUAGE "Russian")
set(DOXYGEN_GENERATE_HTML NO)

doxygen_add_docs(
    doxygen
    ${PROJECT_SOURCE_DIR}
)

set (DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.doxygen)

add_custom_target(doc_doxygen ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating docs with Doxygen"
    VERBATIM
)

install(TARGETS test_app DESTINATION bin)
install(DIRECTORY resources DESTINATION .)
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/rtf DESTINATION .)