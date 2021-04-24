set(SUBDIRECTORIES "dynmem" "utility")

foreach(VAR ${SUBDIRECTORIES})
    add_subdirectory(${VAR})
endforeach()
