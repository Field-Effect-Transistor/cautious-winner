#pragma once

#include <QTableWidget>
#include <QHeaderView>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "../auth/errorDialog.hpp"

class slotStatusTable : public QTableWidget {
    Q_OBJECT
public:
    int currSlot = -1;
    slotStatusTable(QWidget* parent = nullptr);
    ~slotStatusTable() {};

    void updateTable(const QJsonObject& slotInfo);
};