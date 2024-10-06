
add_executable (main main.cpp renderer.cpp renderer.hpp /
					rlFPCamera.cpp rlFPCamera.hpp)


target_link_libraries(main PRIVATE raylib)


set(DOXYGEN_RECURSIVE YES)
set(DOXYGEN_EXCLUDE_PATTERNS "*/_deps/*")
set(DOXYGEN_GENERATE_RTF YES)
set(DOXYGEN_OUTPUT_LANGUAGE "Russian")
set(DOXYGEN_GENERATE_HTML NO)

doxygen_add_docs(
  doxygen
  ${PROJECT_SOURCE_DIR}
)

set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.doxygen)

add_custom_target(doc_doxygen ALL
  COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Generating API documentation with Doxygen"
  VERBATIM )

install(TARGETS main DESTINATION bin)
#install(FILES renderer.hpp DESTINATION include)
install(DIRECTORY resources DESTINATION .)  
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/rtf DESTINATION .)