cmake_minimum_required(VERSION 3.12)
project(ImageContainerTester LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_PREFIX_PATH $ENV{QTDIR}) # Points to the variable name in "Environment Variables"

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/../include")

if(NOT DEFINED INSTALL_TEST_DIRS)
    set(INSTALL_TEST_DIRS "ImageContainerTester")
endif()

set(INSTALL_TEST_DIR "${INSTALL_TEST_DIRS}/ImageContainerTester")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Test Widgets)

include_directories(
    ${INCLUDE_DIR}
)

qt_add_executable(ImageContainerTester
    main.cpp
    ImageContainerTester.h
    ImageContainerTester.cpp
    Resource.qrc
    ../include/ImageContainer.h
    ../src/ImageContainer.cpp
)

set_target_properties(ImageContainerTester PROPERTIES
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(ImageContainerTester PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Test
    Qt::Widgets
)

target_include_directories(ImageContainerTester PRIVATE
    ${INCLUDE_DIR}
)

install(TARGETS ImageContainerTester
    RUNTIME DESTINATION "${INSTALL_TEST_DIR}"
    BUNDLE DESTINATION "${INSTALL_TEST_DIR}"
    LIBRARY DESTINATION "${INSTALL_TEST_DIR}"
)
