#pragma once

#include <QWidget>
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDateEdit>

class bookWidget : public QWidget {
    Q_OBJECT
protected:
    QBoxLayout* layout;

    int currPSlotID;

    QLabel* idLabel;
    QLabel* statusLabel;
    
    QLabel* startDateLabel;
    QLabel* endDateLabel;

public:
    QDateEdit* startDateEdit;
    QDateEdit* endDateEdit;

    QPushButton* bookBtn;

    bookWidget(QWidget* parent = nullptr);
    ~bookWidget();
    
    void setCurrPSlotID(int ID, const QString& status = "");
    int getCurrPSlotID(void) const { return currPSlotID; }
};
