#!/bin/sh

# build.sh
# ^^^^^^^^
# This script is used to build the project.
# It does the following in sequence:
# 1.a) Cleans the build directory if it exists.
#   b) Creates a new build directory if it does not exist.
# 2. Changes the working directory to the build directory.
# 3. Runs cmake to generate the build files.
# 4. Runs make to build the project.
# 5. Deletes the build artifacts.
# 6. Hardlinks the header file to the build directory.
#
# If any of the steps fail, the script will print an error message and exit.
# The script will print a success message if the build is successful.
# The script is intended to be run from the root of the project directory.
# The script is intended to be run on a Unix-like system with a bash shell, GNU Make, and CMake.
# For other systems, manual execution of the substituted commands is required.
# See LICENSE file for license information.

# * Constants *

# Info log strings
readonly CLEAN_STR="Cleaning build directory..."
readonly BUILD_DIR_STR="Creating build directory..."
readonly CMAKE_STR="Running CMake..."
readonly BUILD_STR="Building..."
readonly COPY_STR="Hardlinking header to build directory..."
readonly DEL_ART_STR="Deleting build artifacts..."

# Query log string
readonly ASK_INSTALL="Install the binary?"

# Success log string
readonly BUILD_COMPLETE="Build complete!"

# Error log strings
readonly CLEAN_FAIL="Failed to clean build directory!"
readonly BUILD_DIR_FAIL="Failed to create build directory!"
readonly CMAKE_FAIL="Failed to run CMake!"
readonly BUILD_FAIL="Failed to build using the default build tool (usually GNU Make)!"
readonly COPY_FAIL="Failed to hardlink header to build directory!"
readonly INSTALL_FAIL="Failed to install the binary!"
readonly DEL_ART_FAIL="Failed to delete build artifacts!"

# * Procedure *
print_info() { printf "\x1b[0m[\x1b[34m*\x1b[0m] \x1b[34m%s\x1b[0m
" "$1"; }
print_query() { printf "\x1b[0m\x1b[33m%s\x1b[0m [\x1b[32m%s\x1b[0m/\x1b[31m%s\x1b[0m]: " "$1" "$2" "$3"; }
print_success() { printf "\x1b[0m[\x1b[32;1m+\x1b[0m] \x1b[32;1m%s\x1b[0m
" "$1"; }
print_error() { printf "\x1b[0m[\x1b[37;41;1m%%\x1b[0m] \x1b[37;41;1m%s\x1b[0m
" "$1"; }

# Clean build directory if anything is present within it
print_info "$CLEAN_STR"
rm -rf ./build/* || 
	{ print_error "$CLEAN_FAIL" && exit 1; }
# Create build directory if it does not exista and change working directory to it
print_info "$BUILD_DIR_STR"
{ mkdir -p build && cd ./build; } || 
	{ print_error "$BUILD_DIR_FAIL" && exit 1; }
# Run cmake to generate build files
print_info "$CMAKE_STR"
cmake .. || 
	{ print_error "$CMAKE_FAIL" && exit 1; }
# Run make to build the project
print_info "$BUILD_STR"
cmake --build . --config Release ||
	{ print_error "$BUILD_FAIL" && exit 1; }
# Ask user if they want to install the binary to their system
print_query "$ASK_INSTALL" "y" "N"
read -r QUERY_INSTALL
case $QUERY_INSTALL in
	y|Y) sudo cmake --install . || 
		{ print_error "$INSTALL_FAIL" && exit 1; } ;;
	*) ;;
esac
# Delete build artifacts
print_info "$DEL_ART_STR"
rm -rf ./CMakeFiles ./CMakeCache.txt ./Makefile ./cmake_install.cmake ./build.ninja ./.ninja* || 
	{ print_error "$DEL_ART_FAIL" && exit 1; }
# Print build success message
print_success "$BUILD_COMPLETE"
exit 0
