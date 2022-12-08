# Minimum CMAKE version that supports C++ 20
cmake_minimum_required(VERSION 3.12)

# ----------------------------------------------------------------
# Use C++ 20
# ----------------------------------------------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

# ----------------------------------------------------------------
# Create Project
# ----------------------------------------------------------------
if(WIN32)
    project(BasicImageManipulator LANGUAGES CXX)
elseif(UNIX)
    project(BasicImageManipulator)
endif()

# Add configurations
# set(CMAKE_CONFIGURATION_TYPES "Release;RelWithDebInfo" CACHE STRING "" FORCE)
set(CMAKE_CONFIGURATION_TYPES "Release;Debug" CACHE STRING "" FORCE)

# ----------------------------------------------------------------
# Include Qt
# ----------------------------------------------------------------
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH $ENV{QTDIR}) # Points to the variable name in "Environment Variables"

find_package(Qt6Core REQUIRED)
find_package(Qt6Widgets REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Gui)

# ----------------------------------------------------------------
# Include Project Files
# ----------------------------------------------------------------
set(UI_DIR "${CMAKE_SOURCE_DIR}/ui") # UI directory
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include") # Headers directory
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src") # C++ directory
set(THEME_DIR "${CMAKE_SOURCE_DIR}/theme") # Theme directory

include_directories(${UI_DIR})
include_directories(${INCLUDE_DIR})
include_directories(${SOURCE_DIR})

file(GLOB_RECURSE SOURCES
    "${UI_DIR}/*.ui"
    "${UI_DIR}/*.qrc"
    "${INCLUDE_DIR}/*.h"
    "${SOURCE_DIR}/*.cpp"
    "${THEME_DIR}/*.qss"
)

# ----------------------------------------------------------------
# Setup Executable
# ----------------------------------------------------------------
# Enable debug logging on RELWITHDEBINFO configuration
# set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS
#     $<$<CONFIG:RELWITHDEBINFO>:QT_MESSAGELOGCONTENT>
# )

# Add UI directory to the AUTOUIC search paths
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_AUTOUIC_SEARCH_PATHS} ${UI_DIR})

# Add executable
if(WIN32)
    add_executable(BasicImageManipulator WIN32 ${SOURCES})
elseif(UNIX)
    add_executable(BasicImageManipulator ${SOURCES})
endif()

# Add the target includes for the project
target_include_directories(BasicImageManipulator PRIVATE ${UI_DIR})
target_include_directories(BasicImageManipulator PRIVATE ${INCLUDE_DIR})
target_include_directories(BasicImageManipulator PRIVATE ${SOURCE_DIR})
target_include_directories(BasicImageManipulator PRIVATE ${THEME_DIR})

# ----------------------------------------------------------------
# Libraries Linking
# ----------------------------------------------------------------
target_link_libraries(BasicImageManipulator Qt6::Widgets)
target_link_libraries(BasicImageManipulator Qt6::Gui)
