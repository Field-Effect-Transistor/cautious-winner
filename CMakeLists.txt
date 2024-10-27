cmake_minimum_required(VERSION 3.30.0)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

project(parking_system VERSION 0.1.0)

find_package(Qt5 REQUIRED COMPONENTS Widgets)

set(CLIENT_SOURCES
    client/src/main.cpp
    client/src/auth/startWidget.cpp
    client/src/auth/authWidget.cpp
    client/src/auth/loginWidget.cpp
    client/src/auth/guestWidget.cpp
    client/src/auth/regWidget.cpp   
    "include/validation.cpp"
    client/src/auth/errorDialog.cpp
    client/src/main/pSlot.cpp
    client/src/main/mapWidget.cpp
    client/src/main/mainWindow.cpp
)
set(CLIENT_HEADERS
    client/src/auth/startWidget.hpp
    client/src/auth/authWidget.hpp
    client/src/auth/loginWidget.hpp
    client/src/auth/guestWidget.hpp
    client/src/auth/regWidget.hpp
    "include/validation.hpp"
    client/src/auth/errorDialog.hpp
    client/src/main/pSlot.hpp
    client/src/main/mapWidget.hpp
    client/src/main/mainWindow.hpp
)

add_executable(${PROJECT_NAME}_client ${CLIENT_SOURCES} ${CLIENT_HEADERS})

# Лінкувати з Qt5 бібліотеками
target_link_libraries(${PROJECT_NAME}_client Qt5::Widgets)