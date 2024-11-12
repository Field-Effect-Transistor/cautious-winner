# Додайте всі джерела клієнта
set(CLIENT_SOURCES    
    src/main.cpp
    src/auth/startWidget.cpp
    src/auth/authWidget.cpp
    src/auth/loginWidget.cpp
    src/auth/guestWidget.cpp
    src/auth/regWidget.cpp   
    ../include/validation.cpp
    src/auth/errorDialog.cpp
    src/main/pSlot.cpp
    src/main/mapWidget.cpp
    src/main/mainWindow.cpp
    src/main/parkWidget.cpp
    src/main/bookWidget.cpp
    src/network/Client.cpp
    src/main/parkingTableWidget.cpp
    src/main/slotStatusTable.cpp
)

# Ресурси
set(CLIENT_RESOURCES
    resources/resources.qrc
    themes/themes.qrc
)

# Створення виконуваного файлу клієнта
add_executable(${PROJECT_NAME}_client ${CLIENT_SOURCES} ${CLIENT_RESOURCES})

# Лінкування бібліотек
target_link_libraries(${PROJECT_NAME}_client Qt5::Widgets Qt5::Network)

# Інсталяція клієнта (опціонально)
install(TARGETS ${PROJECT_NAME}_client DESTINATION bin)
install(DIRECTORY resources/icons DESTINATION share/${PROJECT_NAME}/client/resources)
install(DIRECTORY resources/pictures DESTINATION share/${PROJECT_NAME}/client/resources)
install(FILES themes/dark_theme.qss themes/hacker_theme.qss themes/light_theme.qss DESTINATION share/${PROJECT_NAME}/client/themes)
