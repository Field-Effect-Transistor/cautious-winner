# Додайте всі джерела сервера
set(SERVER_SOURCES
    src/main.cpp
    src/database/Database.cpp
    src/models/User.cpp
    src/models/Parking.cpp
    src/models/Slot.cpp
    src/network/Server.cpp
)

# SQL-файли бази даних
set(SERVER_DATABASE
    database/init_db.sql
)

# Створення виконуваного файлу сервера
add_executable(${PROJECT_NAME}_server ${SERVER_SOURCES})

# Підключення бібліотек
include_directories(${SQLite3_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}_server Boost::system Boost::json ${SQLite3_LIBRARIES})

# Інсталяція сервера (опціонально)
install(TARGETS ${PROJECT_NAME}_server DESTINATION bin)
install(FILES ${SERVER_DATABASE} DESTINATION share/${PROJECT_NAME}/server/database)
