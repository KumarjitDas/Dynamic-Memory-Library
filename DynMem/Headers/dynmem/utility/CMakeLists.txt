if(BUILD_SHARED_LIBS AND "${CMAKE_PROJECT_NAME}" STREQUAL "${PROJECT_NAME}")
   target_compile_definitions("${PROJECT_NAME}" PRIVATE DYNMEM_UTILITY_TEST)
endif()

set(
   SOURCE_FILES
   "${CMAKE_CURRENT_SOURCE_DIR}/defines.h"
   "${CMAKE_CURRENT_SOURCE_DIR}/utility.h"
   "${CMAKE_CURRENT_SOURCE_DIR}/allocate.h"
)
set(RELATIVE_PATH "include/dynmem/utility")

if(SOURCE_FILES)
   target_sources("${PROJECT_NAME}" PRIVATE ${SOURCE_FILES})
   install(FILES ${SOURCE_FILES} DESTINATION ${RELATIVE_PATH})
endif()
