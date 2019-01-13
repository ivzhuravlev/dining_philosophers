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
find_package(Qt5 COMPONENTS Core Gui Widgets LinguistTools REQUIRED)

# Set source files to build
set(H_FILES src/mainwindow.h
			src/logwidget.h
			src/dinnerscenemanager.h
			src/settings.h
			src/settingsserializer.h
			src/settingsdialog.h
			src/dinnersettingswidget.h
			src/scenesettingswidget.h
			src/visualsettingswidget.h)

set(CPP_FILES	src/mainwindow.cpp
				src/main.cpp
				src/logwidget.cpp
				src/dinnerscenemanager.cpp
				src/settingsserializer.cpp
				src/settingsdialog.cpp
				src/dinnersettingswidget.cpp
				src/scenesettingswidget.cpp
				src/visualsettingswidget.cpp)

# Set Qt resources files
set(QRC_FILES	src/resources.qrc)

# Set Qt Linguist translation files
set(TS_FILES	src/translations/english.ts
				src/translations/russian.ts)
				
# Set source group for .qrc files
source_group("Resource Files" FILES ${QRC_FILES})

# Set name of source group for generated files
source_group("Generated Files" ${AUTOGEN_SOURCE_GROUP})

# Create .qm files from .ts files
qt5_add_translation(QM_FILES ${TS_FILES})
#qt5_create_translation(QM_FILES ${CPP_FILES} ${TS_FILES})

# Set source group for .ts files
source_group("Translation Files" FILES ${TS_FILES})
source_group("Translation Files\\Compiled" FILES ${QM_FILES})

# Set include directories
include_directories("src" ${COMMON_INCLUDE_DIRECTORY})

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# Set build target
add_executable(${dphGui_PROJECT} WIN32 ${H_FILES} ${CPP_FILES} ${QRC_FILES} ${TS_FILES} ${QM_FILES})

# Set executable name
set_target_properties(${dphGui_PROJECT} PROPERTIES OUTPUT_NAME "dining_philosophers")

# Set dependencies to link
target_link_libraries(${dphGui_PROJECT} ${dphCore_PROJECT} Qt5::Core Qt5::Gui Qt5::Widgets)

# List of Qt target files
set(QT_TARGET_FILES $<TARGET_FILE:Qt5::Core>
					$<TARGET_FILE:Qt5::Gui>
					$<TARGET_FILE:Qt5::Widgets>)

# Copy qt .dll's to .exe file
add_custom_command(TARGET ${dphGui_PROJECT} COMMAND ${CMAKE_COMMAND} -E copy_if_different	${QT_TARGET_FILES}
																							$<TARGET_FILE_DIR:${dphGui_PROJECT}>)

# Copy translation files .qm to .exe file
add_custom_command(TARGET ${dphGui_PROJECT} COMMAND ${CMAKE_COMMAND} -E copy_if_different 
${CMAKE_CURRENT_BINARY_DIR}/english.qm $<TARGET_FILE_DIR:${dphGui_PROJECT}>/translations/english.qm)

add_custom_command(TARGET ${dphGui_PROJECT} COMMAND ${CMAKE_COMMAND} -E copy_if_different 
${CMAKE_CURRENT_BINARY_DIR}/russian.qm $<TARGET_FILE_DIR:${dphGui_PROJECT}>/translations/russian.qm)

# Install binaries
install(TARGETS ${dphGui_PROJECT} CONFIGURATIONS Release RUNTIME DESTINATION .)

# Install Qt's dlls
install(FILES ${QT_TARGET_FILES} DESTINATION .)

# Install translation files
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/english.qm ${CMAKE_CURRENT_BINARY_DIR}/russian.qm DESTINATION translations)
