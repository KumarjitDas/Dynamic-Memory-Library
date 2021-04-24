set(SUBDIRECTORIES "dynmem" "common" "utility")

foreach(VAR ${SUBDIRECTORIES})
    add_subdirectory(${VAR})
endforeach()
