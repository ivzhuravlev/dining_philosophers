cmake_minimum_required(VERSION 3.11.0)

project(dining_philosophers)

set(CMAKE_PREFIX_PATH "C:/Qt/5.11.2/msvc2015/lib/cmake" "C:/Install/Catch2/lib/cmake")

add_subdirectory(dphCore)
add_subdirectory(dphGui)