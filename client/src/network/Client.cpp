#include "Client.hpp"

Client::Client(const QString& host_ip, unsigned short port, QObject* parent)
    : QObject(parent), host_ip(host_ip), port(port) {

    connect(&socket, &QTcpSocket::connected, this, &Client::onConnected);
    connect(&socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
    connect(&socket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::errorOccurred), this, &Client::onErrorOccurred);
}

Client::~Client() {
    if (socket.state() == QAbstractSocket::ConnectedState) 
        disconnectFromServer();
}

bool Client::connectToServer() {
    socket.connectToHost(host_ip, port);

    if (socket.waitForConnected(3000)) {
        qDebug() << "Connected to server at " << host_ip << ":" << port;
        return true;
    } else {
        qDebug() << "Failed to connect to server: " << socket.errorString();
        return false;
    }
}

QString Client::sendRequest(const QString& jsonRequest) {
    if (socket.state() != QAbstractSocket::ConnectedState) {
        qDebug() << "Not connected to server.";
        return "Connection error";
    }

    QByteArray requestData = jsonRequest.toUtf8();
    socket.write(requestData);
    socket.flush();

    // Блокування тільки на короткий час, для отримання відповіді.
    QEventLoop loop;
    QString response;

    connect(this, &Client::responseReceived, &loop, [&](const QString& res) {
        response = res;
        loop.quit();
    });

    loop.exec();

    return response;
}

void Client::onConnected() {
    qDebug() << "Successfully connected to server.";
}

void Client::onReadyRead() {
    QByteArray response = socket.readAll();
    qDebug() << "Received response:" << response;
    emit responseReceived(QString::fromUtf8(response));
}

void Client::onErrorOccurred(QAbstractSocket::SocketError socketError) {
    qDebug() << "Error occurred:" << socket.errorString();
}

void Client::disconnectFromServer() {
    sendRequest("{\"command\":\"CLOSE_CONNECTION\"}");
    socket.close();
}

QString Client::registrationRequest(
    const QString& email,
    const QString& password,
    const QString& lPlate
) {
    QJsonObject jsonRequest;
    jsonRequest["command"] = "REGISTER_USER";
    jsonRequest["email"] = email;
    jsonRequest["password"] = password;
    jsonRequest["lPlate"] = lPlate;

    QString request = QJsonDocument(jsonRequest).toJson(QJsonDocument::Compact);
    return sendRequest(request);
}

QString Client::userLoginRequest(const QString& email, const QString& password) {
    QJsonObject jsonRequest;
    jsonRequest["command"] = "USER_LOGIN";
    jsonRequest["email"] = email;
    jsonRequest["password"] = password;

    QString request = QJsonDocument(jsonRequest).toJson(QJsonDocument::Compact);
    return sendRequest(request);
}

QString Client::guestLoginRequest() {
    QJsonObject jsonRequest;
    jsonRequest["command"] = "GUEST_LOGIN";

    QString request = QJsonDocument(jsonRequest).toJson(QJsonDocument::Compact);
    return sendRequest(request);
}

QString Client::getMap() {
    QJsonObject jsonRequest;
    jsonRequest["command"] = "GET_MAP";

    return sendRequest(QJsonDocument(jsonRequest).toJson(QJsonDocument::Compact));
}

QJsonObject Client::bigDataTransfering(const QJsonObject& request) {
    QJsonObject response;
    QString bigData;
    
    if (request["status"].toString() == "startBigDataTransfering") {
        if (request["command"].toString() == "GET_MAP") {
            do {
                response = QJsonDocument::fromJson(
                    sendRequest("{\"command\":\"BIG_DATA_TRANSFER\"}").toUtf8()
                ).object();

                bigData = bigData + response["data"].toString();

            } while (response["status"].toString() != "endBigDataTransfering");
            
            QJsonArray mapArray = QJsonDocument::fromJson(bigData.toUtf8()).array();
            response["status"] = "success";
            response["data"] = mapArray;
            return response;
        } else if (request["command"].toString() == "GET_PARKING_LIST") {
            do {
                response = QJsonDocument::fromJson(
                    sendRequest("{\"command\":\"BIG_DATA_TRANSFER\"}").toUtf8()
                ).object();

                bigData = bigData + response["data"].toString();

            } while (response["status"].toString() != "endBigDataTransfering");
            QJsonObject list = QJsonDocument::fromJson(bigData.toUtf8()).object();
            response["status"] = "success";
            response["data"] = list;
            return response;
        }
    }
    
    QJsonArray mapArray = QJsonDocument::fromJson(bigData.toUtf8()).array();
    response["status"] = "error";
    response["message"] = "unsupported command";
    //std::cout << response["data"].toString().toStdString() << std::endl;
    return response;
}

QJsonObject Client::parkingRequest(int slot_id) {
    QJsonObject jsonRequest;
    jsonRequest["command"] = "PARKING";
    jsonRequest["slot_id"] = slot_id;
    jsonRequest["user_id"] = user_id;
    jsonRequest["lPlate"] = lPlate;

    return QJsonDocument::fromJson(
        sendRequest(QJsonDocument(jsonRequest).toJson(QJsonDocument::Compact)).toUtf8()
    ).object();
}

QJsonObject Client::endParkingRequest(int slot_id) {
    QJsonObject jsonRequest;
    jsonRequest["command"] = "END_PARKING";
    jsonRequest["slot_id"] = slot_id;
    jsonRequest["user_id"] = user_id;
    jsonRequest["lPlate"] = lPlate;

    return QJsonDocument::fromJson(
        sendRequest(QJsonDocument(jsonRequest).toJson(QJsonDocument::Compact)).toUtf8()
    ).object();
}   

QJsonObject Client::bookingRequest(time_t startTime, time_t endTime, int slot_id) { 
    QJsonObject jsonRequest;
    jsonRequest["command"] = "BOOKING";
    jsonRequest["startTime"] = static_cast<int>(startTime);
    jsonRequest["endTime"] = static_cast<int>(endTime);
    jsonRequest["slot_id"] = slot_id;
    jsonRequest["user_id"] = user_id;
    jsonRequest["lPlate"] = lPlate;

    return QJsonDocument::fromJson(
        sendRequest(QJsonDocument(jsonRequest).toJson(QJsonDocument::Compact)).toUtf8()
    ).object();
}

QString Client::getParkingListRequest(int user_id, const QString& lPlate) {
    QJsonObject jsonRequest;
    jsonRequest["command"] = "GET_PARKING_LIST";
    jsonRequest["user_id"] = user_id;
    jsonRequest["lPlate"] = lPlate;

    return sendRequest(QJsonDocument(jsonRequest).toJson(QJsonDocument::Compact));

}