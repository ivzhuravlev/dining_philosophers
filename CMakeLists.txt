cmake_minimum_required(VERSION 3.11.0)

project(dining_philosophers)

get_filename_component(CMAKE_SOURCE_DIR_PATH ${CMAKE_SOURCE_DIR} ABSOLUTE)
set(COMMON_INCLUDE_DIRECTORY "${CMAKE_SOURCE_DIR_PATH}/include")

option(BUILD_SHARED_LIBS "Build shared library" OFF)

add_subdirectory(dphCore)
add_subdirectory(dphGui)

set_property(DIRECTORY dphGui PROPERTY VS_STARTUP_PROJECT dphGui)

# Set CPack properties
set(QTIFW_DIR "C:/Qt/QtIFW-3.0.6" CACHE PATH "Path to Qt Installer Framework")

set(CPACK_PACKAGE_NAME "DiningPhilosophers")
set(CPACK_PACKAGE_VENDOR "IZhuravlev")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Dining Philosophers")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "1")
set(CPACK_PACKAGE_INSTALL_DIRECTORY ${CPACK_PACKAGE_NAME})
set(CPACK_VERBATIM_VARIABLES YES)

# Set IFW specific options
set(CPACK_IFW_ROOT ${QTIFW_DIR})
set(CPACK_IFW_PACKAGE_ALLOW_SPACE_IN_PATH ON)
set(CPACK_IFW_PACKAGE_ALLOW_NON_ASCII_CHARACTERS ON)
set(CPACK_IFW_PACKAGE_WIZARD_STYLE Modern)

set(CPACK_GENERATOR ZIP IFW)
include (CPack)
include (CPackIFW)
