cmake_minimum_required(VERSION 3.11.0)

project(dining_philosophers)

set(Qt5_DIR "C:/Qt/5.11.2/msvc2015/lib/cmake/Qt5" CACHE PATH "Path to Qt5Config.cmake")
set(Catch2_DIR "C:/Install/Catch2/lib/cmake/Catch2" CACHE PATH "Path to Catch2Config.cmake")

get_filename_component(CMAKE_SOURCE_DIR_PATH ${CMAKE_SOURCE_DIR} ABSOLUTE)
set(COMMON_INCLUDE_DIRECTORY "${CMAKE_SOURCE_DIR_PATH}/include")

add_subdirectory(dphCore)
add_subdirectory(dphGui)

set_property(DIRECTORY dphGui PROPERTY VS_STARTUP_PROJECT dphGui)
