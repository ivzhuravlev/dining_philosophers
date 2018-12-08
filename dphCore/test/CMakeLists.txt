cmake_minimum_required(VERSION 3.11.0)

project(dphCore.Tests)

find_package(Catch2 REQUIRED)

set(TESTS_CPP test_main.cpp
			 philparameters.tests.cpp)
			 
# Set output directories
get_filename_component(CMAKE_CURRENT_BINARY_DIR_PATH ${CMAKE_CURRENT_BINARY_DIR} ABSOLUTE)
set(dph_OUTPUT_FOLDER "${CMAKE_BINARY_DIR_PATH}/bin-test")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dph_OUTPUT_FOLDER})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${dph_OUTPUT_FOLDER})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${dph_OUTPUT_FOLDER})

add_executable(${PROJECT_NAME} ${TESTS_CPP})
target_link_libraries(${PROJECT_NAME} Catch2::Catch2)

include(Catch)
catch_discover_tests(${PROJECT_NAME})