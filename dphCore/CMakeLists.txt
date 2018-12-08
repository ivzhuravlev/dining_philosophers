cmake_minimum_required(VERSION 3.11.0)

# Set project name
set(dphCore_PROJECT dphCore)
project(${dphCore_PROJECT})

# Set project name to the parent scope
set(dphCore_PROJECT ${dphCore_PROJECT} PARENT_SCOPE)

#message("Current source dir " ${CMAKE_CURRENT_SOURCE_DIR})
#message("Bin dir " ${CMAKE_BINARY_DIR})
#message("Autogen dir " ${AUTOGEN_BUILD_DIR})

set(CMAKE_AUTOMOC ON)

# Find necessary Qt packages
find_package(Qt5Core CONFIG REQUIRED)

# Set source files to build
set(H_FILES "${COMMON_INCLUDE_DIRECTORY}/${PROJECT_NAME}/dinner.h"
			"${COMMON_INCLUDE_DIRECTORY}/${PROJECT_NAME}/status.h"
			"${COMMON_INCLUDE_DIRECTORY}/${PROJECT_NAME}/philparameters.h"
			"${COMMON_INCLUDE_DIRECTORY}/${PROJECT_NAME}/philosopher.h")
			
set(CPP_FILES "src/dinner.cpp"
			  "src/philosopher.cpp")

# Set include directories
include_directories("src" ${COMMON_INCLUDE_DIRECTORY})

# Set output directories
get_filename_component(CMAKE_BINARY_DIR_PATH ${CMAKE_BINARY_DIR} ABSOLUTE)
set(dph_OUTPUT_FOLDER "${CMAKE_BINARY_DIR_PATH}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dph_OUTPUT_FOLDER})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${dph_OUTPUT_FOLDER})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${dph_OUTPUT_FOLDER})

# Set build target
add_library(${PROJECT_NAME} STATIC ${H_FILES} ${CPP_FILES})

# Set dependencies to link
target_link_libraries(${PROJECT_NAME} Qt5::Core)

# Set unit test directory
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/test")