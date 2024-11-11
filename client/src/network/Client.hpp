#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QString>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QEventLoop>
#include <QThread>

#include <iostream>

class Client : public QObject {
    Q_OBJECT

private:
    QString host_ip;
    unsigned short port;
    QTcpSocket socket;

public:
    int user_id;
    QString lPlate; 
    
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
    QString userLoginRequest(const QString& email, const QString& password);
    QString guestLoginRequest();
    QString getMap();
    QJsonObject bigDataTransfering(const QJsonObject& request);
    QJsonObject parkingRequest(int slot_id);
    QJsonObject bookingRequest(
        time_t startTime,
        time_t endTime,
        int slot_id
    );
    QJsonObject endParkingRequest(int slot_id);
    QString getParkingListRequest(int user_id, const QString& lPlate);

private slots:
    void onConnected();
    void onReadyRead();
    void onErrorOccurred(QAbstractSocket::SocketError socketError);

signals:
    void responseReceived(const QString& response);
};