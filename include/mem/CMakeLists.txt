# dir: root/include/mem
# file: CMakeLists.txt


# Add the header files to the library
set(HDR_FILES "defs" "mem" "_fast")
foreach(HDR_FILE ${HDR_FILES})

   target_sources(
      ${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/${HDR_FILE}.h"
   )

endforeach()

# Install rules for the header files
install(FILES ${HEADER_FILES} DESTINATION "include/mem")