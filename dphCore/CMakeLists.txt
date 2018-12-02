cmake_minimum_required(VERSION 3.11.0)

project(dphCore)

#message("Current source dir " ${CMAKE_CURRENT_SOURCE_DIR})
#message("Bin dir " ${CMAKE_BINARY_DIR})
#message("Autogen dir " ${AUTOGEN_BUILD_DIR})

set(CMAKE_AUTOMOC ON)
#set(Qt5Core_DIR "C:/Qt/Qt5.11.2/msvc2015/lib/cmake/Qt5Core")
find_package(Qt5Core CONFIG REQUIRED)

set(H_FILES "src/dinner.h"
			"src/status.h"
			"src/philparameters.h"
			"src/philosopher.h")
			
set(CPP_FILES	"src/dinner.cpp"
				"src/philosopher.cpp")

include_directories("src")

add_library(${PROJECT_NAME} STATIC ${H_FILES} ${CPP_FILES})
target_link_libraries(${PROJECT_NAME} Qt5::Core)