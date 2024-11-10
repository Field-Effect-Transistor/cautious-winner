cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#set(CMAKE_BUILD_TYPE Debug)

project(parking_system VERSION 0.1.0)

find_package(Qt5 REQUIRED COMPONENTS Widgets Network)
cmake_policy(SET CMP0167 NEW)
find_package(Boost REQUIRED COMPONENTS system json)
find_package(SQLite3 REQUIRED)

option(BUILD_CLIENT "Build client application" ON)
option(BUILD_SERVER "Build server application" ON)

#CLIENT BUILD
if(BUILD_CLIENT)
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
        client/src/main/parkWidget.cpp
        client/src/main/bookWidget.cpp
        client/src/network/Client.cpp
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
        client/src/main/parkWidget.hpp
        client/src/main/bookWidget.hpp
        client/src/network/Client.hpp
    )

    set(CLIENT_RESOURCES
        client/resources/resources.qrc
        client/themes/themes.qrc
    )

    add_executable(${PROJECT_NAME}_client ${CLIENT_SOURCES} ${CLIENT_HEADERS} ${CLIENT_RESOURCES})
    target_link_libraries(${PROJECT_NAME}_client Qt5::Widgets Qt5::Network)
endif()

#SERVER BUILD
if(BUILD_SERVER)
    set(SERVER_SOURCES
        server/src/main.cpp
        server/src/database/Database.cpp
        server/src/models/User.cpp
        server/src/models/Parking.cpp
        server/src/models/Slot.cpp
        server/src/network/Server.cpp
    )

    set(SERVER_HEADERS
        server/src/database/Database.hpp
        server/src/models/User.hpp
        server/src/models/Parking.hpp
        server/src/models/Slot.hpp
        server/src/network/Server.hpp
    )

    set(SERVER_DATABASE
        server/database/init_db.sql
    )
    add_executable(${PROJECT_NAME}_server ${SERVER_SOURCES} ${SERVER_HEADERS})

    include_directories(${SQLite3_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME}_server Boost::system Boost::json ${SQLite3_LIBRARIES}) 
endif()