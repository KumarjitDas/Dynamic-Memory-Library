# dir: root/config
# file: CMakeLists.txt

# Set the input and output config file names
set(CONFIG_FILE "${PROJECT_NAME}Config.h")
set(BIN_CONFIG_FILE "${CMAKE_CURRENT_BINARY_DIR}/${CONFIG_FILE}")


# Configure the config file
configure_file("${CONFIG_FILE}.in" "${CONFIG_FILE}")


# Add the configured file to the target
target_sources(${PROJECT_NAME} PRIVATE ${BIN_CONFIG_FILE})


# Install rules for the config file
install(FILES ${BIN_CONFIG_FILE} DESTINATION "include")