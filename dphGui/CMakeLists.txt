cmake_minimum_required(VERSION 3.11.0)

# Set project name
set(dphGui_PROJECT dphGui)
project(${dphGui_PROJECT})
set(dphGui_PROJECT ${dphGui_PROJECT} PARENT_SCOPE)

# Set MOC Q_OBJECTS classes automatically
set(CMAKE_AUTOMOC ON)

# Set RCC .qrc files automatically
set(CMAKE_AUTORCC ON)

# Find necessary Qt packages
find_package(Qt5 COMPONENTS Core Gui Widgets CONFIG REQUIRED)

# Set source files to build
set(H_FILES src/mainwindow.h
			src/logwidget.h
			src/dinnerscenemanager.h
			src/settings.h)

set(CPP_FILES	src/mainwindow.cpp
				src/main.cpp
				src/logwidget.cpp
				src/dinnerscenemanager.cpp)

set(QRC_FILES	src/resources.qrc)

# Set source group for .qrc files
source_group("Resource Files" FILES ${QRC_FILES})

# Set name of source group for generated files
#set(AUTOGEN_SOURCE_GROUP "Generated Files")
#source_group(${AUTOGEN_SOURCE_GROUP})

# Set include directories
include_directories("src" ${COMMON_INCLUDE_DIRECTORY})

# Set output directories
get_filename_component(CMAKE_BINARY_DIR_PATH ${CMAKE_BINARY_DIR} ABSOLUTE)
set(dph_OUTPUT_FOLDER "${CMAKE_BINARY_DIR_PATH}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dph_OUTPUT_FOLDER})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${dph_OUTPUT_FOLDER})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${dph_OUTPUT_FOLDER})

# Set build target
add_executable(${dphGui_PROJECT} WIN32 ${H_FILES} ${CPP_FILES} ${QRC_FILES})

# Set dependencies to link
target_link_libraries(${dphGui_PROJECT} ${dphCore_PROJECT} Qt5::Core Qt5::Gui Qt5::Widgets)

# Copy qt .dll's to .exe file
add_custom_command(TARGET ${dphGui_PROJECT} COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core>
																						$<TARGET_FILE:Qt5::Gui>
																						$<TARGET_FILE:Qt5::Widgets>
																						$<TARGET_FILE_DIR:${dphGui_PROJECT}>)