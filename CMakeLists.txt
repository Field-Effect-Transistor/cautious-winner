cmake_minimum_required(VERSION 3.30.0)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

project(parking-system VERSION 0.1.0)

find_package(Qt5 REQUIRED COMPONENTS Widgets)

include_directories(src)
set(SOURCES
    src/main.cpp
    src/startWidget.cpp
    src/authWidget.cpp
)
set(HEADERS
    src/startWidget.hpp
    src/authWidget.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Лінкувати з Qt5 бібліотеками
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)