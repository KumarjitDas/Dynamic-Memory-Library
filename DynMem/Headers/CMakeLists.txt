set(SUBDIRECTORIES "dynmem" "common")

foreach(VAR ${SUBDIRECTORIES})
    add_subdirectory(${VAR})
endforeach()
