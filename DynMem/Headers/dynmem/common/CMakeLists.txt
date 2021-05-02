set(
   SOURCE_FILES
   "${CMAKE_CURRENT_SOURCE_DIR}/defines.h"
   "${CMAKE_CURRENT_SOURCE_DIR}/standard_includes.h"
   "${CMAKE_CURRENT_SOURCE_DIR}/types.h"
)
set(RELATIVE_PATH "include/dynmem/common")

if(SOURCE_FILES)
   target_sources("${PROJECT_NAME}" PRIVATE ${SOURCE_FILES})
   install(FILES ${SOURCE_FILES} DESTINATION ${RELATIVE_PATH})
endif()
