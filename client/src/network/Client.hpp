#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QString>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QEventLoop>

class Client : public QObject {
    Q_OBJECT

private:
    QString host_ip;
    unsigned short port;
    QTcpSocket socket;

public:
    Client(const QString& host_ip, unsigned short port, QObject* parent = nullptr);
    ~Client();

    bool connectToServer();
    void disconnectFromServer();

    QString sendRequest(const QString& jsonRequest);
    QString registrationRequest(
        const QString& email,
        const QString& password,
        const QString& lPlate
    );


private slots:
    void onConnected();
    void onReadyRead();
    void onErrorOccurred(QAbstractSocket::SocketError socketError);

signals:
    void responseReceived(const QString& response);
};
