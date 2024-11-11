#include "parkingTableWidget.hpp"

parkingTableWidget::parkingTableWidget(QWidget* parent) : QTableWidget(parent) {
    setColumnCount(4);
    setRowCount(0);

    QStringList headers;
    headers << "Slot ID" << "Type" << "Satart date" << "End date";
    setHorizontalHeaderLabels(headers);

    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    verticalHeader()->setVisible(false);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
}

parkingTableWidget::~parkingTableWidget() {}

void parkingTableWidget::updateTable(const QJsonObject& parkings) {
    if (parkings["status"].toString() == "error") {
        errorDialog dialog(parkings["message"].toString(), this);
        dialog.exec();
        return;
    }

    QJsonObject data = parkings["data"].toObject();
    if (data["status"].toString() == "error") {
        errorDialog dialog(data["message"].toString(), this);
        dialog.exec();
        return;
    }

    clearContents();
    setRowCount(0);
    int rowCount = 0;

    QJsonArray lPlateParkings = QJsonDocument::fromJson(data["lPlateParkings"].toString().toUtf8()).array();
    //std::cout << QJsonDocument(data).toJson(QJsonDocument::Indented).toStdString() << std::endl;
    for (const QJsonValue& value : lPlateParkings) {
        if (value.isObject()) {
            QJsonObject parkingData = value.toObject();
            
            // Додаємо новий рядок
            insertRow(rowCount);
            
            // Вставляємо дані в рядок
            setItem(rowCount, 0, new QTableWidgetItem(parkingData["slot_id"].toString()));
            setItem(rowCount, 1, new QTableWidgetItem(
                parkingData["type"].toString() == "1" ? QString("Booking") : QString("Parking")
            ));
            setItem(rowCount, 2, new QTableWidgetItem(
                QDateTime::fromSecsSinceEpoch(
                    parkingData["start_date"].toVariant().toLongLong()
                ).toString("yyyy-MM-dd")
            ));
            setItem(rowCount, 3, new QTableWidgetItem( parkingData["end_date"].toString() == "0" ?
                QString("N/A") :
                QDateTime::fromSecsSinceEpoch(
                    parkingData["end_date"].toVariant().toLongLong()
                ).toString("yyyy-MM-dd")
            ));
            
            // Збільшуємо лічильник рядків
            ++rowCount;
        } else {
            errorDialog dialog(value.toString(), this);
            dialog.exec();
        }
    }

    if (data.contains("userParkings")) {
        QJsonArray userParkings = QJsonDocument::fromJson(data["userParkings"].toString().toUtf8()).array();
        //std::cout << QJsonDocument(data).toJson(QJsonDocument::Indented).toStdString() << std::endl;
        for (const QJsonValue& value : userParkings) {
            if (value.isObject()) {
                QJsonObject parkingData = value.toObject();
                
                // Додаємо новий рядок
                insertRow(rowCount);
                
                // Вставляємо дані в рядок
                setItem(rowCount, 0, new QTableWidgetItem(parkingData["slot_id"].toString()));
                setItem(rowCount, 1, new QTableWidgetItem(
                    parkingData["type"].toString() == "1" ? QString("Booking") : QString("Parking")
                ));
                setItem(rowCount, 2, new QTableWidgetItem(
                    QDateTime::fromSecsSinceEpoch(
                        parkingData["start_date"].toVariant().toLongLong()
                    ).toString("yyyy-MM-dd")
                ));
                setItem(rowCount, 3, new QTableWidgetItem( parkingData["end_date"].toString() == "0" ?
                    QString("N/A") :
                    QDateTime::fromSecsSinceEpoch(
                        parkingData["end_date"].toVariant().toLongLong()
                    ).toString("yyyy-MM-dd")
                ));
                
                // Збільшуємо лічильник рядків
                ++rowCount;
            } else {
                errorDialog dialog(value.toString(), this);
                dialog.exec();
            }
        }
    }
}
