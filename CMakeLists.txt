cmake_minimum_required(VERSION 3.11.0)

project(dining_philosophers)

get_filename_component(CMAKE_SOURCE_DIR_PATH ${CMAKE_SOURCE_DIR} ABSOLUTE)
set(COMMON_INCLUDE_DIRECTORY "${CMAKE_SOURCE_DIR_PATH}/include")

add_subdirectory(dphCore)
add_subdirectory(dphGui)

set_property(DIRECTORY dphGui PROPERTY VS_STARTUP_PROJECT dphGui)
