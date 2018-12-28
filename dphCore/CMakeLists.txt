cmake_minimum_required(VERSION 3.11.0)

# Set project name
set(dphCore_PROJECT dphCore)
project(${dphCore_PROJECT})

# Set project name to the parent scope
set(dphCore_PROJECT ${dphCore_PROJECT} PARENT_SCOPE)

set(CMAKE_AUTOMOC ON)

# Find necessary Qt packages
find_package(Qt5 COMPONENTS Core REQUIRED)

# Set source files to build
set(H_EXT_FILES "${COMMON_INCLUDE_DIRECTORY}/${dphCore_PROJECT}/dinner.h"
				"${COMMON_INCLUDE_DIRECTORY}/${dphCore_PROJECT}/dinnersettings.h"
				"${COMMON_INCLUDE_DIRECTORY}/${dphCore_PROJECT}/status.h"
				"${COMMON_INCLUDE_DIRECTORY}/${dphCore_PROJECT}/philevent.h"
				"${COMMON_INCLUDE_DIRECTORY}/${dphCore_PROJECT}/dphCore_global.h")
			
set(H_FILES "src/philparameters.h"
			"src/philosopher.h")
			
set(CPP_FILES "src/dinner.cpp"
			  "src/philosopher.cpp")

# Set name of source group for generated files
source_group("Generated Files" ${AUTOGEN_SOURCE_GROUP})

# Set include current directory
set (CMAKE_INCLUDE_CURRENT_DIR ON)

# Set additional definitions
add_definitions(-DDPHCORE_LIB)

# Set include directories
include_directories("src" ${COMMON_INCLUDE_DIRECTORY})

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# Set build target
add_library(${dphCore_PROJECT} ${H_FILES} ${H_EXT_FILES} ${CPP_FILES})

# Set dependencies to link
target_link_libraries(${dphCore_PROJECT} Qt5::Core)

# Specify public headers to istall target
set_target_properties(${dphCore_PROJECT} PROPERTIES PUBLIC_HEADER "${H_EXT_FILES}")

#include to use CMAKE_INSTALL_<DIR> variables
include(GNUInstallDirs)

# Set install target for release config
install(TARGETS ${dphCore_PROJECT} CONFIGURATIONS Release
									RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
									LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
									ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
									PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
