set(
   SOURCE_FILES
   "${CMAKE_CURRENT_SOURCE_DIR}/utility.c"
   "${CMAKE_CURRENT_SOURCE_DIR}/allocate.c"
   "${CMAKE_CURRENT_SOURCE_DIR}/set-get.c"
)
set(RELATIVE_PATH "src/dynmem/utility")

if(SOURCE_FILES)
   target_sources("${PROJECT_NAME}" PRIVATE ${SOURCE_FILES})
   install(FILES ${SOURCE_FILES} DESTINATION ${RELATIVE_PATH})
endif()
