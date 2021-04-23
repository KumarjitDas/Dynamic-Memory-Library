set(SUBDIRECTORIES "dynmem")

foreach(VAR ${SUBDIRECTORIES})
    add_subdirectory(${VAR})
endforeach()
