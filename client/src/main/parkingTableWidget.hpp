#pragma once

#include <QTableWidget>
#include <QHeaderView>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDateTime>

#include "../auth/errorDialog.hpp"

#include <iostream>

class parkingTableWidget : public QTableWidget {
    Q_OBJECT

public:
    parkingTableWidget(QWidget* parent = nullptr);
    ~parkingTableWidget();

    void updateTable(const QJsonObject& parkings);

};
