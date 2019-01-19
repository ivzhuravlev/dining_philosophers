cmake_minimum_required(VERSION 3.11.0)

project(dining_philosophers)

get_filename_component(CMAKE_SOURCE_DIR_PATH ${CMAKE_SOURCE_DIR} ABSOLUTE)
set(COMMON_INCLUDE_DIRECTORY "${CMAKE_SOURCE_DIR_PATH}/include")
set(dph_COMPONENT_NAME "DiningPhilosophers")

option(BUILD_SHARED_LIBS "Build shared library" OFF)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID STREQUAL GNU)
add_compile_options(-Wno-attributes)
endif()

add_subdirectory(dphCore)
add_subdirectory(dphGui)

set_property(DIRECTORY dphGui PROPERTY VS_STARTUP_PROJECT dphGui)

# Set general CPack properties
set(CPACK_PACKAGE_NAME "DiningPhilosophers")
set(CPACK_PACKAGE_VENDOR "IZhuravlev")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Dining Philosophers")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_INSTALL_DIRECTORY ${CPACK_PACKAGE_NAME})
set(CPACK_VERBATIM_VARIABLES YES)

# Enable package to .zip file
set(CPACK_GENERATOR ZIP)

# Enable IFW installer build
option(BUILD_IFW_INSTALLER OFF)

# Set IFW specific options
if(BUILD_IFW_INSTALLER)
	include (CPackIFW)
	set(QTIFW_DIR "C:/Qt/Tools/QtInstallerFramework/3.0/" CACHE PATH "Path to Qt Installer Framework")

	set(CPACK_IFW_ROOT ${QTIFW_DIR})
	set(CPACK_IFW_PRODUCT_URL "https://github.com/ivzhuravlev/dining_philosophers")
	set(CPACK_IFW_PACKAGE_TITLE "Dining Philosophers")
	set(CPACK_IFW_PACKAGE_ALLOW_SPACE_IN_PATH ON)
	set(CPACK_IFW_PACKAGE_ALLOW_NON_ASCII_CHARACTERS ON)
	set(CPACK_IFW_PACKAGE_WIZARD_STYLE Modern)
	set(CPACK_IFW_PACKAGE_CONTROL_SCRIPT "${CMAKE_SOURCE_DIR}/scripts/controlscript.qs")

	cpack_add_component(${dph_COMPONENT_NAME})
	cpack_ifw_configure_component(${dph_COMPONENT_NAME}
		FORCED_INSTALLATION
		DISPLAY_NAME ${CPACK_IFW_PACKAGE_TITLE}
		DESCRIPTION "Install component"
		VERSION 1.1.0
		RELEASE_DATE 2019-01-19
		SCRIPT "${CMAKE_SOURCE_DIR}/scripts/packagescript.qs"
	)

	list(APPEND CPACK_GENERATOR IFW)
endif()

include (CPack)
