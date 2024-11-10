#pragma once

#include <QWidget>
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

#include "pSlot.hpp"

class parkWidget : public QWidget {
Q_OBJECT
protected:
    QBoxLayout* layout;
    
    int currPSlotID;

    QLabel* idLabel;
    QLabel* status;




public:
    QPushButton* parkBtn;
    QPushButton* endParkBtn;
    
    parkWidget(QWidget* parent = nullptr);
    ~parkWidget();
    
    int getCurrPSlotID(void) const { return currPSlotID; }

    void setCurrPSlotID(int ID, const QString& status = "");
};