set(
    SOURCE_FILES 
    "${CMAKE_CURRENT_SOURCE_DIR}/dynmem.c"
)
set(RELATIVE_PATH "src/dynmem")

if(SOURCE_FILES)
    target_sources("${PROJECT_NAME}" PRIVATE ${SOURCE_FILES})
    install(FILES ${SOURCE_FILES} DESTINATION ${RELATIVE_PATH})
endif()
