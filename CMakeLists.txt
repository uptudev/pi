# See LICENSE file for license information.
cmake_minimum_required(VERSION 3.10)
project(
    pi
	VERSION 1.1.2
    DESCRIPTION "A project initializer for lazy people.")

# Add test executable
add_executable(
	${PROJECT_NAME}
	src/${PROJECT_NAME}.c)
target_include_directories(
	${PROJECT_NAME}
	PRIVATE include)
target_sources(
    ${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/libs/input_handler.c
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/libs/lang_scripts.c
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/libs/uptu_libs.c)

# Binary installation rules
install(
	TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
