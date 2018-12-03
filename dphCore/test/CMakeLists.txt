cmake_minimum_required(VERSION 3.11.0)

project(dphCore.Tests)

find_package(Catch2 REQUIRED)

set(TESTS_CPP test_main.cpp
			 philparameters_Tests.cpp)
			 
add_executable(${PROJECT_NAME} ${TESTS_CPP})
target_link_libraries(${PROJECT_NAME} Catch2::Catch2)

include(Catch)
catch_discover_tests(${PROJECT_NAME})