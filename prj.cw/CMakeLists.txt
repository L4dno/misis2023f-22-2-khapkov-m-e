add_subdirectory("material_lib")
add_subdirectory("map_drawer")

add_executable(test_app "main.cpp")


target_link_libraries(test_app PUBLIC  doctest::doctest material_lib)

set(DOXYGEN_RECURSIVE YES)
set(DOXYGEN_EXCLUDE_PATTERNS "*/_deps/*")
set(DOXYGEN_EXCLUDE "material_lib/include/camera/rlFPCamera.h" "material_lib/rlFPCamera.cpp")
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