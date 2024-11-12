#include <QApplication>
#include <QLabel>
#include <QWidget>
#include <QJsonObject>
#include <iostream>

#include "auth/startWidget.hpp"
#include "network/Client.hpp"
#include "main/parkingTableWidget.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    Client client("127.0.0.1", 3469);
    client.connectToServer();

    startWidget w(client);
    w.show();

    return app.exec();
}
