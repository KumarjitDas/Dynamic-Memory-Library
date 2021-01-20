# dir: root/tests
# file: CMakeLists.txt


# Enable testing for all the tests in this directory
enable_testing()


# Add all the subdirectories of this directory
set(
   SUBDIRS
   "t01_MemLibVersion" "t02_AllocMem"
)
foreach(SUBDIR ${SUBDIRS})

   message(
      STATUS "${PROJECT_NAME} -- tests -- Adding tests for ${SUBDIR}"
   )
   add_subdirectory(${SUBDIR})

endforeach()