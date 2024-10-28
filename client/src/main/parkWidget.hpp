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

    QPushButton* parkBtn;


public:
    parkWidget(QWidget* parent = nullptr);
    ~parkWidget();
    
    void setCurrPSlotID(int ID, const QString& status = "");
};