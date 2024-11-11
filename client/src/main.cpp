#include <QApplication>
#include <QLabel>
#include <QWidget>

#include "auth/startWidget.hpp"
#include "network/Client.hpp"
#include "main/parkingTableWidget.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    Client client("127.0.0.1", 3469);
    client.connectToServer();

    startWidget w(client);
    w.show();

    auto response = client.getParkingListRequest(3, "12312312");
    response = client.getParkingListRequest(3, "12312312");

    QJsonObject parkingList = client.bigDataTransfering(QJsonDocument::fromJson(response.toUtf8()).object());
    std::cout << QJsonDocument(parkingList).toJson(QJsonDocument::Indented).toStdString()    << std::endl;
    //std::cout << parkingList["data"].toString().toStdString() << std::endl;
//*/

    parkingTableWidget tableWidget;
    tableWidget.show();
    tableWidget.updateTable(parkingList);

    return app.exec();
}

//#include "main.moc"