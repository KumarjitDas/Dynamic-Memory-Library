set(
   SOURCE_FILES
   "${CMAKE_CURRENT_SOURCE_DIR}/allocate.c"
   "${CMAKE_CURRENT_SOURCE_DIR}/stack-queue.c"
   "${CMAKE_CURRENT_SOURCE_DIR}/set-get.c"
   "${CMAKE_CURRENT_SOURCE_DIR}/copy-insert.c"
)
set(RELATIVE_PATH "src/dynmem")

if(SOURCE_FILES)
   target_sources("${PROJECT_NAME}" PRIVATE ${SOURCE_FILES})
   install(FILES ${SOURCE_FILES} DESTINATION ${RELATIVE_PATH})
endif()

set(SUBDIRECTORIES "utility")

foreach(VAR ${SUBDIRECTORIES})
   add_subdirectory(${VAR})
endforeach()
