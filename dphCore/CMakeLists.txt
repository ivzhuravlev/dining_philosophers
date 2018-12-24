cmake_minimum_required(VERSION 3.11.0)

# Set project name
set(dphCore_PROJECT dphCore)
project(${dphCore_PROJECT})

# Set project name to the parent scope
set(dphCore_PROJECT ${dphCore_PROJECT} PARENT_SCOPE)

set(CMAKE_AUTOMOC ON)

# Find necessary Qt packages
find_package(Qt5 COMPONENTS Core CONFIG REQUIRED)

# Set source files to build
set(H_FILES "${COMMON_INCLUDE_DIRECTORY}/${dphCore_PROJECT}/dinner.h"
			"${COMMON_INCLUDE_DIRECTORY}/${dphCore_PROJECT}/status.h"
			"${COMMON_INCLUDE_DIRECTORY}/${dphCore_PROJECT}/philparameters.h"
			"${COMMON_INCLUDE_DIRECTORY}/${dphCore_PROJECT}/philosopher.h"
			"${COMMON_INCLUDE_DIRECTORY}/${dphCore_PROJECT}/philevent.h"
			"${COMMON_INCLUDE_DIRECTORY}/${dphCore_PROJECT}/dinnersettings.h")
			
set(CPP_FILES "src/dinner.cpp"
			  "src/philosopher.cpp")

# Set name of source group for generated files
source_group("Generated Files" ${AUTOGEN_SOURCE_GROUP})

# Set include directories
include_directories("src" ${COMMON_INCLUDE_DIRECTORY})

# Set output directories
get_filename_component(CMAKE_BINARY_DIR_PATH ${CMAKE_BINARY_DIR} ABSOLUTE)
set(dph_OUTPUT_FOLDER "${CMAKE_BINARY_DIR_PATH}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dph_OUTPUT_FOLDER})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${dph_OUTPUT_FOLDER})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${dph_OUTPUT_FOLDER})

# Set build target
add_library(${dphCore_PROJECT} STATIC ${H_FILES} ${CPP_FILES})

# Set dependencies to link
target_link_libraries(${dphCore_PROJECT} Qt5::Core)

# Set unit test directory
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/test")