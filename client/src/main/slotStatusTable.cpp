#include "slotStatusTable.hpp"

slotStatusTable::slotStatusTable(QWidget* parent) : QTableWidget(parent) {
    setColumnCount(2);
    setRowCount(0);

    QStringList headers;
    headers << "Start" << "End";
    setHorizontalHeaderLabels(headers);

    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    verticalHeader()->setVisible(false);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void slotStatusTable::updateTable(const QJsonObject& slotInfo) {
    if (slotInfo["status"].toString() == "error") {
        errorDialog dialog(slotInfo["message"].toString(), this);
        dialog.exec();
        return;
    }

    clearContents();
    setRowCount(0);
    int rowCount = 0;


    QJsonArray parkings = slotInfo["parkings"].toArray();
    for(const QJsonValue& value : parkings) {
        QJsonObject info = value.toObject();

        insertRow(rowCount);            
        
        setItem(rowCount, 0, new QTableWidgetItem(
            QDateTime::fromSecsSinceEpoch(
                info["start_date"].toVariant().toLongLong()
            ).toString("yyyy-MM-dd")
        ));
        setItem(rowCount, 1, new QTableWidgetItem( info["end_date"].toString() == "0" ?
            QString("N/A") :
            QDateTime::fromSecsSinceEpoch(
                info["end_date"].toVariant().toLongLong()
            ).toString("yyyy-MM-dd")
        ));

        ++rowCount;
    }

}