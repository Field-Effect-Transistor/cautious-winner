cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

project(parking_system VERSION 0.1.0)

find_package(Qt5 REQUIRED COMPONENTS Widgets Network)
cmake_policy(SET CMP0167 NEW)
find_package(Boost REQUIRED COMPONENTS system json)
find_package(SQLite3 REQUIRED)

# Опції для вибору збірки клієнта та сервера
option(BUILD_CLIENT "Build client application" ON)
option(BUILD_SERVER "Build server application" ON)

# Підключення підкаталогів, якщо опція збірки увімкнена
if(BUILD_CLIENT)
    add_subdirectory(client)
endif()

if(BUILD_SERVER)
    add_subdirectory(server)
endif()

# Загальні налаштування інсталяції
install(DIRECTORY include/ DESTINATION include/${PROJECT_NAME})


configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY
)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    COMMENT "Uninstalling the project..."
)
