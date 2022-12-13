# Minimum CMAKE version that supports C++ 20
cmake_minimum_required(VERSION 3.12)

# ----------------------------------------------------------------
# Create Project
# ----------------------------------------------------------------
project(BasicImageManipulator LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# ----------------------------------------------------------------
# Use C++ 20
# ----------------------------------------------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ----------------------------------------------------------------
# Include Qt
# ----------------------------------------------------------------
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH $ENV{QTDIR}) # Points to the variable name in "Environment Variables"

find_package(Qt6 REQUIRED
    COMPONENTS Core Gui Widgets
)

# ----------------------------------------------------------------
# Include Project Files
# ----------------------------------------------------------------
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include") # Headers directory
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src") # C++ directory
set(THEME_DIR "${CMAKE_SOURCE_DIR}/src/theme") # Theme directory
set(UI_DIR "${CMAKE_SOURCE_DIR}/src/ui") # UI directory
set(RESOURCES_DIR "${CMAKE_SOURCE_DIR}/src/resources") # Resources directory

include_directories(
    ${INCLUDE_DIR}
    ${SOURCE_DIR}
    ${THEME_DIR}
    ${UI_DIR}
    ${RESOURCES_DIR}
)

file(GLOB_RECURSE SOURCES
    "${INCLUDE_DIR}/*.h"
    "${SOURCE_DIR}/*.cpp"
    "${SOURCE_DIR}/*.qrc"
    "${THEME_DIR}/*.qss"
    "${UI_DIR}/*.ui"
    "${RESOURCES_DIR}/*.jpg"
    "${RESOURCES_DIR}/*.jpeg"
    "${RESOURCES_DIR}/*.png"
    "${RESOURCES_DIR}/*.bmp"
    "${RESOURCES_DIR}/*.svg"
)

# ----------------------------------------------------------------
# Setup Executable
# ----------------------------------------------------------------
# Add UI directory to the AUTOUIC search paths
# set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_AUTOUIC_SEARCH_PATHS} ${UI_DIR})

# Add executable
qt_add_executable(BasicImageManipulator WIN32 ${SOURCES})

# Libraries linking
target_link_libraries(BasicImageManipulator PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

# Add the target includes for the project
target_include_directories(BasicImageManipulator PRIVATE
    ${INCLUDE_DIR}
    ${SOURCE_DIR}
    ${THEME_DIR}
    ${UI_DIR}
)
