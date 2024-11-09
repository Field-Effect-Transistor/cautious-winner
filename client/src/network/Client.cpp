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